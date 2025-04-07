#include "Planta.h"

void Planta::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	texture.loadFromFile("images/planta.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 16), glm::vec2(1.f, 0.33f), &texture, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.f, 0.33f));

	sprite->setAnimationSpeed(2, 8);
	sprite->addKeyframe(2, glm::vec2(0.f, 0.66f));

	sprite->changeAnimation(0);

	currentTime = 0;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Planta::setPosition(const glm::vec2& position) {
	pos = position;
	posInit = position;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Planta::update(int deltaTime) {
	currentTime += deltaTime;
	sprite->update(deltaTime);
	if (moving) {
		if (currentTime - lastMoved >= 750) reset();
		else {
			if (currentTime - lastMoved >= 400) sprite->changeAnimation(2);
			pos += glm::vec2(0, 0.4);
			sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
		}
	}
}

void Planta::startMoving() {
	if (!moving) {
		moving = true;
		lastMoved = currentTime;
		sprite->changeAnimation(1);
	}
}

void Planta::render() {
	sprite->render();
}

void Planta::reset() {
	pos = posInit;
	moving = false;
	sprite->changeAnimation(0);
	sprite->setPosition((glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y))));
}

glm::ivec2 Planta::getPosition() {
	return pos;
}
