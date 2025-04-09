#include "Boss.h"

enum BossAnims
{
	FLYING1, FLYING2, ATTACKING
};

void Boss::definirProjectils(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	ProjBoss* p = new ProjBoss();
	p->init(tileMapPos, shaderProgram, 0);
	p->setPosition(glm::vec2(pos.x+32,pos.y));
	projectils.push_back(p);

	p = new ProjBoss();
	p->init(tileMapPos, shaderProgram, 1);
	p->setPosition(glm::vec2(pos.x + 32, pos.y + 48));
	projectils.push_back(p);

	p = new ProjBoss();
	p->init(tileMapPos, shaderProgram, 2);
	p->setPosition(glm::vec2(pos.x, pos.y + 48));
	projectils.push_back(p);

	p = new ProjBoss();
	p->init(tileMapPos, shaderProgram, 3);
	p->setPosition(glm::vec2(pos.x, pos.y));
	projectils.push_back(p);
}

void Boss::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	texture.loadFromFile("images/boss.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 48), glm::vec2(0.33f, 1.f), &texture, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(FLYING1, 8);
	sprite->addKeyframe(FLYING1, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(FLYING2, 8);
	sprite->addKeyframe(FLYING2, glm::vec2(0.33f, 0.f));

	sprite->setAnimationSpeed(ATTACKING, 8);
	sprite->addKeyframe(ATTACKING, glm::vec2(0.66f, 0.f));

	sprite->changeAnimation(FLYING1);

	definirProjectils(tileMapPos, shaderProgram);
	std::srand(std::time(nullptr));
	tileMapDispl = tileMapPos;
	nextChange = 250;
	nextShot = 1500;
	alive = false;
	currentTime = 0;
	lastMoved = 0;
	moving = false;
	distance = 0;

	positions[0] = glm::vec2(16 * 57, 16 * 5);
	positions[1] = glm::vec2(16 * 52, 16 * 4);
	positions[2] = glm::vec2(16 * 50, 16 * 9);
	positions[3] = glm::vec2(16 * 59, 16 * 9);

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Boss::setPosition(const glm::vec2& position) {
	pos = position;
	posInit = position;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Boss::update(int deltaTime) {
	if (alive) {
		currentTime += deltaTime;
		sprite->update(deltaTime);

		if (moving) {
			cout << distance << ", " << glm::distance(lastPosition, pos) << endl;
			if (glm::distance(lastPosition,pos) >= distance) {
				cout << "SIUUUUU" << endl;
				moving = false;
				lastMoved = currentTime;
			}

			else {
				pos += glm::vec2(direction.x*2, direction.y*2);
			}
		}

		else if (currentTime - lastMoved >= 3000) startMoving();

		if (currentTime >= nextChange && currentTime - lastShot >= 250) {
			if (sprite->animation() == FLYING1) sprite->changeAnimation(FLYING2);
			else sprite->changeAnimation(FLYING1);
			nextChange += 250;
		}

		if (currentTime - lastShot >= 500) deactivateProjectils();

		if (currentTime >= nextShot) {
			lastShot = currentTime;
			sprite->changeAnimation(ATTACKING);
			shoot();
			nextShot += 1500;
		}

		for (auto p : projectils) p->update(deltaTime);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	}
}

void Boss::render() {
	if (alive) {
		sprite->render();
		for (auto p : projectils) p->render();
	}
}

void Boss::shoot() {
	for (auto p : projectils) {
		int t = p->getType();
		if(t == 0) p->setPosition(glm::vec2(pos.x + 32 - 10, pos.y - 10));
		else if (t == 1) p->setPosition(glm::vec2(pos.x + 32 - 10, pos.y+48 - 10));
		else if (t == 2) p->setPosition(glm::vec2(pos.x - 10, pos.y+48 - 10));
		else if (t == 3) p->setPosition(glm::vec2(pos.x - 10, pos.y - 10));
		p->activate();
	}
}

void Boss::deactivateProjectils() {
	for (auto p : projectils) p->deactivate();
}

std::vector<ProjBoss*>& Boss::getProjectils() {
	return projectils;
}

glm::vec2 Boss::getPosition() {
	return pos;
}

void Boss::startFight() {
	alive = true;
}

void Boss::startMoving() {
	int n = std::rand() % 4;
	nextPosition = positions[n];
	direction = glm::normalize(nextPosition - pos);
	distance = glm::distance(nextPosition, pos);
	lastPosition = pos;
	moving = true;
}