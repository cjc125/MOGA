#pragma once
#include <vector>
#include <string>
#include "mysetting.h"

class GANode {
protected:
	/*���������ۺ���*/
	virtual void evaluate() = 0;
public:

	/*�ڵ��ʼ��*/
	virtual bool initialize() = 0;

	/*�����ڵ㽻�����飬���������½ڵ��ָ��*/
	virtual std::vector<pGANode> crossover(const pGANode pAnotherNode) = 0;
	/*���ڵ���죬����һ���½ڵ��ָ��*/
	virtual pGANode mutation() = 0;

	/*
	���۽ڵ㣬����һ�����飬����ֵԽСԽ�ã�ÿһ��ֵ����һ���Ż�Ŀ�꣬
	�ڵ�Ŀ�������������СΪ1
	ʵ�ֻ�����ƣ�ԭ���ݲ��������¶�ε�������������ظ�����
	*/
	virtual std::vector<double> getPrices() const = 0;

	/*
	�ڵ�������Լ�������ľ��룬����һ�����飬�����ֵΪ0��������Լ��������
	ֵԽ�����ƫ��Լ������ԽԶ��ֵ�������������Ǽ���ֵ��Լ���Ĳ�ֵ�ľ���ֵ��
	ÿһ��ֵ����һ��Լ������
	*/
	virtual std::vector<double> distanceOfConstraint() = 0;

	/*
	���ؽڵ��ԭʼ���ݡ�
	����ԭʼ������̬�޷�ȷ�������ý�Դ����ת��Ϊ�ַ����ķ�ʽ����
	��һ������Ҫ��main.cpp�ж�ÿ����������зֱ�����ֱ�Ӵ�ӡ
	*/
	virtual std::string sourceDataJSON() const = 0;
};