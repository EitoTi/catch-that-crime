#include "studyinpink.h"

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

	if (((next_pos.getRow() != Position::getNPos().getRow()) || (next_pos.getCol() != Position::getNPos().getCol())))
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

	if (((next_pos.getRow() != Position::getNPos().getRow()) || (next_pos.getCol() != Position::getNPos().getCol())))
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

	if (((next_pos.getRow() != Position::getNPos().getRow()) || (next_pos.getCol() != Position::getNPos().getCol())))
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

ArrayMovingObject::ArrayMovingObject(int capacity) : capacity(capacity), count(0)
{
	arr_mv_objs = new MovingObject * [capacity];
}
ArrayMovingObject::~ArrayMovingObject()
{
	for (int i = 0; i < count; ++i)
		delete arr_mv_objs[i];
	delete[] arr_mv_objs;
	count = 0;
	arr_mv_objs = NULL;
}
bool ArrayMovingObject::isFull() const
{
	return capacity == count;
}
bool ArrayMovingObject::add(MovingObject* mv_obj)
{
	if (isFull())
		return false;
	arr_mv_objs[count++] = mv_obj;
	return true;
}
string ArrayMovingObject::str() const
{
	string result = "ArrayMovingObject[count=" + to_string(count) + ";capacity=" + to_string(capacity) + ";";
	for (int i = 0; i < count; ++i)
	{
		result += arr_mv_objs[i]->str();
		if (i < count - 1)
			result += ";";
	}
	result += "]";
	return result;
}

Configuration::Configuration(const string& filepath)
{
	ifstream fileInput(filepath);

	if (fileInput.fail())
		cout << "Failed to open this file!" << endl;

	// Read each line of file
	string property;
	char tmp;
	int tmpInt = 0;
	while (!fileInput.eof())
	{
		char temp[255];
		fileInput.getline(temp, 255);
		string line = temp;

		for (int i = 0; i < line.size(); ++i)
			if (line[i] == '=')
				line[i] = ' ';

		stringstream sso(line);
		sso >> property;

		if (property == "MAP_NUM_ROWS")
			sso >> map_num_rows;
		else if (property == "MAP_NUM_COLS")
			sso >> map_num_cols;
		else if (property == "MAX_NUM_MOVING_OBJECTS")
			sso >> max_num_moving_objects;
		else if (property == "NUM_WALLS")
			sso >> num_walls;
		else if (property == "ARRAY_WALLS" || property == "ARRAY_FAKE_WALLS")
		{
			string array;
			sso >> array;

			// [(1,2);(2,3);(3,4)] --> remove '[' and ']'
			array = array.substr(1, array.size() - 2);

			stringstream ss(array);
			string toaDo;
			int size = (property == "ARRAY_WALLS") ? num_walls : num_fake_walls;
			Position* positions = new Position[size];

			// Tach string theo ';'
			int i = 0;
			while (getline(ss, toaDo, ';'))
			{
				// toaDo = (1,2)
				Position pos(toaDo);
				if (i < size)
					positions[i++] = pos;
			}

			if (property == "ARRAY_WALLS")
				arr_walls = positions;
			else
				arr_fake_walls = positions;
		}
		else if (property == "NUM_FAKE_WALLS")
			sso >> num_fake_walls;
		else if (property == "SHERLOCK_MOVING_RULE")
			sso >> sherlock_moving_rule;
		else if (property == "SHERLOCK_INIT_POS")
		{
			int r, c;
			sso >> tmp >> r >> tmp >> c >> tmp;
			sherlock_init_pos.setRow(r);
			sherlock_init_pos.setCol(c);
		}
		else if (property == "SHERLOCK_INIT_HP")
			sso >> sherlock_init_hp;
		else if (property == "SHERLOCK_INIT_EXP")
			sso >> sherlock_init_exp;
		else if (property == "WATSON_MOVING_RULE")
			sso >> watson_moving_rule;
		else if (property == "WATSON_INIT_POS")
		{
			int r, c;
			sso >> tmp >> r >> tmp >> c >> tmp;
			watson_init_pos.setRow(r);
			watson_init_pos.setCol(c);
		}
		else if (property == "WATSON_INIT_HP")
			sso >> watson_init_hp;
		else if (property == "WATSON_INIT_EXP")
			sso >> watson_init_exp;
		else if (property == "CRIMINAL_INIT_POS")
		{
			int r, c;
			sso >> tmp >> r >> tmp >> c >> tmp;
			criminal_init_pos.setRow(r);
			criminal_init_pos.setCol(c);
		}
		else if (property == "NUM_STEPS")
			sso >> num_steps;
	}
	cout << endl;

	fileInput.close();
}
Configuration::~Configuration()
{
	delete[] arr_walls;
	delete[] arr_fake_walls;
}
string Configuration::str() const
{
	string result = "Configuration[\n";
	result += "MAP_NUM_ROWS=" + to_string(map_num_rows) + "\n";
	result += "MAP_NUM_COLS=" + to_string(map_num_cols) + "\n";
	result += "MAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) + "\n";
	result += "NUM_WALLS=" + to_string(num_walls) + "\n";
	result += "ARRAY_WALLS=[";
	for (int i = 0; i < num_walls; ++i)
	{
		result += arr_walls[i].str();
		if (i < num_walls - 1)
			result += ";";
	}
	result += "]\n";
	result += "NUM_FAKE_WALLS=" + to_string(num_fake_walls) + "\n";
	result += "ARRAY_FAKE_WALLS=[";
	for (int i = 0; i < num_fake_walls; ++i)
	{
		result += arr_fake_walls[i].str();
		if (i < num_fake_walls - 1)
			result += ";";
	}
	result += "]\n";
	result += "SHERLOCK_MOVING_RULE=" + sherlock_moving_rule + "\n";
	result += "SHERLOCK_INIT_POS=" + sherlock_init_pos.str() + "\n";
	result += "SHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) + "\n";
	result += "SHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) + "\n";
	result += "WATSON_MOVING_RULE=" + watson_moving_rule + "\n";
	result += "WATSON_INIT_POS=" + watson_init_pos.str() + "\n";
	result += "WATSON_INIT_HP=" + to_string(watson_init_hp) + "\n";
	result += "WATSON_INIT_EXP=" + to_string(watson_init_exp) + "\n";
	result += "CRIMINAL_INIT_POS=" + criminal_init_pos.str() + "\n";
	result += "NUM_STEPS=" + to_string(num_steps) + "\n";
	result += "]";
	return result;
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
	if ((nextPos.getRow() != Position::getNPos().getRow()) && (nextPos.getCol() != Position::getNPos().getCol()))
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
	if ((nextPos.getRow() != Position::getNPos().getRow()) && (nextPos.getCol() != Position::getNPos().getCol()))
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
	if ((nextPos.getRow() != Position::getNPos().getRow()) && (nextPos.getCol() != Position::getNPos().getCol()))
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
	if ((nextPos.getRow() != Position::getNPos().getRow()) && (nextPos.getCol() != Position::getNPos().getCol()))
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