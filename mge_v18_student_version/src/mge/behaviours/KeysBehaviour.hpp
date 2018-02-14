#ifndef KEYSBEHAVIOUR_HPP
#define KEYSBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * KeysBehaviour allows you to move an object using the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class KeysBehaviour : public AbstractBehaviour
{
	public:
	    //move speed is in units per second, turnspeed in degrees per second
		KeysBehaviour(float pMoveX = 5, float pMoveY = 45);
		virtual ~KeysBehaviour();
		virtual void update( float pStep );

    private:
        float _moveX;
        float _moveY;
};

#endif // KEYSBEHAVIOUR_HPP
