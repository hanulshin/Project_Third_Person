#ifndef REFERENCE_COUNTER_H
#define REFERENCE_COUNTER_H
#include <vector>
#include "mge/core/GameObject.hpp"
template <typename T>
struct ReferenceCounter
{
public:
	static int objects_created;
	static int objects_alive;

	ReferenceCounter()
	{
		++objects_created;
		++objects_alive;
	}

	ReferenceCounter(const ReferenceCounter&)
	{
		++objects_created;
		++objects_alive;
	}
protected:
	~ReferenceCounter() // objects should never be removed through pointers of this type
	{
		--objects_alive;
	}
};
template <typename T> int ReferenceCounter<T>::objects_created(0);
template <typename T> int ReferenceCounter<T>::objects_alive(0);
//template <class T> ReferenceCounter<T>::gameObjects();
#endif // !REFERENCE_COUNTER_H
