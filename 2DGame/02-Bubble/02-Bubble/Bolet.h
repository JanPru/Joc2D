#pragma once

#include "Sprite.h"
#include "TileMap.h"
#include "Powerups.h"
class Bolet
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int dir);
	void setPosition(const glm::vec2& pos);
	void render();
	void setTileMap(TileMap* tileMap);
	void die();
	void update(int deltaTime);
	bool isAlive();
	void activate();
	Powerups* getPowerup();
	glm::ivec2 getPosition();

private:
	glm::ivec2 pos;
	int startY, jumpAngle;
	glm::vec2 tileMapDispl;
	Texture texture;
	Sprite* sprite;
	TileMap* map;
	Powerups* powerup;
	int direction;
	bool alive;
	bool jumping;
	int currentTime;
	int nextJump;
	int nextChangeDirection;
};

