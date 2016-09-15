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

#include "swarm_handler.h"


/********************************************************/
namespace YAML {
template<>
struct convert<QuadVoxel> {
  inline static Node encode(const QuadVoxel& voxel) {
    Node node;
    node.push_back(voxel.get<0>());
    node.push_back(voxel.get<1>());
    node.push_back(voxel.get<2>());
    return node;
  }

  inline static bool decode(const Node& node, QuadVoxel& voxel) {
    if(!node.IsSequence()) {
      return false;
    }

    boost::get<0>(voxel) = node[0].as<int>();
    boost::get<1>(voxel) = node[1].as<int>();
    boost::get<2>(voxel) = node[2].as<int>();
    return true;
  }
};
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


namespace YAML {
template<>
struct convert<QuadStateCell> {
    static bool decode (const YAML::Node& yaml_node, QuadStateCell &state_cell)
    {
        for (size_t dim = 0; dim < NUM_DOF+1; ++dim)
            state_cell.m_data[dim] = yaml_node[dim].as<int>();
        return true;
    }
};
}
/**************************** SwarmStateCell **************************/

//function prototypes
SwarmStateCell::SwarmStateCell(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
    m_data.assign(first, last);
    assert(m_data.size() == NUM_DOF);
}



SwarmStateCell::SwarmStateCell(int* first, int* last)
{
    m_data.assign(first, last);
    assert(m_data.size() == NUM_DOF);
}


void SwarmStateCell::print(ostream &output) const
{
    output << "(" << m_data.at(0);
//output << m_data.at(0);
    for (size_t dim = 1; dim < m_data.size(); ++dim)
        output << ", " << m_data.at(dim);
    output << ")";
}


bool SwarmStateCell::operator== (const SwarmStateCell &other) const
{
    assert(m_data.size() == NUM_DOF);
    assert(other.m_data.size() == NUM_DOF);
    for (size_t dim = 0; dim < NUM_DOF; ++dim)
        if (m_data.at(dim) != other.m_data.at(dim))
            return false;
    return true;
}


size_t SwarmStateCell::Hash::operator()(const SwarmStateCell &val) const
{
    size_t key = 0;
    for (size_t dim = 0; dim < NUM_DOF; ++dim) {
        size_t key_dim = (size_t) val.m_data.at(dim);
        key_dim ^= (key_dim << 4);
        key_dim += (key_dim >> 9);
        key ^= key_dim;
    }
    return key;
}

QuadVoxel SwarmStateCell::operator+ (const QuadVoxel &other)
{
    QuadVoxel result(m_data.at(X) + other.get<X>(),     \
        m_data.at(Y) + other.get<Y>(),      \
        m_data.at(Z) + other.get<Z>());
    return result;
}

namespace YAML {
template<>
struct convert<SwarmStateCell> {
    static bool decode (const YAML::Node& yaml_node, SwarmStateCell &state_cell)
    {
        for (size_t dim = 0; dim < NUM_DOF+1; ++dim)
            state_cell.m_data[dim] = yaml_node[dim].as<int>();
        return true;
    }
};
}

/**************************** SwarmAction **************************/

std::ostream& operator<< (std::ostream &output, const SwarmAction &action)
    {
        output << "#" << action.index << ": " << action.q_f << ", " << action.cost << ", [";
            BOOST_FOREACH(const QuadVoxel &voxel, action.swath) {
                cout << voxel << " ";
            }
            cout << "]";
return output;
}

std::ostream& operator<< (std::ostream &output, const SwarmAction::QuadParam &coeff)
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

namespace YAML {
template<>
struct convert<SwarmAction::QuadParam> {
    static bool decode (const YAML::Node& yaml_node, SwarmAction::QuadParam &coeff)
    {
        const YAML::Node& node_x = yaml_node[0];
        for (size_t dim = 0; dim < node_x.size(); ++dim) {
            coeff.x_coeffs.push_back(node_x[dim].as<float>());
        }
        const YAML::Node& node_y = yaml_node[1];
        for (size_t dim = 0; dim < node_y.size(); ++dim) {
            coeff.y_coeffs.push_back(node_y[dim].as<float>());
        }
        const YAML::Node& node_z = yaml_node[2];
        for (size_t dim = 0; dim < node_z.size(); ++dim) {
            coeff.z_coeffs.push_back(node_z[dim].as<float>());
        }
        coeff.time = yaml_node[3].as<float>();
        return yaml_node;
    }
};

template<>
struct convert<SwarmAction> {
    static bool decode (const Node& yaml_node, SwarmAction &action)
    {
        action.cost = (uint) (yaml_node["cost"].as<float>() * FLT_COST_MULTIPLIER); // convert float to integer

        // set q_f
        const YAML::Node &node_qf(yaml_node["q_f"]);
        for (size_t dim = 0; dim < node_qf.size(); ++dim) {
            action.q_f.get(dim) = node_qf[dim].as<int>();
        }

        // set params (coeffs and assignment)
        const YAML::Node &node_param(yaml_node["params"]);
        for (size_t dim = 0; dim < node_param.size()-1; ++dim) {
            action.coeffs.push_back(node_param[dim].as<SwarmAction::QuadParam>());
        }
        const YAML::Node &node_assignment = node_param[node_param.size()-1];
        for (size_t dim = 0; dim < node_assignment.size(); ++dim) {
            action.assignment.push_back(node_assignment[dim].as<int>());
        }    

        // set swath
        const YAML::Node &node_swath(yaml_node["swath"]);
        // for each voxel in the swath
        for (size_t i=0; i < node_swath.size(); ++i) {
            QuadVoxel cur_voxel;
            boost::get<0>(cur_voxel) = node_swath[i][0].as<int>();
            boost::get<1>(cur_voxel) = node_swath[i][1].as<int>();
            boost::get<2>(cur_voxel) = node_swath[i][2].as<int>();
            action.swath.push_back(cur_voxel);
        } // end for each voxel in the swath

        return true;
    }
};
}

std::vector<SwarmAction::QuadParam> SwarmAction::getCoeffs(){
    return coeffs;
}

std::vector<int> SwarmAction::getAssignment(){
    return assignment;
}

std::vector<QuadVoxel> SwarmAction::getSwath(){
    return swath;
}


bool SwarmHandler::ReadMotionTemplate(const std::string &template_file, MotionTemplate &motion_template)
{
    YAML::Node doc = YAML::LoadFile(template_file.c_str());
    string buf;
    size_t pos_dim;
    pos_dim = doc["position_dim"].as<size_t>();

    // get extents of non-position vars from the template:
    const YAML::Node &sss(doc["sss"]);
    if (sss.size() != NUM_DOF) {
        printf("ERROR: this template is not compatible with current configuration: its num DOF %zu != %d\n", sss.size(), NUM_DOF);
        return false;
    }

    const YAML::Node &prim_set(doc["prim"]);
    // iterate over initial states, (q_i's):
    for (size_t j = 0; j < prim_set.size(); ++j) {
        // buf now contains the initial state for the prims that follow, in the format: N, N, ...
        boost::char_separator<char> sep(", ");
        boost::tokenizer< boost::char_separator<char> > tokens(prim_set[j][0].as<string>(), sep);

        size_t dim = pos_dim;

        SwarmStateCell q_i;
        BOOST_FOREACH (const string& tok, tokens) {
            assert(dim < NUM_DOF);
            q_i.get(dim) = atoi(tok.c_str());
            ++dim;
        }
        q_i.print(cout);
        // iterate over primitives emanating from this q_i
        size_t prim_idx = 0; // reset primitive index for each q_i
        const YAML::Node &prim_list(prim_set[j][1]);
        for (size_t i=0; i < prim_list.size(); ++i) {
            const YAML::Node &cur_prim(prim_list[i]);
            SwarmAction prim;
            prim.index = prim_idx++; // set index
            prim = cur_prim.as<SwarmAction>();
            int final_state = (int)(2 * prim.q_f.get(3) + prim.q_f.get(4));
            if (motion_template[q_i].size() <= final_state){
                motion_template[q_i].resize(final_state+1);
            }
            motion_template[q_i][final_state].push_back(prim);
        } // end iterate over primitives emanating from this q_i
    } // end iterate over initial states

    return true;
}

