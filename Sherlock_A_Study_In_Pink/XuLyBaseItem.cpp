#include "baseItem.h"

bool MagicBook::canUse(Character* character, Robot* robot)
{
    return (character->getExp() <= 350) ? true : false;
}
void MagicBook::use(Character* character, Robot* robot)
{
    character->setExp(character->getExp() * 1.25);
    character->roundExp();
}
ItemType MagicBook::getItemType() const
{
    return MAGIC_BOOK;
}

bool EnergyDrink::canUse(Character* character, Robot* robot)
{
    return (character->getHp() <= 100) ? true : false;
}
void EnergyDrink::use(Character* character, Robot* robot)
{
    character->setHp(character->getHp() * 1.20);
    character->roundHp();
}
ItemType EnergyDrink::getItemType() const
{
    return ENERGY_DRINK;
}

bool FirstAid::canUse(Character* character, Robot* robot)
{
    return ((character->getHp() <= 100) || (character->getExp() <= 350)) ? true : false;
}
void FirstAid::use(Character* character, Robot* robot)
{
    character->setHp(character->getHp() * 1.50);
    character->roundHp();
}
ItemType FirstAid::getItemType() const
{
    return FIRST_AID;
}

bool ExcemptionCard::canUse(Character* character, Robot* robot)
{
    return ((character->getName() == "Sherlock") && ((int)character->getHp() % 2 == 1)) ? true : false;
}
void ExcemptionCard::use(Character* character, Robot* robot)
{
    character->noModifyCharacterStats = true;
}
ItemType ExcemptionCard::getItemType() const
{
    return EXCEMPTION_CARD;
}

PassingCard::PassingCard(const string& challenge): challenge(challenge) {}
bool PassingCard::canUse(Character* character, Robot* robot)
{
    return ((character->getName() == "Watson") && ((int)character->getHp() % 2 == 0)) ? true : false;
}
void PassingCard::use(Character* character, Robot* robot)
{
    if ((challenge == "all") || (challenge == robot->getName()))
        character->passChallenge = true;
    else
    {
        character->setExp(character->getExp() - 50);
        character->passChallenge = true;
    }
}
ItemType PassingCard::getItemType() const
{
    return PASSING_CARD;
}
