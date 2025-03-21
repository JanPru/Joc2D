#pragma once

#include "Sprite.h"
class Projectil
{
public:
	Projectil();
	Projectil(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
	void activate();
	bool isActive();

private:
	glm::vec2 pos;
	glm::vec2 posInit;
	float velocity;
	Texture texture;
	Sprite *sprite;
	bool active;
};

