#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <exception>
#include <sstream>

#include "Exception.h"
#include "Register.h"
#include "Util.h"
#include "Operation.h"
#include "Tokenizer.h"

using namespace std;

static bool isLabel(string token);

class Process {
private:
	Register r;
	vector<Operation*> ops;

	Tokenizer Fetch(ifstream &stm);
	void Decode(Tokenizer tokens, istream *in = &cin, ostream *out = &cout);
public:
	Process(string sourceFileName, istream *in = &cin, ostream *out = &cout);
	~Process();
	void run();
	string dump();
};