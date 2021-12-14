#pragma once
#include <vector>
#include <string>
#include "mysetting.h"

class GANode {
protected:
	/*真正的评价函数*/
	virtual void evaluate() = 0;
public:

	/*节点初始化*/
	virtual bool initialize() = 0;

	/*两个节点交叉重组，返回两个新节点的指针*/
	virtual std::vector<pGANode> crossover(const pGANode pAnotherNode) = 0;
	/*单节点变异，返回一个新节点的指针*/
	virtual pGANode mutation() = 0;

	/*
	评价节点，返回一个数组，评价值越小越好，每一个值代表一个优化目标，
	在单目标问题中数组大小为1
	实现缓存机制，原数据不变的情况下多次调用这个函数不重复计算
	*/
	virtual std::vector<double> getPrices() const = 0;

	/*
	节点与所有约束条件的距离，返回一个数组，里面的值为0则代表符合约束条件，
	值越大表明偏离约束条件越远，值都是正数并且是计算值与约束的差值的绝对值，
	每一个值代表一个约束条件
	*/
	virtual std::vector<double> distanceOfConstraint() = 0;

	/*
	返回节点的原始数据。
	由于原始数据形态无法确定，采用将源数据转化为字符串的方式返回
	这一部分需要在main.cpp中对每种衍生类进行分别处理，或直接打印
	*/
	virtual std::string sourceDataJSON() const = 0;
};