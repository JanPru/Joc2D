#include "GUI.h"

void GUI::init(ShaderProgram &shaderProgram)
{

    spritesheet = Texture();
    spritesheet.loadFromFile("images/GUI.png", TEXTURE_PIXEL_FORMAT_RGBA);

	cor1 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
    setSprite(cor1, glm::vec2(0.f, 0.f));

    cor2 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
    setSprite(cor2, glm::vec2(0.25f, 0.f));

    cor3 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
    setSprite(cor3, glm::vec2(0.5f, 0.f));

    cor4 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
    setSprite(cor4, glm::vec2(0.75f, 0.f));

	llanternes = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	setSprite(llanternes, glm::vec2(0.f, 0.5f));

	llança = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	setSprite(llança, glm::vec2(0.25f, 0.5f));
	llança->setPosition(glm::vec2(16, 16));

	foc = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	setSprite(foc, glm::vec2(0.5f, 0.5f));
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

void GUI::render()
{
    if (triar) {
		llança->render();
    }
    else {
		foc->render();
    }
}

void GUI::setSprite(Sprite* sprite, glm::vec2 displacement)
{
    sprite->setNumberAnimations(1);
    sprite->setAnimationSpeed(0, 1);
    sprite->addKeyframe(0, displacement);
    sprite->changeAnimation(0);
}
