#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_RIGHT, MOVE_RIGHT, JUMP_RIGHT, STAND, CROUCH, ATTACK_RIGHT, ATTACK_MOVE, ATTACK_CROUCH, JUMP_ATTACK, FALL_ATTACK // EL ORDRE IMPORTA, ALHORA DE DEFINIR LES ANIMACIONS SHA
};																								//DE POSAR EL MATEIX PUTO ORDRE


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/SpritePersonatge.png", TEXTURE_PIXEL_FORMAT_RGBA);
	float sw = 1 / 6;
	float sh = 1 / 4;
	sprite = Sprite::createSprite(glm::ivec2(24, 32), glm::vec2(0.166666666, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.33f, 0.f)); //LO PRIMER ES EL ID(ES UN NUMERO REALMENT), LO SEGON EL DESPLAÇAMENT
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3*0.1666666, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4*0.1666666, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(5*0.1666666, 0.f));

		sprite->setAnimationSpeed(JUMP_RIGHT, 8);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(5 * 0.1666666, 0.25f));

		sprite->setAnimationSpeed(STAND, 8);
		sprite->addKeyframe(STAND, glm::vec2(4 * 0.1666666, 0.25f));

		sprite->setAnimationSpeed(CROUCH, 8);
		sprite->addKeyframe(CROUCH, glm::vec2(5 * 0.1666666, 0.25f));

		sprite->setAnimationSpeed(ATTACK_RIGHT, 8);
		sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(0.16666, 0.25f));
		sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(0.16666, 0.25f));
		sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(0.16666, 0.25f));

		sprite->setAnimationSpeed(ATTACK_MOVE, 8);
		sprite->addKeyframe(ATTACK_MOVE, glm::vec2(1 * 0.1666666, 0.25f));
		sprite->addKeyframe(ATTACK_MOVE, glm::vec2(2 * 0.1666666, 0.25f));
		sprite->addKeyframe(ATTACK_MOVE, glm::vec2(3 * 0.1666666, 0.25f));

		sprite->setAnimationSpeed(ATTACK_CROUCH, 8);
		sprite->addKeyframe(ATTACK_CROUCH, glm::vec2(0.f, 0.5f));
		sprite->addKeyframe(ATTACK_CROUCH, glm::vec2(0.f, 0.5f));
		sprite->addKeyframe(ATTACK_CROUCH, glm::vec2(0.f, 0.5f));
		
	sprite->changeAnimation(0);

	spriteGrande = Sprite::createSprite(glm::ivec2(24, 32), glm::vec2(0.16666666, 0.5), &spritesheet, &shaderProgram);
	spriteGrande->setNumberAnimations(2);

		spriteGrande->setAnimationSpeed(JUMP_ATTACK, 8);
		spriteGrande->addKeyframe(JUMP_ATTACK, glm::vec2(0.16666f, 0.5f));

		spriteGrande->setAnimationSpeed(FALL_ATTACK, 8);
		spriteGrande->addKeyframe(FALL_ATTACK, glm::vec2(0.5f, 0.5f));

	spriteGrande->changeAnimation(5);



	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteGrande->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteTriat = 1;
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	spriteGrande->update(deltaTime);

	if (Game::instance().getKey(GLFW_KEY_UP)) {
		sprite->changeAnimation(STAND);
		if (Game::instance().getKey(GLFW_KEY_DOWN))
			sprite->changeAnimation(STAND_RIGHT);
	}
	else if (Game::instance().getKey(GLFW_KEY_DOWN)) {
		sprite->changeAnimation(CROUCH);
		if (Game::instance().getKey(GLFW_KEY_UP))
			sprite->changeAnimation(STAND);
		else if (Game::instance().getKey(GLFW_KEY_X)) {
			if (sprite->animation() != ATTACK_CROUCH)
				sprite->changeAnimation(ATTACK_CROUCH);
		}
	}
	else if(Game::instance().getKey(GLFW_KEY_LEFT))
	{
		if (Game::instance().getKey(GLFW_KEY_X)) {
			if (sprite->animation() != ATTACK_MOVE)
				sprite->changeAnimation(ATTACK_MOVE);
		}
		else if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(24, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
		sprite->canviaflip(true);
	}
	else if(Game::instance().getKey(GLFW_KEY_RIGHT))
	{
		if (Game::instance().getKey(GLFW_KEY_X)) {
			if (sprite->animation() != ATTACK_MOVE)
				sprite->changeAnimation(ATTACK_MOVE);
		}
		else if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(24, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
		sprite->canviaflip(false);
	}
	else if (Game::instance().getKey(GLFW_KEY_X)) {
		sprite->changeAnimation(ATTACK_RIGHT);
	}
	else
	{
		if(sprite->animation() == MOVE_RIGHT || sprite->animation() == JUMP_RIGHT || sprite->animation() == STAND || sprite->animation() == CROUCH || sprite->animation() == ATTACK_RIGHT || sprite->animation() == ATTACK_CROUCH)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		if (Game::instance().getKey(GLFW_KEY_UP)) {
			spriteGrande->changeAnimation(JUMP_ATTACK);
			spriteTriat = 2;
		}
		else spriteTriat = 1;
		if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(24, 32), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(24, 32), &posPlayer.y))
		{
			if(Game::instance().getKey(GLFW_KEY_Z))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
		else
			sprite->changeAnimation(JUMP_RIGHT);
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteGrande->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	if (spriteTriat == 1)sprite->render();
	else spriteGrande->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::vec2 Player::getPosition() const {
	return posPlayer;
}




