#ifndef _SPRITE_INCLUDE
#define _SPRITE_INCLUDE

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "AnimKeyframes.h"


// This class is derived from code seen earlier in TexturedQuad but it is also
// able to manage animations stored as a spritesheet. 


class Sprite
{

private:
	Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);

public:
	// Textured quads can only be created inside an OpenGL context
	static Sprite *createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);

	void update(int deltaTime);
	void render() const;
	void free();

	void setNumberAnimations(int nAnimations);
	void setAnimationSpeed(int animId, float keyframesPerSec);
	void addKeyframe(int animId, const glm::vec2 &frame);
	void changeAnimation(int animId);
	int animation() const;
	int keyframe() const;
	
	void setPosition(const glm::vec2 &pos);
	void canviaflip(bool b);
	bool animationfinished();
	bool getflip();
	void setkeyframe(int x);
	void esllanca1();
	void esllanca2();
	void esllanca3();
	void esllanca4();
	void posarmodel(const glm::mat4 &modelview);

private:
	Texture *texture;
	ShaderProgram *shaderProgram;
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::vec2 position;
	int currentAnimation, currentKeyframe;
	float timeAnimation;
	glm::vec2 texCoordDispl;
	vector<AnimKeyframes> animations;
	bool flip;
	bool finished;
	glm::vec2 quadSize1;
	bool llanca1, llanca2, llanca3, llanca4;;
	glm::mat4 modelviewmult;
};


#endif // _SPRITE_INCLUDE

