#pragma once

#include "Sprite.h"
class Bolet
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int dir);
	void setPosition(const glm::vec2& pos);
	void render();
	void reset();
	void update(int deltaTime);
	int getDirection();
	glm::ivec2 getPosition();

private:
	glm::vec2 pos;
	glm::vec2 tileMapDispl;
	Texture texture;
	Sprite* sprite;
	int direction;
};

