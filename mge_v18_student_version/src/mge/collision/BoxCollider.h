#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include "mge/core/GameObject.hpp"
#include "glm.hpp"
class Bounds {
public:
	Bounds(float pMinX, float pMaxX, float pMinY, float pMaxY);
	~Bounds();
	float minX;
	float maxX;
	float minY;
	float maxY;
};
class BoxCollider :public GameObject
{
public:
	BoxCollider(float pWidth, float pHeight, glm::vec3 pPos);
	~BoxCollider();
	bool IsOverlapping(BoxCollider*);
	std::vector<GameObject*> IsOverlapping(std::vector<GameObject*> groupOfObjects); //returns the objects that are overlapping this collider
	float width;
	float height;
	Bounds * getBounds() const;
	void OnCollision(GameObject* pOther);
	void update(float pStep);
	bool isTrigger = false;
	static std::vector<BoxCollider*> getAllColliders();
private:
	static std::vector<BoxCollider*> _boxColliders;
	glm::vec3 _newPos;
	bool _playerIsCollidingWithRamp;
};

#endif // !BOXCOLLIDER_H