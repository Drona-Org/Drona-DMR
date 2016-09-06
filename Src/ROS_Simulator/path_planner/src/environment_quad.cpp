/*
 * Copyright (c) 2008, Maxim Likhachev
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University of Pennsylvania nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
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

 using namespace std;

#include "sbpl/headers.h"
#include "environment_quad.h"

#define OBST_COST_THRESHOLD   150
#define FLT_COST_MULTIPLIER   1e6   // factor by which floating point costs are multiplied to get converted into int
// #define HEURISTIC_MULTIPLIER  0.0571545884205
#define HEURISTIC_MULTIPLIER  0.0567254727652
//#define ENABLE_HLUT

#define FREE_SPACE  // if defined, we don't even bother to read the costmap



/********************************************************/
 EnvQuadVoxel operator+ (const EnvQuadVoxel &lhs, const EnvQuadVoxel &rhs)
 {
 	EnvQuadVoxel result;
 	result.get<X>() = lhs.get<X>() + rhs.get<X>();
 	result.get<Y>() = lhs.get<Y>() + rhs.get<Y>();
 	result.get<Z>() = lhs.get<Z>() + rhs.get<Z>();
 	return result;

 }

namespace YAML {
template<>
struct convert<EnvQuadAction::EnvQuadParam> {
	inline static bool decode (const Node& yaml_node, EnvQuadAction::EnvQuadParam &coeff)
	{
		const Node& node_x = yaml_node[0];
		for (size_t dim = 0; dim < node_x.size(); ++dim) {
			coeff.x_coeffs.push_back(node_x[dim].as<float>());
		}
		const Node& node_y = yaml_node[1];
		for (size_t dim = 0; dim < node_y.size(); ++dim) {
			coeff.y_coeffs.push_back(node_y[dim].as<float>());
		}
		const Node& node_z = yaml_node[2];
		for (size_t dim = 0; dim < node_z.size(); ++dim) {
			coeff.z_coeffs.push_back(node_z[dim].as<float>());
		}
		coeff.time = yaml_node[3].as<float>();
		return true;
	}
};

template<>
struct convert<EnvQuadAction> {
	inline static bool decode (const Node& yaml_node, EnvQuadAction &action)
	{
		string buf; // string buffer

		// set cost
		action.cost = (uint) (yaml_node["cost"].as<float>() * FLT_COST_MULTIPLIER); // convert float to integer

		// set q_f
		const Node &node_qf(yaml_node["q_f"]);
		for (size_t dim = 0; dim < node_qf.size(); ++dim) {
			action.q_f.get(dim) = node_qf[dim].as<int>();
		}

	    // set params (coeffs)
		action.coeffs = yaml_node["params"].as<EnvQuadAction::EnvQuadParam>();

		// set swath
		const Node& node_swath = yaml_node["swath"];

		if(!node_swath.IsSequence()) {
			return false;
		}

		// for each voxel in the swath
		for (std::size_t i=0; i < node_swath.size(); ++i) {
			EnvQuadVoxel cur_voxel;
			boost::get<0>(cur_voxel) = node_swath[0].as<int>();
			boost::get<1>(cur_voxel) = node_swath[1].as<int>();
			boost::get<2>(cur_voxel) = node_swath[2].as<int>();
			action.swath.push_back(cur_voxel);
		} // end for each voxel in the swath

		return true;
	}
};
}

/**************************** EnvQuadStateCell **************************/



//function prototypes
 EnvQuadStateCell::EnvQuadStateCell(std::vector<int>::iterator first, std::vector<int>::iterator last)
 {
 	m_data.assign(first, last);
 	assert(m_data.size() == NUM_DOF);
 }




 EnvQuadStateCell::EnvQuadStateCell(int* first, int* last)
 {
 	m_data.assign(first, last);
 	assert(m_data.size() == NUM_DOF);
 }




 void EnvQuadStateCell::print(ostream &output) const
 {
 	output << "(" << m_data.at(0);
	//output << m_data.at(0);
 		for (size_t dim = 1; dim < m_data.size(); ++dim)
 			output << ", " << m_data.at(dim);
 		output << ")";
}


