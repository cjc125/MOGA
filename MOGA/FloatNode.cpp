#include <sstream>
#include "FloatNode.h"
using mysetting::getRandom01;

typedef std::shared_ptr<FloatNode> pFloatNode;

static std::vector<double> upperbound = {
	1,2,3,4,5
};

static std::vector<double> lowerbound = {
	-1,-2,-3,-4,-5
};

double f1(const double x);
double f2(const double x);
double f3(const double x);
double f4(const double x);
double f5(const double x);

typedef double (*func)(const double x);
static std::vector<func> funcs = { f1,f2,f3,f4,f5 };

void FloatNode::evaluate()
{
	this->price = (*funcs[this->questionID])(this->value);
}

FloatNode::FloatNode(const mysetting::Setting & setting)
{
	if (setting.questionID > 0 && setting.questionID < upperbound.size()) {
		this->questionID = setting.questionID;
	}
	else {
		this->questionID = 0u;
	}
	this->value = 0.0;
	this->price = 0.0;
}

FloatNode::~FloatNode()
{
}

bool FloatNode::initialize()
{
	this->value = lowerbound[this->questionID]
		+ getRandom01() * upperbound[this->questionID];
	this->evaluate();
	return true;
}

std::vector<pGANode> FloatNode::crossover(const pGANode pAnotherNode)
{
	auto panother = std::dynamic_pointer_cast<FloatNode>(pAnotherNode);
	double rate = getRandom01();

	double sum = this->value + panother->value;
	double left = sum * rate;
	double right = sum - left;

	if (left > upperbound[this->questionID]) {
		left = upperbound[this->questionID];
	}
	else if (left < lowerbound[this->questionID]) {
		left = lowerbound[this->questionID];
	}
	if (right > upperbound[this->questionID]) {
		right = upperbound[this->questionID];
	}
	else if (right < lowerbound[this->questionID]) {
		right = lowerbound[this->questionID];
	}

	auto pleft = pFloatNode(new FloatNode(*this));
	pleft->value = left;
	pleft->evaluate();
	auto pright = pFloatNode(new FloatNode(*this));
	pright->value = right;
	pright->evaluate();
	std::vector<pGANode> result = { pleft, pright };
	return result;
}

pGANode FloatNode::mutation()
{
	double newVal = lowerbound[this->questionID]
		+ getRandom01() * upperbound[this->questionID];
	auto presult = pFloatNode(new FloatNode(*this));
	presult->value = newVal;
	presult->evaluate();
	return presult;
}

std::vector<double> FloatNode::getPrices() const
{
	return std::vector<double> {this->price};
}

std::vector<double> FloatNode::distanceOfConstraint()
{
	return std::vector<double> {0};
}

std::string FloatNode::sourceDataJSON() const
{
	std::stringstream ss;
	ss << "" << this->value;
	return ss.str();
}

double f1(const double x)
{
	return x * x;
}

double f2(const double x)
{
	return 3 * x * x - 20 * x;
}

double f3(const double x)
{
	return abs(x);
}

double f4(const double x)
{
	return log(abs(x) + 1);
}

double f5(const double x)
{
	return exp(x + 1);
}
