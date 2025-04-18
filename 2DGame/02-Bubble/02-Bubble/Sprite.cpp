﻿#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Sprite.h"


Sprite *Sprite::createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program)
{
	Sprite *quad = new Sprite(quadSize, sizeInSpritesheet, spritesheet, program);

	return quad;
}


Sprite::Sprite(const glm::vec2& quadSize, const glm::vec2& sizeInSpritesheet, Texture* spritesheet, ShaderProgram* program)
{
	float vertices[24] = { 0.f, 0.f, 0.f, 0.f,
												quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y,
												quadSize.x, 0.f, sizeInSpritesheet.x, 0.f,
												0.f, 0.f, 0.f, 0.f,

												0.f, quadSize.y, 0.f, sizeInSpritesheet.y,
												quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y, };

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	texture = spritesheet;
	shaderProgram = program;
	currentAnimation = -1;
	position = glm::vec2(0.f);
	flip = false;
	quadSize1 = quadSize;
	llanca1 = false;
	llanca2 = false;
	llanca3 = false;
	llanca4 = false;

}

void Sprite::update(int deltaTime)
{
	if(currentAnimation >= 0)
	{
		timeAnimation += deltaTime;

		while(timeAnimation > animations[currentAnimation].millisecsPerKeyframe)
		{
			timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
			currentKeyframe = (currentKeyframe + 1) % animations[currentAnimation].keyframeDispl.size();
		}
		if (currentKeyframe >= animations[currentAnimation].keyframeDispl.size()) {
			currentKeyframe = 0;
		}
		texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];
	}
}

void Sprite::render() const
{
	//if (llanca1) std::cout << "llanca1 (spritellances)" << this << std::endl;
	//if (llanca3) std::cout << "llanca3 (spritefoc)" << this << std::endl;
	glm::mat4 modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(position.x, position.y, 0.f));
	if (flip && llanca2) { // aixo es pel jugador
		modelview = glm::translate(modelview, glm::vec3(24/ 2.f, 0.f, 0.f));
		modelview = glm::scale(modelview, glm::vec3(-1.0f, 1.0f, 1.0f));
		modelview = glm::translate(modelview, glm::vec3(-24/2.f, 0.f, 0.f));
	}
	else if (flip && llanca1) { // aixo es per la llança normal
		modelview = glm::translate(modelview, glm::vec3(-quadSize1.x / 2.f, 0.f, 0.f));
		modelview = glm::scale(modelview, glm::vec3(-1.0f, 1.0f, 1.0f));
		modelview = glm::translate(modelview, glm::vec3(quadSize1.x / 2.f - 16, 0.f, 0.f));
	}
	else if (flip && llanca3) { // aixo es pel foc
		modelview = glm::translate(modelview, glm::vec3(-60 / 2.f, 0.f, 0.f));
		modelview = glm::scale(modelview, glm::vec3(-1.0f, 1.0f, 1.0f));
		modelview = glm::translate(modelview, glm::vec3(60 / 2.f - 16, 0.f, 0.f));
	}
	else if (flip && llanca4) { // aixo es per la llança cap amunt i cap avall
		modelview = glm::translate(modelview, glm::vec3(-60 / 2.f, 0.f, 0.f));
		modelview = glm::scale(modelview, glm::vec3(-1.0f, 1.0f, 1.0f));
		modelview = glm::translate(modelview, glm::vec3(60 / 2.f - 16, 0.f, 0.f));
	}
	shaderProgram->setUniformMatrix4f("modelview", modelview);
	shaderProgram->setUniform2f("texCoordDispl", texCoordDispl.x, texCoordDispl.y);
	glEnable(GL_TEXTURE_2D);
	texture->use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);
}

void Sprite::free()
{
	glDeleteBuffers(1, &vbo);
}

void Sprite::setNumberAnimations(int nAnimations)
{
	animations.clear();
	animations.resize(nAnimations);
}

void Sprite::setAnimationSpeed(int animId, float keyframesPerSec)
{
	if(animId < int(animations.size()))
		animations[animId].millisecsPerKeyframe = 1000.f / keyframesPerSec;
}

void Sprite::addKeyframe(int animId, const glm::vec2 &displacement)
{
	if (animId < int(animations.size())) {
		animations[animId].cycleDuration = animations[animId].millisecsPerKeyframe * animations[animId].keyframeDispl.size();
		animations[animId].keyframeDispl.push_back(displacement);
	}
}

void Sprite::changeAnimation(int animId)
{
	if(animId < int(animations.size()))
	{
		currentAnimation = animId;
		currentKeyframe = 0;
		timeAnimation = 0.f;
		texCoordDispl = animations[animId].keyframeDispl[0];
	}
}

int Sprite::animation() const
{
	return currentAnimation;
}

int Sprite::keyframe() const
{
	return currentKeyframe;
}

void Sprite::setkeyframe(int x)
{
	currentKeyframe = x;
}


void Sprite::setPosition(const glm::vec2 &pos)
{
	position = pos;
}

void Sprite::canviaflip(bool a) {
	flip = a;
}

bool Sprite::getflip() {
	return flip;
}

bool Sprite::animationfinished() {

	if (currentAnimation < 0) return false;

	float duration = animations[currentAnimation].millisecsPerKeyframe * animations[currentAnimation].keyframeDispl.size();
	return timeAnimation >= duration;
}

void Sprite::esllanca1() {
	llanca1 = true;
}
void Sprite::esllanca2() {
	llanca2 = true;
}
void Sprite::esllanca3() {
	llanca3 = true;
}

void Sprite::esllanca4() {
	llanca4 = true;
}