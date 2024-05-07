#include "baseItem.h"

bool MagicBook::canUse(Character* obj, Robot* robot)
{
	return (obj->getExp() <= 350) ? true : false;
}
void MagicBook::use(Character* obj, Robot* robot)
{
	obj->increaseExp(25);
}

bool EnergyDrink::canUse(Character* obj, Robot* robot)
{
	return (obj->getHp() <= 100) ? true : false;
}
void EnergyDrink::use(Character* obj, Robot* robot)
{
	obj->increaseHp(20);
}

bool FirstAid::canUse(Character* obj, Robot* robot)
{
	return ((obj->getExp() <= 350) || (obj->getHp() <= 100)) ? true : false;
}
void FirstAid::use(Character* obj, Robot* robot)
{
	obj->increaseHp(50);
}

bool ExcemptionCard::canUse(Character* obj, Robot* robot)
{
	return ((obj->getName() == "Sherlock") && (obj->getHp() % 2 != 0)) ? true : false;
}
void ExcemptionCard::use(Character* obj, Robot* robot)
{

}

PassingCard::PassingCard(const string& challenge) : challenge(challenge) {}
bool PassingCard::canUse(Character* obj, Robot* robot)
{
	return ((obj->getName() == "Watson") && (obj->getHp() % 2 == 0)) ? true : false;
}
void PassingCard::use(Character* obj, Robot* robot)
{

}