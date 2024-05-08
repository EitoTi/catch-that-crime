#include "baseItem.h"

bool MagicBook::canUse(Character *character, Robot *robot)
{
    if (character->getExp() <= 350)
        return true;
    return false;
}

void MagicBook::use(Character *character, Robot *robot)
{
    character->setExp(character->getExp() * 1.25);
    character->roundExp();
}

bool EnergyDrink::canUse(Character *character, Robot *robot)
{
    if (character->getHp() <= 100)
        return true;
    return false;
}

void EnergyDrink::use(Character *character, Robot *robot)
{
    character->setHp(character->getHp() * 1.20);
    character->roundHp();
}

bool FirstAid::canUse(Character *character, Robot *robot)
{
    if ((character->getHp() <= 100) || (character->getExp() <= 350))
        return true;
    return false;
}

void FirstAid::use(Character *character, Robot *robot)
{
    character->setHp(character->getHp() * 1.50);
    character->roundHp();
}

bool ExcemptionCard::canUse(Character *character, Robot *robot)
{
    if ((character->getName() == "Sherlock") && (character->getHp() % 2 == 1))
        return true;
    return false;
}

void ExcemptionCard::use(Character *character, Robot *robot)
{
    character->god = true;
}

bool PassingCard::canUse(Character *character, Robot *robot)
{
    if ((character->getName() == "Watson") && (character->getHp() % 2 == 0))
        return true;
    return false;
}

void PassingCard::use(Character *character, Robot *robot)
{
    if ((challenge == "all") || (challenge == robot->getName()))
        character->inner_main_character = true;
    else
    {
        character->setExp(character->getExp() - 50);
        character->inner_main_character = true;
    }
}
