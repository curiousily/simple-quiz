#ifndef STATEMENT_H_
#define STATEMENT_H_

#include "cocos2d.h"

USING_NS_CC;

class Statement: public CCObject {

CC_SYNTHESIZE_READONLY(bool, isCorrect, Correct)

public:

	static Statement* create(const char* text, bool isCorrect);

	const char* getText();

	virtual ~Statement();

private:
	CCString* text;

	void initWithText(const char* text, bool isCorrect);

};

#endif /* STATEMENT_H_ */
