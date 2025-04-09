#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Player.h"
#include "Game.h"
#include "SoundEngine.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_RIGHT, MOVE_RIGHT, JUMP_RIGHT, STAND, CROUCH, ATTACK_RIGHT, ATTACK_MOVE, ATTACK_CROUCH, JUMP_ATTACK, FALL_ATTACK, DAMAGE // EL ORDRE IMPORTA, ALHORA DE DEFINIR LES ANIMACIONS SHA
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
	sprite->setNumberAnimations(11);

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.33f, 0.f)); //LO PRIMER ES EL ID(ES UN NUMERO REALMENT), LO SEGON EL DESPLAÇAMENT

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

		sprite->setAnimationSpeed(DAMAGE, 8);
		sprite->addKeyframe(DAMAGE, glm::vec2(0.1666666*2, 0.5f));
		
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

	spritellancesvert = Sprite::createSprite(glm::ivec2(40, 15), glm::vec2(0.5f, 0.25f), &spritesheetllances, &shaderProgram);
	spritellancesvert->setNumberAnimations(3);

	spritellancesvert->setAnimationSpeed(0, 8);
	spritellancesvert->addKeyframe(0, glm::vec2(0.5f, 0.5f));

	spritellancesvert->setAnimationSpeed(1, 8);
	spritellancesvert->addKeyframe(1, glm::vec2(0.f, 0.75f));

	spritellancesvert->changeAnimation(0);

	spritesheetfoc.loadFromFile("images/flama.png", TEXTURE_PIXEL_FORMAT_RGBA);

	spritefoc = Sprite::createSprite(glm::ivec2(8, 4), glm::vec2(1, 1), &spritesheetfoc, &shaderProgram);
	spritefoc->setNumberAnimations(1);

	spritefoc->setAnimationSpeed(0, 8);
	spritefoc->addKeyframe(0, glm::vec2(0.f, 0.f));


	spritefoc->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spritellances->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spritefoc->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spritellancesvert->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	posllança = glm::vec2(0, 0);

	limit = 512;
	dreta = true;
	lastProjectil = 0;
	lastBossDamage = 0;
	lastBoletDamage = 0;
	currentTime = 0;
	plantBelow = false;

	vida = 4;
	vidamax = 4;
	llanternes = 2;
	damaged = false;

	godmode = false;

	sprite->esllanca2();
	spritellances->esllanca1();
	spritefoc->esllanca3();
	spritellancesvert->esllanca4();
}

void Player::sons() {
	timers--;
	if (damaged && timers <= 0) {
		SoundEngine::getInstance()->playhit();
		timers = 40;
	}
}

