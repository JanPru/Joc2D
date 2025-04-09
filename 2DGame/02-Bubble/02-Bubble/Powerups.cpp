#include "Powerups.h"
#include <iostream>

using namespace std;

void Powerups::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	texture.loadFromFile("images/powerups.png", TEXTURE_PIXEL_FORMAT_RGBA);
	cor = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.33f, 0.5f), &texture, &shaderProgram);
		cor->setNumberAnimations(1);

		cor->setAnimationSpeed(0, 8);
		cor->addKeyframe(0, glm::vec2(0.33f, 0.f));

		cor->changeAnimation(0);

	tileMapDispl = tileMapPos;
	//cor->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Powerups::setPosition(const glm::vec2& position) {
	pos = position;
	posInit = position;
	cor->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

glm::vec2 Powerups::getPosition() {
	return pos;
}

void Powerups::update(int deltaTime) {
	//cor->update(deltaTime);
	cor->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Powerups::render() {
	//cout << "ES PINTAAAAAAAAAAAAAAAA" << endl;
	cor->render();
}

void Powerups::reset() {
	pos = posInit;
	cor->setPosition((glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y))));
}