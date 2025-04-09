#include "Explosion.h"

void Explosion::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	texture.loadFromFile("images/explosion.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.33f, 1.f), &texture, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.33f, 0.f));

	sprite->setAnimationSpeed(2, 8);
	sprite->addKeyframe(2, glm::vec2(0.66f, 0.f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	currentTime = 0;
	finished = false;
	active = false;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Explosion::setPositon(const glm::vec2& position) {
	pos = position;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Explosion::update(int deltaTime) {
	if (active && !finished) {
		currentTime += deltaTime;
		if (currentTime >= 500 && currentTime < 1000) sprite->changeAnimation(1);
		else if (currentTime >= 1000 && currentTime < 1500) sprite->changeAnimation(2);
		else if (currentTime > 1500) finished = true;
	}
}

void Explosion::render() {
	if (active && !finished) {
		sprite->render();
	}
}

bool Explosion::isFinished() {
	return finished;
}

void Explosion::activate() {
	active = true;
}