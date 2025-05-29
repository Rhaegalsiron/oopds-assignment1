#include "DizzyShooterBot.h"
#include "Unit.h"

DizzyShooterBot::DizzyShooterBot(Unit *unit)
{
    this->setUnit(unit);
}

bool DizzyShooterBot::useAbility()
{
    if (this->getUnit()->isRespawning)
    {
        return false;
    }
    this->getUnit()->log(this->getUnit()->Name + " has spun around too much and is now dizzy. It cannot fire this turn.");
    return true;
}

bool DizzyShooterBot::useAbility(int x, int y)
{
    return false;
}

bool DizzyShooterBot::fire(int x, int y)
{
    return false;
}