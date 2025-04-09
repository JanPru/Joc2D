#ifndef _SOUNDENGINE_INCLUDE
#define _SOUNDENGINE_INCLUDE
#include <irrKlang.h>

using namespace irrklang;

class SoundEngine
{
private:
	static SoundEngine* instance;
	SoundEngine();

public:
	static SoundEngine* getInstance();
	void stopAllSounds();
	void playMainTheme();
	void playstart();
	void playboss();
	void playending();
	void playhit();
	void playpunch();
	void playjump();

private:
	ISoundEngine* engine;
	ISoundSource* main;
	ISoundSource* start;
	ISoundSource* boss;
	ISoundSource* ending;
	ISoundSource* hit;
	ISoundSource* punch;
	ISoundSource* jump;

};


#endif // _SCENE_INCLUDE
