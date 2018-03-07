#include "mge\core\GameObject.hpp"
#include "BoxCollider.h"
#include "../_vs2015/Collision/CollisionManager.h"
#include <map>
#include <vector>
#include <cmath>

CollisionManager::CollisionManager()
{
}

void CollisionManager::Setup(int pSceneWidth, int pSceneHeight, int pCellSize)
{
	columns = pSceneWidth / pCellSize;
	rows = pSceneHeight / pCellSize;
	buckets.insert(std::pair<int, std::vector<GameObject*>>(columns*rows, std::vector<GameObject*>()));
	for (int i = 0; i < columns * rows; i++)
	{
		buckets[i] = std::vector<GameObject*>();
	}
	_sceneWidth = pSceneWidth;
	_sceneHeight = pSceneHeight;
	_cellSize = pCellSize;
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::ClearBuckets()
{
	buckets.clear();
	for (int i = 0; i < columns*rows; i++)
	{
		buckets[i] = std::vector<GameObject*>();
	}
}

void CollisionManager::RegisterObject(/*std::map<int, std::vector<GameObject>>* pBuckets,*/ GameObject* pObj)
{
	std::vector<int> cellIds = GetIdForObj(pObj);
	std::vector<GameObject*> objects;
	for each (int i in cellIds)
	{
		buckets[i].push_back(pObj);
	}
}

std::vector<int> CollisionManager::GetIdForObj(GameObject* pObj) const
{
	if (!pObj->hasCollider())
	{
		return std::vector<int>();
	}
	std::vector<int>* bucketsObjIsIn = new std::vector<int>();
	Bounds* objBounds = pObj->getBoxCollider()->getBounds();
	float width = (float)_sceneWidth / _cellSize;
	AddBucket(glm::vec2(objBounds->minX, objBounds->minY), width, bucketsObjIsIn);//bottom-left
	AddBucket(glm::vec2(objBounds->maxX, objBounds->minY), width, bucketsObjIsIn);//bottom-right
	AddBucket(glm::vec2(objBounds->minX, objBounds->maxY), width, bucketsObjIsIn);//top-left
	AddBucket(glm::vec2(objBounds->maxX, objBounds->maxY), width, bucketsObjIsIn);//top-right

	return *bucketsObjIsIn;
}

std::vector<GameObject*> CollisionManager::GetNearby(std::map<int, std::vector<GameObject*>> pBuckets, GameObject* pObj) const
{
	std::vector<GameObject*> objects;
	std::vector<int> bucketsIds = GetIdForObj(pObj);
	for each (int i in bucketsIds)
	{
		objects.insert(objects.end(), pBuckets[i].begin(), pBuckets[i].end());
	}
	return objects;
}

void CollisionManager::AddBucket(glm::vec2 pGridPos, float pWidth, std::vector<int>* pBucketToAddTo) const
{
	int cellPosition = (int)(
		floor(pGridPos.x / _cellSize) +
		floor(pGridPos.y / _cellSize) * pWidth);
	if (std::find(pBucketToAddTo->begin(),pBucketToAddTo->end(),cellPosition)!=pBucketToAddTo->end())
	{
		pBucketToAddTo->push_back(cellPosition);
	}
}
