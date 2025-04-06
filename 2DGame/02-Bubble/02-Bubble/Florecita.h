#pragma once

#include "Sprite.h"
class Florecita
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int dir);
	void setPosition(const glm::vec2& pos);
	void render();
	void reset();
	void update(int deltaTime);
	int getDirection();
	glm::ivec2 getPosition();
	glm::vec4 getCollisionBox();

private:
	glm::vec2 pos;
	glm::vec2 posInit;
	glm::vec2 tileMapDispl;
	Texture texture;
	Sprite* sprite;
	int direction;
};

