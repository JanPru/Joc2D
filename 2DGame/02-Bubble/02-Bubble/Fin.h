#ifndef _FIN_INCLUDE
#define _FIN_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Sprite.h"
#include "Scene.h"


// Start contains all the entities of our game.
// It is responsible for updating and render them.


class Fin
{

public:
	Fin();
	~Fin();

	void init();
	void update(int deltaTime);
	void render();
	void resize(int width, int height);

private:
	void initShaders();

private:
	Player* player;
	ShaderProgram texProgram;
	float currentTime;
	Sprite* spritefin;
	Texture spritesheetstart;
	glm::mat4 projection;
	int counter, counter2;
	bool enable, enable2;
};


#endif // Fin

