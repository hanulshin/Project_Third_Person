#include "mge\behaviours\BulletBehaviour.hpp"
#include "mge\behaviours\AbstractBehaviour.hpp"
#include "mge\core\GameObject.hpp"
#include "glm.hpp"
#include <algorithm>
#include <vector>

BulletBehaviour::BulletBehaviour(glm::vec2 pVelocity, int pDamage, float pKnockback, float pTime) :
	AbstractBehaviour(), velocity(pVelocity), damage(pDamage), knockback(pKnockback), time(pTime)
{
	bullets->push_back(this);
	//std::cout << velocity.x << ", " << velocity.y << ", " << damage << ", " << time << std::endl;
}

BulletBehaviour::~BulletBehaviour()
{
	bullets->erase(std::remove(bullets->begin(), bullets->end(), this), bullets->end());
}

std::vector<BulletBehaviour*>* BulletBehaviour::bullets = new std::vector<BulletBehaviour*>();
std::vector<BulletBehaviour*>* BulletBehaviour::getBullets() {
	return bullets;
}

void BulletBehaviour::start() {
	
}

void BulletBehaviour::update(float pStep) {
	glm::vec3 pos = _owner->getLocalPosition();
	//std::cout << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
	time -= pStep;
	_owner->translate(glm::vec3(velocity * pStep, 0));
	if (time <= 0) delete(_owner);
}

AbstractBehaviour* BulletBehaviour::copy() {
	return new BulletBehaviour(velocity, damage, knockback, time);
}

int BulletBehaviour::getDamage() {
	return damage;
}

float BulletBehaviour::getKnockBack() {
	return knockback;
}