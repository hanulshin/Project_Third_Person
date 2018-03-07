#ifndef ROTATINGBEHAVIOUR_HPP
#define ROTATINGBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class RotatingBehaviour : public AbstractBehaviour
{
	public:
		RotatingBehaviour(float pRpm, glm::vec3 pAxis);
		virtual ~RotatingBehaviour();

		virtual void update(float pStep);
		virtual void start();
		virtual AbstractBehaviour* copy();
	private:
		float _rpm;
		glm::vec3 _axis;
};

#endif // ROTATINGBEHAVIOUR_HPP
