#pragma once
#include <memory>

class GA;
class GANode;

typedef std::shared_ptr<GA> pGA;
typedef std::shared_ptr<GANode> pGANode;

namespace mysetting {

	extern const unsigned int DEFAULT_MAX_ITER;
	extern const unsigned int DEFAULT_NODE_NUM;
	extern const double DEFAULT_CORSSOVER_PROBABILITY;
	extern const double DEFAULT_MUTATION_PROBABILITY;

	typedef struct {
		unsigned int nodeNum = 0u;
		unsigned int maxIter = 0u;
		unsigned int questionID = 0u;
		double pc = 0;
		double pm = 0;
	} Setting;

	typedef enum { _GA } GAType;
	typedef enum { _FLOAT_NODE } NodeType;
	extern GAType gaType;
	extern NodeType nodeType;

	pGA getGAFromSetting(const mysetting::Setting &setting);
	pGANode getNodeFromSetting(const mysetting::Setting &setting);

	double getRandom01();
	int getRandInt();
}