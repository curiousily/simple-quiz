#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"

USING_NS_CC;

using namespace CocosDenshion;

class SoundManager {
public:
	SoundManager();
	static SoundManager* sharedSoundManager();

	void onAppStarting();

	void playLoopingBackground(const char* name = "Background");

	void loadEffect(const char* name);

	void playSoundEffect(const char* name);

	void muteSound();

	void unmuteSound();

	void muteMusic();

	void unmuteMusic();

	bool isSoundEnabled();

	bool isMusicEnabled();

	virtual ~SoundManager();

private:
	static const char* SOUND_ENABLED_KEY;
	static const char* MUSIC_ENABLED_KEY;
	
	void setEffectsVolume(float newVolume);

	void setBackgroundVolume(float newVolume);
};

#endif /* SOUNDMANAGER_H_ */