bool EnvQuadStateCell::operator== (const EnvQuadStateCell &other) const
{
	assert(m_data.size() == NUM_DOF);
	assert(other.m_data.size() == NUM_DOF);
	for (size_t dim = 0; dim < NUM_DOF; ++dim)
		if (m_data.at(dim) != other.m_data.at(dim))
			return false;
		return true;
	}


	size_t EnvQuadStateCell::Hash::operator()(const EnvQuadStateCell &val) const
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



	EnvQuadVoxel EnvQuadStateCell::operator+ (const EnvQuadVoxel &other)
	{
		EnvQuadVoxel result(m_data.at(X) + other.get<X>(),  	\
			m_data.at(Y) + other.get<Y>(),  	\
			m_data.at(Z) + other.get<Z>());
		return result;
	}



	const YAML::Node& operator>> (const YAML::Node& yaml_node, EnvQuadStateCell &state_cell)
	{
		for (size_t dim = 0; dim < NUM_DOF; ++dim)
			state_cell.m_data[dim] = yaml_node[dim].as<int>();
		return yaml_node;
	}



/**************************** EnvQuadAction **************************/

	std::ostream& operator<< (std::ostream &output, const EnvQuadAction &action)
	{
		output << "#" << action.index << ": " << action.q_f << ", " << action.cost << ", [";
			BOOST_FOREACH(const EnvQuadVoxel &voxel, action.swath) {
				cout << voxel << " ";
			}
			cout << "]";
		return output;
	}

