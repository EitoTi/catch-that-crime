#include "position.h"

// npos, r = c = -1
const Position Position::npos = Position(-1, -1);

Position::Position(int r, int c) : r(r), c(c) {}
Position::Position(const string& str_pos) // str_pos = (r,c)
{
	char temp;
	stringstream sso(str_pos);
	sso >> temp >> r >> temp >> c >> temp;
}
int Position::getRow() const
{
	return r;
}
int Position::getCol() const
{
	return c;
}
void Position::setRow(int r)
{
	this->r = r;
}
void Position::setCol(int c)
{
	this->c = c;
}
string Position::str() const // str_pos = (r,c)
{
	return "(" + to_string(r) + "," + to_string(c) + ")";
}
bool Position::isEqual(int in_r, int in_c) const
{
	return (r == in_r && c == in_c) ? true : false;
}
const Position& Position::getNPos()
{
	return npos;
}