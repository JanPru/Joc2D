#pragma once

#include "Sprite.h"
class Explosion
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
	void setPositon(const glm::vec2& position);
	void activate();
	bool isFinished();

private:
	Texture texture;
	Sprite* sprite;
	glm::vec2 tileMapDispl;
	glm::vec2 pos;
	bool active;
	bool finished;
	int currentTime;
};

