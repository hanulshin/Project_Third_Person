#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "glm.hpp"

RotatingBehaviour::RotatingBehaviour(float pRPM, glm::vec3 pAxis):AbstractBehaviour(), _rpm(pRPM), _axis(pAxis)
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
	_owner->rotate(pStep * glm::radians(_rpm * 6.0f * pStep), _axis);
}

AbstractBehaviour* RotatingBehaviour::copy(){
	return new RotatingBehaviour(_rpm, _axis);
}