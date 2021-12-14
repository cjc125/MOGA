#pragma once
#include "GANode.h"
#include "mysetting.h"

/*�������GA������Ŀ���������������Ż�����*/
class GA {
protected:
	int nodeNum;
	int maxIter;
	int curIter;
	double pc;	//crossover probability
	double pm;	//mutation probability
	std::vector<pGANode> pNodes;
	std::vector<pGANode> pBestNodes;
	mysetting::Setting setting;

	/*��ʼ����Ⱥ�����ø����ʼֵ�����ҳ�Ŀǰ��õĽ�*/
	virtual void initialize();
	/*������Ⱥ������Ŀǰ���Ž⣬������ʷ����*/
	virtual void getPrices();
	/*ѡ�����ӣ����ù�ģΪ2�Ľ�����ѡ������*/
	virtual void selection();
	/*���ݸ���pc����GANode�Ľ����㷨������������һ��Ľ������������������*/
	virtual void crossover();
	/*���ݸ���pm����GANode�ı����㷨���и���ı������������������*/
	virtual void mutation();
	/*û����������*/
	virtual void otherOperations();

public:
	/*�����㷨�������ã�������Ⱥ������г�ʼ��*/
	GA(const mysetting::Setting &setting);
	virtual ~GA();
	
	/*����Ⱥ���г�ʼ����Ȼ�󲻶����ε���ֱ�����������������*/
	virtual void running();
	virtual std::vector<pGANode> getBestResult() const;
};