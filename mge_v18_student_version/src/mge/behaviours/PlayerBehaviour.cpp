#include "mge/behaviours/PlayerBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "glm.hpp"

PlayerBehaviour::PlayerBehaviour(float speed) : AbstractBehaviour(), _moveX(speed)
{
}

PlayerBehaviour::~PlayerBehaviour()
{
}

void PlayerBehaviour::start()
{}

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

	//translate the object in its own local space

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
