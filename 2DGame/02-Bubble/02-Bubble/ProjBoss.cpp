#include "ProjBoss.h"

void ProjBoss::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int type) {
	texture.loadFromFile("images/projBoss.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25f, 1.f), &texture, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(2, 8);
	sprite->addKeyframe(2, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(3, 8);
	sprite->addKeyframe(3, glm::vec2(0.75f, 0.f));

	sprite->changeAnimation(type);

	if (type == 0) direction = glm::vec2(2, -2);
	else if(type == 1) direction = glm::vec2(2, 2);
	else if (type == 2) direction = glm::vec2(-2, 2);
	else if (type == 3) direction = glm::vec2(-2, -2);
	active = false;
	this->type = type;

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void ProjBoss::setPosition(const glm::vec2& position) {
	pos = position;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void ProjBoss::render() {
	if (active) sprite->render();
}

void ProjBoss::update(int deltaTime) {
	if (active) {
		sprite->update(deltaTime);
		pos += direction;
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	}
}

void ProjBoss::activate() {
	active = true;
}

void ProjBoss::deactivate() {
	active = false;
}

int ProjBoss::getType() {
	return type;
}

glm::vec2 ProjBoss::getPosition() {
	return pos;
}