#include "BoxCollider.h"
#include "glm.hpp"

BoxCollider::BoxCollider(float pWidth, float pHeight, glm::vec3 pPos) :GameObject("Collider", pPos) {
	setLocalPosition(glm::vec3(0, 0, 0));
	translate(glm::vec3(pWidth, 0, 0));
	width = pWidth;
	height = pHeight;
}
bool BoxCollider::IsOverlapping(BoxCollider* pOther) {
	if (pOther == nullptr || this == nullptr || pOther == this)
		return false;
	glm::vec3 pos = getWorldPosition();
	glm::vec3 otherPos = pOther->getWorldPosition();
	if (pos.x < otherPos.x + pOther->width &&// _| < |_
		pos.x + width > otherPos.x &&// _| > |_
		pos.y < otherPos.y + pOther->height &&// downside of this collider < upside of other collider
		pos.y + height > otherPos.y) {//upside of this collider > downside of other collider
		return true;
	}
	return false;
}

std::vector<GameObject*> BoxCollider::IsOverlapping(std::vector<GameObject*> groupOfObjects) {
	glm::vec3 pos = getWorldPosition();
	std::vector<GameObject*> collidingObjects = std::vector<GameObject*>();
	for (size_t i = 0; i < groupOfObjects.size(); i++)
	{
		BoxCollider* otherCollider = groupOfObjects[i]->getBoxCollider();
		glm::vec3 otherPos = otherCollider->getWorldPosition();
		if (pos.x < otherPos.x + otherCollider->width &&// _| < |_
			pos.x + width > otherPos.x &&// _| > |_
			pos.y < otherPos.y + otherCollider->height &&// downside of this collider < upside of other collider
			pos.y + height > otherPos.y) {//upside of this collider > downside of other collider
			collidingObjects.push_back(groupOfObjects[i]);
		}
		delete otherCollider;
	}
	return collidingObjects;
}

Bounds * BoxCollider::getBounds() const
{
	glm::vec3 pos = getWorldPosition();
	return new Bounds(pos.x, pos.x + width, pos.y, pos.y + height);
}

void BoxCollider::OnCollision(GameObject* pOther)
{
	//std::cout << "help";
	if (!isTrigger)
	{
		if (_parent->getName() == "Player" && pOther->getName() == "ElevatorPlatform")
		{
			std::cout << pOther->getLocalPosition().y << std::endl;
			_newPos = glm::vec3(0.0f, 1, 0.0f);
		}
	}
}

void BoxCollider::update(float pStep)
{
	_parent->translate(_newPos * pStep);
	_newPos = glm::vec3();
}

BoxCollider::~BoxCollider() {};


Bounds::Bounds(float pMinX, float pMaxX, float pMinY, float pMaxY)
{
	minX = pMinX;
	maxX = pMaxX;
	minY = pMinY;
	maxY = pMaxY;
}

Bounds::~Bounds()
{
}


//glm::vec3 pos = getLocalPosition();
//glm::vec3 otherPos = pOther->getLocalPosition();
//glm::vec2 diff = glm::vec2(otherPos.x - pos.x, otherPos.y - pos.y);
//glm::vec3 newPos = glm::vec3();
//std::cout << diff;
//if (diff.x < 0)
//{
//	newPos.x = width + diff.x;
//}
//else if (diff.x >= 0)
//{
//	newPos.x = pOther->getBoxCollider()->width/2 - diff.x;
//}
//if (diff.y<0)
//{
//	newPos.y = height/2 + diff.y;
//}
//else if (diff.y >= 0)
//{
//	newPos.y = pOther->getBoxCollider()->height/2 - diff.y;
//}
//_newPos = -newPos;