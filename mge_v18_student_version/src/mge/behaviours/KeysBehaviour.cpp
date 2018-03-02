#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "glm.hpp"

KeysBehaviour::KeysBehaviour(float pMoveX, float pMoveY) : AbstractBehaviour(), _moveX(pMoveX), _moveY(pMoveY)
{
}

KeysBehaviour::~KeysBehaviour()
{
}

void KeysBehaviour::update(float pStep)
{
	float deltaX = 0;
	float deltaY = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		deltaY += _moveY;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		deltaY -= _moveY;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		deltaX += _moveX;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		deltaX -= _moveX;
	}
	//translate the object in its own local space
	_owner->translate(glm::vec3(deltaX * pStep, deltaY *pStep, 0.0f));

	//we can also translate directly, basically we take the z axis from the matrix
	//which is normalized and multiply it by moveSpeed*step, then we add it to the
	//translation component
	//glm::mat4 transform = _owner->getTransform();
	//transform[3] += transform[2] * moveSpeed*pStep;
	//_owner->setTransform(transform);

	//rotate the object in its own local space
	//_owner->rotate( glm::radians(turnSpeed*pStep), glm::vec3(0.0f, 1.0f, 0.0f ) );

	//NOTE:
	//The reason the above happens in the local space of the object and not in the world space
	//is that we use the _owner->translate / rotate shortcuts which in turn call glm::rotate / glm::translate
	//The methods multiply the current transform with the translation/rotation matrix from left to right
	//meaning everything happens in local space.
}
