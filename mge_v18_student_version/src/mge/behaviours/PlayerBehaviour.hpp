#ifndef PLAYERBEHAVIOUR_HPP
#define PLAYERBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"

/**
 * KeysBehaviour allows you to move an object using the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class PlayerBehaviour : public AbstractBehaviour
{
	public:
	    //move speed is in units per second, turnspeed in degrees per second
		PlayerBehaviour(float speed = 5);
		virtual ~PlayerBehaviour();
		virtual void update( float pStep );
		virtual void start();
		virtual AbstractBehaviour* copy();
    private:
		glm::vec2 _aim;
        float _moveX;
		int _facing = 1;
};

#endif // PLAYERBEHAVIOUR_HPP
