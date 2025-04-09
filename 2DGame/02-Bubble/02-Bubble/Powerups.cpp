	#include "Powerups.h"
#include <iostream>

using namespace std;

void Powerups::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int tipus) {
	texture.loadFromFile("images/powerups.png", TEXTURE_PIXEL_FORMAT_RGBA);
	cor = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.33f, 0.5f), &texture, &shaderProgram);
		cor->setNumberAnimations(1);

		cor->setAnimationSpeed(0, 8);
		cor->addKeyframe(0, glm::vec2(0.33f, 0.f));

		cor->changeAnimation(0);

	corgran = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.33f, 0.5f), &texture, &shaderProgram);
		corgran->setNumberAnimations(1);

		corgran->setAnimationSpeed(0, 8);
		corgran->addKeyframe(0, glm::vec2(0.f, 0.f));

		corgran->changeAnimation(0);

	carbassa = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.33f, 0.5f), &texture, &shaderProgram);
		carbassa->setNumberAnimations(1);

		carbassa->setAnimationSpeed(0, 8);
		carbassa->addKeyframe(0, glm::vec2(0.33f, 0.5f));

		carbassa->changeAnimation(0);

	llanterna = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.33f, 0.5f), &texture, &shaderProgram);
		llanterna->setNumberAnimations(1);

		llanterna->setAnimationSpeed(0, 8);
		llanterna->addKeyframe(0, glm::vec2(0.66f, 0.f));

		llanterna->changeAnimation(0);

	pechera = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.33f, 0.5f), &texture, &shaderProgram);
		pechera->setNumberAnimations(1);

		pechera->setAnimationSpeed(0, 8);
		pechera->addKeyframe(0, glm::vec2(0.f, 0.5f));

		pechera->changeAnimation(0);

	texture2.loadFromFile("images/webTotem.png", TEXTURE_PIXEL_FORMAT_RGBA);
	webTotem = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f, 1.f), &texture2, &shaderProgram);
		webTotem->setNumberAnimations(1);

		webTotem->setAnimationSpeed(0, 8);
		webTotem->addKeyframe(0, glm::vec2(0.f, 0.f));

		webTotem->changeAnimation(0);

	tileMapDispl = tileMapPos;
	//cor->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	tocat = false;
	actiu = true;
	type = tipus;
}

void Powerups::setPosition(const glm::vec2& position) {
	pos = position;
	if (type == 1) cor->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	else if (type == 2) corgran->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	else if (type == 3) carbassa->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	else if (type == 4) llanterna->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	else if (type == 5) pechera->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	else if (type == 6) webTotem->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

glm::vec2 Powerups::getPosition() {
	return pos;
}

void Powerups::update(int deltaTime) {
	//cor->update(deltaTime);
	//cor->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Powerups::render() {
	if(!tocat && actiu && type == 1) cor->render();
	else if (!tocat && actiu && type == 2) corgran->render();
	else if (!tocat && actiu && type == 3) carbassa->render();
	else if (!tocat && actiu && type == 4) llanterna->render();
	else if (!tocat && actiu && type == 5) pechera->render();
	else if (!tocat && actiu && type == 6) webTotem->render();
}

void Powerups::reset() {
	pos = posInit;
	cor->setPosition((glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y))));
}

void Powerups::poweruptocat() {
	tocat = true;
}

int Powerups::getType() {
	return type;
}

void Powerups::setactiu() {
	actiu = true;
	tocat = false;
}

void Powerups::setinactiu() {
	actiu = false;
}

bool Powerups::getactiu() {
	return actiu;
}