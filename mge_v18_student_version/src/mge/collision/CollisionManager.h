#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H
#include "mge/core/GameObject.hpp"
#include <vector>
#include <map>

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	void Setup(int pSceneWidth, int pSceneHeight, int pCellSize);
	void ClearBuckets();
	void RegisterObject(/*std::map<int, std::vector<GameObject>> pBuckets,*/ GameObject* pObj);
	std::vector<GameObject*> GetNearby(std::map<int, std::vector<GameObject*>> pBuckets,GameObject* pObj) const;
	std::map<int, std::vector<GameObject*>> buckets;
	int columns;
	int rows;
private:
	std::vector<int> GetIdForObj(GameObject* pObj)const;
	void AddBucket(glm::vec2 pGridPos, float pWidth, std::vector<int>* pBucketToAddTo)const;
	int _sceneWidth;
	int _sceneHeight;
	int _cellSize;
};
#endif // !COLIISION_MANAGER_H
