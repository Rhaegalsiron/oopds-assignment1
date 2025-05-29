#include "StealthBot.h"

StealthBot::StealthBot(Unit *unit)
{
    this->unit = unit;
}

bool StealthBot::useAbility()
{
    if (this->unit->isRespawning) {
        return false;
    }

    if (this->hideCount <= 0) {
        return false;
    }

    this->unit->messageLog.push_back(this->unit->Name + " is currently immune to all attacks.");
    this->unit->isStealthed = true; // You just needed to add this flag on Unit.cpp and set to true/false based on stealth state.:3
    this->hideCount--;
    return true;
}
