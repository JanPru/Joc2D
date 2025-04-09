#ifndef _POWERUPS_INCLUDE
#define _POWERUPS_INCLUDE

#pragma once

#include "Sprite.h"
class Powerups
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int i);
	void update(int deltaTime);
	void render();
	void reset();
	void setPosition(const glm::vec2& pos);
	glm::vec2 getPosition();
	void poweruptocat();
	int getType();

	void setactiu();
	void setinactiu();
	bool getactiu();

private:
	glm::vec2 pos;
	glm::vec2 posInit;
	glm::vec2 tileMapDispl;
	float velocity;
	Texture texture;
	Texture texture2;
	Sprite* cor;
	Sprite* corgran;
	Sprite* carbassa;
	Sprite* llanterna;
	Sprite* pechera;
	Sprite* webTotem;
	bool actiu;
	int type; //1 cor 2 corgran 3 carbassa 4 llanterna 5 pechera
	bool tocat;
};

#endif // _POWERUPS_INCLUDE

