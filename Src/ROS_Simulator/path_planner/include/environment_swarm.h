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
#ifndef __ENVIRONMENT_SWARM_H_
#define __ENVIRONMENT_SWARM_H_

//#include <boost/tuple/tuple.hpp>
#include <vector>
#include <tr1/unordered_map>
#include <ostream>
#include <boost/tuple/tuple.hpp> // tuple for EnvQuadVoxel
#include <yaml-cpp/yaml.h> 
// declaring this up here because EnvQuadAction needs this for the >> operator


typedef unsigned int uint;

typedef boost::tuple<int, int, int> EnvQuadVoxel;
const YAML::Node& operator>> (const YAML::Node& yaml_node, EnvQuadVoxel &voxel);
EnvQuadVoxel operator+ (const EnvQuadVoxel &lhs, const EnvQuadVoxel &rhs);



class EnvQuadVoxelHash
{
public:
	size_t operator()(const EnvQuadVoxel &val) const;
};


typedef enum {
	X = 0,
	Y,
	Z,
	V,
    F,
	NUM_DOF
} DimList_t;

class EnvQuadStateCell
{
public:
	EnvQuadStateCell() {m_data.assign(NUM_DOF+1, 0);}
	EnvQuadStateCell(const EnvQuadStateCell &other) {m_data = other.m_data;}
	EnvQuadStateCell(std::vector<int>::iterator first, std::vector<int>::iterator last);
	EnvQuadStateCell(int* first, int* last);
    
	virtual ~EnvQuadStateCell() {};
    
	inline void assign(int* first, int* last) {m_data.assign(first, last); assert(m_data.size() == NUM_DOF+1);}
    
	inline int & get(size_t dim) {return m_data.at(dim);}
	inline const int & get(size_t dim) const {return m_data.at(dim);}
    
	/* useful when we need to use this state as the key in the template */
	inline void reset_position() {m_data.at(X) = 0; m_data.at(Y) = 0; m_data.at(Z) = 0;}
	inline void offset_position(const EnvQuadStateCell &other)
	{
		m_data.at(X) += other.m_data.at(X);
		m_data.at(Y) += other.m_data.at(Y);
		m_data.at(Z) += other.m_data.at(Z);
	}

    inline void offset_position_inv(const EnvQuadStateCell &other)
    {
        m_data.at(X) = other.m_data.at(X)-m_data.at(X);
        m_data.at(Y) = other.m_data.at(Y)-m_data.at(Y);
        m_data.at(Z) = other.m_data.at(Z)-m_data.at(Z);
    }

	// operators
	bool operator== (const EnvQuadStateCell &other) const;
	EnvQuadStateCell operator= (const EnvQuadStateCell &other) {m_data = other.m_data; return *this;}
	EnvQuadVoxel operator+ (const EnvQuadVoxel &other);
    
	// i/o:
	void print(std::ostream &output) const;
	friend std::ostream& operator<< (std::ostream &output, \
									 const EnvQuadStateCell &state_cell)
    {state_cell.print(output); return output;}
	friend const YAML::Node& operator>> (const YAML::Node& yaml_node, EnvQuadStateCell &state_cell);
    
	// Own hash function, useful for the stl::unordered_map
	class Hash
	{
	public:
		size_t operator()(const EnvQuadStateCell &val) const;
	};
    
protected:
    
	std::vector<int> m_data;
};


class EnvSwarmStateCell
{
public:
	EnvSwarmStateCell() {m_data.assign(NUM_DOF, 0);}
	EnvSwarmStateCell(const EnvSwarmStateCell &other) {m_data = other.m_data;}
	EnvSwarmStateCell(std::vector<int>::iterator first, std::vector<int>::iterator last);
	EnvSwarmStateCell(int* first, int* last);

	virtual ~EnvSwarmStateCell() {};

	inline void assign(int* first, int* last) {m_data.assign(first, last); assert(m_data.size() == NUM_DOF);}

	inline int & get(size_t dim) {return m_data.at(dim);}
	inline const int & get(size_t dim) const {return m_data.at(dim);}

