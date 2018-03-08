#include "mge/behaviours/UpMovementBehaviour.h"
#include "mge/core/GameObject.hpp"

UpMovementBehaviour::UpMovementBehaviour()
{
}

UpMovementBehaviour::~UpMovementBehaviour()
{
}

void UpMovementBehaviour::update(float pStep)
{
	_owner->translate(pStep*glm::vec3(0.0f, 1.0f, 0.0f));
	//std::cout << _owner->getLocalPosition() << std::endl;
}

void UpMovementBehaviour::start()
{
}

AbstractBehaviour * UpMovementBehaviour::copy()
{
	return nullptr;
}
