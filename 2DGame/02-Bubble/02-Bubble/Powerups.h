#ifndef _POWERUPS_INCLUDE
#define _POWERUPS_INCLUDE

#pragma once

#include "Sprite.h"
class Powerups
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
	void reset();
	void setPosition(const glm::vec2& pos);
	glm::vec2 getPosition();

private:
	glm::vec2 pos;
	glm::vec2 posInit;
	glm::vec2 tileMapDispl;
	float velocity;
	Texture texture;
	Sprite* cor;
	Sprite* corgran;
	Sprite* carbassa;
	bool active;
};

#endif // _POWERUPS_INCLUDE

