#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include <GLFW/glfw3.h>
#include "Scene.h"
#include "Start.h"
#include "Fin.h"
#include "Instruccions.h"
#include <string>
#include "SoundEngine.h"	


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

private:
	Game() {}
	
public:
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	void resize(int width, int height);
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;

	void startturn();
	bool isgodmode();
	void playsound(std::string sound);

private:
	bool bPlay; // Continue to play game?
	bool keys[GLFW_KEY_LAST+1]; // Store key states so that 
							    // we can have access at any time
	Scene scene;
	Start start;
	Fin fin;
	Instruccions instruccions;

	bool startbool;
	bool inst;
	int estat;

	int timer;
	int timeri;

	bool godmode;

	bool primerjoc = true;
	bool primerfi = true;

};


#endif // _GAME_INCLUDE


