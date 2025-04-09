#include "bolet.h"

void Bolet::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int dir) {
	texture.loadFromFile("images/florecita.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 16), glm::vec2(1.f, 1.f), &texture, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	direction = dir;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}