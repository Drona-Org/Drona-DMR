#include <iostream>
#include <algorithm>  // for find
#include <string>
#include <fstream>
#include <assert.h>


// for tokenizing strings
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

#include <boost/tuple/tuple_io.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <math.h>

#define FLT_COST_MULTIPLIER   1e6  

using namespace std;

#include "quad_handler.h"


/********************************************************/
 const YAML::Node& operator>> (const YAML::Node& yaml_node, QuadVoxel &voxel)
 {
    yaml_node[0] >> voxel.get<0>();
    yaml_node[1] >> voxel.get<1>();
    yaml_node[2] >> voxel.get<2>();
    return yaml_node;
 }



 QuadVoxel operator+ (const QuadVoxel &lhs, const QuadVoxel &rhs)
 {
    QuadVoxel result;
    result.get<X>() = lhs.get<X>() + rhs.get<X>();
    result.get<Y>() = lhs.get<Y>() + rhs.get<Y>();
    result.get<Z>() = lhs.get<Z>() + rhs.get<Z>();
    return result;

 }

/**************************** QuadStateCell **************************/


//function prototypes
 QuadStateCell::QuadStateCell(std::vector<int>::iterator first, std::vector<int>::iterator last)
 {
    m_data.assign(first, last);
    assert(m_data.size() == NUM_DOF+1);
 }




 QuadStateCell::QuadStateCell(int* first, int* last)
 {
    m_data.assign(first, last);
    assert(m_data.size() == NUM_DOF+1);
 }




 void QuadStateCell::print(ostream &output) const
 {
    output << "(" << m_data.at(0);
    //output << m_data.at(0);
        for (size_t dim = 1; dim < m_data.size(); ++dim)
            output << ", " << m_data.at(dim);
        output << ")";
}


bool QuadStateCell::operator== (const QuadStateCell &other) const
{
    assert(m_data.size() == NUM_DOF+1);
    assert(other.m_data.size() == NUM_DOF+1);
    for (size_t dim = 0; dim < NUM_DOF+1; ++dim)
        if (m_data.at(dim) != other.m_data.at(dim))
            return false;
    return true;
}


size_t QuadStateCell::Hash::operator()(const QuadStateCell &val) const
{
    size_t key = 0;
    for (size_t dim = 0; dim < NUM_DOF+1; ++dim) {
        size_t key_dim = (size_t) val.m_data.at(dim);
        key_dim ^= (key_dim << 4);
        key_dim += (key_dim >> 9);
        key ^= key_dim;
    }
    return key;
}


QuadVoxel QuadStateCell::operator+ (const QuadVoxel &other)
{
    QuadVoxel result(m_data.at(X) + other.get<X>(),     \
        m_data.at(Y) + other.get<Y>(),      \
        m_data.at(Z) + other.get<Z>());
    return result;
}



const YAML::Node& operator>> (const YAML::Node& yaml_node, QuadStateCell &state_cell)
{
    for (size_t dim = 0; dim < NUM_DOF+1; ++dim)
        yaml_node[dim] >> state_cell.m_data.at(dim);
    return yaml_node;
}

/**************************** QuadAction **************************/

std::ostream& operator<< (std::ostream &output, const QuadAction &action)
    {
        output << "#" << action.index << ": " << action.q_f << ", " << action.cost << ", [";
            BOOST_FOREACH(const QuadVoxel &voxel, action.swath) {
                cout << voxel << " ";
            }
            cout << "]";
return output;
}

std::ostream& operator<< (std::ostream &output, const QuadAction::QuadParam &coeff)
{
    output << "[[" << coeff.x_coeffs.at(0);
        for (size_t dim = 1; dim < coeff.x_coeffs.size(); ++dim)
            output << ", " << coeff.x_coeffs.at(dim);
        output << "], [" << coeff.y_coeffs.at(0);
        for (size_t dim = 1; dim < coeff.y_coeffs.size(); ++dim)
            output << ", " << coeff.y_coeffs.at(dim);
        output << "], [" << coeff.z_coeffs.at(0);
        for (size_t dim = 1; dim < coeff.y_coeffs.size(); ++dim)
            output << ", " << coeff.z_coeffs.at(dim);
        output << "], " << coeff.time << "]";
output << endl;
return output;
}

