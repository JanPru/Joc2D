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
	STAND_RIGHT, MOVE_RIGHT, JUMP_RIGHT, STAND, CROUCH
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/SpritePersonatge.png", TEXTURE_PIXEL_FORMAT_RGBA);
	float sw = 1 / 6;
	float sh = 1 / 4;
	sprite = Sprite::createSprite(glm::ivec2(24, 32), glm::vec2(0.166666666, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.33f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT,8 );
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3*0.1666666, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4*0.1666666, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(5*0.1666666, 0.f));

		sprite->setAnimationSpeed(JUMP_RIGHT, 8);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(5 * 0.1666666, 0.25f));

		sprite->setAnimationSpeed(STAND, 8);
		sprite->addKeyframe(STAND, glm::vec2(4 * 0.1666666, 0.25f));

		sprite->setAnimationSpeed(CROUCH, 8);
		sprite->addKeyframe(CROUCH, glm::vec2(5 * 0.1666666, 0.25f));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getKey(GLFW_KEY_UP)) {
		sprite->changeAnimation(STAND);
		if (Game::instance().getKey(GLFW_KEY_DOWN))
			sprite->changeAnimation(STAND_RIGHT);
	}
	else if(Game::instance().getKey(GLFW_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_RIGHT)
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
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(24, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
		sprite->canviaflip(false);
	}
	else
	{
		if(sprite->animation() == MOVE_RIGHT || sprite->animation() == JUMP_RIGHT || sprite->animation() == STAND)
			sprite->changeAnimation(STAND_RIGHT);
		
	}
	
	if(bJumping)
	{
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
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
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