void Player::update(int deltaTime)
{
	currentTime += deltaTime;

	timergod--;

	collisionPowerups();

	sons();
	if (boss->isDead()) powerups->push_back(boss->getPowerup());

	if (Game::instance().getKey(GLFW_KEY_H)) {
		vida = vidamax;
		llanternes = 2;
	}

	if (Game::instance().getKey(GLFW_KEY_G) && timergod < 0) {
		godmode = !godmode;
		timergod = 100;
	}

	timerpress--;
	if (Game::instance().getKey(GLFW_KEY_T) && timerpress <= 0) {
		triar = !triar;
		timerpress = 20;
	}


	if (collisionFlorecitas()) {
		int direction = collisionFlorecitas();

		if (direction == 1) {
			posPlayer.x += 1;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(24, 32)) || (posPlayer.x == limit && dreta)) posPlayer.x -= 1;
		}

		else if (direction == -1) {
			posPlayer.x -= 1;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(24, 32)) || (posPlayer.x == limit + 16 && dreta)) posPlayer.x += 1;
		}
	}

	if (collisionProjectils() && (currentTime - 1000 >= lastProjectil)) {
		setvida(-0.33);
		lastProjectil = currentTime;
	}

	if (collisionBoss() && (currentTime - 1000 >= lastBossDamage)) {
		setvida(-0.33);
		lastBossDamage = currentTime;
	}

	if (collisionBolets() && (currentTime - 1000 >= lastBoletDamage)) {
		setvida(-0.33);
		lastBoletDamage = currentTime;
	}

	sprite->update(deltaTime);
	spritellances->update(deltaTime);
	spritefoc->update(deltaTime);

	if (damaged) {
		spriteTriat = 0;
		damageTimer -= deltaTime;
		if (damageTimer <= 0.f) {
			damaged = false;
			overrideAnimation = false;
			sprite->changeAnimation(lastAnimation); // torna a la que tenia
		}
	}
	if (Game::instance().getKey(GLFW_KEY_UP)) {
		setAnimation(STAND);
		if (Game::instance().getKey(GLFW_KEY_DOWN))
			setAnimation(STAND_RIGHT);
	}
	else if (Game::instance().getKey(GLFW_KEY_DOWN)) {
		if (sprite->animation() != CROUCH && sprite->animation() != ATTACK_CROUCH)
		setAnimation(CROUCH);
		if (Game::instance().getKey(GLFW_KEY_UP))
			setAnimation(STAND);
		else if (Game::instance().getKey(GLFW_KEY_X) && !activaLlança && !bJumping) {
			activaLlança = true;
			timerLlança = 0;
			frameLlança = 0;
			capEndavant = !sprite->getflip();
			spritellances->changeAnimation(ATTACK);
			spriteTriat = 1;
			posllança = glm::vec2(22, 17);
			setAnimation(ATTACK_CROUCH);
			SoundEngine::getInstance()->playpunch();
		}
	}
	else if (Game::instance().getKey(GLFW_KEY_LEFT))
	{
			if (Game::instance().getKey(GLFW_KEY_X)) {
				activaLlança = true;
				spriteTriat = 1;
				timerLlança = 0;
				frameLlança = 0;
				posllança = glm::vec2(24, 9);
				setAnimation(ATTACK_MOVE);
				if (primers) {
					SoundEngine::getInstance()->playpunch();
					primers = false;
				}
			}
			else if (sprite->animation() != MOVE_RIGHT) {
				setAnimation(MOVE_RIGHT);
				primers = true;
			}
			posPlayer.x -= 2;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(24, 32)) || (posPlayer.x == limit && dreta))
			{
				posPlayer.x += 2;
			}
			sprite->canviaflip(true);
			spritellances->canviaflip(true);
			spritefoc->canviaflip(true);
		}
		else if (Game::instance().getKey(GLFW_KEY_RIGHT))
		{
			if (Game::instance().getKey(GLFW_KEY_X)) {
				activaLlança = true;
				spriteTriat = 1;
				timerLlança = 0;
				frameLlança = 0;
				posllança = glm::vec2(24, 9);
				if (primers) {
					SoundEngine::getInstance()->playpunch();
					primers = false;
				}
				if (sprite->animation() != ATTACK_MOVE)
					setAnimation(ATTACK_MOVE);
			}
			else if (sprite->animation() != MOVE_RIGHT) {
				setAnimation(MOVE_RIGHT);
				primers = true;
			}
			posPlayer.x += 2;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(24, 32)) || (posPlayer.x == limit + 16 && !dreta))
			{
				posPlayer.x -= 2;
			}
			sprite->canviaflip(false);
			spritellances->canviaflip(false);
			spritefoc->canviaflip(false);
		}

		else if (Game::instance().getKey(GLFW_KEY_X) && !activaLlança && !bJumping) {
			activaLlança = true;
			timerLlança = 0;
			frameLlança = 0;
			spritellances->changeAnimation(ATTACK);
			spriteTriat = 1;
			posllança = glm::vec2(24, 9);
			setAnimation(ATTACK_RIGHT);
			SoundEngine::getInstance()->playpunch();
		}

		else
		{
			if (sprite->animation() == MOVE_RIGHT || sprite->animation() == JUMP_RIGHT || sprite->animation() == STAND || sprite->animation() == ATTACK_CROUCH || sprite->animation() == CROUCH || sprite->animation() == ATTACK_CROUCH || sprite->animation() == JUMP_ATTACK || sprite->animation() == FALL_ATTACK || sprite->animation() == ATTACK_MOVE){
				setAnimation(STAND_RIGHT);
				spriteTriat = 0;
			}
		}

		if (bJumping)
		{
			primerb = true;
			lava = false;
			if (activaLlança) {
				timerLlança += deltaTime;
				if (sprite->animation() == ATTACK_MOVE) {
					frameLlança = 2;
					spritellances->setkeyframe(frameLlança);
					spriteTriat = 1;
				}
				else if (timerLlança >= 100) {
					timerLlança = 0;

					spritellances->setkeyframe(frameLlança);
					if (frameLlança == 2) {
						activaLlança = false;
						spriteTriat = 0;
						if (Game::instance().getKey(GLFW_KEY_DOWN)) setAnimation(CROUCH);
						else setAnimation(STAND_RIGHT);
					}
					else frameLlança++;
					if (frameLlança == 1) {
						spritefoc->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x + posllança.x + 16), float(tileMapDispl.y + posPlayer.y + posllança.y + 6)));
					}
					else {
						spritefoc->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x + posllança.x + 8), float(tileMapDispl.y + posPlayer.y + posllança.y + 6)));
					}
				}
			}
			else if (Game::instance().getKey(GLFW_KEY_UP)) {
				setAnimation(JUMP_ATTACK);
				spritellancesvert->changeAnimation(0);
				spriteTriat = 2;
				posllança = glm::vec2(-7, -14);
			}
			else if (Game::instance().getKey(GLFW_KEY_DOWN)) {
				setAnimation(FALL_ATTACK);
				spritellancesvert->changeAnimation(1);
				spriteTriat = 2;
				posllança = glm::vec2(-4, 32);
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
				if (plantBelow) posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
				else posPlayer.y = int(startY - 48 * sin(3.14159f * jumpAngle / 180.f));

				if (map->collisionMoveUp(posPlayer, glm::ivec2(24, 32), &posPlayer.y)) {
					bJumping = false;
					jumpAngle = 180;
				}

				if (jumpAngle > 90) {
					if (map->collisionMoveDown(posPlayer, glm::ivec2(24, 32), &posPlayer.y) || collisionFlorecitas() || collisionPlantes()) {
						bJumping = false;
						if (!collisionPlantes()) plantBelow = false;
						else plantBelow = true;
					}
				}

			}
		}
		else
		{
			if (!collisionPlantes()) plantBelow = false;
			else {
				plantBelow = true;
			}
			if (!collisionFlorecitas() && !collisionPlantes()) posPlayer.y += FALL_STEP;
			if (map->collisionMoveDown(posPlayer, glm::ivec2(24, 32), &posPlayer.y) || collisionFlorecitas() || collisionPlantes())
			{
				if (Game::instance().getKey(GLFW_KEY_Z))
				{
					if (primerb) {
						SoundEngine::getInstance()->playjump();
						primerb = false;
					}
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			}
			else
				setAnimation(JUMP_RIGHT);
		}

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
		spritellances->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x + posllança.x), float(tileMapDispl.y + posPlayer.y + posllança.y)));
		spritefoc->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x + posllança.x + 8), float(tileMapDispl.y + posPlayer.y + posllança.y + 6)));
		spritellancesvert->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x + posllança.x), float(tileMapDispl.y + posPlayer.y + posllança.y)));
		if (posPlayer.y == 1120) lava = true;
		//std::cout << "PosPlayer: " << posPlayer.x << " " << posPlayer.y << std::endl;
		if (eslavap())
		{
			timerLava += deltaTime;
			if (primer) {
				setvida(-0.33);
				primer = false;
			}
			if (timerLava > 1000) {
				setvida(-0.33);
				if (vida < 0) vida = 0;
				timerLava = 0;
			}
		}
		else {
			primer = true;
			timerLava = 0;
		}

		if (activaLlança) {
			timerLlança += deltaTime;
			if (sprite->animation() == ATTACK_MOVE) {
				frameLlança = 2;
				spritellances->setkeyframe(frameLlança);
				spriteTriat = 1;
			}
			else if (timerLlança >= 100) {
				timerLlança = 0;

				spritellances->setkeyframe(frameLlança);
				if (frameLlança == 2) {
					activaLlança = false;
					spriteTriat = 0;
					if (Game::instance().getKey(GLFW_KEY_DOWN)) setAnimation(CROUCH);
					else setAnimation(STAND_RIGHT);
				}
				else frameLlança++;
				if (frameLlança == 1) {
					spritefoc->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x + posllança.x + 16), float(tileMapDispl.y + posPlayer.y + posllança.y + 6)));
				}
				else {
					spritefoc->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x + posllança.x + 8), float(tileMapDispl.y + posPlayer.y + posllança.y + 6)));
				}
			}
		}
}

