#ifndef ROTATINGBEHAVIOUR_HPP
#define ROTATINGBEHAVIOUR_HPP

#include "glm.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class RotatingBehaviour : public AbstractBehaviour
{
	public:
		RotatingBehaviour(float pRPM, glm::vec3 pAxis);
		virtual ~RotatingBehaviour();

		virtual void update(float pStep);
		virtual void start();
		virtual AbstractBehaviour* copy();
	private:
		glm::vec3 _axis;
		float _rpm;
};

#endif // ROTATINGBEHAVIOUR_HPP
