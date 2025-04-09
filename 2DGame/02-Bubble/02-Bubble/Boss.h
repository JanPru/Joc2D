#pragma once

#include "Sprite.h"
#include "ProjBoss.h"
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

private:
	void shoot();
	void definirProjectils(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void deactivateProjectils();

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
	std::vector<ProjBoss*> projectils;
	bool alive;
};

