#ifndef LEVELDONESCENE_H_
#define LEVELDONESCENE_H_

#include "cocos2d.h"
#include "../Macros.h"
#include "../AssetManager.h"
#include "../VisibleRect.h"
#include "../GameManager.h"
#include "../Formatter.h"
#include "../Model/Level.h"
#include "GameScene.h"
#include "HomeScene.h"
USING_NS_CC;

class LevelDone: public CCLayer, public AssetManager {
public:

	static CCScene* complete(int requiredAnswers, int playerAnswers,
			int levelTime);
	static CCScene* fail(int requiredAnswers, int playerAnswers,
			int levelTime);

	virtual const char* getResourceDirectory() {
		return "LevelDone";
	}

	~LevelDone();

private:

	void initComplete(int requiredAnswers, int playerAnswers, int levelTime);
	void initFailed(int requiredAnswers, int playerAnswers, int levelTime);
	void addSprites();
	void addLabels(int requiredAnswers, int playerAnswers, int levelTime);

	void onNextLevelPressed(CCObject* sender);
	void onReplayLevelPressed(CCObject* sender);
	void onMainPressed(CCObject* sender);
};

#endif /* LEVELDONESCENE_H_ */
