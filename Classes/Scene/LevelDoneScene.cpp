#include "LevelDoneScene.h"

LevelDone::~LevelDone() {
}

CCScene* LevelDone::complete(int requiredAnswers, int playerAnswers,
		int levelTime) {
	auto levelDone = new LevelDone();
	levelDone->initComplete(requiredAnswers, playerAnswers, levelTime);
	levelDone->autorelease();
	auto scene = CCScene::create();
	scene->addChild(levelDone);
	return scene;
}

CCScene* LevelDone::fail(int requiredAnswers, int playerAnswers,
		int levelTime) {
	auto levelDone = new LevelDone();
	levelDone->initFailed(requiredAnswers, playerAnswers, levelTime);
	levelDone->autorelease();
	auto scene = CCScene::create();
	scene->addChild(levelDone);
	return scene;
}

void LevelDone::addSprites() {
	CCLayer::init();
	addBackground(this);
	addChild(sprite("ResultBox", VisibleRect::center()));
}

void LevelDone::addLabels(int requiredAnswers, int playerAnswers,
		int levelTime) {
	auto labelPadding = 150;
	auto requiredLabel =
			LabelBuilder::label("Required", SANS_SEMIBOLD_FONT)->size(48)->position(
					ccp(VisibleRect::center().x - labelPadding, VisibleRect::center().y + 150))
					->color(BLUE_TEXT)->anchorPoint(ccp(0.0f, 0.5f))->addTo(this);
	auto correctAnswersLabel =
			label(Formatter::toString("%d", requiredAnswers), 48,
					ccp(VisibleRect::center().x + labelPadding, requiredLabel->getPositionY()), ccBLACK);
	correctAnswersLabel->setAnchorPoint(ccp(1.0f, 0.5f));
	addChild(correctAnswersLabel);
	auto youLabel =
			LabelBuilder::label("You", SANS_SEMIBOLD_FONT)->size(48)->position(
					ccp(VisibleRect::center().x - labelPadding, VisibleRect::center().y + 30))
					->color(BLUE_TEXT)->anchorPoint(ccp(0.0f, 0.5f))->addTo(this);
	auto playerAnswersLabel =
			label(Formatter::toString("%d", playerAnswers), 48,
					ccp(VisibleRect::center().x + labelPadding, youLabel->getPositionY()), ccBLACK);
	playerAnswersLabel->setAnchorPoint(ccp(1.0f, 0.5f));
	addChild(playerAnswersLabel);
	auto timeLabel =
			LabelBuilder::label("Time", SANS_SEMIBOLD_FONT)->size(48)->position(
					ccp(VisibleRect::center().x - labelPadding, VisibleRect::center().y - 80))
					->color(BLUE_TEXT)->anchorPoint(ccp(0.0f, 0.5f))->addTo(this);
	auto levelCompleteTimeLabel =
			label(Formatter::toString("%ds", levelTime), 48,
					ccp(VisibleRect::center().x + labelPadding, timeLabel->getPositionY()), ccBLACK);
	levelCompleteTimeLabel->setAnchorPoint(ccp(1.0f, 0.5f));
	addChild(levelCompleteTimeLabel);
}

void LevelDone::initComplete(int requiredAnswers, int playerAnswers,
		int levelTime) {
	addSprites();
	addChild(
			sprite("LevelCompleteText",
					ccp(VisibleRect::top().x, VisibleRect::top().y - 200)));
	auto nextButton = CCMenuItemSprite::create(sprite("NextButton"),
			sprite("NextButtonPressed"), this,
			menu_selector(LevelDone::onNextLevelPressed));
	nextButton->setPosition(
			ccp(VisibleRect::bottom().x, VisibleRect::bottom().y + 220));
	auto mainButton = CCMenuItemSprite::create(sprite("MainButton"),
			sprite("MainButtonPressed"), this,
			menu_selector(LevelDone::onMainPressed));
	mainButton->setPosition(
			ccp(VisibleRect::bottom().x, VisibleRect::bottom().y + 100));
	auto menu = CCMenu::create(mainButton, nextButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);

	addLabels(requiredAnswers, playerAnswers, levelTime);
}

void LevelDone::initFailed(int requiredAnswers, int playerAnswers,
		int levelTime) {
	addSprites();
	addChild(
			sprite("LevelFailedText",
					ccp(VisibleRect::top().x, VisibleRect::top().y - 200)));
	auto nextButton = CCMenuItemSprite::create(sprite("ReplayButton"),
			sprite("ReplayButtonPressed"), this,
			menu_selector(LevelDone::onReplayLevelPressed));
	nextButton->setPosition(
			ccp(VisibleRect::bottom().x, VisibleRect::bottom().y + 220));
	auto mainButton = CCMenuItemSprite::create(sprite("MainButton"),
			sprite("MainButtonPressed"), this,
			menu_selector(LevelDone::onMainPressed));
	mainButton->setPosition(
			ccp(VisibleRect::bottom().x, VisibleRect::bottom().y + 100));
	auto menu = CCMenu::create(mainButton, nextButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);
	addLabels(requiredAnswers, playerAnswers, levelTime);
}

void LevelDone::onNextLevelPressed(CCObject* sender) {
	SoundManager::sharedSoundManager()->playSoundEffect("ButtonClick");
	Level::getCurrentLevel()->goToNextLevel();
	GameManager::sharedGameManager()->runScene(
			CCTransitionMoveInR::create(0.5f, Game::scene()));
}

void LevelDone::onReplayLevelPressed(CCObject* sender) {
	SoundManager::sharedSoundManager()->playSoundEffect("ButtonClick");
	GameManager::sharedGameManager()->runScene(
			CCTransitionMoveInR::create(0.5f, Game::scene()));
}

void LevelDone::onMainPressed(CCObject* sender) {
	SoundManager::sharedSoundManager()->playSoundEffect("ButtonClick");
	GameManager::sharedGameManager()->runScene(
			CCTransitionMoveInR::create(0.5f, Home::scene()));
}
