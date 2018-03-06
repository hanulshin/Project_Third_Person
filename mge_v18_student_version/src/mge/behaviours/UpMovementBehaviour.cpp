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
}

void UpMovementBehaviour::start()
{
}