std::ostream& operator<< (std::ostream &output, const EnvQuadAction::EnvQuadParam &coeff)
{
	printf("parsing coefs");
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


EnvQuadAction::EnvQuadParam EnvQuadAction::getCoeffs(){
	return coeffs;
}

std::vector<EnvQuadVoxel> EnvQuadAction::getSwath(){
	return swath;
}
/**************************** EnvCostmap **************************/
bool EnvCostMap::collision_check(std::vector<EnvQuadVoxel> swath, EnvQuadStateCell cur_state)
{

#ifdef FREE_SPACE
	return true;
#endif
	vector<EnvQuadVoxel>::const_iterator vox_it = swath.begin();
	for (; vox_it != swath.end(); ++vox_it) {
		EnvQuadVoxel cur_vox = cur_state + *vox_it;
		if(cur_vox.get<0>() < 0 || cur_vox.get<1>() < 0 || cur_vox.get<2>() < 0 || cur_vox.get<0>() >= map_size[0] || cur_vox.get<1>() >= map_size[1] || cur_vox.get<2>() >= map_size[2])
			return false;
		tr1::unordered_map<EnvQuadVoxel, uint, EnvQuadVoxelHash>::const_iterator cmap_iter = m_cost.find(cur_vox);
		if (cmap_iter != m_cost.end() && cmap_iter->second > OBST_COST_THRESHOLD){
		// if (m_cost[cur_vox] > OBST_COST_THRESHOLD){
			return false;
		}
    } // end for
    return true;
}

void EnvCostMap::update_map_index(EnvQuadVoxel index, uint cost)
{
	m_cost[index] = cost;
}

uint EnvCostMap::get_cost(EnvQuadVoxel index)
{
	return m_cost[index];
}

size_t EnvCostMap::get_size(uint dim)
{
	return map_size[dim];
}

int EnvCostMap::get_offset(uint dim)
{
	return map_offset[dim];
}

void EnvCostMap::set_mapoffset(int off_x,int off_y,int off_z)
{
	map_offset[0] = off_x;
	map_offset[1] = off_y;
	map_offset[2] = off_z;    
}


bool EnvCostMap::read_cost_map(const std::string &costmap_file)
{
	EnvQuadVoxel xyz_offset; //(-20, -15, -50); // TODO: a better way to specify this offset?

	YAML::Node doc = YAML::LoadFile(costmap_file.c_str());

	std::tr1::unordered_map<EnvQuadVoxel, uint, EnvQuadVoxelHash> temp_map;
    //		doc["position_dim"] >> str_val;
    //		cout << str_val << endl;

	// get extents of position vars from the world model:
	EnvQuadVoxel extents = doc["extent"].as<EnvQuadVoxel>();
	//cout << extents << endl;
	map_size[0] = extents.get<0>();
	map_size[1] = extents.get<1>();
	map_size[2] = extents.get<2>();
	xyz_offset = doc["xyz_offset"].as<EnvQuadVoxel>();

	map_offset[0] = xyz_offset.get<0>();
	map_offset[1] = xyz_offset.get<1>();
	map_offset[2] = xyz_offset.get<2>();

	const YAML::Node &cost_node(doc["cost"]);
	//cout << "len: " << cost_node.size() << endl;
	//cost_node >> buf;

	size_t num_obst = 0;

	//for (YAML::Iterator it = cost_node.begin(); it != cost_node.end(); ++it) {
	for (uint idx = 0; idx < cost_node.size(); ++idx) {
		EnvQuadVoxel voxel;
		uint cost;
		const YAML::Node &voxel_node(cost_node[idx]);
		voxel = voxel_node.as<EnvQuadVoxel>();
		cost = voxel_node[3].as<uint>();
		//cout << vox << ": " << cost << endl;
		m_cost[voxel] = cost;  // TODO: can't assume that these coordinates are all > 0 as this code expects; figure out the offset to make sure of that
		if (cost > 200) {
			++num_obst;
		}
	}
	printf("Read %zu obsts\n", num_obst);


    //	EnvQuadVoxel v;
    //	v.get<0>() = 9;
    //	v.get<1>() = 60;
    //	v.get<2>() = 44;
    //	cout << "* " << m_costmap[v] << endl;
	return true;
}

/**************************** EnvironmentQuad **************************/



//-----------interface with outside functions-----------------------------------
EnvironmentQuad::~EnvironmentQuad()
{
	SBPL_PRINTF("Destroying EnvironmentQuadrotor...\n");
	for (size_t id = 0; id < StateID2IndexMapping.size(); ++id) {
		delete [] StateID2IndexMapping.at(id);
		StateID2IndexMapping.at(id) = NULL;
	}

	// dealloc the HLUT
	if (m_hlut) {
		size_t hlut_bins = 8*8*2;
		for (size_t bin = 0; bin < hlut_bins; ++bin)
			if (m_hlut[bin])
				delete [] m_hlut[bin];
			delete [] m_hlut;
		}
	}



	bool EnvironmentQuad::InitializeEnv(const char* sEnvFile)
	{
		FILE* fCfg = fopen(sEnvFile, "r");
		if(fCfg == NULL)
		{
			SBPL_ERROR("ERROR: unable to open %s\n", sEnvFile);
			throw new SBPL_Exception();
		}
		m_extents[X] = 100;
		m_extents[Y] = 100;
		m_extents[Z] = 100;
		m_extents[3] = 0;
		ReadConfiguration(fCfg);
		fclose(fCfg);

	// override position extents manually, in case world costmap is too big
	// for HLUT tests:
//	m_extents[X] = 25;
//	m_extents[Y] = 25;
//	m_extents[Z] = 25;

	printf("%zu, %zu, %zu, %zu\n", m_extents[X],m_extents[Y],m_extents[Z],m_extents[3]);

		for (size_t i = 0; i < NUM_DOF; ++i) {
			m_stride[i] = 1;
			for (size_t j = NUM_DOF-1; j > i; --j)
				m_stride[i] *= m_extents[j];
			// printf("%zu: %zu\n", i, m_stride[i]);
		}

	// init memory
		size_t max_num_cells = m_extents[0] * m_stride[0];
		fprintf(stderr, "reserving %zu cells... ", max_num_cells);
		for (size_t id = 0; id <= max_num_cells; ++id) {
			int* entry = new int [NUMOFINDICES_STATEID2IND];
			for (size_t i = 0; i < NUMOFINDICES_STATEID2IND; i++)
				entry[i] = -1;
			StateID2IndexMapping.push_back(entry);
			if (! (id % 1000000))
				fprintf(stderr, "*");
		}
		fprintf(stderr, " done.\n");

#ifdef ENABLE_HLUT
	// do the hlut test
		fprintf(stderr, "HLUT init... ");
		size_t hlut_bins = 8*8*2;
		m_hlut = new int*[hlut_bins];
		for (size_t bin = 0; bin < hlut_bins; ++bin) {
			m_hlut[bin] = new int[max_num_cells];
			for (size_t i = 0; i < max_num_cells; ++i)
				m_hlut[bin][i] = 10000000;
		}
		fprintf(stderr, "done.\n");

	// read in the HLUT
		string hlut_file("hlut_10.dat");
		if (!read_hlut(hlut_file)) {
			SBPL_ERROR("ERROR reading the HLUT in %s\n", hlut_file.c_str());
			throw new SBPL_Exception();
		}
#endif



    // testing:
		EnvQuadStateCell cell_key;
		const vector<vector<EnvQuadAction> > &prim_list = m_template[cell_key];
		printf("Got %zu prims\n", prim_list.size());
		BOOST_FOREACH(vector<EnvQuadAction> prim, prim_list) {
			BOOST_FOREACH(const EnvQuadAction pp, prim){ 
				cout << pp << endl;
			}
		}


#if 1
	//int q_start_data[] = {40, 20, 10, 0, 0};
	//int q_start_data[] = {25, 20, 25, 0, 0};
		int q_start_data[] = {5, 5, 15, 0};
		q_start.assign(q_start_data, q_start_data+NUM_DOF);

		int q_goal_data[] = {40, 20, 25, 0};
	//int q_goal_data[] = {15, 5, 15, 0, 0};
	//int q_goal_data[] = {20, 20, 23, 0, 0};
		q_goal.assign(q_goal_data, q_goal_data+NUM_DOF);
#endif

		return true;
	}



	bool EnvironmentQuad::InitializeMDPCfg(MDPConfig *MDPCfg)
	{
	//initialize MDPCfg with the start and goal ids
		MDPCfg->startstateid  = state2id(q_start);
		MDPCfg->goalstateid = state2id(q_goal);
		printf("start id: %d, goal id: %d\n", MDPCfg->startstateid, MDPCfg->goalstateid);
		return true;
	}



	void EnvironmentQuad::ReadConfiguration(FILE* fCfg)
	{
#ifndef FREE_SPACE
	// read in the costmap
		if(1){
			string cmap_file("/home/tee/ros_ws/sandbox/path_planner/datas/demo_map.yaml");
			// string cmap_file("rand.yaml");
			if (!read_cost_map(cmap_file)) {
				SBPL_ERROR("ERROR reading the costmap in %s\n", cmap_file.c_str());
				throw new SBPL_Exception();
			}
			m_extents[0] = m_costmap.get_size(0);
			m_extents[1] = m_costmap.get_size(1);
			m_extents[2] = m_costmap.get_size(2);
			m_extents[3] = 0;
		}
		else{
		// only set m_extents
			set_map_extents(30, 30, 20);
		}
#endif

	// read in the template
		string template_file("/home/tee/ros_ws/sandbox/path_planner/datas/quad_tem.yaml");
		if (!ReadMotionTemplate(template_file, m_template)) {
			SBPL_ERROR("ERROR reading the template in %s\n", template_file.c_str());
			throw new SBPL_Exception();
		}
	}



	bool EnvironmentQuad::ReadMotionTemplate(const std::string &template_file, MotionTemplate &motion_template)
	{
		
		YAML::Node doc = YAML::LoadFile(template_file.c_str());
//		doc["position_dim"] >> str_val;
//		cout << str_val << endl;

		// get extents of non-position vars from the template:
		const YAML::Node &sss(doc["sss"]);
		if (sss.size() != NUM_DOF) {
			SBPL_ERROR("ERROR: this template is not compatible with current configuration: its num DOF %zu != %d\n", sss.size(), NUM_DOF);
			throw new SBPL_Exception();
		}
		for (size_t dim = 3; dim < NUM_DOF; ++dim) {
			if(m_extents[dim] < sss[dim].size())
				m_extents[dim] = sss[dim].size();
			printf("set #%zu done\n", sss[dim].size());
		}

		const YAML::Node &prim_set(doc["prim"]);
		// iterate over initial states, (q_i's):
		for (size_t j=0; j < prim_set.size(); ++j) {
			
			// buf now contains the initial state for the prims that follow, in the format: N, N, ...
			boost::char_separator<char> sep(", ");
			boost::tokenizer< boost::char_separator<char> > tokens(prim_set[j][0].as<string>(), sep);
			size_t dim = 3; // we're skipping 3D position dims (TODO: make this a param based on env?)
			EnvQuadStateCell q_i;
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
				EnvQuadAction prim;
				prim.index = prim_idx++; // set index
				prim = cur_prim.as<EnvQuadAction>();
				int final_state = (int)(prim.q_f.get(3));
				if (motion_template[q_i].size() <= final_state){
					motion_template[q_i].resize(final_state+1);
				}
				motion_template[q_i][final_state].push_back(prim);
			} // end iterate over primitives emanating from this q_i
		} // end iterate over initial states
		return true;
	}

