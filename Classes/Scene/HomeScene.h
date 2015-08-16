#ifndef HOMESCENE_H_
#define HOMESCENE_H_

#include "cocos2d.h"
#include "../Macros.h"
#include "../AssetManager.h"
#include "../VisibleRect.h"
#include "../GameManager.h"
#include "GameScene.h"
#include "../Model/Reader/StatementReader.h"
USING_NS_CC;

class Home: public cocos2d::CCLayer, public AssetManager {
public:
	virtual bool init();

	SCENE_FUNC(Home)
	CREATE_FUNC(Home)

	virtual const char* getResourceDirectory() {
		return "Home";
	}

private:

	void onPlayPressed(CCObject* sender);
	void onExitPressed(CCObject* sender);
	void fadeInAfterDelay(CCNodeRGBA* node);
	void addMenu();
};

#endif /* HOMESCENE_H_ */
