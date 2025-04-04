#include "GUI.h"

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

    llan�a = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
    llan�a->setNumberAnimations(1);

    llan�a->setAnimationSpeed(0, 8);
    llan�a->addKeyframe(0, glm::vec2(0.25f, 0.5f));

    llan�a->changeAnimation(0);

    llan�a->setPosition(glm::vec2(16, 16));

    foc = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
    foc->setNumberAnimations(1);

    foc->setAnimationSpeed(0, 8);
    foc->addKeyframe(0, glm::vec2(0.5f, 0.5f));

    foc->changeAnimation(0);

    foc->setPosition(glm::vec2(16, 16));

    triar = true;

}

void GUI::setPlayer(Player* player)
{
    this->player = player;
}

void GUI::update(int deltaTime)
{
    //Funcio que et digui els cors en funcio de la vida del personatge
}

void GUI::render(int vida)
{
    if (triar) {
        llan�a->render();
    }
    else {
        foc->render();
    }
    for (int i = 0; i < 4; ++i) {
        float lifeSlot = vida - i;
        lifeSlot = std::max(0.0f, std::min(lifeSlot, 1.0f));

        int frame;
        if (lifeSlot >= 1.0f) frame = 3;
        else if (lifeSlot >= 0.66f) frame = 2;
        else if (lifeSlot >= 0.33f) frame = 1;
        else if (lifeSlot > 0.0f) frame = 0;
        else frame = 0;

        cor->changeAnimation(frame);
        cor->setPosition(glm::vec2(15, 35 + i * 8));
        cor->render();
    }
}
