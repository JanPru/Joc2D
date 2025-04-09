#include "Bolet.h"

#define JUMP_ANGLE_STEP 4
#define FALL_STEP 4

enum BoletAnims {
	STAND_LEFT, JUMP_LEFT, JUMP_RIGHT, STAND_RIGHT
};

void Bolet::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int dir) {
	texture.loadFromFile("images/bolet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25f, 1.f), &texture, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(JUMP_LEFT, 8);
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(JUMP_RIGHT, 8);
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.75f, 0.f));
	sprite->changeAnimation(0);

	powerup = new Powerups();
	int type = (std::rand() % 5) + 1;
	powerup->init(tileMapPos, shaderProgram, type);

	std::srand(std::time(nullptr));
	tileMapDispl = tileMapPos;
	direction = dir;
	alive = false;
	jumping = false;
	currentTime = 0;
	nextJump = (std::rand() % 500) + 1000;
	nextChangeDirection = (std::rand() % 6000) + 1000;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Bolet::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Bolet::setPosition(const glm::vec2& position) {
	pos = position;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Bolet::update(int deltaTime) {
	if (alive) {
		currentTime += deltaTime;

		if (currentTime >= nextChangeDirection && !jumping) {
			if (direction == 1) {
				sprite->changeAnimation(STAND_LEFT);
				direction = -1;
			}
			else {
				sprite->changeAnimation(STAND_RIGHT);
				direction = 1;
			}
			nextChangeDirection += (std::rand() % 2000) + 3000;
		}

		if (jumping) {

			if (direction == 1 && !map->collisionMoveRight(pos, glm::ivec2(16, 16))) pos.x += 1;
			else if (direction == -1 && !map->collisionMoveLeft(pos, glm::ivec2(16, 16))) pos.x -= 1;

			jumpAngle += JUMP_ANGLE_STEP;

			if (jumpAngle == 180) {
				jumping = false;
				pos.y = startY;
			}

			else
			{
				pos.y = int(startY - 32 * sin(3.14159f * jumpAngle / 180.f));

				if (jumpAngle > 90) {
					if (map->collisionMoveDown(pos, glm::ivec2(16, 16), &pos.y)) {
						jumping = false;
						if (direction == 1) sprite->changeAnimation(STAND_RIGHT);
						else sprite->changeAnimation(STAND_LEFT);
					}
				}

			}
		}

		else {
			pos.y += FALL_STEP;

			if (map->collisionMoveDown(pos, glm::ivec2(16, 16), &pos.y)) {
				if (currentTime >= nextJump) {
					jumpAngle = 0;
					startY = pos.y;
					jumping = true;
					if (direction == 1) sprite->changeAnimation(JUMP_RIGHT);
					else sprite->changeAnimation(JUMP_LEFT);
					nextJump += (std::rand() % 500) + 1000;
				}
				else {
					if (direction == 1) sprite->changeAnimation(STAND_RIGHT);
					else sprite->changeAnimation(STAND_LEFT);
				}
			}
			else {
				if (direction == 1 && !map->collisionMoveRight(pos, glm::ivec2(16, 16))) pos.x += 1;
				else if (direction == -1 && !map->collisionMoveLeft(pos, glm::ivec2(16, 16))) pos.x -= 1;
			}
		}

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	}
}

void Bolet::render() {
	if (alive) sprite->render();
}

void Bolet::die() {
	alive = false;
	powerup->setPosition(pos);
}

void Bolet::activate() {
	alive = true;
}

glm::ivec2 Bolet::getPosition() {
	return pos;
}

bool Bolet::isAlive() {
	return alive;
}

Powerups* Bolet::getPowerup() {
	return powerup;
}