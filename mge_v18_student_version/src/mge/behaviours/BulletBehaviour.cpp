#include "mge\behaviours\BulletBehaviour.hpp"
#include "mge\behaviours\AbstractBehaviour.hpp"
#include "mge\core\GameObject.hpp"
#include "glm.hpp"

BulletBehaviour::BulletBehaviour(glm::vec2 pVelocity, int pDamage, float pTime) :
	AbstractBehaviour(), velocity(pVelocity), damage(pDamage), time(pTime)
{
	//std::cout << velocity.x << ", " << velocity.y << ", " << damage << ", " << time << std::endl;
}

BulletBehaviour::~BulletBehaviour()
{
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
	return new BulletBehaviour(velocity, damage, time);
}