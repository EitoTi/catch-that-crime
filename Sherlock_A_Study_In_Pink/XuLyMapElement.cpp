#include "mapelement.h"

MapElement::MapElement() : type(PATH) {}
MapElement::MapElement(ElementType in_type) : type(in_type) {}
MapElement::~MapElement() {}
ElementType MapElement::getType() const
{
	return type;
}

Path::Path() : MapElement(PATH) {}
Path::~Path() {}
ElementType Path::getType() const
{
	return PATH;
}

Wall::Wall() : MapElement(WALL) {}
Wall::~Wall() {}
ElementType Wall::getType() const
{
	return WALL;
}

FakeWall::FakeWall(int in_req_exp) : req_exp(in_req_exp), MapElement(FAKE_WALL) {}
FakeWall::~FakeWall() {}
ElementType FakeWall::getType() const
{
	return FAKE_WALL;
}
int FakeWall::getReqExp() const
{
	return req_exp;
}