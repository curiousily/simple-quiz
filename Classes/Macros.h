#ifndef MACROS_H_
#define MACROS_H_

#include "cocos2d.h"

USING_NS_CC;

#define SCENE_FUNC(__TYPE__) \
static CCScene* scene() \
{ \
	CCScene *scene = CCScene::create(); \
	scene->addChild(__TYPE__::create()); \
	return scene; \
}

#endif /* MACROS_H_ */