	/* useful when we need to use this state as the key in the template */
	inline void reset_position() {m_data.at(X) = 0; m_data.at(Y) = 0; m_data.at(Z) = 0;}
	inline void offset_position(const EnvSwarmStateCell &other)
	{
		m_data.at(X) += other.m_data.at(X);
		m_data.at(Y) += other.m_data.at(Y);
		m_data.at(Z) += other.m_data.at(Z);
	}

    inline void offset_position_inv(const EnvSwarmStateCell &other)
    {
        m_data.at(X) = other.m_data.at(X)-m_data.at(X);
        m_data.at(Y) = other.m_data.at(Y)-m_data.at(Y);
        m_data.at(Z) = other.m_data.at(Z)-m_data.at(Z);
    }
	// operators
	bool operator== (const EnvSwarmStateCell &other) const;
	EnvSwarmStateCell operator= (const EnvSwarmStateCell &other) {m_data = other.m_data; return *this;}
	EnvQuadVoxel operator+ (const EnvQuadVoxel &other);

	// i/o:
	void print(std::ostream &output) const;
	friend std::ostream& operator<< (std::ostream &output, \
									 const EnvSwarmStateCell &state_cell)
									{state_cell.print(output); return output;}
	friend const YAML::Node& operator>> (const YAML::Node& yaml_node, EnvSwarmStateCell &state_cell);

	// Own hash function, useful for the stl::unordered_map
	class Hash
	{
	public:
		size_t operator()(const EnvSwarmStateCell &val) const;
	};

protected:

	std::vector<int> m_data;
};


class EnvSwarmAction
{
public:
	EnvSwarmAction() {};
	virtual ~EnvSwarmAction() {};

	friend std::ostream& operator<< (std::ostream &output, const EnvSwarmAction &action);
	friend const YAML::Node& operator>> (const YAML::Node& yaml_node, EnvSwarmAction &action);

    class EnvQuadParam
    {
    public:
        std::vector<double> x_coeffs;
        std::vector<double> y_coeffs;
        std::vector<double> z_coeffs;
        double time;
    };

    friend const YAML::Node& operator>> (const YAML::Node& yaml_node, EnvQuadParam &coeff);
    friend std::ostream& operator<< (std::ostream &output, const EnvSwarmAction::EnvQuadParam &coeff);
    std::vector<EnvQuadParam> getCoeffs();
    std::vector<int> getAssignment();
    std::vector<EnvQuadVoxel> getSwath();
protected:
	uint index;
	uint cost;
	EnvSwarmStateCell q_f;  // final state
	std::vector<EnvQuadParam> coeffs;
        std::vector<int> assignment;
	std::vector<EnvQuadVoxel> swath;

	friend class EnvironmentSwarm; // environment gets authority to manipulate the members directly
	friend class EnvironmentSwarmGF; // environment gets authority to manipulate the members directly
};


typedef std::tr1::unordered_map<EnvSwarmStateCell, std::vector<std::vector<EnvSwarmAction> >, EnvSwarmStateCell::Hash> MotionTemplate;



//typedef struct EnvQuadConfig_t
//{
//	uint env_extents[3]; // environment extents: [x, y, z]
//	EnvQuadStateCell q_i;  // initial state
//	EnvQuadStateCell q_f;  // final state
//
//	//the value at which and above which cells are obstacles in the maps sent from outside
//	//the default is defined above
//	uint obsthresh;
//
//
//
//} EnvQuadConfig;

class EnvCostMap
{
public:
    EnvCostMap() {};
    EnvCostMap(std::tr1::unordered_map<EnvQuadVoxel, uint, EnvQuadVoxelHash> costmap) {
	m_cost = costmap;
    }
    virtual ~EnvCostMap() {};
    bool collision_check(std::vector<EnvQuadVoxel> swath, EnvSwarmStateCell cur_state);
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

/** \brief this is just an example of environment and can be used (copy and paste) for creating a more complex environment
  */
class EnvironmentSwarm : public DiscreteSpaceInformation
{

public:
    EnvironmentSwarm() : m_hlut(NULL) {}; // all the init takes place in InitializeEnv()
    virtual ~EnvironmentSwarm();

