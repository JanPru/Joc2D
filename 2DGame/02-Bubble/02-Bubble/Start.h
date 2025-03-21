#ifndef _START_INCLUDE
#define _START_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Sprite.h"
#include "Scene.h"


// Start contains all the entities of our game.
// It is responsible for updating and render them.


class Start
{

public:
	Start();
	~Start();

	void init();
	void update(int deltaTime);
	void render();
	void resize(int width, int height);

private:
	void initShaders();

private:
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	Sprite* spritestart;
	Texture spritesheetstart;
	glm::mat4 projection;
};


#endif // Start

