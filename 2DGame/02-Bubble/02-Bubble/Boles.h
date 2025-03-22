#ifndef _BOLES_INCLUDE
#define _BOLES_INCLUDE


#include "Sprite.h"
#include "TileMap.h"




class Boles
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition() const;
	
private:
	glm::ivec2 tileMapDispl, posBoles;
	Texture spritesheet, spritesheetllances;
	Sprite *sprite1, *spritellances;
	bool bola1, bola2, primer;

};


#endif


