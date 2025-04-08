#include "GUI.h"
#include "Game.h"

void GUI::init(ShaderProgram& shaderProgram)
{
    this->shaderProgram = shaderProgram;
    spritesheet.loadFromFile("images/GUI.png", TEXTURE_PIXEL_FORMAT_RGBA);

    cor = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
    cor->setNumberAnimations(4);

    cor->setAnimationSpeed(3, 0);
    cor->addKeyframe(3, glm::vec2(0.0f, 0.f));

    cor->setAnimationSpeed(2, 0);
    cor->addKeyframe(2, glm::vec2(0.25f, 0.f));

    cor->setAnimationSpeed(1, 0);
    cor->addKeyframe(1, glm::vec2(0.50f, 0.f));

    cor->setAnimationSpeed(0, 0);
    cor->addKeyframe(0, glm::vec2(0.75f, 0.f));

    cor->changeAnimation(0);

    llanternes = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
    llanternes->setNumberAnimations(1);

    llanternes->setAnimationSpeed(0, 8);
    llanternes->addKeyframe(0, glm::vec2(0.f, 0.5f));

    llanternes->changeAnimation(0);

    llança = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
    llança->setNumberAnimations(1);

    llança->setAnimationSpeed(0, 8);
    llança->addKeyframe(0, glm::vec2(0.25f, 0.5f));

    llança->changeAnimation(0);

    llança->setPosition(glm::vec2(16, 16));

    foc = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
    foc->setNumberAnimations(1);

    foc->setAnimationSpeed(0, 8);
    foc->addKeyframe(0, glm::vec2(0.5f, 0.5f));

    foc->changeAnimation(0);

    foc->setPosition(glm::vec2(16, 16));

    triar = true;
    vida = 4;
    nllanternes = 2;
    timerpress = 20;
    vidamax = 4;

}

void GUI::setPlayer(Player* player)
{
    this->player = player;
}

void GUI::update(int deltaTime)
{
    timerpress--;
	if (Game::instance().getKey(GLFW_KEY_T) && timerpress <= 0) {
		triar = !triar;
        timerpress = 20;
	}
}

void GUI::render(float vidatot, float vidamax)
{
    if (triar) {
        llança->render();
    }
    else {
        foc->render();
    }
    for (int i = 0; i < int(vidamax); ++i) {
        float vida = vidatot - i;
        vida = std::max(0.0f, std::min(vida, 1.0f));

        int frame;
        if (vida >= 1.0f) frame = 3;
        else if (vida >= 0.66f) frame = 2;
        else if (vida >= 0.33f) frame = 1;
        else if (vida > 0.0f) frame = 0;
        else frame = 0;

        cor->changeAnimation(frame);
        cor->setPosition(glm::vec2(15, 35 + i * 8));
        cor->render();
    }

    for (int i = 0; i < nllanternes; ++i) {
		llanternes->setPosition(glm::vec2(35 + i * 8, 15));
		llanternes->render();
    }
}

void GUI::setllanternes(int l) {
    nllanternes = l;
}
