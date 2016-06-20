#pragma once
#include <string>
using namespace std;

class Exception {
	string name;

	virtual string message();
public:
	Exception(const string &name = "");
	virtual string what();
};

class OutofRangeException : public Exception {
	int index;
	unsigned size;

	string message();
public:
	OutofRangeException(int index, unsigned int size);
};

class FailedOpenFileException : public Exception {
private:
	string filename;
	string option;

	string message();
public:
	FailedOpenFileException(string filename, string option = "read");
};

class UndefinedLabelException : public Exception {
	string labelName;

	string message();
public:
	UndefinedLabelException(string labelName);
};

class UndefineOperationException : public Exception {
	string token;

	string message();
public:
	UndefineOperationException(string token);
};

class NotReferenceDestinationException : public Exception {
	string message();
public:
	NotReferenceDestinationException();
};

class UnvalidOperandException : public Exception {
	string token;

	string message();
public:
	UnvalidOperandException(string token);
};

class UndefinedTokenException : public Exception {
	string token;

	string message();
public:
	UndefinedTokenException(string token);
};

class ZeroDivisionException : public Exception {
	string message();
public:
	ZeroDivisionException();
};