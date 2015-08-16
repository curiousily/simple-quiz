#include "LifesLayer.h"

bool Lifes::init() {
	if (!CCLayer::init()) {
		return false;
	}
	addChild(sprite("LifeAvailable"));

	return true;
}

Lifes* Lifes::create() {
	auto lifes = new Lifes();
	lifes->init();
	lifes->autorelease();
	return lifes;
}

Lifes::~Lifes() {
}

