#pragma once
#ifndef _ARRAY_MOVING_OBJECT
#include "movingObject.h"

class ArrayMovingObject
{
private:
	MovingObject** arr_mv_objs;
	int count;
	int capacity;
public:
	ArrayMovingObject(int);
	~ArrayMovingObject();
	bool isFull() const;
	bool add(MovingObject*);
	string str() const;
	int getCount();

	MovingObject* getMovingObjectAtIndex(int) const;
};
#endif // !_ARRAY_MOVING_OBJECT
