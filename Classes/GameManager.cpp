#include "GameManager.h"

static GameManager *gameManager = NULL;

GameManager *GameManager::sharedGameManager() {
	if (gameManager == NULL) {
		gameManager = new GameManager();
	}
	return gameManager;
}

void GameManager::startWithScene(CCScene* scene) {
	CCDirector::sharedDirector()->runWithScene(scene);
}

void GameManager::runScene(CCScene *scene) {
	CCDirector::sharedDirector()->replaceScene(scene);
}

GameManager::~GameManager() {
}
