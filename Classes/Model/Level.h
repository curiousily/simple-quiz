#ifndef LEVEL_H_
#define LEVEL_H_

#include "cocos2d.h"
#include "Statement.h"
#include "StatementList.h"
#include "Rank.h"
#include <math.h>

USING_NS_CC;

class Level: public CCObject {

CC_SYNTHESIZE_READONLY(int, time, Time)

CC_SYNTHESIZE_READONLY(int, statementCount, StatementCount)

public:

	static Level* getCurrentLevel();

	int getNumber();
	int getCurrentStatementNumber();
	Statement* getStatement();
	int getRequiredCorrectAnswerCount();
	int getCorrectAnswerCount();

	void goToNextLevel();

	static void setOnLevelComplete(CCObject* target, SEL_CallFunc callback);
	static void setOnLevelFailed(CCObject* target, SEL_CallFunc callback);
	static void setOnCorrectAnswer(CCObject* target, SEL_CallFunc callback);
	static void setOnWrongAnswer(CCObject* target, SEL_CallFunc callback);
	static void setOnGameOver(CCObject* target, SEL_CallFunc callback);

	void onTruePressed();
	void onFalsePressed();
	void onTimesUp();

	virtual ~Level();

private:

	static const float MIN_REQUIRED_ANSWER_PERCENTAGE;
	static const int SECONDS_TO_ANSWER_PER_STATEMENT;
	static const int MIN_NUMBER_OF_STATEMENTS_PER_LEVEL;

	static const char* LEVEL_KEY;
	static const char* LEVEL_STATEMENT_KEY;
	static const char* CORRECT_ANSWERS_KEY;

	void init();
	void onLevelComplete();

	void goToNextStatement();

	void incrementCorrectStatements();
};

#endif /* LEVEL_H_ */
