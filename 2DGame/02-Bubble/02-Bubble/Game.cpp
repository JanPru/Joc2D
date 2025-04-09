#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"

enum estats
{
	INICI, JOC, FI, INST, WIN
};

void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	start.init();
	estat = INICI;
	timer = 530;
	timeri = 20;
	primerjoc = true;
	primerfi = true;
	SoundEngine::getInstance()->stopAllSounds();
}

bool Game::update(int deltaTime)
{
	timer--;
	timeri--;
	if(estat == INICI)
	{
		start.update(deltaTime);
		if (Game::instance().getKey(GLFW_KEY_ENTER) && timer <= 0)
		{
			estat = JOC;
			scene.init();
		}
	}
	else if(estat == JOC)
	{
		if (primerjoc) {
			SoundEngine::getInstance()->stopAllSounds();
			SoundEngine::getInstance()->playMainTheme();
			primerjoc = false;
		}
		scene.update(deltaTime);
		if (scene.getvidaPlayer() < 0.33f && estat != FI)
		{
			estat = FI;
			fin.init();
		}
		if (scene.getfinalbool() && estat != WIN)
		{
			estat = WIN;
			win.init();
		}
		if (Game::instance().getKey(GLFW_KEY_I) && timeri <= 0) {
			estat = INST;
			instruccions.init();
			timeri = 20;
		}

	}
	else if (estat == FI)
	{
		if (primerfi) {
			SoundEngine::getInstance()->stopAllSounds();
			SoundEngine::getInstance()->playending();
			primerfi = false;
		}
		if (Game::instance().getKey(GLFW_KEY_ENTER))
		{
			timer = 20;
			estat = JOC;
			scene.init();
			primerfi = true;
			primerjoc = true;
		}
	}
	else if (estat == INST)
	{
		instruccions.update(deltaTime);
		if (Game::instance().getKey(GLFW_KEY_I) && timeri <= 0)
		{
			estat = JOC;
			timeri = 20;
		}
	}
	else if (estat == WIN) {
		if (primerfi) {
			SoundEngine::getInstance()->stopAllSounds();
			SoundEngine::getInstance()->playending();
			primerfi = false;
		}
		if (Game::instance().getKey(GLFW_KEY_ENTER))
		{
			timer = 20;
			estat = JOC;
			scene.init();
			primerfi = true;
			primerjoc = true;
		}
	}

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(estat == INICI) start.render();
	else if(estat == JOC) scene.render();
	else if (estat == FI) fin.render();
	else if (estat == INST) instruccions.render();
	else if (estat == WIN) win.render();
}

void Game::keyPressed(int key)
{
	if (key == GLFW_KEY_ESCAPE) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

void Game::resize(int width, int height) {
	scene.resize(width, height);
}

bool Game::isgodmode()
{
	return godmode;
}