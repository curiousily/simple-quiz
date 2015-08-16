#include "Level.h"

const float Level::MIN_REQUIRED_ANSWER_PERCENTAGE = 0.4f;
const int Level::SECONDS_TO_ANSWER_PER_STATEMENT = 10;
const int Level::MIN_NUMBER_OF_STATEMENTS_PER_LEVEL = 2;

const char* Level::LEVEL_KEY = "level_key";
const char* Level::LEVEL_STATEMENT_KEY = "level_statement_key";
const char* Level::CORRECT_ANSWERS_KEY = "correct_answers_key";

static CCCallFunc* onLevelCompleteCallback;
static CCCallFunc* onLevelFailedCallback;
static CCCallFunc* onCorrectAnswerCallback;
static CCCallFunc* onWrongAnswerCallback;
static CCCallFunc* onGameOverCallback;

Level* Level::getCurrentLevel() {
	auto level = new Level();
	level->init();
	level->autorelease();
	return level;
}

void Level::init() {
	statementCount = getNumber() + MIN_NUMBER_OF_STATEMENTS_PER_LEVEL;
	time = SECONDS_TO_ANSWER_PER_STATEMENT * statementCount - getNumber();
}

void Level::setOnLevelComplete(CCObject* target, SEL_CallFunc callback) {
	onLevelCompleteCallback = CCCallFunc::create(target, callback);
	onLevelCompleteCallback->retain();
}

void Level::setOnLevelFailed(CCObject* target, SEL_CallFunc callback) {
	onLevelFailedCallback = CCCallFunc::create(target, callback);
	onLevelFailedCallback->retain();
}

void Level::setOnGameOver(CCObject* target, SEL_CallFunc callback) {
	onGameOverCallback = CCCallFunc::create(target, callback);
	onGameOverCallback->retain();
}

void Level::setOnCorrectAnswer(CCObject* target, SEL_CallFunc callback) {
	onCorrectAnswerCallback = CCCallFunc::create(target, callback);
	onCorrectAnswerCallback->retain();
}

void Level::setOnWrongAnswer(CCObject* target, SEL_CallFunc callback) {
	onWrongAnswerCallback = CCCallFunc::create(target, callback);
	onWrongAnswerCallback->retain();
}

int Level::getNumber() {
	auto userDefaults = CCUserDefault::sharedUserDefault();
	return userDefaults->getIntegerForKey(LEVEL_KEY, 1);
}

int Level::getCurrentStatementNumber() {
	auto userDefaults = CCUserDefault::sharedUserDefault();
	return userDefaults->getIntegerForKey(LEVEL_STATEMENT_KEY, 1);
}

Statement* Level::getStatement() {
	return StatementList::getInstance()->getStatement();
}

void Level::goToNextLevel() {
	auto userDefaults = CCUserDefault::sharedUserDefault();
	int currentLevel = getNumber();
	userDefaults->setIntegerForKey(LEVEL_KEY, currentLevel + 1);
	userDefaults->setIntegerForKey(LEVEL_STATEMENT_KEY, 1);
	userDefaults->setIntegerForKey(CORRECT_ANSWERS_KEY, 0);
	userDefaults->flush();
	Rank::onNewLevel();
}

int Level::getCorrectAnswerCount() {
	auto userDefaults = CCUserDefault::sharedUserDefault();
	return userDefaults->getIntegerForKey(CORRECT_ANSWERS_KEY, 0);
}

void Level::onTimesUp() {
	onLevelComplete();
}

void Level::incrementCorrectStatements() {
	auto userDefaults = CCUserDefault::sharedUserDefault();
	int correctStatements = userDefaults->getIntegerForKey(CORRECT_ANSWERS_KEY,
			0);
	userDefaults->setIntegerForKey(CORRECT_ANSWERS_KEY, correctStatements + 1);
	userDefaults->flush();
}

void Level::onTruePressed() {
	if (getStatement()->getCorrect()) {
		incrementCorrectStatements();
		onCorrectAnswerCallback->execute();
	} else {
		onWrongAnswerCallback->execute();
	}
	goToNextStatement();
}

void Level::onFalsePressed() {

	auto statement = getStatement();
	if (!statement->getCorrect()) {
		incrementCorrectStatements();
		onCorrectAnswerCallback->execute();
	} else {
		onWrongAnswerCallback->execute();
	}
	goToNextStatement();
}

void Level::onLevelComplete() {
	auto userDefaults = CCUserDefault::sharedUserDefault();
	int correctAnswers = userDefaults->getIntegerForKey(CORRECT_ANSWERS_KEY);
	if (correctAnswers >= getRequiredCorrectAnswerCount()) {
		onLevelCompleteCallback->execute();
	} else {
		onLevelFailedCallback->execute();
	}
}

void Level::goToNextStatement() {
	int currentStatement = getCurrentStatementNumber();
	StatementList::getInstance()->markCurrentStatementComplete();
	if (currentStatement == getStatementCount()) {
		onLevelComplete();
	} else {
		auto userDefaults = CCUserDefault::sharedUserDefault();
		userDefaults->setIntegerForKey(LEVEL_STATEMENT_KEY,
				currentStatement + 1);
		userDefaults->flush();
	}
}

Level::~Level() {
}

int Level::getRequiredCorrectAnswerCount() {

	float levelPercentage = fmin(
			MIN_REQUIRED_ANSWER_PERCENTAGE + (getNumber() / 100.0f), 1.0f);
	return (int) (statementCount * levelPercentage);

}
