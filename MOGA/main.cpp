#include <iostream>
#include "mysetting.h"
#include "GA.h"
#include "FloatNode.h"

using std::cout;
using std::endl;


int main() {
	for (auto i = 0u; i < 5; ++i) {
		mysetting::gaType = mysetting::GAType::_GA;
		mysetting::nodeType = mysetting::NodeType::_FLOAT_NODE;

		mysetting::Setting setting;
		setting.maxIter = 100;
		setting.nodeNum = 20;
		setting.pc = 0.8;
		setting.pm = 0.1;
		setting.questionID = i;

		auto GAptr = mysetting::getGAFromSetting(setting);
		GAptr->running();
		auto best = GAptr->getBestResult()[0];
		cout << "best node: " << best->sourceDataJSON() << endl;
		cout << "best value: " << best->getPrices()[0] << endl;
	}
}

