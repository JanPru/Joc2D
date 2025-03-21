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
	spritestart->setNumberAnimations(1);

		spritestart->setAnimationSpeed(0,2);
		spritestart->addKeyframe(0, glm::vec2(0 * 0.2, 0.f));
		spritestart->addKeyframe(0, glm::vec2(1 * 0.2, 0.f));
		spritestart->addKeyframe(0, glm::vec2(2 * 0.2, 0.f));

	spritestart->changeAnimation(0);
}

void Start::update(int deltaTime)
{
	currentTime += deltaTime;
	spritestart->update(deltaTime);
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
