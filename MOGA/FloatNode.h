#pragma once
#include "mysetting.h"
#include "GANode.h"

class FloatNode : public GANode {
protected:
	/*����������������еĵڼ�������
	�漰���������ۺ�����Լ��������*/
	unsigned int questionID;
	/*Դ����*/
	double value;
	/*����ֵ��ԽСԽ��*/
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