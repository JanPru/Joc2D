#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Boles.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
																																	
void Boles::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/boles.png", TEXTURE_PIXEL_FORMAT_RGBA);

	sprite1 = Sprite::createSprite(glm::ivec2(48, 48), glm::vec2(0.1428f, 1), &spritesheet, &shaderProgram);
	sprite1->setNumberAnimations(7);

		sprite1->setAnimationSpeed(0, 1.f);
		sprite1->addKeyframe(0, glm::vec2(0 * 0.1428f, 0.f));

		sprite1->setAnimationSpeed(1, 1.f);
		sprite1->addKeyframe(1, glm::vec2(1 * 0.1428f, 0.f));

		sprite1->setAnimationSpeed(2, 1.f);
		sprite1->addKeyframe(2, glm::vec2(2 * 0.1428f, 0.f));

		sprite1->setAnimationSpeed(3, 1.f);
		sprite1->addKeyframe(3, glm::vec2(3 * 0.1428f, 0.f));

		sprite1->setAnimationSpeed(4, 1.f);
		sprite1->addKeyframe(4, glm::vec2(4 * 0.1428f, 0.f));

		sprite1->setAnimationSpeed(5, 1.f);
		sprite1->addKeyframe(5, glm::vec2(5 * 0.1428f, 0.f));

		sprite1->setAnimationSpeed(6, 1.f);
		sprite1->addKeyframe(6, glm::vec2(6 * 0.1428f, 0.f));
		
	sprite1->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite1->setPosition(glm::vec2(float(posBoles.x), float(posBoles.y)));
	primer = true;
	bola1 = true;
	bola2 = false;
	bola3 = false;
	bola4= false;
	bola5= false;
	bola6 = false;
	bola7= false;
	
}

void Boles::update(int deltaTime)
{
	sprite1->update(deltaTime);
	if (bola1){
		posBoles.y += 10;
		if (posBoles.y > SCREEN_HEIGHT) {
			bola1 = false;
			bola2 = true;
		}
	}
	if (bola2) {
		if (primer) {
			primer = false;
			posBoles = (glm::vec2(0, SCREEN_HEIGHT - 48));
			sprite1->changeAnimation(1);
		}
		else {
			posBoles.y -= 10;
			posBoles.x += 10;
		}
		if (posBoles.y < -48) {
			bola2 = false;
			bola3 = true;
			primer = true;
		}
	}
	
	else if (bola3) {
		if (primer) {
			primer = false;
			posBoles = (glm::vec2(SCREEN_WIDTH - 48, SCREEN_HEIGHT - 48));
			sprite1->changeAnimation(2);
		}
		else {
			posBoles.y -= 10;
			posBoles.x -= 10;
		}
		if (posBoles.y < -48) {
			bola3 = false;
			bola4 = true;
			primer = true;
		}
	}

	else if (bola4) {
		if (primer) {
			primer = false;
			posBoles = (glm::vec2(0, SCREEN_HEIGHT/2));
			sprite1->changeAnimation(3);
		}
		else {
			posBoles.x += 10;
		}
		if (posBoles.x > SCREEN_WIDTH + 48) {
			bola4 = false;
			bola5 = true;
			primer = true;
		}
	}

	else if (bola5) {
		if (primer) {
			primer = false;
			posBoles = (glm::vec2(SCREEN_WIDTH - 48, 0));
			sprite1->changeAnimation(4);
		}
		else {
			posBoles.y += 10;
			posBoles.x -= 10;
		}
		if (posBoles.y > SCREEN_HEIGHT) {
			bola5 = false;
			bola6 = true;
			primer = true;
		}
	}
	else if (bola6) {
		if (primer) {
			primer = false;
			posBoles = (glm::vec2(48, 48));
			sprite1->changeAnimation(5);
		}
		else {
			posBoles.y += 10;
			posBoles.x += 10;
		}
		if (posBoles.y > SCREEN_HEIGHT) {
			bola6 = false;
			bola7 = true;
			primer = true;
		}
	}

	else if (bola7) {
		if (primer) {
			primer = false;
			posBoles = (glm::vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT));
			sprite1->changeAnimation(6);
		}
		else {
			posBoles.y -= 10;
		}
		if (posBoles.y < -48) {
			bola7 = false;
		}
	}

	sprite1->setPosition(glm::vec2(float(posBoles.x), float(posBoles.y)));
}

void Boles::render()
{
	sprite1->render();

}

void Boles::setPosition(const glm::vec2 &pos)
{
	posBoles = pos;
	sprite1->setPosition(glm::vec2(float(posBoles.x), float(posBoles.y)));
}

glm::vec2 Boles::getPosition() const {
	return posBoles;
}




