#include "Formatter.h"

const char* Formatter::toString(const char* format, int param) {
	return CCString::createWithFormat(format, param)->getCString();
}

const char* Formatter::toString(const char* format, int param1, int param2) {
	return CCString::createWithFormat(format, param1, param2)->getCString();
}

const char* Formatter::toString(const char* format, const char* param) {
	return CCString::createWithFormat(format, param)->getCString();
}

Formatter::~Formatter() {
}