bool EnvironmentQuad::read_cost_map(const std::string &costmap_file)
{
	return m_costmap.read_cost_map(costmap_file);
}

void EnvironmentQuad::set_map_extents(int mx, int my, int mz)
{
	m_extents[0] = mx;
	m_extents[1] = my;
	m_extents[2] = mz;
}

int EnvironmentQuad::getMapoffset(uint dim){
	return m_costmap.get_offset(dim);
}
void EnvironmentQuad::set_map_offset(int ox, int oy, int oz)
{
	m_costmap.set_mapoffset(ox,oy,oz);
}

void EnvironmentQuad::update_map_index(int x, int y, int z, uint cost){
	EnvQuadVoxel voxel(x,y,z);
	m_costmap.update_map_index(voxel, cost);
}

#if 0 // due to large size, HLUT can't be YAML, just plan text
bool EnvironmentQuad::read_hlut(const std::string &hlut_file)
{
	ifstream fin;
	fin.open(hlut_file.c_str());
	if (fin.good()) {
		SBPL_PRINTF("Loading HLUT... ");
		YAML::Parser parser(fin);
		YAML::Node doc;
		parser.GetNextDocument(doc); // we're not wrapping this in a loop because we're expecting a single document in this file
		string buf;
		const YAML::Node &cost_node(doc["cost"]);
		//cout << "len: " << cost_node.size() << endl;
		//cost_node >> buf;
		for (YAML::Iterator it = cost_node.begin(); it != cost_node.end(); ++it) {
			EnvQuadStateCell state_cell;
			uint cost;
			it.first() >> state_cell;
			it.second() >> cost;
			//cout << vox << ": " << cost << endl;
			m_hlut[state_cell] = cost; //(uint)(cost * FLT_COST_MULTIPLIER);
		}
		SBPL_PRINTF("done.\n");
	}
	else {
		SBPL_PRINTF("ERROR opening the file: %s\n", hlut_file.c_str());
		return false;
	}
	fin.close();


	int cell1_data[] = {-2, 1, -3, 6, 0, 1};
	EnvQuadStateCell cell1(cell1_data, cell1_data+NUM_DOF);
	cout << "* " << m_hlut[cell1] << endl;
	return true;
}
#endif


