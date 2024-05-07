#include "movingObject.h"
#include "map.h"
MovingObject::MovingObject(int index, const Position pos, Map* map, const string& name) : index(index), pos(pos), map(map), name(name) {}
MovingObject::~MovingObject()
{
	delete map;
	map = NULL;
}
Position MovingObject::getCurrentPosition() const
{
	return pos;
}

Character::Character(int index, const Position pos, Map* map, const string& name, int hp, int exp) : MovingObject(index, pos, map, name), hp(hp), exp(exp)
{
	// Xu ly hp
	if (hp > 500)
		this->hp = 500;
	else if (hp <= 0)
		this->hp = 0;
	else
		this->hp = hp;

	// Xu ly exp
	if (exp > 900)
		this->exp = 900;
	else if (exp <= 0)
		this->exp = 0;
	else
		this->exp = exp;
}
Character::~Character() {}
void Character::increaseExp(int percentage)
{
	int increase = this->exp * percentage / 100;
	this->exp += increase;
}
void Character::increaseHp(int percentage)
{
	int increase = this->hp * percentage / 100;
	this->hp += increase;
}
void Character::decreaseExp(int percentage)
{
	this->exp -= 50;
}

Sherlock::Sherlock(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp) : moving_rule(moving_rule), Character(index, init_pos, map, "Sherlock", init_hp, init_exp)
{
	// Xu ly hp
	if (init_hp > 500)
		hp = 500;
	else if (init_hp <= 0)
		hp = 0;
	else
		hp = init_hp;

	// Xu ly exp
	if (init_exp > 900)
		exp = 900;
	else if (init_exp <= 0)
		exp = 0;
	else
		exp = init_exp;
}
Position Sherlock::getNextPosition()
{
	char direction = moving_rule[moving_rule_index];

	// Object di chuyen theo moving_rule va quay lai dau chuoi khi den cuoi chuoi
	int size = moving_rule.size();
	moving_rule_index = (moving_rule_index + 1) % size;

	// Vi tri tiep theo dua tren moving_rule
	Position next_pos = getCurrentPosition();
	switch (direction)
	{
	case 'L':
		next_pos.setCol(next_pos.getCol() - 1);
		break;
	case 'R':
		next_pos.setCol(next_pos.getCol() + 1);
		break;
	case 'U':
		next_pos.setRow(next_pos.getRow() - 1);
		break;
	case 'D':
		next_pos.setRow(next_pos.getRow() + 1);
		break;
	default:
		return Position::getNPos();
	}

	return (!map->isValid(next_pos, this)) ? Position::getNPos() : next_pos;
}
void Sherlock::move()
{
	Position next_pos = getNextPosition();

	if (next_pos != Position::getNPos())
		pos = next_pos;

	// pos khong doi --> Sherlock dung im
}
string Sherlock::str() const
{
	// to_string -> typecast int to string
	return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}
string Sherlock::getName() const
{
	return name;
}
int Sherlock::getHp() const
{
	return hp;
}
int Sherlock::getExp() const
{
	return exp;
}

