#ifndef BULLETBEHAVIOUR_HPP
#define BULLETBEHAVIOUR_HPP

#include "glm.hpp"
#include "mge\behaviours\AbstractBehaviour.hpp"

class BulletBehaviour :
	public AbstractBehaviour
{
public:
	BulletBehaviour(glm::vec2 pVelocity, int pDamage, float pTime);
	virtual ~BulletBehaviour();

	virtual void start();
	virtual void update(float dt);
	virtual AbstractBehaviour* copy();
	void fire();
private:
	glm::vec2 velocity;
	int damage;
	float time;
	bool frozen;
};

#endif // BULLETBEHAVIOUR_HPP