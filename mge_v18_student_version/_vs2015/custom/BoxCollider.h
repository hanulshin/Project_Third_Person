#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include "mge/core/GameObject.hpp"
#include "glm.hpp"

class BoxCollider:public GameObject
{
public:
	BoxCollider(float pWidth, float pHeight, glm::vec3 pPos);
	virtual ~BoxCollider();
	bool IsOverlapping(BoxCollider&);
	float width;
	float height;
};
#endif // !BOXCOLLIDER_H