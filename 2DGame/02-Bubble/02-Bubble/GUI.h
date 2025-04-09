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

    void render(float vida, float vidamax, float vidaboss, bool alive);

    void setllanternes(int l);

private:

private:
    Player* player;
    ShaderProgram shaderProgram;
    Texture spritesheet;
    Texture spritesheet2;

    Sprite* cor;
    Sprite* llanternes;
    Sprite* llança;
    Sprite* foc;
    Sprite* corb;

    int ncors;
    int nllanternes;
    bool triar;
    float vida;
    int timerpress;
    int vidamax;

};

#endif // _GUI_INCLUDE
#pragma once
