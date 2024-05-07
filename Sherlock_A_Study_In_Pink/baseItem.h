#pragma once
#ifndef _BASE_ITEM
#include "movingObject.h"

class BaseItem
{
public:
	virtual bool canUse(Character* obj, Robot* robot) = 0;
	virtual void use(Character* obj, Robot* robot) = 0;
};

class MagicBook : public BaseItem
{
public:
	bool canUse(Character*, Robot*);
	void use(Character*, Robot*);
};

class EnergyDrink : public BaseItem
{
public:
	bool canUse(Character*, Robot*);
	void use(Character*, Robot*);
};

class FirstAid : public BaseItem
{
public:
	bool canUse(Character*, Robot*);
	void use(Character*, Robot*);
};

class ExcemptionCard : public BaseItem
{
public:
	bool canUse(Character*, Robot*);
	void use(Character*, Robot*);
};

class PassingCard : public BaseItem
{
private:
	string challenge;
public:
	PassingCard(const string&);
	bool canUse(Character*, Robot*);
	void use(Character*, Robot*);
};

#endif // !_BASE_ITEM
