#include "mge/behaviours/UpMovementBehaviour.h"
#include "mge/core/GameObject.hpp"
#include "SFML\Window\Keyboard.hpp"

UpMovementBehaviour::UpMovementBehaviour(float pOffset, float pResetSpeed)
{
	_offset = pOffset;
	_resetSpeed = pResetSpeed;
	_isResetting = false;
	_startMoving = false;
}

UpMovementBehaviour::~UpMovementBehaviour()
{
}

void UpMovementBehaviour::update(float pStep)
{
	if (_isResetting)
	{
		ResetPosition(pStep, _owner);
		return;
	}
	if (_startMoving)
	{
		MoveUp(2.0f, pStep, _owner);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		_isResetting = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		_startMoving = true;
	}

}


void UpMovementBehaviour::start()
{
}

AbstractBehaviour * UpMovementBehaviour::copy()
{
	return nullptr;
}

void UpMovementBehaviour::MoveUp(float pSpeed, float pStep, GameObject * pObjectToMoveUp)
{
	if (pObjectToMoveUp->getLocalPosition().y < 49.0f + _offset)
	{
		pObjectToMoveUp->translate(pStep*glm::vec3(0.0f, pSpeed, 0.0f));
	}
}


void UpMovementBehaviour::ResetPosition(float pStep, GameObject* pObjectToReset)
{
	glm::vec3 pos = pObjectToReset->getLocalPosition();
	if (pos.y > _offset)
	{
		pObjectToReset->translate(glm::vec3(0, -_resetSpeed * pStep, 0));
	}
	else
	{
		pObjectToReset->setLocalPosition(glm::vec3(pos.x, _offset, pos.z));
		_isResetting = false;
		_startMoving = false;
	}
}
