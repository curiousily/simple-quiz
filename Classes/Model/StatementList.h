#ifndef STATEMENTLIST_H_
#define STATEMENTLIST_H_

#include "cocos2d.h"
#include "Statement.h"
#include "../Model/Reader/StatementReader.h"

USING_NS_CC;

class StatementList: public CCObject {
public:

	Statement* getStatement();

	int getStatementCount();

	void markCurrentStatementComplete();

	static StatementList* getInstance();

	virtual ~StatementList();
private:

	static StatementList* create();

	void init();

	static const char* STATEMENT_KEY;

	CCArray* statements;
};

#endif /* STATEMENTLIST_H_ */
