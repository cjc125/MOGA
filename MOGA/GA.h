#pragma once
#include "GANode.h"
#include "mysetting.h"

/*最基本的GA，处理单目标无限制条件的优化问题*/
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

	/*初始化种群，设置个体初始值，并找出目前最好的解*/
	virtual void initialize();
	/*评价种群，更新目前最优解，保留历史最优*/
	virtual void getPrices();
	/*选择算子，采用规模为2的锦标赛选择算子*/
	virtual void selection();
	/*根据概率pc调用GANode的交叉算法进行两个个体一组的交叉操作，不保留父代*/
	virtual void crossover();
	/*根据概率pm调用GANode的变异算法进行个体的变异操作，不保留父代*/
	virtual void mutation();
	/*没有其他操作*/
	virtual void otherOperations();

public:
	/*进行算法参数设置，不对种群个体进行初始化*/
	GA(const mysetting::Setting &setting);
	virtual ~GA();
	
	/*对种群进行初始化，然后不断依次迭代直到到达迭代次数上限*/
	virtual void running();
	virtual std::vector<pGANode> getBestResult() const;
};