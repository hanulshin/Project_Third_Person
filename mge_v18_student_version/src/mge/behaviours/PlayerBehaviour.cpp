#include "mge/behaviours/PlayerBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "glm.hpp"

<<<<<<< HEAD:mge_v18_student_version/src/mge/behaviours/PlayerBehaviour.cpp
PlayerBehaviour::PlayerBehaviour(float speed): AbstractBehaviour(), _moveX(speed)
=======
KeysBehaviour::KeysBehaviour(float pMoveX, float pMoveY) : AbstractBehaviour(), _moveX(pMoveX), _moveY(pMoveY)
>>>>>>> Collisions:mge_v18_student_version/src/mge/behaviours/KeysBehaviour.cpp
{
}

PlayerBehaviour::~PlayerBehaviour()
{
}

<<<<<<< HEAD:mge_v18_student_version/src/mge/behaviours/PlayerBehaviour.cpp
void PlayerBehaviour::start() 
=======
void KeysBehaviour::update(float pStep)
>>>>>>> Collisions:mge_v18_student_version/src/mge/behaviours/KeysBehaviour.cpp
{

<<<<<<< HEAD:mge_v18_student_version/src/mge/behaviours/PlayerBehaviour.cpp
}

void PlayerBehaviour::update( float pStep )
{

	glm::vec2 delta = glm::vec2(0, 0);
 
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up )) {
		_aim.y = 1;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down )) {
		_aim.y = -1;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right )) {
		delta.x += _moveX;
		_facing = 1;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left )) {
		delta.x -= _moveX;
		_facing = -1;
	}
	_aim.x = _facing;
	_aim = glm::normalize(_aim);

	_owner->translate( glm::vec3(delta.x * pStep, 0.0f, 0.0f) );
=======
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
>>>>>>> Collisions:mge_v18_student_version/src/mge/behaviours/KeysBehaviour.cpp

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