bool EnvironmentQuad::read_hlut(const std::string &hlut_file)
{
	ifstream fin;
	fin.open(hlut_file.c_str());
	SBPL_PRINTF("Loading HLUT... ");
	//m_hlut.reserve(1000000);
//	int q_i_data[] = {0, 0, 0, 7, 7, 1};
//	EnvQuadStateCell q_i(q_i_data, q_i_data+NUM_DOF);
//	cout << q_i << " #" << state2id(q_i) << endl;
//	return false;

	EnvQuadStateCell q_i;
	size_t item_cnt = 0; // this var is declared here so that we can use it to see whether we read any data from the file
	while(fin.good()) {
		char buf[1025];
		fin.getline(buf, 1024);
		//cout << buf << endl;
		string buf_str(buf); // tokenizer expects a string object
		boost::char_separator<char> sep(", ");
		boost::tokenizer< boost::char_separator<char> > tokens(buf_str, sep);
		vector<string> toks(tokens.begin(), tokens.end()); // just to find out how many tokens we got
		if (toks.size() == (NUM_DOF - 3)) {  // this is the template key
			size_t dim = 3; // skip XYZ dims to start with
			BOOST_FOREACH (const string& tok, tokens) {
				q_i.get(dim++) = atoi(tok.c_str()); // the first 3 elements of q_i (XYZ) are never touched, so they will always remain 0
			}
			item_cnt = 0; // reset progress counter
			cerr << endl << q_i << ": ";
		} // end if (toks.size() == (NUM_DOF - 3))
		else if (toks.size() == (NUM_DOF + 1)) { // if this is an HLUT data item (state + cost)
			EnvQuadStateCell q_f;
			float cost = 0.0;
			size_t dim = 0;
			BOOST_FOREACH (const string& tok, tokens) {
				if (dim < NUM_DOF) // we're collecting state cell data
					q_f.get(dim) = atoi(tok.c_str());
				else { // must be the cost value, a float
					cost = atof(tok.c_str());
				}
				++dim;
			} // end BOOST_FOREACH (const string& tok, tokens)
			// xform q_f into absolute coords for storage
			q_f.get(X) += m_extents[X] >> 1;
			q_f.get(Y) += m_extents[Y] >> 1;
			q_f.get(Z) += m_extents[Z] >> 1;
			if (q_f.get(X) >= 0 && q_f.get(X) < m_extents[X] &&   \
				q_f.get(Y) >= 0 && q_f.get(Y) < m_extents[Y] &&   \
				q_f.get(Z) >= 0 && q_f.get(Z) < m_extents[Z]) {
				m_hlut[state2id(q_i)][state2id(q_f)] = (uint)(cost * FLT_COST_MULTIPLIER);
			} // end if (q_f.get(X) >= 0 && ...
			// just a progress counter
				++item_cnt;
				if (!(item_cnt % 10000))
					fprintf(stderr, ".");
		} // end else if (toks.size() == (NUM_DOF + 1))
		// just ignore everything else for now:
//		else { // something's wrong
//			fin.close();
//			SBPL_PRINTF("ERROR reading the file: got an entry with %zu elements.\n", toks.size());
//			return false;
//		}
	} // end while(fin.good())
	fin.close();
//	if (m_hlut.size() == 0) {
//		SBPL_PRINTF("ERROR opening the file: %s\n", hlut_file.c_str());
//		return false;
//	}
//	SBPL_PRINTF("done, %zu entries.\n", m_hlut.size());
//	if (item_cnt == 0) {
//		SBPL_PRINTF("ERROR reading the file: %s\n", hlut_file.c_str());
//		return false;
//	}
	//SBPL_PRINTF("done, %zu entries.\n", item_cnt);

	int q_i_test_data[] = {0, 0, 0, 0, 0};
	EnvQuadStateCell q_i_test(q_i_test_data, q_i_test_data+NUM_DOF);
	// 4, -3, 1, 5, 2, 1
	//int cell_data[] = {4 + (m_extents[X]>>1), -3 + (m_extents[Y]>>1), 1 + (m_extents[Z]>>1), 5, 2, 1};
	// 0, 0, -2, 7, 5, 1
	int cell_data[] = {0 + (m_extents[X]>>1), 0 + (m_extents[Y]>>1), -2 + (m_extents[Z]>>1), 7, 5, 1};
	EnvQuadStateCell cell(cell_data, cell_data+NUM_DOF);
	cout << "* " << m_hlut[state2id(q_i_test)][state2id(cell)] << endl;
	return true;
}

