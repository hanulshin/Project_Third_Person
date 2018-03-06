#pragma once
#include "mge\colliders\Collider.hpp"
#include "glm.hpp"

class CircleCollider :
	public Collider
{
public:
	CircleCollider();
	virtual ~CircleCollider();
	float getRadius() const { return _radius; }
	void setRadius(float pRadius) { _radius = pRadius; }
private:
	float _radius;
};

