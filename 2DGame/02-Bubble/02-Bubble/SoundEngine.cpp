#include "SoundEngine.h"



SoundEngine* SoundEngine::instance = 0;

SoundEngine* SoundEngine::getInstance() {

	if (instance == 0) {
		instance = new SoundEngine();
	}
	return instance;
}

SoundEngine::SoundEngine() {
	engine = createIrrKlangDevice();

	main = engine->addSoundSourceFromFile("sounds/main.wav");
	start = engine->addSoundSourceFromFile("sounds/1.wav");
	boss = engine->addSoundSourceFromFile("sounds/boss.wav");
	ending = engine->addSoundSourceFromFile("sounds/ending.wav");
	punch = engine->addSoundSourceFromFile("sounds/punch.wav");
	hit = engine->addSoundSourceFromFile("sounds/hit.wav");
	jump = engine->addSoundSourceFromFile("sounds/jump.wav");

	main->setDefaultVolume(0.3f);
	start->setDefaultVolume(0.3f);
	boss->setDefaultVolume(0.3f);
	ending->setDefaultVolume(0.3f);
	hit->setDefaultVolume(0.5f);
	punch->setDefaultVolume(0.5f);
	jump->setDefaultVolume(0.5f);
}

void SoundEngine::stopAllSounds() {
	engine->stopAllSounds();
}

void SoundEngine::playMainTheme() {
	engine->play2D(main, true);
}

void SoundEngine::playstart() {
	engine->play2D(start, false);
}

void SoundEngine::playboss() {
	engine->play2D(boss, false);
}
void SoundEngine::playending() {
	engine->play2D(ending, false);
}
void SoundEngine::playhit() {
	engine->play2D(hit, false);
}
void SoundEngine::playpunch() {
	engine->play2D(punch, false);
}
void SoundEngine::playjump() {
	engine->play2D(jump, false);
}

