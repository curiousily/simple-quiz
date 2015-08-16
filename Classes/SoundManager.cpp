#include "SoundManager.h"

static SoundManager *soundManager = NULL;

const char* SoundManager::SOUND_ENABLED_KEY = "sound_enabled";
const char* SoundManager::MUSIC_ENABLED_KEY = "music_enabled";

SoundManager::SoundManager() {
}

void SoundManager::onAppStarting() {

	float soundVolume = isSoundEnabled() ? SOUND_EFFECTS_VOLUME : 0.0f;
	setEffectsVolume(soundVolume);

	float musicVolume = isMusicEnabled() ? BACKGROUND_MUSIC_VOLUME : 0.0f;
	setBackgroundVolume(musicVolume);
}

void SoundManager::loadEffect(const char *name) {
	SimpleAudioEngine::sharedEngine()->preloadEffect(
			CCString::createWithFormat("Sound/Effects/%s.wav", name)->getCString());
}

void SoundManager::setEffectsVolume(float newVolume) {
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(newVolume);
}

bool SoundManager::isMusicEnabled() {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	return db->getBoolForKey(MUSIC_ENABLED_KEY, true);
}

bool SoundManager::isSoundEnabled() {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	return db->getBoolForKey(SOUND_ENABLED_KEY, true);
}

void SoundManager::setBackgroundVolume(float newVolume) {
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(newVolume);
}

void SoundManager::playLoopingBackground(const char *name) {
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
			CCString::createWithFormat("Sound/%s.mp3", name)->getCString(),
			true);
}

void SoundManager::playSoundEffect(const char *name) {
	SimpleAudioEngine::sharedEngine()->playEffect(
			CCString::createWithFormat("Sound/Effects/%s.wav", name)->getCString());
}

void SoundManager::unmuteMusic() {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	db->setBoolForKey(MUSIC_ENABLED_KEY, true);
	db->flush();
	setBackgroundVolume(BACKGROUND_MUSIC_VOLUME);
}

void SoundManager::unmuteSound() {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	db->setBoolForKey(SOUND_ENABLED_KEY, true);
	db->flush();
	setEffectsVolume(SOUND_EFFECTS_VOLUME);
}

void SoundManager::muteSound() {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	db->setBoolForKey(SOUND_ENABLED_KEY, false);
	db->flush();
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
}

void SoundManager::muteMusic() {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	db->setBoolForKey(MUSIC_ENABLED_KEY, false);
	db->flush();
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
}

SoundManager::~SoundManager() {
}

SoundManager *SoundManager::sharedSoundManager() {
	if (soundManager == NULL) {
		soundManager = new SoundManager();
	}
	return soundManager;
}
