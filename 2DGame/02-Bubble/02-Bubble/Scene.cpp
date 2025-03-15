#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 40
#define INIT_PLAYER_Y_TILES 20


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/mapa.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	currentTime = 0.0f;

	mapsize = map->getMapSize();
	tilesize = map->getTileSize();

	float camX = player->getPosition().x;
	float camY = player->getPosition().y;
	zoom = 2.0f;

	l = 32;
	r = camX + (float(SCREEN_WIDTH) / (2.0f * zoom));
	b = 464;
	t = camY - (float(SCREEN_HEIGHT) / (2.0f * zoom));


	std::cout << "camx " << camX << " camy " << camY <<std::endl;
	std::cout << "l " << l << " r " << r << " b " << b << " t " << t <<std::endl;

	//std::cout << "Map Size: " << mapsize.x << "x" << mapsize.y << " pixels" << std::endl;
	//std::cout << "Tile Size: " << tilesize << " pixels" << std::endl;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	modifcam();

	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
}

void Scene::modifcam() {
	float camX = player->getPosition().x;
	float camY = player->getPosition().y;
	
	const float MAP_LEFT = tilesize * 2;
	const float MAP_RIGHT = tilesize*(mapsize.x + 2);
	const float MAP_BOTTOM = tilesize * 1;
	const float MAP_TOP = tilesize*(mapsize.y + 1);

	float camHalfWidth = (float(SCREEN_WIDTH) / (2.0f * zoom));
	float camHalfHeight = (float(SCREEN_HEIGHT) / (2.0f * zoom));

	camX = glm::clamp(camX, MAP_LEFT + camHalfWidth, MAP_RIGHT - camHalfWidth);
	camY = glm::clamp(camY, MAP_BOTTOM + camHalfHeight, MAP_TOP - camHalfHeight);

	float l = camX - camHalfWidth;
	float r = camX + camHalfWidth;
	float b = camY + camHalfHeight;
	float t = camY - camHalfHeight;

	projection = glm::ortho(l, r, b, t);
	texProgram.setUniformMatrix4f("projection", projection);
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



