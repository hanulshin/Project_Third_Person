#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"

/**
* Simply moves the object upwards with a fixed speed.
*/
class UpMovementBehaviour : public AbstractBehaviour
{
public:
	UpMovementBehaviour(float pOffset);
	virtual ~UpMovementBehaviour();

	virtual void update(float pStep);
	virtual void start();
	virtual AbstractBehaviour* copy();

private:
	float offset;
};