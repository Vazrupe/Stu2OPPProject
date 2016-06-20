#include "Tokenizer.h"

Tokenizer::Tokenizer(ifstream &source, string delimiters) {
	char c;
	string tokenString = "";
	unsigned int fnd;
	do {
		c = source.get();
		fnd = delimiters.find(c);
		bool isDelim = (fnd != string::npos) || (c == EOF);
		if (isDelim) {
			if (tokenString.length() > 0) {
				this->tokens.push_back(tokenString);

				tokenString = "";
			}
			continue;
		}

		tokenString += c;
	} while (c != EOF);
}

string Tokenizer::getToken(unsigned int pos) {
	bool outOfRange = (tokens.size() - 1) < pos;
	if (outOfRange) {
		throw new OutofRangeException((int)pos, tokens.size());
	}

	return tokens.at(pos);
}

unsigned int Tokenizer::size() {
	return tokens.size();
}