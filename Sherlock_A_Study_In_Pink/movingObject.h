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
	// If Sherlock and Watson have invalid hp and exp -> canMove = false
	// -> Sherlock and Watson cannot move to the nextPos
	bool canMove;
protected:
	double hp;
	double exp;
public:
	// noModifyCharacterStats -> cannot solve challenges, character stats are not modified (use for excemption_card in baseItem class)
	// passChallenge -> no need to take the challenge 
	bool noModifyCharacterStats = false, passChallenge = false;

	Character(int, const Position, Map*, const string&, int, int);
	virtual ~Character();

	virtual double getHp() const = 0;
	virtual double getExp() const = 0;

	void setHp(double);
	void setExp(double);

	void roundHp();
	void roundExp();

	virtual Position getNextPosition() = 0;
	virtual void move() = 0;
	virtual string str() const = 0;
	virtual string getName() const = 0;

	virtual void setPos(const Position&) = 0;

	bool getCanMove() const;
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
	double getHp() const;
	double getExp() const;

	void setPos(const Position&);
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
	double getHp() const;
	double getExp() const;

	void setPos(const Position&);
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
	double getHp() const;
	double getExp() const;

	Position getPreviousPosition() const;

	int getCriminalNumSteps() const;
	void setCriminalNumSteps(int);

	void setPos(const Position&);
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
	void setItem(BaseItem*);

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
