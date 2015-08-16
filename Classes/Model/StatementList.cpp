#include "StatementList.h"

const char* StatementList::STATEMENT_KEY = "statement_key";

static StatementList *statementList = NULL;

Statement* StatementList::getStatement() {
	auto userDefaults = CCUserDefault::sharedUserDefault();
	int currentStatement = userDefaults->getIntegerForKey(STATEMENT_KEY, 0);
	if (currentStatement >= statements->count()) {
		userDefaults->setIntegerForKey(STATEMENT_KEY, 0);
		userDefaults->flush();
		currentStatement = 0;
	}
	return (Statement*) statements->objectAtIndex(currentStatement);
}

StatementList* StatementList::create() {
	StatementList* list = new StatementList();
	list->init();
	return list;
}

void StatementList::markCurrentStatementComplete() {
	auto userDefaults = CCUserDefault::sharedUserDefault();
	int currentStatement = userDefaults->getIntegerForKey(STATEMENT_KEY, 0);
	userDefaults->setIntegerForKey(STATEMENT_KEY, currentStatement + 1);
	userDefaults->flush();
}

StatementList* StatementList::getInstance() {
	if (statementList == NULL) {
		statementList = StatementList::create();
	}
	return statementList;
}

int StatementList::getStatementCount() {
	return statements->count();
}

void StatementList::init() {
	statements = StatementReader::read("Data/statements.json");
	statements->retain();
}

StatementList::~StatementList() {
	statements->release();
}
