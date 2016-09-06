//#include <boost/tuple/tuple.hpp>
#include <vector>
#include <tr1/unordered_map>
#include <ostream>
#include <boost/tuple/tuple.hpp> // tuple for QuadVoxel
#include <yaml-cpp/yaml.h> 
// declaring this up here because EnvQuadAction needs this for the >> operator


typedef unsigned int uint;

typedef boost::tuple<int, int, int> QuadVoxel;
const YAML::Node& operator>> (const YAML::Node& yaml_node, QuadVoxel &voxel);
QuadVoxel operator+ (const QuadVoxel &lhs, const QuadVoxel &rhs);


typedef enum {
	X = 0,
	Y,
	Z,
	V,
	NUM_DOF
} DimList_t;

class QuadStateCell
{
public:
	QuadStateCell() {m_data.assign(NUM_DOF+1, 0);}
	QuadStateCell(const QuadStateCell &other) {m_data = other.m_data;}
	QuadStateCell(std::vector<int>::iterator first, std::vector<int>::iterator last);
	QuadStateCell(int* first, int* last);
    
	virtual ~QuadStateCell() {};
    
	inline void assign(int* first, int* last) {m_data.assign(first, last); assert(m_data.size() == NUM_DOF+1);}
    
	inline int & get(size_t dim) {return m_data.at(dim);}
	inline const int & get(size_t dim) const {return m_data.at(dim);}
    
	/* useful when we need to use this state as the key in the template */
	// operators
	bool operator== (const QuadStateCell &other) const;
	QuadStateCell operator= (const QuadStateCell &other) {m_data = other.m_data; return *this;}
	QuadVoxel operator+ (const QuadVoxel &other);
    
	// i/o:
	void print(std::ostream &output) const;
	friend std::ostream& operator<< (std::ostream &output, \
									 const QuadStateCell &state_cell)
    {state_cell.print(output); return output;}
    
	// Own hash function, useful for the stl::unordered_map
	class Hash
	{
	public:
		size_t operator()(const QuadStateCell &val) const;
	};
    
protected:
    
	std::vector<int> m_data;

	friend struct YAML::convert<QuadStateCell>;
};


class QuadAction
{
public:
	QuadAction() {};
	virtual ~QuadAction() {};

	friend std::ostream& operator<< (std::ostream &output, const QuadAction &action);
	friend const YAML::Node& operator>> (const YAML::Node& yaml_node, QuadAction &action);

    class QuadParam
    {
    public:
        std::vector<double> x_coeffs;
        std::vector<double> y_coeffs;
        std::vector<double> z_coeffs;
        double time;
    };

    friend std::ostream& operator<< (std::ostream &output, const QuadAction::QuadParam &coeff);
    QuadParam getCoeffs();
    std::vector<QuadVoxel> getSwath();
protected:
	uint index;
	uint cost;
	QuadStateCell q_f;  // final state
	QuadParam coeffs;
	std::vector<QuadVoxel> swath;

	friend class QuadHandler; // environment gets authority to manipulate the members directly
	friend struct YAML::convert<QuadAction>;
};


typedef std::tr1::unordered_map<QuadStateCell, std::vector<std::vector<QuadAction> >, QuadStateCell::Hash> MotionTemplate;


/** \brief this is just an example of environment and can be used (copy and paste) for creating a more complex environment
  */
class QuadHandler
{

public:
	bool ReadMotionTemplate(const std::string &template_file, MotionTemplate &motion_template);
};