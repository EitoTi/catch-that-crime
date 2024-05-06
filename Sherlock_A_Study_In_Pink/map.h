#pragma once
#ifndef _MAP
#include "thuvien.h"
class Map
{
private:
	int num_rows;
	int num_cols;
	MapElement*** map;
public:
	Map(int, int, int, Position*, int, Position*);
	~Map();
	bool isValid(const Position&, MovingObject*) const;
};
#endif // !_MAP
