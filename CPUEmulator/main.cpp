#include <iostream>
#include <fstream>
#include <string>

#include "Process.h"
using namespace std;

int main(int argc, char *args[]) {
	bool okRunnable = true;
	string sourceFile = "";

	bool existInFile = false;
	string inFile = "";
	bool existOutFile = false;
	string outFile = "";

	bool dump = false;
	// Argument Parsing
	for (int i = 1; i < argc; i++) {
		bool isFlag = args[i][0] == '-';
		if (isFlag) {
			if (args[i][1] == 'i') {
				inFile = args[i + 1];
				existInFile = true;
				i++;
				continue;
			}
			if (args[i][1] == 'o') {
				outFile = args[i + 1];
				existOutFile = true;
				i++;
				continue;
			}
			if (args[i][1] == 'd') {
				dump = true;
				continue;
			}
		}
		else {
			sourceFile = args[i];
		}
	}

	if (existInFile && existOutFile  && (inFile == outFile)) {
		cout << "Compare In stream And Out stream" << endl;
		return 0;
	}

	// Stream open
	istream *in;
	if (existInFile) {
		in = new ifstream(inFile);

		if (!in) {
			cout << "In File Open Failed" << endl;
			return 0;
		}
	}
	else {
		in = &cin;
	}

	ostream *out;
	if (existOutFile) {
		out = new ofstream(outFile);

		if (!out) {
			cout << "Out File Open Failed" << endl;
			return 0;
		}
	}
	else {
		out = &cout;
	}


	// init
	Process *p;
	try {
		p = new Process(sourceFile, in, out);
	}
	catch (Exception *e) {
		cout << e->what() << endl;
		if (in != &cin) ((ifstream*)in)->close();
		if (out != &cout) ((ofstream*)out)->close();
		return 0;
	}

	// run
	try {
		p->run();
	}
	catch (Exception *e) {
		cout << e->what() << endl;
		cout << p->dump() << endl;

		delete p;
		if (in != &cin) ((ifstream*)in)->close();
		if (out != &cout) ((ofstream*)out)->close();
		return 0;
	}
	
	if (dump) {
		cout << endl << endl;
		cout << p->dump() << endl;
	}

	delete p;
	if (in != &cin) ((ifstream*)in)->close();
	if (out != &cout) ((ofstream*)out)->close();
	
	return 0;
}