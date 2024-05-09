#pragma once
#ifndef _BASE_ITEM
#include "movingObject.h"

class BaseItem
{
public:
	BaseItem() {};
	virtual bool canUse(Character* obj, Robot* robot) = 0;
	virtual void use(Character* obj, Robot* robot) = 0;
	virtual ItemType getItemType() const = 0;
};

class MagicBook : public BaseItem
{
public:
	bool canUse(Character*, Robot*);
	void use(Character*, Robot*);
	ItemType getItemType() const;
};

class EnergyDrink : public BaseItem
{
public:
	bool canUse(Character*, Robot*);
	void use(Character*, Robot*);
	ItemType getItemType() const;
};

class FirstAid : public BaseItem
{
public:
	bool canUse(Character*, Robot*);
	void use(Character*, Robot*);
	ItemType getItemType() const;
};

class ExcemptionCard : public BaseItem
{
public:
	bool canUse(Character*, Robot*);
	void use(Character*, Robot*);
	ItemType getItemType() const;
};

class PassingCard : public BaseItem
{
private:
	string challenge;
public:
	PassingCard(const string&);
	bool canUse(Character*, Robot*);
	void use(Character*, Robot*);
	ItemType getItemType() const;
};

#endif // !_BASE_ITEM
