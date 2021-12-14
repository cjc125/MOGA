#include <random>
#include "mysetting.h"
#include "GA.h"
#include "GANode.h"
#include "FloatNode.h"

using namespace mysetting;

const unsigned int mysetting::DEFAULT_MAX_ITER = 1000;
const unsigned int mysetting::DEFAULT_NODE_NUM = 100;
const double mysetting::DEFAULT_CORSSOVER_PROBABILITY = 0.8;
const double mysetting::DEFAULT_MUTATION_PROBABILITY = 0.1;

GAType mysetting::gaType = GAType::_GA;
NodeType mysetting::nodeType = NodeType::_FLOAT_NODE;

pGA mysetting::getGAFromSetting(const mysetting::Setting &setting) {
	pGA ptr;
	switch (gaType) {
	case GAType::_GA:
		ptr = pGA(new GA(setting));
		break;
	default:
		break;
	}
	return ptr;
}

pGANode mysetting::getNodeFromSetting(const mysetting::Setting &setting)
{
	pGANode ptr = nullptr;
	switch (nodeType) {
	case NodeType::_FLOAT_NODE:
		ptr = pGANode(new FloatNode(setting));
		break;
	default:break;
	}
	return ptr;
}

std::random_device rd;
std::default_random_engine engine(rd());
std::uniform_real_distribution<double> realDistr(0.0, 1.0);
std::uniform_int_distribution<int> intDistr(0, 0x7fff);

double mysetting::getRandom01()
{
	return realDistr(engine);
}

int mysetting::getRandInt()
{
	return intDistr(engine);
}