const YAML::Node& operator>> (const YAML::Node& yaml_node, QuadAction::QuadParam &coeff)
{
    string buf; // string buffer
    const YAML::Node& node_x = yaml_node[0];
    for (size_t dim = 0; dim < node_x.size(); ++dim) {
        node_x[dim] >> buf;
        coeff.x_coeffs.push_back(atof(buf.c_str()));
    }
    const YAML::Node& node_y = yaml_node[1];
    for (size_t dim = 0; dim < node_y.size(); ++dim) {
        node_y[dim] >> buf;
        coeff.y_coeffs.push_back(atof(buf.c_str()));
    }
    const YAML::Node& node_z = yaml_node[2];
    for (size_t dim = 0; dim < node_z.size(); ++dim) {
        node_z[dim] >> buf;
        coeff.z_coeffs.push_back(atof(buf.c_str()));
    }
    yaml_node[3] >> buf;
    coeff.time = atof(buf.c_str());
    return yaml_node;
}

const YAML::Node& operator>> (const YAML::Node& yaml_node, QuadAction &action)
{
    string buf; // string buffer

    // set cost
    yaml_node["cost"] >> buf;
    action.cost = (uint) (atof(buf.c_str()) * FLT_COST_MULTIPLIER); // convert float to integer

    // set q_f
    const YAML::Node &node_qf(yaml_node["q_f"]);
    for (size_t dim = 0; dim < node_qf.size(); ++dim) {
        node_qf[dim] >> buf;
        action.q_f.get(dim) = atoi(buf.c_str());
    }

    // set params (coeffs and assignment)
    const YAML::Node &node_param(yaml_node["params"]);
    QuadAction::QuadParam coeff;
    node_param >> coeff;
    action.coeffs = coeff;


    // set swath
    const YAML::Node &node_swath(yaml_node["swath"]);
    // for each voxel in the swath
    for (YAML::Iterator swath_it = node_swath.begin(); swath_it != node_swath.end(); ++swath_it) {
        QuadVoxel cur_voxel;
        (*swath_it)[0] >> cur_voxel.get<0>();
        (*swath_it)[1] >> cur_voxel.get<1>();
        (*swath_it)[2] >> cur_voxel.get<2>();
        action.swath.push_back(cur_voxel);
    } // end for each voxel in the swath

    return yaml_node;
}

QuadAction::QuadParam QuadAction::getCoeffs(){
    return coeffs;
}

std::vector<QuadVoxel> QuadAction::getSwath(){
    return swath;
}


bool QuadHandler::ReadMotionTemplate(const std::string &template_file, MotionTemplate &motion_template)
{
    ifstream fin;
    fin.open(template_file.c_str());
    if (fin.good()) {
        YAML::Parser parser(fin);
        YAML::Node doc;
        parser.GetNextDocument(doc); // we're not wrapping this in a loop because we're expecting a single document in this file
        string buf;
        size_t pos_dim;
        doc["position_dim"] >> pos_dim;

        // get extents of non-position vars from the template:
        const YAML::Node &sss(doc["sss"]);
        if (sss.size() != NUM_DOF) {
            printf("ERROR: this template is not compatible with current configuration: its num DOF %zu != %d\n", sss.size(), NUM_DOF);
            return false;
        }

        const YAML::Node &prim_set(doc["prim"]);
        // iterate over initial states, (q_i's):
        for (YAML::Iterator it = prim_set.begin(); it != prim_set.end(); ++it) {
            it.first() >> buf;
            // buf now contains the initial state for the prims that follow, in the format: N, N, ...
            boost::char_separator<char> sep(", ");
            boost::tokenizer< boost::char_separator<char> > tokens(buf, sep);

            size_t dim = pos_dim;

            QuadStateCell q_i;
            BOOST_FOREACH (const string& tok, tokens) {
                assert(dim < NUM_DOF);
                q_i.get(dim) = atoi(tok.c_str());
                ++dim;
            }
            q_i.print(cout);
            // iterate over primitives emanating from this q_i
            size_t prim_idx = 0; // reset primitive index for each q_i
            const YAML::Node &prim_list(it.second());
            for (YAML::Iterator prim_it = prim_list.begin(); prim_it != prim_list.end(); ++prim_it) {
                const YAML::Node &cur_prim(*prim_it);
                QuadAction prim;
                prim.index = prim_idx++; // set index
                cur_prim >> prim;
                int final_state = (int)prim.q_f.get(3);
                if (motion_template[q_i].size() <= final_state){
                    motion_template[q_i].resize(final_state+1);
                }
                motion_template[q_i][final_state].push_back(prim);
            } // end iterate over primitives emanating from this q_i
        } // end iterate over initial states
    }
    else {
        printf("ERROR opening the file: %s\n", template_file.c_str());
        return false;
    }

    fin.close();
    return true;
}

