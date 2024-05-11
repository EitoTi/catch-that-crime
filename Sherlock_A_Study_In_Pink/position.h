#pragma once
#ifndef _POSITION
#include "thuvien.h"
class Position
{
private:
	int r;
	int c;
	static const Position npos;
public:
	Position(int r = 0, int c = 0);
	Position(const string&);
	int getRow() const;
	int getCol() const;
	void setRow(int);
	void setCol(int);
	string str() const;
	bool isEqual(int, int) const;
	bool isEqual(const Position&) const;

	static const Position& getNPos();

	// Operator Overload
	bool operator!=(const Position&) const; 
	void operator=(const Position&);
};
#endif // !_POSITION
