#include "GameScene.h"

using namespace cocos2d;

bool Game::init() {
	if (!CCLayer::init()) {
		return false;
	}
	auto level = Level::getCurrentLevel();

	Level::setOnLevelComplete(this, callfunc_selector(Game::onLevelComplete));
	Level::setOnLevelFailed(this, callfunc_selector(Game::onLevelFailed));
	Level::setOnCorrectAnswer(this, callfunc_selector(Game::onCorrectAnswer));
	Level::setOnWrongAnswer(this, callfunc_selector(Game::onWrongAnswer));

	levelRemainingTime = level->getTime();

	addBackground(this);
	addStatement();
	addClock();
	addStatusBar();
	addControls();
	schedule(schedule_selector(Game::updateClock), 1.0f);
	return true;
}

void Game::addControls() {
	auto controlsBackground = sprite("ControlsBackground",
			ccp(VisibleRect::center().x - 1, VisibleRect::bottom().y + 253));
			addChild(controlsBackground);
			trueButton = CCMenuItemSprite::create(sprite("TrueButton"),
					sprite("TrueButtonPressed"), this,
					menu_selector(Game::onTrueButtonPressed));
			trueButton->setPosition(
					ccp(VisibleRect::center().x - 160, controlsBackground->getPositionY() - 20));
    falseButton = CCMenuItemSprite::create(sprite("FalseButton"),
			sprite("FalseButtonPressed"), this,
			menu_selector(Game::onFalseButtonPressed));
    falseButton->setPosition(
			ccp(VisibleRect::center().x + 160, controlsBackground->getPositionY() - 20));
    auto menu = CCMenu::create(trueButton, falseButton, NULL);
    menu->setPosition(CCPointZero);
    addChild(menu);
}

void Game::addStatusBar() {
	auto statusBackground = sprite("StatusBarBackground",
			ccp(VisibleRect::center().x, VisibleRect::top().y - 65));
			addChild(statusBackground);
			auto level = Level::getCurrentLevel();
			auto levelLabel = label(
					CCString::createWithFormat("Level %d", level->getNumber())->getCString(), 42);
			levelLabel->setAnchorPoint(ccp(1.0, 0.5));
			levelLabel->setPosition(
					ccp(VisibleRect::rightTop().x - 50, statusBackground->getPositionY()));
    addChild(levelLabel);
    currentStatementLabel = label("", 42);
    updateCurrentStatementLabel();
    currentStatementLabel->setAnchorPoint(ccp(0.0, 0.5));
    currentStatementLabel->setPosition(
			ccp(VisibleRect::leftTop().x + 50, statusBackground->getPositionY()));
    addChild(currentStatementLabel);
}

void Game::addClock() {
	auto clockBackground = sprite("ClockBackground",
			ccp(VisibleRect::left().x + 65, VisibleRect::center().y + 170));
			addChild(clockBackground);
			clockLabel = LabelBuilder::label("", SANS_SEMIBOLD_FONT)->size(60)
			->position(ccp(clockBackground->getPositionX() - 10,clockBackground->getPositionY()))
			->color(ccWHITE)->addTo(this);
			updateClockLabelWithRemainingTime();
}

void Game::updateClockLabelWithRemainingTime() {
	clockLabel->setString(Formatter::toString("%d", levelRemainingTime));
}

void Game::updateClock(float delta) {
	levelRemainingTime--;
	updateClockLabelWithRemainingTime();
	if (levelRemainingTime <= 0) {
		unschedule(schedule_selector(Game::updateClock));
		onTimesUp();
	}
}

void Game::addStatement() {
	auto statementBox = sprite("QuestionBox",
			ccp(VisibleRect::center().x, VisibleRect::center().y + 170));
			auto level = Level::getCurrentLevel();
			auto statement = level->getStatement();

			addChild(statementBox);
			statementLabel = LabelBuilder::label(statement->getText())->position(statementBox->getPosition())->dimensions(
											statementBox->getContentSize())->size(
											42)->color(BLACK_TEXT)->addTo(this);

		}

Game::~Game() {
}

void Game::onTimesUp() {
	Level::getCurrentLevel()->onTimesUp();
}

