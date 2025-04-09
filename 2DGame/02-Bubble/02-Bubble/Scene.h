#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Projectil.h"
#include "Florecita.h"
#include "Planta.h"
#include "GUI.h"
#include "Powerups.h"
#include "Boss.h"
#include "Bolet.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.
enum Fase {
	FASE0, FASE1, FASE2, FASE3, FASE4, FASE5
};
class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void resize(int width, int height);
	float getvidaPlayer();
	float getfinalbool();

private:
	void initShaders();
	void modifcam();
	void definirProjectils();
	void definirFlorecitas();
	void definirPlantes();
	void definirPowerups();
	void crearPlanta(int type, glm::vec2 position);
	void definirBolets();

private:
	TileMap* map;
	Player* player;
	Boss* boss;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	float l, r, b, t;
	float camX, camY;
	float segCanviTiles;
	float segProjectil;
	float segFlorecita;
	float zoom;
	glm::vec2 mapsize;
	float tilesize;
	std::vector<Projectil*> projectils;
	std::vector<Florecita*> florecitas;
	std::vector<Planta*> plantes;
	std::vector<Powerups*> powerups;
	std::vector<Bolet*> bolets;
	Fase fase;
	glm::vec2 limitszona[6];
	GUI* gui;
};


#endif // _SCENE_INCLUDE