std::vector<double> EnvironmentQuad::getExecutionTime(vector<int> path)
{
	std::vector<double> temp;
	double exe_time = 0;
	double cost = 0;
	EnvQuadStateCell cur_cell;
	int prev_order[] = {0, 1, 2, 3};
	int id = *path.begin();
	id2state(id, cur_cell);
	path.erase(path.begin());
	BOOST_FOREACH(int id, path) {
		EnvQuadStateCell next_cell,key;
		id2state(id, next_cell);
		key = cur_cell;
		key.reset_position();
		size_t next_id = next_cell.get(V);
		vector<EnvQuadAction> cur_action_list = m_template[key].at(next_id);
		int dx = next_cell.get(X) - cur_cell.get(X);
		int dy = next_cell.get(Y) - cur_cell.get(Y);
		int dz = next_cell.get(Z) - cur_cell.get(Z);
		BOOST_FOREACH(EnvQuadAction cur_action, cur_action_list){
			if(cur_action.q_f.get(X) == dx && cur_action.q_f.get(Y) == dy && cur_action.q_f.get(Z) == dz ){
				cost += cur_action.cost;
				exe_time += cur_action.coeffs.time;
				cur_cell = next_cell;
				break;
			}
		}
	}
	temp.push_back(cost);
	temp.push_back(exe_time);
	return temp;
}


void EnvironmentQuad::PrintParam(vector<int> path)
{
	cout << "printing path";
	EnvQuadStateCell cur_cell;
	int id = *path.begin();
	id2state(id, cur_cell);
	path.erase(path.begin());
	BOOST_FOREACH(int id, path) {
		EnvQuadStateCell next_cell,key;
		id2state(id, next_cell);
		key = cur_cell;
		key.reset_position();
		size_t next_id = next_cell.get(V);
		vector<EnvQuadAction> cur_action_list = m_template[key].at(next_id);
		int dx = next_cell.get(X) - cur_cell.get(X);
		int dy = next_cell.get(Y) - cur_cell.get(Y);
		int dz = next_cell.get(Z) - cur_cell.get(Z);
		BOOST_FOREACH(EnvQuadAction cur_action, cur_action_list){
			if(cur_action.q_f.get(X) == dx && cur_action.q_f.get(Y) == dy && cur_action.q_f.get(Z) == dz ){
				cout << cur_action.coeffs;
				break;
			}
		}
	}
}


