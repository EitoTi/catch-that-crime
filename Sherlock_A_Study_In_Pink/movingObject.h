#pragma once
#ifndef _MOVING_OBJECT
#include "thuvien.h"
#include "position.h"
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
	Position getCurrentPosition() const;

	virtual Position getNextPosition() = 0;
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
	// noModifyCharacterStats -> cannot solve challenges, character stats is not modified
	// passChallenge -> no need to take the challenge 
	bool noModifyCharacterStats = false, passChallenge = false;

	Character(int, const Position, Map*, const string&, int, int);
	virtual ~Character();

	virtual int getHp() const = 0;
	virtual int getExp() const = 0;

	void setHp(int);
	void setExp(int);

	void roundHp();
	void roundExp();

	virtual Position getNextPosition() = 0;
	virtual void move() = 0;
	virtual string str() const = 0;
	virtual string getName() const = 0;
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
	Position previous_pos;
	int num_steps;
public:
	Criminal(int, const Position&, Map*, Sherlock*, Watson*);

	Position getNextPosition();
	void move();
	string str() const;
	string getName() const;
	int getHp() const;
	int getExp() const;

	Position getPreviousPosition() const;

	int getCriminalNumSteps() const;
	void setCriminalNumSteps(int);
};

class Robot : public MovingObject
{
protected:
	RobotType robot_type;
	BaseItem* item;
	static bool first_robot;

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

	virtual Position getNextPosition() = 0;
	virtual void move() = 0;
	virtual string str() const = 0;
	virtual string getName() const = 0;

	BaseItem* getItem();
	BaseItem* setItem(BaseItem*);

	static bool isFirstRobot();
	static void setFirstRobot(bool);
};

class RobotC : public Robot
{
private:
	Criminal* criminal;
public:
	RobotC(int, const Position&, Map*, Criminal*);
	~RobotC();

	RobotType getType() const;

	Position getNextPosition();
	void move();
	string str() const;
	string getName() const;
};

class RobotS : public Robot
{
private:
	Criminal* criminal;
	Sherlock* sherlock;
public:
	RobotS(int, const Position&, Map*, Criminal*, Sherlock*);
	~RobotS();

	RobotType getType() const;

	Position getNextPosition();
	void move();
	string str() const;
	string getName() const;
};

class RobotW : public Robot
{
private:
	Criminal* criminal;
	Watson* watson;
public:
	RobotW(int, const Position&, Map*, Criminal*, Watson*);
	~RobotW();

	RobotType getType() const;

	Position getNextPosition();
	void move();
	string str() const;
	string getName() const;
};

class RobotSW : public Robot
{
private:
	Criminal* criminal;
	Sherlock* sherlock;
	Watson* watson;
public:
	RobotSW(int, const Position&, Map*, Criminal*, Sherlock*, Watson*);
	~RobotSW();

	RobotType getType() const;

	Position getNextPosition();
	void move();
	string str() const;
	string getName() const;
};
#endif // !_MOVING_OBJECT
