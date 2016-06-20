#include "Exception.h"

Exception::Exception(const string &name) : name(name) {}
string Exception::what() {
	return name + ", " + message();
}
string Exception::message() {
	return "";
}

OutofRangeException::OutofRangeException(int index, unsigned int size) 
	: Exception("OutofRangeException"), index(index), size(size) { 
}
string OutofRangeException::message() {
	string msg = "Index Out of Range `"
		+ to_string(index)
		+ " < "
		+ to_string(size)
		+ "`";
	return msg;
}

FailedOpenFileException::FailedOpenFileException(string filename, string option) 
	: Exception("FailedOpenFileException"), filename(filename), option(option) {
}
string FailedOpenFileException::message() {
	string msg = "file: `" + filename + "` " + option + " Mode Open Failed";
	return msg;
}

UndefinedLabelException::UndefinedLabelException(string labelName) : Exception("UndefinedLabelException"), labelName(labelName) { }
string UndefinedLabelException::message() {
	return "Undefined Label Name `" + labelName + "`";
}

UndefineOperationException::UndefineOperationException(string token) : Exception("UndefineOperationException"), token(token) { }
string UndefineOperationException::message() {
	return "Undefined Operation `" + token + "`";
}

NotReferenceDestinationException::NotReferenceDestinationException() : Exception("NotReferenceDestinationException") { }
string NotReferenceDestinationException::message() {
	return "Destination Only Register";
}

UnvalidOperandException::UnvalidOperandException(string token) : Exception("UnvalidOperandException"), token(token) { }
string UnvalidOperandException::message() {
	return "This Token Unvalid Operand `" + token + "`";
}

UndefinedTokenException::UndefinedTokenException(string token) : Exception("UndefinedTokenException"), token(token) { }
string UndefinedTokenException::message() {
	string msg = "Undefined Token `" + token + "`";
	return msg;
}

ZeroDivisionException::ZeroDivisionException() : Exception("ZeroDivisionException") { }
string ZeroDivisionException::message() {
	return "Denominator is Zero";
}