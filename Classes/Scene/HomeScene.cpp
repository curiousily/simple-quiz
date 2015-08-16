#include "HomeScene.h"

void Home::fadeInAfterDelay(CCNodeRGBA* node) {
	node->setOpacity(0.0f);
	node->runAction(CCFadeIn::create(1.6f));
}

void Home::addMenu() {
	auto playButton = CCMenuItemSprite::create(sprite("PlayButton"),
			sprite("PlayButtonPressed"), sprite("PlayButtonPressed"), this,
			menu_selector(Home::onPlayPressed));
	playButton->setPosition(VisibleRect::center().x,
			VisibleRect::bottom().y + 220);
	fadeInAfterDelay(playButton);
	auto exitButton = CCMenuItemSprite::create(sprite("ExitButton"),
			sprite("ExitButtonPressed"), sprite("ExitButtonPressed"), this,
			menu_selector(Home::onExitPressed));
	exitButton->setPosition(VisibleRect::center().x,
			VisibleRect::bottom().y + 100);
	fadeInAfterDelay(exitButton);
	auto menu = CCMenu::create(exitButton, playButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);
}

bool Home::init() {

	if (!CCLayer::init()) {
		return false;
	}

	addBackground(this);

	LabelBuilder::label(Formatter::toString("Rank: %s", Rank::getText()),
			SANS_SEMIBOLD_FONT)->size(42)->position(
			ccp(VisibleRect::rightTop().x - 20, VisibleRect::rightTop().y - 20))->anchorPoint(
					ccp(1.0f, 1.0f))->addTo(
					this);

	auto logoBackground = sprite("LogoBackground", VisibleRect::top());
	addChild(logoBackground);
	auto moveToPosition =
			CCEaseBackOut::create(
					CCMoveTo::create(1.2f,
							ccp(VisibleRect::center().x - 40, VisibleRect::center().y + 110)));
	auto fadeIn = CCFadeIn::create(1.0f);

	logoBackground->runAction(moveToPosition);
	logoBackground->runAction(fadeIn);
	logoBackground->runAction(
			CCRepeatForever::create(
					CCSequence::create(
CCMoveBy			::create(2.0f, ccp(0, 15)), CCMoveBy::create(2.0f, ccp(0, -15)), NULL)));
	logoBackground->runAction(
			CCRepeatForever::create(
					CCSequence::create(CCDelayTime::create(1.4f),
							CCRotateBy::create(30.0f, 360), NULL)));

	auto logoTextIQ = sprite("LogoIQText",
			ccp(VisibleRect::center().x - 120, VisibleRect::center().y + 75));
	logoTextIQ->setOpacity(0.0f);
	logoTextIQ->runAction(CCFadeIn::create(1.6f));
	fadeInAfterDelay(logoTextIQ);
	addChild(logoTextIQ);

	auto logoText = sprite("LogoText",
			ccp(VisibleRect::center().x - 15, VisibleRect::center().y + 160));
	fadeInAfterDelay(logoText);
	addChild(logoText);

	addMenu();
	return true;
}

void Home::onPlayPressed(CCObject* sender) {
	SoundManager::sharedSoundManager()->playSoundEffect("ButtonClick");
	GameManager::sharedGameManager()->runScene(Game::scene());
}

void Home::onExitPressed(CCObject* sender) {
	SoundManager::sharedSoundManager()->playSoundEffect("ButtonClick");
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
