#include <vector>
#include <tr1/unordered_map>
#include <ostream>
#include <boost/tuple/tuple.hpp> // tuple for EnvQuadVoxel
#include <yaml-cpp/yaml.h> 

typedef unsigned int uint;

typedef boost::tuple<int, int, int> EnvQuadVoxel;


class EnvQuadVoxelHash
{
public:
    inline size_t operator()(const EnvQuadVoxel &val) const
    {
        size_t key = 0;
        key ^= (val.get<0>() << 5);
        key += (val.get<0>() >> 3);
        key ^= (val.get<1>() << 6);
        key += (val.get<1>() >> 2);
        key ^= (val.get<2>() << 7);
        key += (val.get<2>() >> 1);
        return key;
    }
};

class EnvCostMap
{
public:
    EnvCostMap() {};
    EnvCostMap(std::tr1::unordered_map<EnvQuadVoxel, uint, EnvQuadVoxelHash> costmap) {
	m_cost = costmap;
    }
    virtual ~EnvCostMap() {};
    void update_map_index(EnvQuadVoxel index, uint cost);
    bool read_cost_map(const std::string &costmap_file);
    uint get_cost(EnvQuadVoxel index);
    size_t get_size(uint dim);
    int get_offset(uint dim);
    void set_mapoffset(int off_x,int off_y,int off_z);
    
protected:
    std::tr1::unordered_map<EnvQuadVoxel, uint, EnvQuadVoxelHash> m_cost;
    size_t map_size[3];
    int map_offset[3];
};