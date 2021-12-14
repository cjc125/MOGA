#include <iostream>
#include "GA.h"
using mysetting::getRandom01;
using mysetting::getRandInt;
using std::cout;
using std::endl;

void GA::initialize()
{
	this->pNodes.clear();
	this->pBestNodes.clear();
	pGANode pbest = nullptr;
	double bestVal = 0.0;
	for (unsigned int i = 0; i < this->nodeNum; ++i) {
		auto pnode = mysetting::getNodeFromSetting(this->setting);
		pnode->initialize();
		double value = pnode->getPrices()[0];
		if (pbest == nullptr || bestVal > value) {
			pbest = pnode;
			bestVal = value;
		}
		this->pNodes.push_back(pnode);
	}
	this->pBestNodes.push_back(pbest);
}

void GA::getPrices()
{
	pGANode pbest = this->pBestNodes[0];
	double bestVal = pbest->getPrices()[0];
	for (unsigned int i = 0; i < this->nodeNum; ++i) {
		auto pnode = this->pNodes[i];
		double value = pnode->getPrices()[0];
		if (pbest == nullptr || bestVal > value) {
			pbest = pnode;
			bestVal = value;
		}
	}
	this->pBestNodes[0] = pbest;
}

void GA::selection()
{
	std::vector<pGANode> nextGen;
	unsigned int curSize = this->pNodes.size();
	while (nextGen.size() < this->nodeNum) {
		auto pleft = this->pNodes[getRandInt() % curSize];
		auto pright = this->pNodes[getRandInt() % curSize];
		if (pleft->getPrices() < pright->getPrices()) {
			nextGen.push_back(pleft);
		}
		else {
			nextGen.push_back(pright);
		}
	}
	this->pNodes = nextGen;
}

void GA::crossover()
{
	std::vector<pGANode> waiting;
	std::vector<pGANode> result;
	for (auto ptr : this->pNodes) {
		if (getRandom01() < this->pc) {
			waiting.push_back(ptr);
		}
		else {
			result.push_back(ptr);
		}
	}
	if (waiting.size() % 2 > 0) {
		result.push_back(waiting.back());
		waiting.pop_back();
	}
	for (auto i = 0u; i < waiting.size(); i += 2) {
		auto children = waiting[i]->crossover(waiting[i + 1]);
		result.push_back(children[0]);
		result.push_back(children[1]);
	}
	this->pNodes = result;
}

void GA::mutation()
{
	for (auto i = 0u; i < this->pNodes.size(); ++i) {
		if (getRandom01() < this->pm) {
			this->pNodes[i] = this->pNodes[i]->mutation();
		}
	}
}

void GA::otherOperations()
{
}

GA::GA(const mysetting::Setting & setting):setting(setting)
{
	if (setting.maxIter > 0u) {
		this->maxIter = setting.maxIter;
	}
	else {
		this->maxIter = mysetting::DEFAULT_MAX_ITER;
	}
	if (setting.nodeNum > 0u) {
		this->nodeNum = setting.nodeNum;
	}
	else {
		this->nodeNum = mysetting::DEFAULT_NODE_NUM;
	}
	if (setting.pc > 0.0 && setting.pc <= 1.0) {
		this->pc = setting.pc;
	}
	else {
		this->pc = mysetting::DEFAULT_CORSSOVER_PROBABILITY;
	}
	if (setting.pm > 0.0 && setting.pm < 1.0) {
		this->pm = setting.pm;
	}
	else {
		this->pm = mysetting::DEFAULT_MUTATION_PROBABILITY;
	}
}

GA::~GA()
{
}

void GA::running()
{
	this->initialize();
	this->getPrices();
	for (auto i = 0u; i < this->maxIter; ++i) {
		cout << "iter: " << i << " : ";
		this->crossover();
		this->mutation();
		this->getPrices();
		this->selection();
		cout << " best: " << this->pBestNodes[0]->getPrices()[0] << endl;
	}
}

std::vector<pGANode> GA::getBestResult() const
{
	return this->pBestNodes;
}
