#pragma once
#ifndef _STUDYINPINK

#include "thuvien.h"

enum ItemType {
	MAGIC_BOOK,
	ENERGY_DRINK,
	FIRST_AID,
	EXCEMPTION_CARD,
	PASSING_CARD
};
enum ElementType {
	PATH,
	WALL,
	FAKE_WALL
};
enum RobotType {
	C = 0,
	S,
	W,
	SW
};

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;

class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;

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

	static const Position& getNPos();
};

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

class MovingObject
{
protected:
	int index;
	Position pos;
	Map* map;
	string name;

	int ManhattanDistance(const Position& pos1, const Position& pos2) const
	{
		return (abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol()));
	}
public:
	MovingObject(int, const Position, Map*, const string& name = "");
	virtual ~MovingObject();
	virtual Position getNextPosition() = 0;
	Position getCurrentPosition() const;
	virtual void move() = 0;
	virtual string str() const = 0;
	virtual string getName() const = 0;
};

class Character : public MovingObject
{
protected:
	int hp;
	int exp;
public:
	Character(int, const Position, Map*, const string&, int, int);
	virtual ~Character();

	virtual int getHp() const = 0;
	virtual int getExp() const = 0;
};

class Sherlock : public Character
{
private:
	string moving_rule;
	int moving_rule_index = 0;
public:
	Sherlock(int, const string&, const Position&, Map*, int, int);
	Position getNextPosition();
	void move();
	string str() const;

	string getName() const;
	int getHp() const;
	int getExp() const;
};

class Watson : public Character
{
private:
	string moving_rule;
	int moving_rule_index = 0;
public:
	Watson(int, const string&, const Position&, Map*, int, int);
	Position getNextPosition();
	void move();
	string str() const;

	string getName() const;
	int getHp() const;
	int getExp() const;
};

class Criminal : public Character
{
private:
	string moving_rule;
	int moving_rule_index = 0;
	Sherlock* sherlock;
	Watson* watson;
public:
	Criminal(int, const Position&, Map*, Sherlock*, Watson*);
	Position getNextPosition();
	void move();
	string str() const;

	string getName() const;
	int getHp() const;
	int getExp() const;
};

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
};

class Configuration
{
private:
	int map_num_rows = 0, map_num_cols = 0;
	int max_num_moving_objects = 0;
	int num_walls = 0;
	Position* arr_walls = nullptr;
	int num_fake_walls = 0;
	Position* arr_fake_walls = nullptr;
	string sherlock_moving_rule;
	Position sherlock_init_pos;
	int sherlock_init_hp = 0;
	int sherlock_init_exp = 0;
	string watson_moving_rule;
	Position watson_init_pos;
	int watson_init_hp = 0;
	int watson_init_exp = 0;
	Position criminal_init_pos;
	int num_steps = 0;
public:
	Configuration(const string&);
	~Configuration();
	string str() const;
};

class BaseItem
{
public:

};


class Robot : public MovingObject
{
protected:
	RobotType robot_type;
	BaseItem* item;

	const string ToString(RobotType robot_type) const
	{
		switch (robot_type)
		{
		case C:
			return "C";
		case S:
			return "S";
		case W:
			return "W";
		case SW:
			return "SW";
		default:
			return "[Unknown Robot Type]";
		}
	}
public:
	Robot(int, const Position, Map*, const string&);
	virtual ~Robot();
	int getDistance(Sherlock*) const;
	int getDistance(Watson*) const;
	virtual RobotType getType() const;

	void setRobotType(RobotType);
};

class RobotC : public Robot
{
private:
	Criminal* criminal;
public:
	RobotC(int, const Position&, Map*, Criminal*);
	~RobotC();
	Position getNextPosition();
	void move();
	string str() const;

	string getName() const;
	RobotType getType() const;
};

class RobotS: public Robot
{
private:
	Criminal* criminal;
	Sherlock* sherlock;
public:
	RobotS(int, const Position&, Map*, Criminal*, Sherlock*);
	~RobotS();
	Position getNextPosition();
	void move();
	string str() const;

	string getName() const;
	RobotType getType() const;
};

#endif // !_STUDYINPINK
