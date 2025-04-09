#pragma once

#include "Sprite.h"
#include "ProjBoss.h"
#include "Powerups.h"
class Boss
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void setPosition(const glm::vec2& pos);
	void render();
	void update(int deltaTime);
	std::vector<ProjBoss*>& getProjectils();
	glm::vec2 getPosition();
	void startFight();
	void setVida(float v);
	Powerups* getPowerup();
	float getVida();
	void die();

private:
	void shoot();
	void definirProjectils(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void deactivateProjectils();
	void startMoving();

private:
	glm::vec2 pos;
	glm::vec2 posInit;
	glm::vec2 tileMapDispl;
	Texture texture;
	Sprite* sprite;
	int nextChange;
	int currentTime;
	int nextShot;
	int lastShot;
	int lastDamaged;
	float vida;
	Powerups* totem;
	std::vector<ProjBoss*> projectils;
	glm::vec2 positions[4];
	glm::vec2 nextPosition;
	glm::vec2 lastPosition;
	glm::vec2 direction;
	int lastMoved;
	int distance;
	bool moving;
	bool alive;
};

