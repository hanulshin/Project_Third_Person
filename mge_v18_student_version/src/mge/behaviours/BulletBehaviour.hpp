#ifndef BULLETBEHAVIOUR_HPP
#define BULLETBEHAVIOUR_HPP

#include "glm.hpp"
#include <vector>
#include "mge\behaviours\AbstractBehaviour.hpp"

class BulletBehaviour :
	public AbstractBehaviour
{
public:
	BulletBehaviour(glm::vec2 pVelocity, int pDamage, float pKnockback, float pTime);
	virtual ~BulletBehaviour();

	virtual void start();
	virtual void update(float dt);
	virtual AbstractBehaviour* copy();
	int getDamage();
	float getKnockBack();
	static std::vector<BulletBehaviour*>* getBullets();
private:
	glm::vec2 velocity;
	int damage;
	float knockback;
	float time;
	static std::vector<BulletBehaviour*>* bullets;
};

#endif // BULLETBEHAVIOUR_HPP