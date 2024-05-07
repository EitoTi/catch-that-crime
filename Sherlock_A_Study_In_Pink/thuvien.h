#pragma once
#ifndef _THUVIEN

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <climits>
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

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

// Forward declarations
class MapElement;
class Map;
class Position;

class MovingObject;
class Character;
class Sherlock;
class Waston;
class Criminal;

class ArrayMovingObject;
class Configuration;

class Robot;
class RobotC;
class RobotS;
class RobotW;
class RobotSW;

class BaseItem;
class MagicBook;
class EnergyDrink;
class FirstAid;
class ExcemptionCard;
class PassingCard;

class BaseBag;
class SherlockBag;
class WatsonBag;

class StudyInPinkProgram;
class TestStudyInPink;

#endif // !_THUVIEN

// Hello Cuong dep trai!