EnvQuadAction EnvironmentQuad::GetAction(int start, int end)
{
	EnvQuadStateCell start_cell, end_cell, key;
	id2state(start, start_cell);
	id2state(end, end_cell);
	key = start_cell;
	key.reset_position();
	size_t next_id = end_cell.get(V);
	int dx = end_cell.get(X) - start_cell.get(X);
	int dy = end_cell.get(Y) - start_cell.get(Y);
	int dz = end_cell.get(Z) - start_cell.get(Z);
	vector<EnvQuadAction> cur_action_list = m_template[key].at(next_id);
	BOOST_FOREACH(EnvQuadAction cur_action, cur_action_list){
		if(cur_action.q_f.get(X) == dx && cur_action.q_f.get(Y) == dy && cur_action.q_f.get(Z) == dz ){
			return cur_action;
		}
	}
	EnvQuadAction temp;
	return temp;
}

//------------------------------Heuristic computation--------------------------

int EnvironmentQuad::GetFromToHeuristic(int FromStateID, int ToStateID)
{
	SBPL_ERROR("ERROR in EnvQuadrotor... function: GetFromToHeuristic is undefined\n");
	throw new SBPL_Exception();
}



int EnvironmentQuad::GetGoalHeuristic(int stateID)
{

	EnvQuadStateCell q_query(id2state(stateID));

#ifdef ENABLE_HLUT
	EnvQuadStateCell q_goal_rel(q_goal); // goal state relative to q_query
	q_goal_rel.get(X) -= q_query.get(X);
	q_goal_rel.get(Y) -= q_query.get(Y);
	q_goal_rel.get(Z) -= q_query.get(Z);

	// offset wrt HLUT center:
	q_goal_rel.get(X) += m_extents[X]>>1;
	q_goal_rel.get(Y) += m_extents[Y]>>1;
	q_goal_rel.get(Z) += m_extents[Z]>>1;

	// bounds check
	if (q_goal_rel.get(X) >= 0 && q_goal_rel.get(X) < m_extents[X] &&   \
		q_goal_rel.get(Y) >= 0 && q_goal_rel.get(Y) < m_extents[Y] &&   \
		q_goal_rel.get(Z) >= 0 && q_goal_rel.get(Z) < m_extents[Z]) {
			q_query.reset_position(); // to use it as an HLUT key
		return m_hlut[state2id(q_query)][state2id(q_goal_rel)];
	}
	return 100000000;


#else

	// just weighted L2 distance
	int dx = q_goal.get(X) - q_query.get(X);
	int dy = q_goal.get(Y) - q_query.get(Y);
	int dz = q_goal.get(Z) - q_query.get(Z);
	double l2 = (double)(dx*dx + dy*dy + dz*dz);
	int h = (int) (sqrt(l2) * FLT_COST_MULTIPLIER * HEURISTIC_MULTIPLIER);
	//fprintf(stderr, "%d, %d, %d: %f, %f, %d\n", dx, dy, dz, l2, sqrt(l2) * 3.0,  h);
	return h;
#endif
}



int EnvironmentQuad::GetStartHeuristic(int stateID)
{
	EnvQuadStateCell q_query(id2state(stateID));
	// just weighted L2 distance
	int dx = q_start.get(X) - q_query.get(X);
	int dy = q_start.get(Y) - q_query.get(Y);
	int dz = q_start.get(Z) - q_query.get(Z);
	double l2 = (double)(dx*dx + dy*dy + dz*dz);
	int h = (int) (sqrt(l2) * FLT_COST_MULTIPLIER * HEURISTIC_MULTIPLIER);
	//fprintf(stderr, "%d, %d, %d: %f, %f, %d\n", dx, dy, dz, l2, sqrt(l2) * 3.0,  h);
	return h;
}



void EnvironmentQuad::SetAllActionsandAllOutcomes(CMDPSTATE* state)
{
	SBPL_ERROR("ERROR in EnvQuadrotor... function: SetAllActionsandAllOutcomes is undefined\n");
	throw new SBPL_Exception();
}



void EnvironmentQuad::SetAllPreds(CMDPSTATE* state)
{
	//implement this if the planner needs access to predecessors
	
	SBPL_ERROR("ERROR in EnvQuadrotor... function: SetAllPreds is undefined\n");
	throw new SBPL_Exception();
}