Watson::Watson(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp) : moving_rule(moving_rule), Character(index, init_pos, map, "Watson", init_hp, init_exp)
{
	// Xu ly hp
	if (init_hp > 500)
		hp = 500;
	else if (init_hp <= 0)
		hp = 0;
	else
		hp = init_hp;

	// Xu ly exp
	if (init_exp > 900)
		exp = 900;
	else if (init_exp <= 0)
		exp = 0;
	else
		exp = init_exp;
}
Position Watson::getNextPosition()
{
	char direction = moving_rule[moving_rule_index];

	// Object di chuyen theo moving_rule va quay lai dau chuoi khi den cuoi chuoi
	int size = moving_rule.size();
	moving_rule_index = (moving_rule_index + 1) % size;

	// Vi tri tiep theo dua tren moving_rule
	Position next_pos = getCurrentPosition();
	switch (direction)
	{
	case 'L':
		next_pos.setCol(next_pos.getCol() - 1);
		break;
	case 'R':
		next_pos.setCol(next_pos.getCol() + 1);
		break;
	case 'U':
		next_pos.setRow(next_pos.getRow() - 1);
		break;
	case 'D':
		next_pos.setRow(next_pos.getRow() + 1);
		break;
	default:
		return Position::getNPos();
	}

	return (!map->isValid(next_pos, this)) ? Position::getNPos() : next_pos;
}
void Watson::move()
{
	Position next_pos = getNextPosition();

	if (next_pos != Position::getNPos())
		pos = next_pos;

	// pos khong doi --> Watson dung im
}
string Watson::str() const
{
	// to_string -> typecast int to string
	return "Watson[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}
string Watson::getName() const
{
	return name;
}
int Watson::getHp() const
{
	return hp;
}
int Watson::getExp() const
{
	return exp;
}

Criminal::Criminal(int index, const Position& init_pos, Map* map, Sherlock* sherlock, Watson* watson) : sherlock(sherlock), watson(watson), Character(index, init_pos, map, "Criminal", 0, 0) {}
Position Criminal::getNextPosition()
{
	Position currentPos = getCurrentPosition();
	int numNextPositions = 0; // use for nextPositions[]
	Position nextPositions[4];
	int maxDistance = -1;
	int element = 0; // use for priorityDirection[]
	char* priorityDirection = new char[4];

	// Tim potential position voi 'L', 'R', 'U', 'D'
	for (char direction : {'L', 'R', 'U', 'D'})
	{
		Position potentialPos = currentPos;
		switch (direction)
		{
		case 'L':
			potentialPos.setCol(potentialPos.getCol() - 1);
			break;
		case 'R':
			potentialPos.setCol(potentialPos.getCol() + 1);
			break;
		case 'U':
			potentialPos.setRow(potentialPos.getRow() - 1);
			break;
		case 'D':
			potentialPos.setRow(potentialPos.getRow() + 1);
			break;
		}

		// Kiem tra hop le potential position
		if (!map->isValid(potentialPos, this))
			continue;

		int distanceToSherlock = ManhattanDistance(potentialPos, sherlock->getCurrentPosition());
		int distanceToWatson = ManhattanDistance(potentialPos, watson->getCurrentPosition());
		int totalDistance = distanceToSherlock + distanceToWatson;

		if (totalDistance > maxDistance)
		{
			maxDistance = totalDistance;
			numNextPositions = 1;
			nextPositions[0] = potentialPos;
			priorityDirection[element] = direction;
		}
		else if (totalDistance == maxDistance)
		{
			nextPositions[numNextPositions++] = potentialPos;
			priorityDirection[++element] = direction;
		}
	}

	if (numNextPositions > 0 && numNextPositions < 2)
	{
		delete[] priorityDirection;
		return nextPositions[0];
	}
	else if (numNextPositions > 1)
	{
		for (char direction : {'U', 'L', 'D', 'R'})
			for (int i = 0; i < numNextPositions; ++i) // for (int i = 0, j = 0; i < numNextPositions && j < element + 1; ++i, ++j)
				if (priorityDirection[i] == direction)
				{
					delete[] priorityDirection;
					return nextPositions[i];
				}
	}
	else
	{
		delete[] priorityDirection;
		return Position::getNPos();
	}
}
void Criminal::move()
{
	Position next_pos = getNextPosition();

	if (next_pos != Position::getNPos())
		pos = next_pos;

	// pos khong doi --> Criminal dung im
}
string Criminal::str() const
{
	return "Criminal[index=" + to_string(index) + ";pos=" + pos.str() + "]";
}
string Criminal::getName() const
{
	return name;
}
int Criminal::getHp() const
{
	return hp;
}
int Criminal::getExp() const
{
	return exp;
}

Robot::Robot(int index, const Position pos, Map* map, const string& name) : MovingObject(index, pos, map, name), robot_type(C), item(NULL) {}
Robot::~Robot()
{
	delete item;
	item = NULL;
}
int Robot::getDistance(Sherlock* sherlock) const
{
	return ManhattanDistance(this->pos, sherlock->getCurrentPosition());
}
int Robot::getDistance(Watson* watson) const
{
	return ManhattanDistance(this->pos, watson->getCurrentPosition());
}
RobotType Robot::getType() const
{
	return robot_type;
}
void Robot::setRobotType(RobotType robot_type)
{
	this->robot_type = robot_type;
}

RobotC::RobotC(int index, const Position& init_pos, Map* map, Criminal* criminal) : Robot(index, init_pos, map, "RobotC"), criminal(criminal)
{
	this->setRobotType(C);
}
RobotC::~RobotC()
{
	delete RobotC::criminal;
	criminal = NULL;
}
Position RobotC::getNextPosition()
{
	Position nextPos = criminal->getCurrentPosition();
	return (map->isValid(nextPos, this)) ? nextPos : Position::getNPos();
}
void RobotC::move()
{
	Position nextPos = getNextPosition();
	if (nextPos != Position::getNPos())
		this->pos = getNextPosition();
}
string RobotC::str() const
{
	return "Robot[pos=" + this->pos.str() + ";type=" + ToString(this->getType()) + "]";
}
string RobotC::getName() const
{
	return name;
}
RobotType RobotC::getType() const
{
	return C;
}

RobotS::RobotS(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock) : Robot(index, init_pos, map, "RobotS"), criminal(criminal), sherlock(sherlock)
{
	this->setRobotType(S);
}
RobotS::~RobotS()
{
	delete RobotS::criminal;
	delete RobotS::sherlock;
	criminal = NULL;
	sherlock = NULL;
}
Position RobotS::getNextPosition()
{
	Position currentPos = this->pos;
	Position sherlockPos = sherlock->getCurrentPosition();

	// Define the four possible next positions
	Position upPos(currentPos.getRow() - 1, currentPos.getCol());
	Position rightPos(currentPos.getRow(), currentPos.getCol() + 1);
	Position downPos(currentPos.getRow() + 1, currentPos.getCol());
	Position leftPos(currentPos.getRow(), currentPos.getCol() - 1);

	// Calculate the Manhattan distance to Sherlock for each possible next position
	int upDist = map->isValid(upPos, this) ? ManhattanDistance(upPos, sherlockPos) : INT_MAX;
	int rightDist = map->isValid(rightPos, this) ? ManhattanDistance(rightPos, sherlockPos) : INT_MAX;
	int downDist = map->isValid(downPos, this) ? ManhattanDistance(downPos, sherlockPos) : INT_MAX;
	int leftDist = map->isValid(leftPos, this) ? ManhattanDistance(leftPos, sherlockPos) : INT_MAX;

	// Find the minimum distance
	int minDist = min(min(upDist, rightDist), min(downDist, leftDist));

	// If all positions are invalid, return npos
	if (minDist == INT_MAX)
		return Position::getNPos();

	// Choose the next position based on the minimum distance and the clockwise order
	if (upDist == minDist)
		return upPos;
	else if (rightDist == minDist)
		return rightPos;
	else if (downDist == minDist)
		return downPos;
	else // leftDist == minDist
		return leftPos;
}
void RobotS::move()
{
	Position nextPos = getNextPosition();
	if (nextPos != Position::getNPos())
		this->pos = getNextPosition();
}
string RobotS::str() const
{
	return "Robot[pos=" + this->pos.str() + ";type=" + ToString(this->getType()) + ";dist=" + to_string(ManhattanDistance(this->pos, sherlock->getCurrentPosition())) + "]";
}

string RobotS::getName() const
{
	return name;
}
RobotType RobotS::getType() const
{
	return S;
}

RobotW::RobotW(int index, const Position& init_pos, Map* map, Criminal* criminal, Watson* watson) : Robot(index, init_pos, map, "RobotW"), criminal(criminal), watson(watson)
{
	this->setRobotType(W);
}
RobotW::~RobotW()
{
	delete RobotW::criminal;
	delete RobotW::watson;
	criminal = NULL;
	watson = NULL;
}
Position RobotW::getNextPosition()
{
	Position currentPos = this->pos;
	Position watsonPos = watson->getCurrentPosition();

	// Define the four possible next positions
	Position upPos(currentPos.getRow() - 1, currentPos.getCol());
	Position rightPos(currentPos.getRow(), currentPos.getCol() + 1);
	Position downPos(currentPos.getRow() + 1, currentPos.getCol());
	Position leftPos(currentPos.getRow(), currentPos.getCol() - 1);

	// Calculate the Manhattan distance to Sherlock for each possible next position
	int upDist = map->isValid(upPos, this) ? ManhattanDistance(upPos, watsonPos) : INT_MAX;
	int rightDist = map->isValid(rightPos, this) ? ManhattanDistance(rightPos, watsonPos) : INT_MAX;
	int downDist = map->isValid(downPos, this) ? ManhattanDistance(downPos, watsonPos) : INT_MAX;
	int leftDist = map->isValid(leftPos, this) ? ManhattanDistance(leftPos, watsonPos) : INT_MAX;

	// Find the minimum distance
	int minDist = min(min(upDist, rightDist), min(downDist, leftDist));

	// If all positions are invalid, return npos
	if (minDist == INT_MAX)
		return Position::getNPos();

	// Choose the next position based on the minimum distance and the clockwise order
	if (upDist == minDist)
		return upPos;
	else if (rightDist == minDist)
		return rightPos;
	else if (downDist == minDist)
		return downPos;
	else // leftDist == minDist
		return leftPos;
}
void RobotW::move()
{
	Position nextPos = getNextPosition();
	if (nextPos != Position::getNPos())
		this->pos = getNextPosition();
}
string RobotW::str() const
{
	return "Robot[pos=" + this->pos.str() + ";type=" + ToString(this->getType()) + ";dist=" + to_string(ManhattanDistance(this->pos, watson->getCurrentPosition())) + "]";
}
string RobotW::getName() const
{
	return name;
}
RobotType RobotW::getType() const
{
	return W;
}

RobotSW::RobotSW(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson) : Robot(index, init_pos, map, "RobotSW"), criminal(criminal), sherlock(sherlock), watson(watson)
{
	this->setRobotType(SW);
}
RobotSW::~RobotSW()
{
	delete RobotSW::criminal;
	delete RobotSW::sherlock;
	delete RobotSW::watson;
	criminal = NULL;
	sherlock = NULL;
	watson = NULL;
}
Position RobotSW::getNextPosition()
{
	Position currentPos = this->pos;
	Position sherlockPos = sherlock->getCurrentPosition();
	Position watsonPos = watson->getCurrentPosition();

	// Define the eight possible next positions
	Position upPos(currentPos.getRow() - 2, currentPos.getCol());
	Position upRightPos(currentPos.getRow() - 2, currentPos.getCol() + 2);
	Position rightPos(currentPos.getRow(), currentPos.getCol() + 2);
	Position downRightPos(currentPos.getRow() + 2, currentPos.getCol() + 2);
	Position downPos(currentPos.getRow() + 2, currentPos.getCol());
	Position downLeftPos(currentPos.getRow() + 2, currentPos.getCol() - 2);
	Position leftPos(currentPos.getRow(), currentPos.getCol() - 2);
	Position upLeftPos(currentPos.getRow() - 2, currentPos.getCol() - 2);

	// Calculate the total Manhattan distance to Sherlock and Watson for each possible next position
	int upDist = map->isValid(upPos, this) ? (ManhattanDistance(upPos, sherlockPos) + ManhattanDistance(upPos, watsonPos)) : INT_MAX;
	int upRightDist = map->isValid(upRightPos, this) ? (ManhattanDistance(upRightPos, sherlockPos) + ManhattanDistance(upRightPos, watsonPos)) : INT_MAX;
	int rightDist = map->isValid(rightPos, this) ? (ManhattanDistance(rightPos, sherlockPos) + ManhattanDistance(rightPos, watsonPos)) : INT_MAX;
	int downRightDist = map->isValid(downRightPos, this) ? (ManhattanDistance(downRightPos, sherlockPos) + ManhattanDistance(downRightPos, watsonPos)) : INT_MAX;
	int downDist = map->isValid(downPos, this) ? (ManhattanDistance(downPos, sherlockPos) + ManhattanDistance(downPos, watsonPos)) : INT_MAX;
	int downLeftDist = map->isValid(downLeftPos, this) ? (ManhattanDistance(downLeftPos, sherlockPos) + ManhattanDistance(downLeftPos, watsonPos)) : INT_MAX;
	int leftDist = map->isValid(leftPos, this) ? (ManhattanDistance(leftPos, sherlockPos) + ManhattanDistance(leftPos, watsonPos)) : INT_MAX;
	int upLeftDist = map->isValid(upLeftPos, this) ? (ManhattanDistance(upLeftPos, sherlockPos) + ManhattanDistance(upLeftPos, watsonPos)) : INT_MAX;

	// Find the minimum distance
	int minDist = min({ upDist, upRightDist, rightDist, downRightDist, downDist, downLeftDist, leftDist, upLeftDist });

	// If all positions are invalid, return npos
	if (minDist == INT_MAX)
		return Position::getNPos();

	// Choose the next position based on the minimum distance and the clockwise order
	if (upDist == minDist)
		return upPos;
	else if (upRightDist == minDist)
		return upRightPos;
	else if (rightDist == minDist)
		return rightPos;
	else if (downRightDist == minDist)
		return downRightPos;
	else if (downDist == minDist)
		return downPos;
	else if (downLeftDist == minDist)
		return downLeftPos;
	else if (leftDist == minDist)
		return leftPos;
	else // upLeftDist == minDist
		return upLeftPos;
}
void RobotSW::move()
{
	Position nextPos = getNextPosition();
	if (nextPos != Position::getNPos())
		this->pos = getNextPosition();
}
string RobotSW::str() const
{
	return "Robot[pos=" + this->pos.str() + ";type=" + ToString(this->getType()) + ";dist=" + to_string(ManhattanDistance(this->pos, sherlock->getCurrentPosition()) + ManhattanDistance(this->pos, watson->getCurrentPosition())) + "]";
}
string RobotSW::getName() const
{
	return name;
}
RobotType RobotSW::getType() const
{
	return SW;
}