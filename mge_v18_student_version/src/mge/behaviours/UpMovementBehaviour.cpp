#include "mge/behaviours/UpMovementBehaviour.h"
#include "mge/core/GameObject.hpp"

UpMovementBehaviour::UpMovementBehaviour(float pOffset)
{
	offset = pOffset;
}

UpMovementBehaviour::~UpMovementBehaviour()
{
}

void UpMovementBehaviour::update(float pStep)
{
	if (_owner->getLocalPosition().y < 49.0f + offset)
	{
		_owner->translate(pStep*glm::vec3(0.0f, 2.0f, 0.0f));
	}
}

void UpMovementBehaviour::start()
{
}

AbstractBehaviour * UpMovementBehaviour::copy()
{
	return nullptr;
}
