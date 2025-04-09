#pragma once

#include "Sprite.h"
class ProjBoss
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int type);
	void update(int deltaTime);
	void render();
	void setPosition(const glm::vec2& pos);
	void deactivate();
	void activate();
	int getType();
	glm::vec2 getPosition();

private:
	glm::vec2 pos;
	glm::vec2 tileMapDispl;
	float velocity;
	Texture texture;
	Sprite* sprite;
	bool active;
	int type;
	glm::vec2 direction;
};