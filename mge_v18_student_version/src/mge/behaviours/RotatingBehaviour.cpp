#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "glm.hpp"

RotatingBehaviour::RotatingBehaviour(float pRpm, glm::vec3 pAxis):AbstractBehaviour(), _rpm(pRpm), _axis(pAxis)
{
	//ctor
}

RotatingBehaviour::~RotatingBehaviour()
{
	//dtor
}

void RotatingBehaviour::start() 
{

}

void RotatingBehaviour::update(float pStep)
{
	_owner->rotate(pStep * glm::radians(_rpm * 6.0f), _axis );
}

AbstractBehaviour* RotatingBehaviour::copy()
{
	return new RotatingBehaviour(_rpm, _axis);
}
