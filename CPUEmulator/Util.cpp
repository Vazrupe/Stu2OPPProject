#include "Util.h"

string trim(string source) {
	return ltrim(rtrim(source));
}

string ltrim(string source) {
	unsigned int i;
	for (i = 0; i < source.length(); i++) {
		bool isSpace = (source[i] == ' ') ||
			(source[i] == '\r') ||
			(source[i] == '\n');
		if (!isSpace) break;
	}
	return source.substr(i);
}

string rtrim(string source) {
	unsigned int i;
	for (i = source.length() - 1; i >= 0; i--) {
		bool isSpace = (source[i] == ' ') ||
			(source[i] == '\r') ||
			(source[i] == '\n');
		if (!isSpace) break;
	}
	return source.substr(0, i);
}

string uppercase(string source) {
	transform(source.begin(), source.end(), source.begin(), ::toupper);
	return source;
}

string lowercase(string source) {
	transform(source.begin(), source.end(), source.begin(), ::tolower);
	return source;
}

bool isNumberic(const string& source) {
	bool rs = true;

	int sign = (source[0] == '+') || (source[0] == '-');

	bool isOctMode = source[0 + sign] == '0';
	bool isHexMode = isOctMode
		&& ((source[1 + sign] == 'x') || (source[1 + sign] == 'X'));

	string checkChars = "0123456789";
	unsigned int checkPos = 0;
	if (isHexMode) {
		checkChars = "0123456789abcdefABCDEF";
		checkPos = sign + 2;
	}
	else if (isOctMode) {
		checkChars = "01234567";
		checkPos = sign + 1;
	}

	for (unsigned int i = checkPos; i < source.length(); i++) {
		size_t f = checkChars.find(source[i]);
		if (f == string::npos) {
			rs = false;
			break;
		}
	}

	return rs;
}