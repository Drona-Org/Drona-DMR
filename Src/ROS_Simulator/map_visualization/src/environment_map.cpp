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

#include "environment_map.h"


namespace YAML {
template<>
struct convert<EnvQuadVoxel> {
  inline static Node encode(const EnvQuadVoxel& voxel) {
    Node node;
    node.push_back(voxel.get<0>());
    node.push_back(voxel.get<1>());
    node.push_back(voxel.get<2>());
    return node;
  }

  inline static bool decode(const Node& node, EnvQuadVoxel& voxel) {
    if(!node.IsSequence() || node.size() != 3) {
      return false;
    }

    boost::get<0>(voxel) = node[0].as<int>();
    boost::get<1>(voxel) = node[1].as<int>();
    boost::get<2>(voxel) = node[2].as<int>();
    return true;
  }
};
}

/**************************** EnvCostmap **************************/

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
		m_cost[voxel] = cost;  // TODO: can't assume that these coordinates are all > 0 as this code expects; figure out the offset to make sure of that
		if (cost > 200) {
			++num_obst;
		}
	}
	printf("Read %zu obsts\n", num_obst);

	return true;
}
