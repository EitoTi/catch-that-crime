#include "arrayMovingObject.h"

ArrayMovingObject::ArrayMovingObject(int capacity) : capacity(capacity), count(0)
{
	arr_mv_objs = new MovingObject * [capacity];
}
ArrayMovingObject::~ArrayMovingObject()
{
	delete[] arr_mv_objs;
}
bool ArrayMovingObject::isFull() const
{
	return capacity == count;
}
bool ArrayMovingObject::add(MovingObject* mv_obj)
{
	if (isFull())
		return false;
	arr_mv_objs[count++] = mv_obj;
	return true;
}
string ArrayMovingObject::str() const
{
	string result = "ArrayMovingObject[count=" + to_string(count) + ";capacity=" + to_string(capacity) + ";";
	for (int i = 0; i < count; ++i)
	{
		result += arr_mv_objs[i]->str();
		if (i < count - 1)
			result += ";";
	}
	result += "]";
	return result;
}
int ArrayMovingObject::getCount()
{
	return count;
}
MovingObject* ArrayMovingObject::getMovingObectAtPosition(int position) const
{
	return arr_mv_objs[position];
}
