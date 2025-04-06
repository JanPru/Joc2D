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
};																																			//DE POSAR EL MATEIX PUTO ORDRE

enum LlancesAnims
{
	JUMP_ATTACKL, FALL_ATTACKL, ATTACK
};

void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/SpritePersonatge.png", TEXTURE_PIXEL_FORMAT_RGBA);
	float sw = 1 / 6;
	float sh = 1 / 4;
	sprite = Sprite::createSprite(glm::ivec2(24, 32), glm::vec2(0.166666666, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.33f, 0.f)); //LO PRIMER ES EL ID(ES UN NUMERO REALMENT), LO SEGON EL DESPLA�AMENT

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3 * 0.1666666, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4 * 0.1666666, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(5 * 0.1666666, 0.f));

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

	sprite->setAnimationSpeed(JUMP_ATTACK, 8);
	sprite->addKeyframe(JUMP_ATTACK, glm::vec2(0.1666666, 0.75f));

	sprite->setAnimationSpeed(FALL_ATTACK, 8);
	sprite->addKeyframe(FALL_ATTACK, glm::vec2(0.1666666, 0.5f));

	sprite->changeAnimation(0);

	spritesheetllances.loadFromFile("images/llances.png", TEXTURE_PIXEL_FORMAT_RGBA);

	spritellances = Sprite::createSprite(glm::ivec2(40, 15), glm::vec2(0.5f, 0.25f), &spritesheetllances, &shaderProgram);
	spritellances->setNumberAnimations(3);

	spritellances->setAnimationSpeed(JUMP_ATTACKL, 8);
	spritellances->addKeyframe(JUMP_ATTACKL, glm::vec2(0.5f, 0.5f));

	spritellances->setAnimationSpeed(FALL_ATTACKL, 8);
	spritellances->addKeyframe(FALL_ATTACKL, glm::vec2(0.f, 0.75f));

	spritellances->setAnimationSpeed(ATTACK, 8);
	spritellances->addKeyframe(ATTACK, glm::vec2(0.f, 0.5f));
	spritellances->addKeyframe(ATTACK, glm::vec2(0.5f, 0.25f));
	spritellances->addKeyframe(ATTACK, glm::vec2(0.f, 0.5f));


	spritellances->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spritellances->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	posllan�a = glm::vec2(0, 0);

	limit = 512;
	dreta = true;

	vida = 4;
}

void Player::update(int deltaTime)
{
	if (collisionFlorecitas()) {
		int direction = collisionFlorecitas();

		if (direction == 1) {
			posPlayer.x += 1;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(24, 32)) || (posPlayer.x == limit + 16 && dreta)) posPlayer.x -= 1;
		}

		else if (direction == -1) {
			posPlayer.x -= 1;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(24, 32)) || (posPlayer.x == limit + 16 && dreta)) posPlayer.x += 1;
		}
	}

	sprite->update(deltaTime);
	spritellances->update(deltaTime);

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
	else if (Game::instance().getKey(GLFW_KEY_LEFT))
	{
		if (Game::instance().getKey(GLFW_KEY_X)) {
			if (sprite->animation() != ATTACK_MOVE)
				sprite->changeAnimation(ATTACK_MOVE);
		}
		else if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x -= 2;
		//if (map->collisionMoveLeft(posPlayer, glm::ivec2(24, 32)) || (posPlayer.x == limit + 16 && dreta))
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(24, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
		sprite->canviaflip(true);
	}
	else if (Game::instance().getKey(GLFW_KEY_RIGHT))
	{
		if (Game::instance().getKey(GLFW_KEY_X)) {
			if (sprite->animation() != ATTACK_MOVE)
				sprite->changeAnimation(ATTACK_MOVE);
		}
		else if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		//if (map->collisionMoveRight(posPlayer, glm::ivec2(24, 32)) || (posPlayer.x == limit + 16 && !dreta))
		if (map->collisionMoveRight(posPlayer, glm::ivec2(24, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
		sprite->canviaflip(false);
	}
	else if (Game::instance().getKey(GLFW_KEY_X)) {
		sprite->changeAnimation(ATTACK_RIGHT);
		spritellances->changeAnimation(ATTACK);
		spriteTriat = 1;
		posllan�a = glm::vec2(24, 10);
	}
	else
	{
		if (sprite->animation() == MOVE_RIGHT || sprite->animation() == JUMP_RIGHT || sprite->animation() == STAND || sprite->animation() == CROUCH || sprite->animation() == ATTACK_RIGHT || sprite->animation() == ATTACK_CROUCH || sprite->animation() == JUMP_ATTACK || sprite->animation() == FALL_ATTACK) {
			sprite->changeAnimation(STAND_RIGHT);
			spriteTriat = 0;
		}
	}

	if (bJumping)
	{
		if (Game::instance().getKey(GLFW_KEY_UP)) {
			sprite->changeAnimation(JUMP_ATTACK);
			spritellances->changeAnimation(JUMP_ATTACKL);
			spriteTriat = 1;
			posllan�a = glm::vec2(-7, -14);
		}
		else if (Game::instance().getKey(GLFW_KEY_DOWN)) {
			sprite->changeAnimation(FALL_ATTACK);
			spritellances->changeAnimation(FALL_ATTACKL);
			spriteTriat = 1;
			posllan�a = glm::vec2(-4, 32);
		}
		else spriteTriat = 0;
		if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90) {
				if (map->collisionMoveDown(posPlayer, glm::ivec2(24, 32), &posPlayer.y) || collisionFlorecitas()) bJumping = false;
			}

		}
	}
	else
	{
		if (!collisionFlorecitas()) posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(24, 32), &posPlayer.y) || collisionFlorecitas())
		{
			if (Game::instance().getKey(GLFW_KEY_Z))
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
	spritellances->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x + posllan�a.x), float(tileMapDispl.y + posPlayer.y + posllan�a.y)));

	if (map->eslava())
	{
		timerLava += deltaTime;
		if (timerLava > 1000) {
			vida -= 0.33f;
			if (vida < 0) vida = 0;
			timerLava = 0;
		}
	}
	else {
		timerLava = 0;
	}
}

int Player::collisionFlorecitas() {
	if (florecitas == nullptr) return false;

	glm::ivec2 playerSize = glm::ivec2(24, 32);  // el tama�o del sprite

	const int margen = 4; // tolerancia vertical

	for (auto& flor : *florecitas) {
		glm::vec2 posFlor = flor->getPosition();  // Asegurate de tener este m�todo
		glm::ivec2 sizeFlor = glm::ivec2(24, 16); // Tama�o de flor (ajustalo si es distinto)

		bool estaEncimaHorizontalmente =
			(posPlayer.x + playerSize.x > posFlor.x) &&
			(posPlayer.x < posFlor.x + sizeFlor.x);

		bool estaEncimaVerticalmente =
			abs((posPlayer.y + playerSize.y) - posFlor.y) <= margen;

		if (estaEncimaHorizontalmente && estaEncimaVerticalmente)
			return flor->getDirection();
	}

	return 0;
}

void Player::setFlorecitas(std::vector<Florecita*>* flors) {
	florecitas = flors;
}

void Player::render()
{
	sprite->render();
	if (spriteTriat == 1) spritellances->render();
}

void Player::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::vec2 Player::getPosition() const {
	return posPlayer;
}

void Player::canvialimit(int l, bool b) {
	limit = l;
	dreta = b;
}

float Player::getvida() {
	return vida;
}
