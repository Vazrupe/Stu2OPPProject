#include "Operand.h"

Operand::Operand() {
	this->isValue = true;
	this->isLabelb = false;
	this->source = "tmp";
	this->value = 0;
}

Operand::Operand(string source, bool isLabelb) : Operand() {
	this->source = source;

	this->isValue = false;
	this->isLabelb = isLabelb;
}

Operand::Operand(int value) : Operand() {
	this->value = value;
}

Operand* Operand::Build(string token) {
	if (token[0] == '$')
		return new Operand(token.substr(1));

	if (token[0] == '@')
		return new Operand(token.substr(1), true);

	if (isNumberic(token))
		return new Operand(stoi(token));

	bool isChar = (token.length() == 3) && (token[0] == '\'') && (token[2] == '\'');
	if (isChar)
		return new Operand(token[1]);

	throw new UnvalidOperandException(token);
}

bool Operand::isOperand(string token) {
	// Register
	if (token[0] == '$')
		return true;

	// Number
	if (isNumberic(token))
		return true;

	// Label Operand
	if (token[0] == '@')
		return true;

	// Char
	bool isChar = (token.length() == 3) && (token[0] == '\'') && (token[2] == '\'');
	if (isChar)
		return true;

	return false;
}

int Operand::getValue(Register &reg) {
	if (isValue) {
		return value;
	}
	if (isLabelb) {
		try {
			return reg.getLabel(source);
		}
		catch (Exception *e) {
			throw e;
		}
	}

	return reg.getReg(source);
}

void Operand::setValue(Register &reg, int value) {
	if (!this->isReference()) {
		throw new NotReferenceDestinationException();
	}

	reg.setReg(this->source, value);
}

bool Operand::isReference() {
	return !(isValue || isLabelb);
}
bool Operand::isLabel() {
	return isLabelb;
}