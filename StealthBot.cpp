#include "StealthBot.h"

StealthBot::StealthBot(Unit *unit)
{
    this->unit = unit;
}

bool StealthBot::useAbility(int x, int y)
{
    if (this->unit->isRespawning) {
        return false;
    }

    if (this->hideCount <= 0) {
        return false;
    }

    this->unit->messageLog.push_back(this->unit->Name + " is currently immune to all attacks.");
    this->hideCount--;
    return true;
}
