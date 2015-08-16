#include "Statement.h"

Statement* Statement::create(const char* text, bool isCorrect) {
	auto statement = new Statement();
	statement->initWithText(text, isCorrect);
	statement->autorelease();
	return statement;
}

Statement::~Statement() {
	CC_SAFE_RELEASE(text);
}

const char* Statement::getText() {
	return text->getCString();
}

void Statement::initWithText(const char* text, bool isCorrect) {
	this->text = CCString::create(text);
	this->text->retain();
	this->isCorrect = isCorrect;
}
