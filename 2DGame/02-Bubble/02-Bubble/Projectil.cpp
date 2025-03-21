#include "Projectil.h"

Projectil::Projectil() {
	sprite = nullptr;
}

Projectil::Projectil(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	texture.loadFromFile("images/projectil.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.f, 0.f), &texture, &shaderProgram);
	sprite->setNumberAnimations(1);
	posInit = tileMapPos;

	active = false;
	velocity = 0.01f;
}

void Projectil::update(int deltaTime) {
	if (active) {
		pos += glm::vec2(0, int(velocity * float(deltaTime)));
		sprite->setPosition(pos);
		sprite->update(deltaTime);
	}
}

void Projectil::render() {
	if(active)
		sprite->render();
}

void Projectil::activate() {
	active = true;
	pos = posInit;
	sprite->setPosition(posInit);
}

bool Projectil::isActive() {
	return active;
}