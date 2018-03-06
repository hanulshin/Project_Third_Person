#pragma once

#include "mge\core\GameObject.hpp"
#include <glm.hpp>
#include <map>
#include <string>

class Collider
{
public:
	Collider(glm::vec3 pOrigin = glm::vec3(0, 0, 0));
	virtual ~Collider();

	glm::vec3 getOrigin() const { return _origin; }
	void setOrigin(glm::vec3 pOrigin) { _origin = pOrigin; }

	static void add()
private:
	GameObject* parent;
	glm::vec3 _origin;

	static std::map<std::string, Collider*> colliders;
};

