#include "mge\behaviours\BulletBehaviour.hpp"
#include "mge\behaviours\AbstractBehaviour.hpp"
#include "mge\core\GameObject.hpp"
#include "glm.hpp"

BulletBehaviour::BulletBehaviour(glm::vec2 pVelocity, int pDamage, float pTime) :
	AbstractBehaviour(), velocity(pVelocity), damage(pDamage), time(pTime), frozen(true)
{
}

BulletBehaviour::~BulletBehaviour()
{
}

void BulletBehaviour::start() {
	fire();
}

void BulletBehaviour::update(float dt) {
	if (frozen) return;
	time -= dt;
	_owner->translate(glm::vec3(velocity * dt, 0));
	if (time <= 0) delete(_owner);
}

void BulletBehaviour::fire() {
	frozen = false;
}

AbstractBehaviour* BulletBehaviour::copy() {
	return new BulletBehaviour(velocity, damage, time);
}