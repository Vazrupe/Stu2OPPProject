#pragma once

#include <fstream>
#include <iostream> 
#include <vector>
#include <string>
#include "Exception.h"
#include "Util.h"
using namespace std;

class Tokenizer {
private:
	vector<string> tokens;
public:
	Tokenizer(ifstream &source, string delimiters = " ");
	string getToken(unsigned int pos);
	unsigned int size();
};
