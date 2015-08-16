#ifndef STATEMENTREADER_H_
#define STATEMENTREADER_H_

#include "cocos2d.h"
#include "../Statement.h"
#include "../../lib/rapidjson/document.h"

USING_NS_CC;
using namespace rapidjson;

class StatementReader {
public:

	static CCArray* read(const char* fileName);

	virtual ~StatementReader();
};

#endif /* STATEMENTREADER_H_ */