void EnvironmentQuad::GetSuccs(int state_id, vector<int>* succ_idV, vector<int>* succ_costV)
{
	EnvQuadStateCell cur_state, key;
	id2state(state_id, cur_state);
	//cout << cur_state << " [" << state_id << "]" << endl;
	key = cur_state;
	key.reset_position();
	// copy of the the successor data
	const vector<vector<EnvQuadAction> > &prim_list = m_template[key];

	// reset input data
	succ_idV->clear();
	succ_costV->clear();

	BOOST_FOREACH(const vector<EnvQuadAction> &prim, prim_list) {
		BOOST_FOREACH(const EnvQuadAction &pp, prim){
	        EnvQuadStateCell q_f(pp.q_f); // making a local copy, so we can offset its position
	        q_f.offset_position(cur_state);

	        // check bounds wrt world model
	        if (q_f.get(X) < 0 || q_f.get(Y) < 0 || q_f.get(Z) < 0)
	        	continue;
	        if (q_f.get(X) >= m_extents[X] || q_f.get(Y) >= m_extents[Y] || q_f.get(Z) >= m_extents[Z])
	        	continue;

	        // check for collisions
	        bool valid = m_costmap.collision_check(pp.swath, cur_state);
	        if(valid){
		    //cout << "- " << q_f << " [" << state2id(q_f) << "]" << endl;
	        	succ_idV->push_back(state2id(q_f));
	        	succ_costV->push_back(pp.cost);
	        }
	    }
	}
}



// for now this is doing the same thing as GetSuccs
void EnvironmentQuad::GetPreds(int state_id, vector<int>* pred_idV, vector<int>* pred_costV)
{
	EnvQuadStateCell cur_state, key;
	id2state(state_id, cur_state);
	//cout << cur_state << " [" << state_id << "]" << endl;
	key = cur_state;
	key.reset_position();
	// copy of the the successor data
	const vector<vector<EnvQuadAction> > &prim_list = m_template_inv[key];

	// reset input data
	pred_idV->clear();
	pred_costV->clear();

	BOOST_FOREACH(const vector<EnvQuadAction> &prim, prim_list) {
		BOOST_FOREACH(const EnvQuadAction &pp, prim){
	        EnvQuadStateCell q_f(pp.q_f); // making a local copy, so we can offset its position
	        q_f.offset_position_inv(cur_state);

	        // check bounds wrt world model
	        if (q_f.get(X) < 0 || q_f.get(Y) < 0 || q_f.get(Z) < 0)
	        	continue;
	        if (q_f.get(X) >= m_extents[X] || q_f.get(Y) >= m_extents[Y] || q_f.get(Z) >= m_extents[Z])
	        	continue;

	        // check for collisions
	        bool valid = m_costmap.collision_check(pp.swath, q_f);
	        if(valid){
		    //cout << "- " << q_f << " [" << state2id(q_f) << "]" << endl;
	        	pred_idV->push_back(state2id(q_f));
	        	pred_costV->push_back(pp.cost);
	        }
	    }
	}
}



int EnvironmentQuad::SizeofCreatedEnv()
{
	SBPL_ERROR("ERROR in EnvQuadrotor... function: SizeofCreatedEnv is undefined\n");
	throw new SBPL_Exception();
	
}



void EnvironmentQuad::PrintState(int stateID, bool bVerbose, FILE* fOut)
{
	EnvQuadStateCell state;
	id2state(stateID, state);
	cout << state;
}



void EnvironmentQuad::PrintEnv_Config(FILE* fOut)
{

	//implement this if the planner needs to print out EnvQuadrotor. configuration
	
	SBPL_ERROR("ERROR in EnvQuadrotor... function: PrintEnv_Config is undefined\n");
	throw new SBPL_Exception();

}



size_t EnvironmentQuad::state2id(const EnvQuadStateCell & state_cell)
{
	size_t state_id = 0;

	for (size_t dof = 0; dof < NUM_DOF; ++dof) {
		assert(state_cell.get(dof) >= 0);
		state_id += m_stride[dof] * state_cell.get(dof);
	}
	return state_id;
}



void EnvironmentQuad::id2state(size_t state_id, EnvQuadStateCell & state_cell)
{
	for (size_t dof = 0; dof < NUM_DOF; ++dof) {
		state_cell.get(dof) = state_id / m_stride[dof];
		assert(state_cell.get(dof) >= 0);
		state_id = state_id % m_stride[dof]; // should be a no-op: compiler should get this remainder from the divide above
	}

}





//------------------------------------------------------------------------------



