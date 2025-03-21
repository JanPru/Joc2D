#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	start.init();
	scene.init();
	startbool = true;
}

bool Game::update(int deltaTime)
{
	if(startbool)
	{
		start.update(deltaTime);
		if (Game::instance().getKey(GLFW_KEY_ENTER))
		{
			startbool = false;
			scene.init();
		}
	}
	else
	{
		scene.update(deltaTime);
	}
	start.update(deltaTime);

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(startbool) start.render();
	else scene.render();
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
