#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"

enum estats
{
	INICI, JOC, FI
};

void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	start.init();
	estat = INICI;
	timer = 20;
}

bool Game::update(int deltaTime)
{
	timer--;
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
		if (Game::instance().getKey(GLFW_KEY_G)) godmode = !godmode;
		scene.update(deltaTime);
		if (scene.getvidaPlayer() < 0.33f && estat != FI)
		{
			estat = FI;
			fin.init();
		}
	}
	else if (estat == FI)
	{
		if (Game::instance().getKey(GLFW_KEY_ENTER))
		{
			timer = 20;
			estat = INICI;
			start.init();
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