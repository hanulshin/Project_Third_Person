#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"

RotatingBehaviour::RotatingBehaviour():AbstractBehaviour()
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
    //rotates 90° per second
	_owner->rotate(pStep * glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) );
}
