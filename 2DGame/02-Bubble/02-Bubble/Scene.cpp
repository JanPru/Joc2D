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
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (projectils != NULL)
		delete[] projectils;
}

void Scene::definirProjectils() {
	projectils = new Projectil[5];
	glm::vec2* posPlantes = map->getPosPlantes();

	for (int i = 0; i < 5; ++i) {
		projectils[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		glm::vec2 actPos = posPlantes[i];
		projectils[i].setPosition(glm::vec2(actPos.x * map->getTileSize(), (actPos.y - 1) * map->getTileSize()));
	}
}

void Scene::definirFlorecitas() {
	florecitas.clear();
	
	Florecita* flor1 = new Florecita();
	flor1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	flor1->setPosition(glm::vec2(0 * map->getTileSize(), 29 * map->getTileSize()));

	florecitas.push_back(flor1);

	Florecita* flor2 = new Florecita();
	flor2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, -1);
	flor2->setPosition(glm::vec2(16 * map->getTileSize(), 27 * map->getTileSize()));

	florecitas.push_back(flor2);

	Florecita* flor3 = new Florecita();
	flor3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	flor3->setPosition(glm::vec2(0 * map->getTileSize(), 21 * map->getTileSize()));

	florecitas.push_back(flor3);

	Florecita* flor4 = new Florecita();
	flor4->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, -1);
	flor4->setPosition(glm::vec2(16 * map->getTileSize(), 16 * map->getTileSize()));

	florecitas.push_back(flor4);

	Florecita* flor5 = new Florecita();
	flor5->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	flor5->setPosition(glm::vec2(0 * map->getTileSize(), 8 * map->getTileSize()));

	florecitas.push_back(flor5);
}

void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/mapa2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	definirProjectils();
	definirFlorecitas();
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	player->setFlorecitas(&florecitas);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	currentTime = 0.0f;

	mapsize = map->getMapSize();
	tilesize = map->getTileSize();

	float camX = player->getPosition().x;
	float camY = player->getPosition().y;
	zoom = 2.0f;
	segCanviTiles = 250;
	segProjectil = 1000;
	segFlorecita = 4500;

	l = 32;
	r = camX + (float(SCREEN_WIDTH) / (2.0f * zoom));
	b = 464;
	t = camY - (float(SCREEN_HEIGHT) / (2.0f * zoom));

	fase = FASE0;

	//std::cout << "camx " << camX << " camy " << camY <<std::endl;
	//std::cout << "l " << l << " r " << r << " b " << b << " t " << t <<std::endl;

	//std::cout << "Map Size: " << mapsize.x << "x" << mapsize.y << " pixels" << std::endl;
	//std::cout << "Tile Size: " << tilesize << " pixels" << std::endl;
	gui = new GUI();
	gui->init(texProgram);
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);

	if (currentTime >= segCanviTiles) {
		map->canviTiles(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		segCanviTiles += 250;
	}

	if (currentTime >= segProjectil) {
		for (int i = 0; i < 5; ++i) {
			projectils[i].reset();
		}
		segProjectil += 1000;
	}

	else {
		for (int i = 0; i < 5; ++i) projectils[i].update(deltaTime);
	}

	if (currentTime >= segFlorecita) {
		for (auto& f : florecitas) {
			f->reset();
		}
		segFlorecita += 4500;
	}

	else {
		for (auto& f : florecitas) {
			f->update(deltaTime);
		}
	}

	// COSES DE LA CAMERA
	limitszona[0] = glm::vec2(2032, 512);
	limitszona[1] = glm::vec2(2288, 2032);
	limitszona[2] = glm::vec2(256, 2032);
	limitszona[3] = glm::vec2();
	/*
	limitszona[4] = glm::vec2();
	limitszona[5] = glm::vec2();*/

	if (fase == FASE0 && player->getPosition().x >= limitszona[0].x) {
		player->canvialimit(limitszona[0].x, true);
		fase = FASE1;
	}
	if (fase == FASE1 && player->getPosition().x < limitszona[1].y + 16 && player->getPosition().y > 704) {
		player->canvialimit(limitszona[1].y - 16, false);
		fase = FASE2;
	}
	if (fase == FASE2 && player->getPosition().x <= limitszona[2].x && player->getPosition().y > 704) {
		player->canvialimit(limitszona[2].x - 16, false);
		fase = FASE3;
	}

	//std::cout << "Fase: " << fase << std::endl;
	//std::cout << player->getPosition().x << std::endl;
	//std::cout << player->getPosition().y << std::endl;

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
	for (int i = 0; i < 5; ++i) {
		projectils[i].render();
	}
	for (auto& f : florecitas) {
		f->render();
	}
	player->render();
}

void Scene::modifcam() {
	camX = player->getPosition().x;
	camY = player->getPosition().y;
	//std::cout << "camx " << camX << " camy " << camY << std::endl;

	const float MAP_LEFT = tilesize * 2;
	const float MAP_RIGHT = tilesize * (mapsize.x + 2);
	const float MAP_BOTTOM = tilesize * 1;
	const float MAP_TOP = tilesize * (mapsize.y + 1);

	float camHalfWidth = (float(SCREEN_WIDTH) / (2.0f * zoom));
	float camHalfHeight = (float(SCREEN_HEIGHT) / (2.0f * zoom));

	/*
		if (camX >= 512 && camX < limitszona[0].x && camY < 704) {  // ZONA 1: Solo movimiento horizontal
			camX = glm::clamp(camX, 34 * tilesize + camHalfWidth, 130 * tilesize - camHalfWidth); // LIMIT CANVI CAMERA
			camY = 616;  // Bloquear verticalmente
		}
		else if (camY >= 400 && camY < 1168 && camX >= limitszona[0].x) {
			camX = 146 * tilesize - camHalfWidth; // Bloquear horizontalmente
			camY = glm::clamp(camY, float(616), MAP_TOP - camHalfHeight);
		}
		else if (camX >= 16 * tilesize && camX < 129 * tilesize && camY >= 900 && camY < 1200) {  // ZONA 1: Solo movimiento horizontal
			camX = glm::clamp(camX, 18 * tilesize + camHalfWidth, 129 * tilesize - camHalfWidth);
			camY = MAP_TOP - camHalfHeight;  // Bloquear verticalmente
		}
		*/
	if (fase == FASE0) {

		camX = glm::clamp(camX, limitszona[0].y + 32 + camHalfWidth, limitszona[0].x + 48 - camHalfWidth);
		camY = 616;
	}
	if (fase == FASE1) {
		camX = 146 * tilesize - camHalfWidth;
		camY = glm::clamp(camY, float(616), MAP_TOP - camHalfHeight);
	}
	if (fase == FASE2) {
		camX = glm::clamp(camX, limitszona[2].x + 32 + camHalfWidth, limitszona[2].y + 48 - camHalfWidth);
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

	//glm::mat4 hudProjection = glm::ortho(0.f, float(camHalfWidth*2), float(camHalfHeight*2), 0.f);
	//texProgram.setUniformMatrix4f("projection", hudProjection);
	gui->render(4);
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
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
