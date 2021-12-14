#pragma once
#include "mysetting.h"
#include "GANode.h"

class FloatNode : public GANode {
protected:
	/*处理的是问题数组中的第几个问题
	涉及定义域、评价函数、约束条件等*/
	unsigned int questionID;
	/*源数据*/
	double value;
	/*评价值，越小越好*/
	double price;

	void evaluate() override;
public:
	FloatNode(const mysetting::Setting &setting);
	~FloatNode();
	
	bool initialize() override;
	std::vector<pGANode> crossover(const pGANode pAnotherNode) override;
	pGANode mutation() override;
	std::vector<double> getPrices() const override;
	std::vector<double> distanceOfConstraint() override;
	std::string sourceDataJSON() const override;
};