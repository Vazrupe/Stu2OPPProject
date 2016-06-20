#include "Process.h"

static bool isLabel(string token) {
	return (token[token.length() - 1] == ':');
}

Tokenizer Process::Fetch(ifstream &stm) {
	Tokenizer tokens(stm, " \t\r\n,");
	return tokens;
}

void Process::Decode(Tokenizer tokens, istream *in, ostream *out) {
	OneOpOperationFactory oneFac;
	TwoOpOperationFactory twoFac;
	ThreeOpOperationFactory threeFac;
	istreamOpOperationFactory istmFac;
	ostreamOpOperationFactory ostmFac;

	for (unsigned int i = 0; i < tokens.size(); i++) {
		try {
			string token = uppercase(tokens.getToken(i));

			// Check Token Type is Label
			if (isLabel(token)) {
				r.setLabel(token.substr(0, token.size() - 1), ops.size() - 1);
				continue;
			}

			// Check Token Type is Operation
			if (Operation::isOperation(token)) {
				if (OneOpOperation::isOperation(token)) {
					Operand *op = Operand::Build(tokens.getToken(i + 1));

					OneOpOperation* oper = oneFac.OneOpOperationBuild(token, op);
					ops.push_back((Operation*)oper);

					i += 1;
					continue;
				}
				else if (TwoOpOperation::isOperation(token)) {
					Operand *op1 = Operand::Build(tokens.getToken(i + 1));
					Operand *op2 = Operand::Build(tokens.getToken(i + 2));

					TwoOpOperation* oper = twoFac.TwoOpOperationBuild(token, op1, op2);
					ops.push_back((Operation*)oper);

					i += 2;
					continue;
				}
				else if (ThreeOpOperation::isOperation(token)) {
					Operand *op1 = Operand::Build(tokens.getToken(i + 1));
					Operand *op2 = Operand::Build(tokens.getToken(i + 2));
					Operand *op3 = Operand::Build(tokens.getToken(i + 3));

					ThreeOpOperation* oper = threeFac.ThreeOpOperationBuild(token, op1, op2, op3);
					ops.push_back((Operation*)oper);

					i += 3;
					continue;
				}
				else if (istreamOpOperation::isOperation(token)) {
					Operand *op = Operand::Build(tokens.getToken(i + 1));

					istreamOpOperation* oper = istmFac.istreamOpOperationBuild(token, op, in);
					ops.push_back((Operation*)oper);

					i += 1;
					continue;
				}
				else if (ostreamOpOperation::isOperation(token)) {
					Operand *op = Operand::Build(tokens.getToken(i + 1));

					ostreamOpOperation* oper = ostmFac.ostreamOpOperationBuild(token, op, out);
					ops.push_back((Operation*)oper);

					i += 1;
					continue;
				}
			}

			// Undefined Token
			throw new UndefinedTokenException(token);
		}
		catch (Exception *e) {
			throw e;
		}
	}
}

Process::Process(string sourceFileName, istream *in, ostream *out) {
	try {
		r.setReg("PC", 0);

		ifstream source;
		source.open(sourceFileName);

		if (!source) {
			throw new FailedOpenFileException(sourceFileName);
		}

		Tokenizer tokens = Fetch(source);

		source.close();

		Decode(tokens, in, out);
	}
	catch (Exception *e) {
		throw e;
	}
}

Process::~Process() {
	for (unsigned int i = 0; i < ops.size(); i++)
		delete ops.at(i);
}

void Process::run() {
	try {
		while ((unsigned int)r.getReg("PC") < ops.size())
			ops.at(r.getReg("PC"))->run(r);
	}
	catch (Exception *e) {
		throw e;
	}
}

string Process::dump() {
	string dmp = "";

	dmp += "REGISTERs:\n";
	vector<string> regNames = r.getRegNames();
	for (unsigned int i = 0; i < regNames.size(); i++) {
		string name = regNames.at(i);
		dmp += " - $" + name + " = " + to_string(r.getReg(name)) + "\n";
	}

	dmp += "\n";

	dmp += "LABELs:\n";
	vector<string> labelNames = r.getLabelNames();
	for (unsigned int i = 0; i < labelNames.size(); i++) {
		string name = labelNames.at(i);
		dmp += " - $" + name + " => Op(" + to_string(r.getLabel(name)) + ")\n";
	}

	return dmp;
}