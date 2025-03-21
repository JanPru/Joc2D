#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 35
#define INIT_PLAYER_Y_TILES 33


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

void Scene::definirProjectils() {
	projectils.resize(5);
	glm::vec2* posPlantes = map->getPosPlantes();

	for (int i = 0; i < 5; ++i) {
		projectils[i] = Projectil(posPlantes[i], texProgram);
	}
}

void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/mapa2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	definirProjectils();
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
	segCanviTiles = 500;
	segProjectil = 2000;

	l = 32;
	r = camX + (float(SCREEN_WIDTH) / (2.0f * zoom));
	b = 464;
	t = camY - (float(SCREEN_HEIGHT) / (2.0f * zoom));


	//std::cout << "camx " << camX << " camy " << camY <<std::endl;
	//std::cout << "l " << l << " r " << r << " b " << b << " t " << t <<std::endl;

	//std::cout << "Map Size: " << mapsize.x << "x" << mapsize.y << " pixels" << std::endl;
	//std::cout << "Tile Size: " << tilesize << " pixels" << std::endl;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	for (int i = 0; i < 5; ++i) {
		projectils[i].update(deltaTime);
	}
	if (currentTime >= segCanviTiles) {
		map->canviTiles(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		segCanviTiles += 500;
	}
	if (currentTime >= segProjectil) {
		for (int i = 0; i < 5; ++i) {
			if (!projectils[i].isActive()) {
				projectils[i].activate();
			}
		}
	}
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
	camX = player->getPosition().x;
	camY = player->getPosition().y;
	//std::cout << "camx " << camX << " camy " << camY << std::endl;
	
	const float MAP_LEFT = tilesize * 2;
	const float MAP_RIGHT = tilesize*(mapsize.x + 2);
	const float MAP_BOTTOM = tilesize * 1;
	const float MAP_TOP = tilesize*(mapsize.y + 1);

	float camHalfWidth = (float(SCREEN_WIDTH) / (2.0f * zoom));
	float camHalfHeight = (float(SCREEN_HEIGHT) / (2.0f * zoom));

	if (camX >= 29 * tilesize && camX < 129 * tilesize && camY >= 400 && camY < 668) {  // ZONA 1: Solo movimiento horizontal
		camX = glm::clamp(camX, 34 * tilesize + camHalfWidth, 130 * tilesize - camHalfWidth); // LIMIT CANVI CAMERA
		camY = 616;  // Bloquear verticalmente
	}
	else if (camY >= 400 && camY < 1168 && camX >= 129 * tilesize) {
		camX = 146 * tilesize - camHalfWidth; // Bloquear horizontalmente
		camY = glm::clamp(camY, float(616), MAP_TOP - camHalfHeight);
	}
	else if (camX >= 16 * tilesize && camX < 129 * tilesize && camY >= 900 && camY < 1200) {  // ZONA 1: Solo movimiento horizontal
		camX = glm::clamp(camX, 18 * tilesize + camHalfWidth, 129 * tilesize - camHalfWidth);
		camY = MAP_TOP - camHalfHeight;  // Bloquear verticalmente
	}


	//camX = glm::clamp(camX, MAP_LEFT + camHalfWidth, MAP_RIGHT - camHalfWidth);
	//camY = glm::clamp(camY, MAP_BOTTOM + camHalfHeight, MAP_TOP - camHalfHeight);

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

void Scene::resize(int width, int height) {
	float ratio = float(width) / float(height);
	int camWidth = (r - l);
	int camHeight = (t - b);
	float ratioOriginal = float(camWidth) / float(camHeight);

	if (ratio > ratioOriginal) {
		float newHeight = camHeight * ratio;
		float dif = (newHeight - camHeight) / 2.f;
		projection = glm::ortho(camX - dif, camX + camWidth + dif, camY + camHeight + dif, camY - dif);
	}

	else {
		float newHeight = camHeight / ratio;
		float dif = (newHeight - camHeight) / 2.f;
		projection = glm::ortho(camX, camX + camWidth, camY + camHeight + dif, camY - dif);	
	}

	modifcam();
}

