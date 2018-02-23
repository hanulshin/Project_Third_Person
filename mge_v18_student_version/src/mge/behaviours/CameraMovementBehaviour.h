#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
class CameraMovementBehaviour :
	public AbstractBehaviour
{
public:
	CameraMovementBehaviour(float pMoveSpeed = 5, float pTurnSpeed = 45, float plookUpSpeed = 40);
	~CameraMovementBehaviour();
	virtual void update(float pStep);
	virtual void start();
private:
	float _moveSpeed;
	float _turnSpeed;
	float _z;
	float _lookUpSpeed;
};

