#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"

/**
* Simply moves the object upwards with a fixed speed.
*/
class UpMovementBehaviour : public AbstractBehaviour
{
public:
	UpMovementBehaviour(float pOffset, float pResetSpeed);
	virtual ~UpMovementBehaviour();

	virtual void update(float pStep);
	virtual void start();
	virtual AbstractBehaviour* copy();
	void MoveUp(float pSpeed, float pStep, GameObject* pObjectToMoveUp);
	void ResetPosition(float pStep, GameObject* pObjectToReset);
private:
	float _resetSpeed;
	float _offset;
	bool _isResetting;
	bool _startMoving;
};