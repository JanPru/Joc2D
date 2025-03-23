#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Start.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 35
#define INIT_PLAYER_Y_TILES 33


Start::Start()
{
	player = NULL;
}

Start::~Start()
{
	if(player != NULL)
		delete player;
}


void Start::init()
{
	initShaders();

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	/*
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	*/
	currentTime = 0.0f;
	spritesheetstart.loadFromFile("images/Pantalla_inici.png", TEXTURE_PIXEL_FORMAT_RGBA);

	spritestart = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(0.2f, 0.3333f), &spritesheetstart, &texProgram);
	spritestart->setNumberAnimations(3);

		spritestart->setAnimationSpeed(0, 1.f);
		spritestart->addKeyframe(0, glm::vec2(0 * 0.2, 0.f));

		spritestart->setAnimationSpeed(1, 4.f);
		spritestart->addKeyframe(1, glm::vec2(1 * 0.2, 0.f));
		spritestart->addKeyframe(1, glm::vec2(2 * 0.2, 0.f));
		spritestart->addKeyframe(1, glm::vec2(3 * 0.2, 0.f));
		spritestart->addKeyframe(1, glm::vec2(4 * 0.2, 0.f));
		spritestart->addKeyframe(1, glm::vec2(0 * 0.2, 0.33333f));
		spritestart->addKeyframe(1, glm::vec2(1 * 0.2, 0.33333f));
		spritestart->addKeyframe(1, glm::vec2(2 * 0.2, 0.33333f));

		spritestart->setAnimationSpeed(2, 1.f);
		spritestart->addKeyframe(2, glm::vec2(3 * 0.2, 0.333333f));

	spritestart->changeAnimation(0);
	counter = 7000;
	counter2 = 1750;
	enable = true;
	enable2 = false;
	bola = new Boles();
	bola->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	bola->setPosition(glm::vec2(SCREEN_WIDTH/2, -24));
}

void Start::update(int deltaTime)
{
	currentTime += deltaTime;
	if (enable) counter -= deltaTime;
	if (enable2) counter2 -= deltaTime;
	//std::cout << currentTime << std::endl;
	spritestart->update(deltaTime);
	if (counter <= 0 && enable) {
		spritestart->changeAnimation(1);
		enable2 = true;
		enable = false;

	}
	else if (counter2 <= 0 && enable2)
	{
		spritestart->changeAnimation(2);
		enable2 = false;
	}
	if(enable) bola->update(deltaTime);

	//player->update(deltaTime);
}

void Start::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("projection", projection);

	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	spritestart->render();
	if(enable) bola->render();
}


void Start::initShaders()
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
