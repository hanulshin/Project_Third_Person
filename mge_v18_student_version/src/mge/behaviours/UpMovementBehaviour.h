#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/behaviours/LuaScripts/EnemySpawner.hpp"

/**
* Simply moves the object upwards with a fixed speed.
*/
class UpMovementBehaviour : public AbstractBehaviour
{
public:
	UpMovementBehaviour(float pSpeed, float pOffset, float pResetSpeed);
	virtual ~UpMovementBehaviour();

	virtual void update(float pStep);
	virtual void start();
	virtual AbstractBehaviour* copy();
	void MoveUp(float pSpeed, float pStep, GameObject* pObjectToMoveUp);
	void ResetPosition(float pStep, GameObject* pObjectToReset);
	void Reset(bool b = true);

	static int resetElevator(lua_State * state);
private:
	float _upSpeed;
	float _resetSpeed;
	float _offset;
	bool _isResetting;
	bool _startMoving;
};