#include "map.h"
#include "mapElement.h"
#include "position.h"
#include "movingObject.h"

Map::Map(int num_rows, int num_cols, int num_walls, Position* array_walls, int num_fake_walls, Position* array_fake_walls) : num_rows(num_rows), num_cols(num_cols)
{
	// Khoi tao Ban Do
	map = new MapElement * *[num_rows];
	for (int i = 0; i < num_rows; ++i)
		map[i] = new MapElement * [num_cols];
	for (int i = 0; i < num_rows; ++i)
		for (int j = 0; j < num_cols; ++j)
			map[i][j] = new Path();

	// Danh dau WALL tren Ban Do
	int tmpR, tmpC;
	for (int i = 0; i < num_walls; ++i)
	{
		tmpR = array_walls[i].getRow();
		tmpC = array_walls[i].getCol();
		delete map[tmpR][tmpC];
		map[tmpR][tmpC] = new Wall();
	}

	// Danh dau FAKE_WALL tren Ban Do
	for (int i = 0; i < num_fake_walls; ++i)
	{
		tmpR = array_fake_walls[i].getRow();
		tmpC = array_fake_walls[i].getCol();
		delete map[tmpR][tmpC];
		map[tmpR][tmpC] = new FakeWall((tmpR * 257 + tmpC * 139 + 89) % 900 + 1);
	}
}
Map::~Map()
{
	for (int i = 0; i < num_rows; ++i)
	{
		for (int j = 0; j < num_cols; ++j)
			delete map[i][j]; // Xoa tung doi tuong
		delete[] map[i]; // Xoa mang con tro map[i]
	}
	delete[] map; // Xoa mang map[]
	map = NULL;
	num_rows = num_cols = 0;
}
bool Map::isValid(const Position& pos, MovingObject* mv_obj) const
{
	// Kiem tra hop le
	if (pos.getRow() < 0 || pos.getRow() >= num_rows || pos.getCol() < 0 || pos.getCol() >= num_cols)
		return false;

	// Lay phan tu tai vi tri mv_obj muon di chuyen den
	MapElement* element = map[pos.getRow()][pos.getCol()];

	// Kiem tra
	if (element->getType() == WALL)
		return false;
	else if (element->getType() == FAKE_WALL)
	{
		FakeWall* fakewall = (FakeWall*)element;
		if (mv_obj->getName() == "Sherlock" || mv_obj->getName() == "Criminal")
			return true;
		else if (mv_obj->getName() == "Watson")
		{
			Watson* watson = (Watson*)mv_obj;
			if (watson->getExp() > fakewall->getReqExp())
				return true;
			return false;
		}
	}
	return true;
}