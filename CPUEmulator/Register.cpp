#include "Register.h"

void Register::setReg(string regName, int regValue) {
	string key = uppercase(regName);
	regs[key] = regValue;
}
int Register::getReg(string regName) {
	string key = uppercase(regName);
	bool isExist = regs.count(key) > 0;
	if (!isExist) {
		regs[key] = 0;
	}

	return regs[key];
}
vector<string> Register::getRegNames() {
	vector<string> v;
	for (map<string, int>::iterator it = regs.begin(); it != regs.end(); ++it) {
		v.push_back(it->first);
	}
	return v;
}

void Register::setLabel(string labelName, unsigned int lineNumber) {
	string key = uppercase(labelName);
	labels[key] = lineNumber;
}
unsigned int Register::getLabel(string labelName) {
	string key = uppercase(labelName);
	bool isExist = labels.count(key) > 0;
	if (!isExist) {
		throw new UndefinedLabelException(labelName);
	}

	return labels[key];
}
vector<string> Register::getLabelNames() {
	vector<string> v;
	for (map<string, unsigned int>::iterator it = labels.begin(); it != labels.end(); ++it) {
		v.push_back(it->first);
	}
	return v;
}