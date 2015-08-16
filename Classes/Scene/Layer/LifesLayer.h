#ifndef LIFESLAYER_H_
#define LIFESLAYER_H_

#include "cocos2d.h"
#include "../../AssetManager.h"
#include "../../VisibleRect.h"

USING_NS_CC;

class Lifes: public CCLayer, AssetManager {
public:

	virtual bool init();

	static Lifes* create();

	virtual const char* getResourceDirectory() {
		return "Game";
	}

	virtual ~Lifes();
};

#endif /* LIFESLAYER_H_ */
