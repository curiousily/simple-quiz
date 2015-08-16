#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "../GameManager.h"
#include "../Macros.h"
#include "../AssetManager.h"
#include "../VisibleRect.h"
#include "../Model/StatementList.h"
#include "../Model/Level.h"
#include "../Constants.h"
#include "../Model/Statement.h"
#include "Layer/LifesLayer.h"
#include "LevelDoneScene.h"
USING_NS_CC;

class Game: public cocos2d::CCLayer, public AssetManager {
public:
	virtual bool init();

	SCENE_FUNC(Game)
	CREATE_FUNC(Game)

	virtual const char* getResourceDirectory() {
		return "Game";
	}

	void updateClock(float delta);

	virtual ~Game();

private:

	int levelRemainingTime;
	CCLabelTTF* clockLabel;
	CCLabelTTF* currentStatementLabel;
	CCLabelTTF* statementLabel;

	CCMenuItemSprite* trueButton;
	CCMenuItemSprite* falseButton;

	void onTrueButtonPressed(CCObject* sender);
	void onFalseButtonPressed(CCObject* sender);
	void addControls();
	void addStatusBar();
	void addClock();
	void addStatement();
	void updateClockLabelWithRemainingTime();
	void updateCurrentStatementLabel();

	void onLevelComplete();
	void onLevelFailed();

	void onTimesUp();
	void onCorrectAnswer();
	void onWrongAnswer();
	void showNextQuestion();
	void disableButtons();
	void enableButtons();
	void createStatementLabel();
};

#endif // __HELLOWORLD_SCENE_H__