void Game::onCorrectAnswer() {
	SoundManager::sharedSoundManager()->playSoundEffect("CorrectAnswer");
	auto correctLabel =
			LabelBuilder::label("CORRECT", SANS_SEMIBOLD_FONT)->size(52)->opacity(
					0)->position(VisibleRect::center())->color(GREEN_TEXT)->addTo(
					this);
	correctLabel->runAction(
			CCSequence::create(CCFadeIn::create(1.0), CCRemoveSelf::create(),
					NULL));
	correctLabel->runAction(CCScaleTo::create(0.6f, 2.5));
	runAction(
			CCSequence::create(CCDelayTime::create(1.2f),
					CCCallFunc::create(this,
							callfunc_selector(Game::showNextQuestion)), NULL));
}

void Game::onWrongAnswer() {
	SoundManager::sharedSoundManager()->playSoundEffect("WrongAnswer");
	auto wrongLabel =
			LabelBuilder::label("WRONG", SANS_SEMIBOLD_FONT)->size(52)->opacity(
					0)->position(VisibleRect::center())->color(RED_TEXT)->addTo(
					this);

	wrongLabel->runAction(
			CCSequence::create(CCFadeIn::create(1.0), CCRemoveSelf::create(),
					NULL));
	wrongLabel->runAction(CCScaleTo::create(0.6f, 2.5));
	runAction(
			CCSequence::create(CCDelayTime::create(1.2f),
					CCCallFunc::create(this,
							callfunc_selector(Game::showNextQuestion)), NULL));
}

void Game::onLevelComplete() {
	stopAllActions();
	SoundManager::sharedSoundManager()->playSoundEffect("LevelComplete");
	auto level = Level::getCurrentLevel();
	int requiredAnswers = level->getRequiredCorrectAnswerCount();
	int playerAnswers = level->getCorrectAnswerCount();
	int completionTime = level->getTime() - levelRemainingTime;
	GameManager::sharedGameManager()->runScene(
			CCTransitionMoveInR::create(0.5f,
					LevelDone::complete(requiredAnswers, playerAnswers,
							completionTime)));
}

void Game::onLevelFailed() {
	stopAllActions();
	SoundManager::sharedSoundManager()->playSoundEffect("LevelFailed");
	auto level = Level::getCurrentLevel();
	int requiredAnswers = level->getRequiredCorrectAnswerCount();
	int playerAnswers = level->getCorrectAnswerCount();
	int completionTime = level->getTime() - levelRemainingTime;
	GameManager::sharedGameManager()->runScene(
			CCTransitionMoveInR::create(0.5f,
					LevelDone::fail(requiredAnswers, playerAnswers,
							completionTime)));
}

void Game::onTrueButtonPressed(CCObject* sender) {
	SoundManager::sharedSoundManager()->playSoundEffect("ButtonClick");
	auto level = Level::getCurrentLevel();
	level->onTruePressed();
	disableButtons();
}

void Game::disableButtons() {
	trueButton->setEnabled(false);
	falseButton->setEnabled(false);
}

void Game::enableButtons() {
	trueButton->setEnabled(true);
	falseButton->setEnabled(true);
}

void Game::onFalseButtonPressed(CCObject* sender) {
	SoundManager::sharedSoundManager()->playSoundEffect("ButtonClick");
	auto level = Level::getCurrentLevel();
	level->onFalsePressed();
	disableButtons();
}

void Game::updateCurrentStatementLabel() {
	auto level = Level::getCurrentLevel();
	int currentStatement = level->getCurrentStatementNumber();
	int statementCount = level->getStatementCount();
	currentStatementLabel->setString(
			Formatter::toString("%d/%d", currentStatement, statementCount));
}

void Game::createStatementLabel() {
	auto level = Level::getCurrentLevel();
	auto text = level->getStatement()->getText();
	statementLabel->setString(text);
	auto pos = statementLabel->getPosition();
	if (statementLabel) {
		statementLabel->removeFromParentAndCleanup(true);
	}
	statementLabel =
			LabelBuilder::label(text)->position(pos)->size(42)->dimensions(
					CCSizeMake(420, 450))->color(BLACK_TEXT)->addTo(this);
}

void Game::showNextQuestion() {
	createStatementLabel();
	updateCurrentStatementLabel();
	enableButtons();
}
