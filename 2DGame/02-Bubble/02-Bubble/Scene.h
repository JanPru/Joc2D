#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Projectil.h"
#include "GUI.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void resize(int width, int height);

private:
	void initShaders();
	void modifcam();
	void definirProjectils();

private:
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	float l, r, b, t;
	float camX, camY;
	float segCanviTiles;
	float segProjectil;
	float zoom;
	glm::vec2 mapsize;
	float tilesize;
	Projectil* projectils;
};


#endif // _SCENE_INCLUDE

