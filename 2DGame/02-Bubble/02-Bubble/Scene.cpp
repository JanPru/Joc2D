#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 35
#define INIT_PLAYER_Y_TILES 33

#define INIT_BOSS_X_TILES 57
#define INIT_BOSS_Y_TILES 5


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
}

void Scene::definirProjectils() {
	projectils.clear();
	glm::vec2* posPlantes = map->getPosPlantes();

	for (int i = 0; i < 5; ++i) {
		Projectil* projectil = new Projectil();
		projectil->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		glm::vec2 actPos = posPlantes[i];
		projectil->setPosition(glm::vec2(actPos.x * map->getTileSize(), (actPos.y - 1) * map->getTileSize()));
		
		projectils.push_back(projectil);
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
	flor5->setPosition(glm::vec2(0 * map->getTileSize(), 14 * map->getTileSize()));

	florecitas.push_back(flor5);

	Florecita* flor6 = new Florecita();
	flor6->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	flor6->setPosition(glm::vec2(0 * map->getTileSize(), 8 * map->getTileSize()));

	florecitas.push_back(flor6);
}

void Scene::definirPowerups() {
	powerups.clear();

	Powerups* pow1 = new Powerups();
	pow1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	pow1->setPosition(glm::vec2(50 * map->getTileSize(), 39 * map->getTileSize()));
	pow1->setinactiu();
	powerups.push_back(pow1);

	Powerups* pow2 = new Powerups();
	pow2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 2);
	pow2->setPosition(glm::vec2(50 * map->getTileSize(), 39 * map->getTileSize()));
	pow2->setinactiu();

	powerups.push_back(pow2);

	Powerups* pow3 = new Powerups();
	pow3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 3);
	pow3->setPosition(glm::vec2(50 * map->getTileSize(), 39 * map->getTileSize()));
	pow3->setinactiu();

	powerups.push_back(pow3);

	Powerups* pow4 = new Powerups();
	pow4->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 4);
	pow4->setPosition(glm::vec2(50 * map->getTileSize(), 39 * map->getTileSize()));
	pow4->setinactiu();

	powerups.push_back(pow4);

	Powerups* pow5 = new Powerups();
	pow5->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 5);
	pow5->setPosition(glm::vec2(50 * map->getTileSize(), 39 * map->getTileSize()));
	pow5->setinactiu();

	powerups.push_back(pow5);


}

void Scene::definirPlantes() {
	plantes.clear();

	Planta* p = new Planta();
	p->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0);
	p->setPosition(glm::vec2(116 * map->getTileSize(), 69 * map->getTileSize()));
	plantes.push_back(p);

	p = new Planta();
	p->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	p->setPosition(glm::vec2(112 * map->getTileSize(), 64 * map->getTileSize()));
	plantes.push_back(p);

	p = new Planta();
	p->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0);
	p->setPosition(glm::vec2(108 * map->getTileSize(), 69 * map->getTileSize()));
	plantes.push_back(p);

	p = new Planta();
	p->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	p->setPosition(glm::vec2(104 * map->getTileSize(), 65 * map->getTileSize()));
	plantes.push_back(p);

	p = new Planta();
	p->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0);
	p->setPosition(glm::vec2(99 * map->getTileSize(), 68 * map->getTileSize()));
	plantes.push_back(p);

	p = new Planta();
	p->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	p->setPosition(glm::vec2(95 * map->getTileSize(), 68 * map->getTileSize()));
	plantes.push_back(p);

	p = new Planta();
	p->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0);
	p->setPosition(glm::vec2(92 * map->getTileSize(), 64 * map->getTileSize()));
	plantes.push_back(p);

	p = new Planta();
	p->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	p->setPosition(glm::vec2(88 * map->getTileSize(), 70 * map->getTileSize()));
	plantes.push_back(p);

	p = new Planta();
	p->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	p->setPosition(glm::vec2(84 * map->getTileSize(), 66 * map->getTileSize()));
	plantes.push_back(p);

	p = new Planta();
	p->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0);
	p->setPosition(glm::vec2(77 * map->getTileSize(), 66 * map->getTileSize()));
	plantes.push_back(p);

	p = new Planta();
	p->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0);
	p->setPosition(glm::vec2(72 * map->getTileSize(), 65 * map->getTileSize()));
	plantes.push_back(p);

	p = new Planta();
	p->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	p->setPosition(glm::vec2(68 * map->getTileSize(), 70 * map->getTileSize()));
	plantes.push_back(p);
	
	crearPlanta(0, glm::vec2(12, 65));
	crearPlanta(0, glm::vec2(12, 53));
	crearPlanta(0, glm::vec2(12, 49));
	crearPlanta(0, glm::vec2(12, 42));
	crearPlanta(0, glm::vec2(12, 18));

	crearPlanta(1, glm::vec2(8, 66));
	crearPlanta(1, glm::vec2(8, 62));
	crearPlanta(1, glm::vec2(8, 45));
	crearPlanta(1, glm::vec2(8, 34));
	crearPlanta(1, glm::vec2(8, 11));

	crearPlanta(0, glm::vec2(6, 57));
	crearPlanta(0, glm::vec2(6, 53));
	crearPlanta(0, glm::vec2(6, 43));
	crearPlanta(0, glm::vec2(6, 39));
	crearPlanta(0, glm::vec2(6, 25));

	crearPlanta(1, glm::vec2(2, 62));
	crearPlanta(1, glm::vec2(2, 58));
	crearPlanta(1, glm::vec2(2, 46));
	crearPlanta(1, glm::vec2(2, 18));
	crearPlanta(1, glm::vec2(2, 11));
}

