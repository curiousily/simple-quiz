#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "cocos2d.h"

USING_NS_CC;

class GameManager {
public:
	virtual ~GameManager();

	static GameManager* sharedGameManager();

	void startWithScene(CCScene* scene);
	void runScene(CCScene* scene);
};

#endif /* GAMEMANAGER_H_ */
