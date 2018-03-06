#include "BoxCollider.h"
#include "glm.hpp"

BoxCollider::BoxCollider(float pWidth, float pHeight, glm::vec3 pPos):GameObject("Collider", pPos){
	width = pWidth;
	height = pHeight;
}
bool BoxCollider::IsOverlapping(BoxCollider& pOther) {
	glm::vec3 pos;
	if (_parent!= nullptr)
	{
		pos = _parent->getWorldPosition();
	}
	glm::vec3 otherPos = pOther.getWorldPosition();
	if (pos.x < otherPos.x + pOther.width &&
		pos.x + width > otherPos.x &&
		pos.y < otherPos.y + pOther.height &&
		pos.y + height > otherPos.y){
		return true;
	}
	return false;
};
BoxCollider::~BoxCollider() {};