	/** \brief see comments on the same function in the parent class
    */
	bool InitializeEnv(const char* sEnvFile); ///


	/** \brief see comments on the same function in the parent class
    */
	bool InitializeMDPCfg(MDPConfig *MDPCfg); ///


	/** \brief see comments on the same function in the parent class
    */
	int  GetFromToHeuristic(int FromStateID, int ToStateID); ///


	/** \brief see comments on the same function in the parent class
    */
	int  GetGoalHeuristic(int stateID); ///


	/** \brief see comments on the same function in the parent class
    */
	int  GetStartHeuristic(int stateID); ///


	/** \brief see comments on the same function in the parent class
    */
	void SetAllActionsandAllOutcomes(CMDPSTATE* state); ///


	/** \brief see comments on the same function in the parent class
    */
	void SetAllPreds(CMDPSTATE* state); ///


	/** \brief see comments on the same function in the parent class
    */
	virtual void GetSuccs(int SourceStateID, std::vector<int>* SuccIDV, std::vector<int>* CostV); ///


	/** \brief see comments on the same function in the parent class
    */
	void GetPreds(int TargetStateID, std::vector<int>* PredIDV, std::vector<int>* CostV); ///

	/** \brief see comments on the same function in the parent class
    */
	int	 SizeofCreatedEnv(); ///


	/** \brief see comments on the same function in the parent class
    */
	void PrintState(int stateID, bool bVerbose, FILE* fOut=NULL); ///


	/** \brief see comments on the same function in the parent class
    */
	void PrintEnv_Config(FILE* fOut); ///

	size_t state2id(const EnvSwarmStateCell & state_cell);
	void id2state(size_t state_id, EnvSwarmStateCell & state_cell);
	inline EnvSwarmStateCell id2state(size_t state_id)
	{
		EnvSwarmStateCell result;
		id2state(state_id, result);
		return result;
	}


	inline void set_goal(const EnvSwarmStateCell &state) {q_goal = state;}
	inline void set_start(const EnvSwarmStateCell &state) {q_start = state;}
	size_t *get_extents() {return m_extents;}
	
    int getMapoffset(uint dim);
    std::vector<double> getExecutionTime(std::vector<int> path);
    void PrintParam(std::vector<int> path);
    EnvSwarmAction GetAction(int start, int end);
    void set_map_extents(int mx, int my, int mz);
    void set_map_offset(int ox, int oy, int oz);
    void update_map_index(int x, int y, int z, uint cost);    
protected:

	virtual void ReadConfiguration(FILE* fCfg);
	bool ReadMotionTemplate(const std::string &template_file, MotionTemplate &motion_template);
	bool read_cost_map(const std::string &costmap_file);
	bool read_hlut(const std::string &hlut_file);
	//member variables
	//EnvQuadConfig m_env_config;

	/**
	 * These are full (unsigned) extents; it doesn't make sense to have
	 * half extents for non-position dimensions.
	 */
	size_t m_extents[NUM_DOF];

	/**
	 * Pre-computed strides for indexing into the multi-dimensional state cell grid
	 */
	size_t m_stride[NUM_DOF];

	/**
	 * A hash table of motion primitives, a motion template
	 */
	//size_t hash_fn(const EnvQuadStateCell &cell) {return 0;}
	MotionTemplate m_template;
	MotionTemplate m_template_inv;

	EnvCostMap m_costmap;

	//EnvQuadVoxel m_map_offset;

	//std::tr1::unordered_map<EnvQuadStateCell, uint, EnvQuadStateCell::Hash> m_hlut;


	EnvSwarmStateCell q_start;
	EnvSwarmStateCell q_goal;

	//boost::tuple<double, double, double> m_pos_resolution; // position sampling resolution (for error checking of template compatibility with the world)
	int **m_hlut;
};


#endif

