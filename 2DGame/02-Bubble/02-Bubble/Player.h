#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Florecita.h"
#include "Projectil.h"
#include "Planta.h"
#include "Powerups.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::vec2 getPosition() const;
	void canvialimit(int l, bool b); //true es que el limit sera dreta i false que limit sera esquerra

	float getvida();
	float getvidamax();
	int getllanternes();
	void setvida(float v);
	
	void setFlorecitas(std::vector<Florecita*>* flors);
	void setProjectils(std::vector<Projectil*>* proj);
	void setPlantes(std::vector<Planta*>* proj);

	void setAnimation(int anim);

	bool gettriar();
	bool eslavap();

private:
	int collisionFlorecitas();
	bool collisionProjectils();
	bool collisionPlantes();
	bool collisionPowerups();


private:
	bool bJumping;
	int lastProjectil;
	int currentTime;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet, spritesheetllances, spritesheetfoc;
	Sprite* sprite;
	Sprite* spritellances;
	Sprite* spritefoc;
	Sprite* spritellancesvert;
	TileMap* map;
	std::vector<Florecita*>* florecitas;
	std::vector<Projectil*>* projectils;
	std::vector<Powerups*>* powerups;
	std::vector<Planta*>* plantes;
	int spriteTriat;
	glm::vec2 posllança;
	int limit;
	bool dreta;
	float vida;
	float vidamax;
	int llanternes;
	int timerLava;
	bool lava = false;
	float vidaant = 0;
	int frameLlança = 0;
	int timerLlança = 0;
	bool activaLlança = false;
	bool capEndavant = true;
	bool plantBelow;

	bool damaged = false;
	float damageTimer = 0.f;
	const float damageDuration = 500.f;
	int lastAnimation = -1;
	bool overrideAnimation = false;

	bool godmode;

	bool triar = true;
	int timerpress = 20;

	bool primer = true;
	bool plantatocada = false;
};


#endif // _PLAYER_INCLUDE
