#include "mge/behaviours/UpMovementBehaviour.h"
#include "mge/core/GameObject.hpp"
#include "SFML\Window\Keyboard.hpp"

UpMovementBehaviour::UpMovementBehaviour(float pSpeed, float pOffset, float pResetSpeed)
{
	_upSpeed = pSpeed;
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
		MoveUp(_upSpeed, pStep, _owner);
	}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	//{
	//	Reset();
	//}
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
	if (pObjectToMoveUp->getLocalPosition().y < (13 * 17) + _offset)
	{
		pObjectToMoveUp->translate(pStep*glm::vec3(0.0f, pSpeed * pStep * 10, 0.0f));
	}
}


void UpMovementBehaviour::ResetPosition(float pStep, GameObject* pObjectToReset)
{
	glm::vec3 pos = pObjectToReset->getLocalPosition();
	if (pos.y > _offset)
	{
		pObjectToReset->translate(glm::vec3(0, -_resetSpeed * pStep * 20.f, 0));
	}
	else
	{
		pObjectToReset->setLocalPosition(glm::vec3(pos.x, _offset, pos.z));
		Reset(false);
		_startMoving = false;
	}
}

void UpMovementBehaviour::Reset(bool b) {
	_isResetting = b;
	GameObject::getActor("spawner")->getBehaviour()->setActive(!b);
}

int UpMovementBehaviour::resetElevator(lua_State * state) {
	UpMovementBehaviour* up = dynamic_cast<UpMovementBehaviour*>(GameObject::getActor("elevator")->getBehaviour());
	UpMovementBehaviour* cam = dynamic_cast<UpMovementBehaviour*>(GameObject::getActor("camera")->getBehaviour());
	up->Reset();
	cam->Reset();
	return 0;
}
