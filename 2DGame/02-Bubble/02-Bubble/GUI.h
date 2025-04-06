#ifndef _GUI_INCLUDE
#define _GUI_INCLUDE

#include "Sprite.h"
#include "Texture.h"
#include "Player.h"

class GUI
{
public:

    void init(ShaderProgram& shaderProgram);

    void setPlayer(Player* player);

    void update(int deltaTime);

    void render(float vida);

private:
    void setSprite(Sprite* sprite, glm::vec2 displacement);

private:
    Player* player;
    ShaderProgram shaderProgram;
    Texture spritesheet;

    Sprite* cor;
    Sprite* llanternes;
    Sprite* llança;
    Sprite* foc;

    int ncors;
    int nllanternes;
    bool triar;

};

#endif // _GUI_INCLUDE
#pragma once
