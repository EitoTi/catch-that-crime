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

bool EnergyDrink::canUse(Character* character, Robot* robot)
{
    return (character->getHp() <= 100) ? true : false;
}
void EnergyDrink::use(Character* character, Robot* robot)
{
    character->setHp(character->getHp() * 1.20);
    character->roundHp();
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

bool ExcemptionCard::canUse(Character* character, Robot* robot)
{
    return ((character->getName() == "Sherlock") && (character->getHp() % 2 == 1)) ? true : false;
}
void ExcemptionCard::use(Character* character, Robot* robot)
{
    character->noModifyCharacterStats = true;
}

bool PassingCard::canUse(Character* character, Robot* robot)
{
    return ((character->getName() == "Watson") && (character->getHp() % 2 == 0)) ? true : false;
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
