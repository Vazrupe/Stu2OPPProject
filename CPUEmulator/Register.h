#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "Exception.h"
#include "Util.h"
using namespace std;

class Register {
private:
	map<string, int> regs;
	map<string, unsigned int> labels;
public:
	void setReg(string regName, int regValue);
	int getReg(string regName);
	vector<string> getRegNames();
	void setLabel(string labelName, unsigned int lineNumber);
	unsigned int getLabel(string labelName);
	vector<string> getLabelNames();
};