void Scene::crearPlanta(int type, glm::vec2 position) {
	Planta* p = new Planta();
	p->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, type);
	p->setPosition(glm::vec2(position.x * map->getTileSize(), position.y * map->getTileSize()));
	plantes.push_back(p);
}

void Scene::definirBolets() {
	bolets.clear();

	Bolet* b = new Bolet();
	b->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, -1);
	b->setPosition(glm::vec2(37 * map->getTileSize(), 7  * map->getTileSize()));
	b->setTileMap(map);

	bolets.push_back(b);

	b = new Bolet();
	b->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, -1);
	b->setPosition(glm::vec2(40 * map->getTileSize(), 5 * map->getTileSize()));
	b->setTileMap(map);

	bolets.push_back(b);
}

void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/mapa2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	definirProjectils();
	definirFlorecitas();
	definirPlantes();
	definirBolets();

	boss = new Boss();
	boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	boss->setPosition(glm::vec2(INIT_BOSS_X_TILES * map->getTileSize(), INIT_BOSS_Y_TILES * map->getTileSize()));

	definirPowerups();
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	player->setFlorecitas(&florecitas);
	player->setProjectils(&projectils);
	player->setPlantes(&plantes);
	player->setBoss(boss);
	player->setBolets(&bolets);

	player->setPowerups(&powerups);
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
	gui->setPlayer(player);

	//powerup = new Powerups();
	//powerup->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	//powerup->setPosition(glm::vec2((INIT_PLAYER_X_TILES +5) * map->getTileSize(), (INIT_PLAYER_Y_TILES + 3)* map->getTileSize()));
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	gui->update(deltaTime);
	boss->update(deltaTime);

	if (currentTime >= segCanviTiles) {
		map->canviTiles(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		segCanviTiles += 250;
	}

	if (currentTime >= segProjectil) {
		for (auto& p : projectils) {
			p->reset();
		}
		segProjectil += 1000;
	}

	else {
		for (auto& p : projectils) p->update(deltaTime);
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

	for (auto& p : plantes) {
		p->update(deltaTime);
	}

	for (auto& b : bolets) {
		b->update(deltaTime);
	}

	// COSES DE LA CAMERA
	limitszona[0] = glm::vec2(2032, 512);
	limitszona[1] = glm::vec2(2288, 2032);
	limitszona[2] = glm::vec2(256, 2032);
	limitszona[3] = glm::vec2(0, 256);
	limitszona[4] = glm::vec2(256, 752);
	limitszona[5] = glm::vec2(752, 1108);

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
	if (fase == FASE3 && player->getPosition().x >= limitszona[3].y - 16 && player->getPosition().y < 704) {
		player->canvialimit(limitszona[3].y, true);
		fase = FASE4;
		for (auto& b : bolets) {
			b->activate();
		}
	}
	if (fase == FASE4 && player->getPosition().x > limitszona[4].y && player->getPosition().y < 704) {
		player->canvialimit(limitszona[4].y, true);
		fase = FASE5;
		boss->startFight();
		SoundEngine::getInstance()->stopAllSounds();
		SoundEngine::getInstance()->playboss();
	}
	//std::cout << "LIMIT:3 " << fase << std::endl;
	//std::cout << limitszona[2].x << std::endl;
	//std::cout << "LIMIT:4 " << fase << std::endl;
	//std::cout << limitszona[3].y << std::endl;

	//std::cout << "Fase: " << fase << std::endl;
	//std::cout << player->getPosition().x << std::endl;
	//std::cout << player->getPosition().y << std::endl;
	gui->setllanternes(player->getllanternes());
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
	for (auto& p : projectils) {
		p->render();
	}
	for (auto& f : florecitas) {
		f->render();
	}
	for (auto& p : plantes) {
		p->render();
	}
	for (auto& b : bolets) {
		b->render();
	}
	boss->render();
	for (auto& p : powerups) {
		p->render();
	}
	player->render();

	float camHalfWidth = (float(SCREEN_WIDTH) / (2.0f * zoom));
	float camHalfHeight = (float(SCREEN_HEIGHT) / (2.0f * zoom));

	glm::mat4 GUIproj = glm::ortho(0.f, float(camHalfWidth * 2), float(camHalfHeight * 2), 0.f);
	texProgram.setUniformMatrix4f("projection", GUIproj);
	gui->render(player->getvida(), player->getvidamax(), boss->getVida(), boss->getalive());
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
	if (fase == FASE3) {
		camX =  camHalfWidth + 32;
		camY = glm::clamp(camY, MAP_BOTTOM + camHalfHeight, MAP_TOP - camHalfHeight);
	}
	if (fase == FASE4) {
		camX = glm::clamp(camX, limitszona[4].x + 32 + camHalfWidth, limitszona[4].y + 48 - camHalfWidth);
		camY = MAP_BOTTOM + camHalfHeight;
	}
	if (fase == FASE5) {
		camX = 1108 - camHalfWidth;
		camY = MAP_BOTTOM + camHalfHeight;
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

float Scene::getvidaPlayer() {
	return player->getvida();
}

float Scene::getfinalbool() {
	return player->getfinalbool();
}
