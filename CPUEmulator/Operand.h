#pragma once
#include <string>
#include "Exception.h"
#include "Register.h"
using namespace std;

class Operand {
	bool isValue;
	bool isLabelb;
	string source;
	int value;
public:
	Operand();
	Operand(string source, bool isLabel = false);
	Operand(int value);
	static Operand* Build(string token);
	static bool isOperand(string token);
	int getValue(Register &reg);
	void setValue(Register &reg, int value);
	bool isReference();
	bool isLabel();
};