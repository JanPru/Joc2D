#pragma once

#include "Sprite.h"
class Planta
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void setPosition(const glm::vec2& pos);
	void render();
	void reset();
	void update(int deltaTime);
	void startMoving();
	glm::ivec2 getPosition();

private:
	glm::vec2 pos;
	glm::vec2 posInit;
	glm::vec2 tileMapDispl;
	Texture texture;
	Sprite* sprite;
	int currentTime;
	int lastMoved;
	bool moving;
};

