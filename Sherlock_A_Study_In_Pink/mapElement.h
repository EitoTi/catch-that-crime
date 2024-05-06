#pragma once
#ifndef _MAP_ELEMENT
#include "thuvien.h"

class MapElement
{
protected:
	ElementType type;
public:
	MapElement();
	MapElement(ElementType in_type);
	virtual ~MapElement();
	virtual ElementType getType() const;
};

class Path : public MapElement
{
public:
	Path();
	~Path();
	ElementType getType() const;
};

class Wall : public MapElement
{
public:
	Wall();
	~Wall();
	ElementType getType() const;
};

class FakeWall : public MapElement
{
private:
	int req_exp;
public:
	FakeWall(int in_req_exp);
	~FakeWall();
	ElementType getType() const;
	int getReqExp() const;
};

#endif // !_MAP_ELEMENT