int Player::collisionFlorecitas() {
	if (florecitas == nullptr) return false;

	glm::ivec2 playerSize = glm::ivec2(24, 32);

	const int margen = 4;

	for (auto& flor : *florecitas) {
		glm::vec2 posFlor = flor->getPosition();  
		glm::ivec2 sizeFlor = glm::ivec2(24, 16); 

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

bool Player::collisionPlantes() {
	if (plantes == nullptr) return false;

	glm::ivec2 playerSize = glm::ivec2(24, 32);  

	const int margen = 4; 

	for (auto& p : *plantes) {
		glm::vec2 posPlanta = p->getPosition();  
		glm::ivec2 sizePlanta = glm::ivec2(32, 16); 

		bool estaEncimaHorizontalmente =
			(posPlayer.x + playerSize.x > posPlanta.x) &&
			(posPlayer.x < posPlanta.x + sizePlanta.x);

		bool estaEncimaVerticalmente =
			abs((posPlayer.y + playerSize.y) - posPlanta.y) <= margen;

		if (estaEncimaHorizontalmente && estaEncimaVerticalmente) {
			p->startMoving();
			return true;
		}
	}

	return false;
}

bool Player::collisionProjectils() {
	if (projectils == nullptr) return false;

	glm::ivec2 playerSize = glm::ivec2(24, 32);

	const int margen = 4;

	for (auto& p : *projectils) {
		glm::vec2 posProjectil = p->getPosition();
		glm::ivec2 sizeProjectil = glm::ivec2(16, 16);

		bool overlapX = posPlayer.x < posProjectil.x + sizeProjectil.x &&
			posPlayer.x + playerSize.x > posProjectil.x;

		bool overlapY = posPlayer.y < posProjectil.y + sizeProjectil.y &&
			posPlayer.y + playerSize.y > posProjectil.y;

		if (overlapX && overlapY)
			return true;
	}

	for (auto& p : *projectilsBoss) {
		glm::vec2 posProjectil = p->getPosition();
		glm::ivec2 sizeProjectil = glm::ivec2(16, 16);
		bool overlapX = posPlayer.x < posProjectil.x + sizeProjectil.x &&
			posPlayer.x + playerSize.x > posProjectil.x;
		bool overlapY = posPlayer.y < posProjectil.y + sizeProjectil.y &&
			posPlayer.y + playerSize.y > posProjectil.y;
		if (overlapX && overlapY)
			return true;
	}
	return false;
}

bool Player::collisionBoss() {
	glm::vec2 bossPosition = boss->getPosition();
	glm::ivec2 sizeBoss = glm::ivec2(32, 48);
	if (activaLlança) {
		glm::ivec2 playerSize = glm::ivec2(32, 32);

		if (!sprite->getflip()) {
			glm::vec2 posAux = glm::vec2(posPlayer.x + 16, posPlayer.y);

			bool overlapX = posAux.x < bossPosition.x + sizeBoss.x &&
				posAux.x + playerSize.x > bossPosition.x;

			bool overlapY = posAux.y < bossPosition.y + sizeBoss.y &&
				posAux.y + playerSize.y > bossPosition.y;

			if (overlapX && overlapY) {
				if (triar) boss->setVida(-0.33);
				else boss->setVida(-0.66);
				if (boss->getVida() < 0.33) {
					boss->die();
				}
			}
		}

		else {
			glm::vec2 posAux = glm::vec2(posPlayer.x - 16, posPlayer.y);

			bool overlapX = posAux.x < bossPosition.x + sizeBoss.x &&
				posAux.x + playerSize.x > bossPosition.x;

			bool overlapY = posAux.y < bossPosition.y + sizeBoss.y &&
				posAux.y + playerSize.y > bossPosition.y;

			if (overlapX && overlapY) {
				if (triar) boss->setVida(-0.33);
				else boss->setVida(-0.66);
				if (boss->getVida() < 0.33) {
					boss->die();
				}
			}
		}
	}

	bool overlapX = posPlayer.x < bossPosition.x + sizeBoss.x &&
		posPlayer.x + sizeBoss.x > bossPosition.x;

	bool overlapY = posPlayer.y < bossPosition.y + sizeBoss.y &&
		posPlayer.y + sizeBoss.y > bossPosition.y;

	if (overlapX && overlapY && !boss->isDead())
		return true;

	else return false;
}

void Player::collisionPowerups() {
	if (powerups != nullptr) {
		glm::ivec2 playerSize = glm::ivec2(24, 32);

		const int margen = 4;
		timervida--;

		for (auto& p : *powerups) {
			glm::vec2 posProjectil = p->getPosition();
			glm::ivec2 sizeProjectil = glm::ivec2(16, 16);

			bool overlapX = posPlayer.x < posProjectil.x + sizeProjectil.x &&
				posPlayer.x + playerSize.x > posProjectil.x;

			bool overlapY = posPlayer.y < posProjectil.y + sizeProjectil.y &&
				posPlayer.y + playerSize.y > posProjectil.y;

			if (overlapX && overlapY && p->getactiu()) {
				p->poweruptocat();
				if (p->getactiu()) {
					int tipus = p->getType();
					if (tipus == 1) {
						setvida(1);
					}
					else if (tipus == 2) {
						setvida(vidamax);
					}
					else if (tipus == 4) {
						if (llanternes < 4) {
							llanternes++;
						}
					}
					else if (tipus == 3) {
						vidamax++;
					}
					else if (tipus == 5) {
						comença_timer = true;
						godmode = true;
					}

				}
				p->setinactiu();
			}

		}

	}
	if (comença_timer) {
		timervida--;
		//cout << "timervida: " << timervida << endl;
		if (timervida <= 0) {
			godmode = false;
			comença_timer = false;
			timervida = 463;
		}
	}
}

bool Player::collisionBolets() {
	glm::ivec2 playerSize = glm::ivec2(24, 32);

	for (auto& b : *bolets) {
		glm::vec2 posBolet = b->getPosition();
		glm::ivec2 sizeBolet = glm::ivec2(16, 16);

		if (activaLlança) {
			glm::ivec2 playerSize = glm::ivec2(32, 32);

			if (!sprite->getflip()) {
				glm::vec2 posAux = glm::vec2(posPlayer.x + 16, posPlayer.y);

				bool overlapX = posAux.x < posBolet.x + sizeBolet.x &&
					posAux.x + playerSize.x > posBolet.x;

				bool overlapY = posAux.y < posBolet.y + sizeBolet.y &&
					posAux.y + playerSize.y > posBolet.y;

				if (overlapX && overlapY) {
					b->die();
					Powerups* p = b->getPowerup();
					powerups->push_back(p);
				}
			}

			else {
				glm::vec2 posAux = glm::vec2(posPlayer.x - 16, posPlayer.y);

				bool overlapX = posAux.x < posBolet.x + sizeBolet.x &&
					posAux.x + playerSize.x > posBolet.x;

				bool overlapY = posAux.y < posBolet.y + sizeBolet.y &&
					posAux.y + playerSize.y > posBolet.y;

				if (overlapX && overlapY)
					b->die();
					Powerups* p = b->getPowerup();
					powerups->push_back(p);
			}
		}

		if (b->isAlive()) {
			glm::ivec2 playerSize = glm::ivec2(24, 32);

			bool overlapX = posPlayer.x < posBolet.x + sizeBolet.x &&
				posPlayer.x + playerSize.x > posBolet.x;

			bool overlapY = posPlayer.y < posBolet.y + sizeBolet.y &&
				posPlayer.y + playerSize.y > posBolet.y;

			if (overlapX && overlapY) return true;
		}
	}

	return false;
}

void Player::setFlorecitas(std::vector<Florecita*>* flors) {
	florecitas = flors;
}

void Player::setProjectils(std::vector<Projectil*>* proj) {
	projectils = proj;
}

void Player::setPlantes(std::vector<Planta*>* plant) {
	plantes = plant;
}

void Player::setPowerups(std::vector<Powerups*>* prow) {
	powerups = prow;
}

void Player::setBoss(Boss* b) {
	boss = b;
	projectilsBoss = &b->getProjectils();
}

void Player::setBolets(std::vector<Bolet*>* bol) {
	bolets = bol;
}

void Player::render()
{
	sprite->render();
	if (spriteTriat == 1) {
		spritellances->render();
		if (!triar) {
			spritefoc->render();
		}
	}
	if (spriteTriat == 2) {
		spritellancesvert->render();
	}
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

float Player::getvidamax() {
	return vidamax;
}

int Player::getllanternes() {
	return llanternes;
}

bool Player::gettriar() {
	return triar;
}

void Player::setvida(float v) {
	if (!godmode) {
		vidaant = vida;
		vida = vida + v;
		if (vida < vidaant && !damaged) {
			damaged = true;
			damageTimer = damageDuration;
			lastAnimation = sprite->animation();
			overrideAnimation = true;
			sprite->changeAnimation(DAMAGE);
		}
		if (vida < 0.33f) {
			if (llanternes > 0) {
				llanternes--;
				vida = 4;
			}
		}
	}
}

void Player::setAnimation(int anim) {
	if (!overrideAnimation && sprite->animation() != anim) {
		sprite->changeAnimation(anim);
	}
}

bool Player::eslavap() {
	return lava && map->eslava();
}