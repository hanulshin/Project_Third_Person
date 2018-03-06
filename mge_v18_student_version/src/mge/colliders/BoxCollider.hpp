#pragma once
#include "mge\colliders\Collider.hpp"
#include "glm.hpp"

class BoxCollider :
	public Collider
{
public:
	BoxCollider();
	virtual ~BoxCollider();
	glm::vec3 getSize() const { return _size; }
	void setSize(glm::vec3 pSize) { _size = pSize; }
private:
	glm::vec3 _size;
};

