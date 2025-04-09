#include "Projectil.h"
#include <iostream>

using namespace std;

void Projectil::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	texture.loadFromFile("images/projectil.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f, 1.f), &texture, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Projectil::setPosition(const glm::vec2& position) {
	pos = position;
	posInit = position;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

glm::vec2 Projectil::getPosition() {
	return pos;
}

void Projectil::update(int deltaTime) {
	sprite->update(deltaTime);
	pos -= glm::vec2(0, 3);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Projectil::render() {
	sprite->render();
}

void Projectil::reset() {
	pos = posInit;
	sprite->setPosition((glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y))));
}