#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "cocos2d.h"

USING_NS_CC;

static const char* GLOBAL_FONT = "OpenSans-Regular";
static const char* SANS_SEMIBOLD_FONT = "OpenSans-Semibold";

static const int DEFAULT_FONT_SIZE = 42;

static const float BACKGROUND_MUSIC_VOLUME = 0.2f;
static const float SOUND_EFFECTS_VOLUME = 0.5f;

static const ccColor3B BLACK_TEXT = { 37, 37, 37 };
static const ccColor3B BLUE_TEXT = { 41, 128, 185 };
static const ccColor3B GREEN_TEXT = { 46, 204, 113 };
static const ccColor3B RED_TEXT = { 231, 76, 60 };

static const char* RANKS[] = { "Newbie", "Puppet", "Worm", "Tamagotchi", "Slow",
		"Average", "Good", "Smart", "Pro", "Amazing", "Genius", "Unreal" };
static const int RANK_COUNT = sizeof(RANKS) / sizeof(RANKS[0]);

#endif /* CONSTANTS_H_ */
