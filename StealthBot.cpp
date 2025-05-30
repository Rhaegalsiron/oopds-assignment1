#include "StealthBot.h"
#include "Unit.h"

StealthBot::StealthBot(Unit *unit)
{
    this->robot_type = STEALTH_BOT;
    this->setUnit(unit);
}

bool StealthBot::useAbility()
{
    if (this->getUnit()->isRespawning) {
        return false;
    }

    if (this->hideCount <= 0) {
        return false;
    }

    this->getUnit()->messageLog.push_back(this->getUnit()->Name + " is currently immune to all attacks.");
    this->getUnit()->isStealthed = true; // You just needed to add this flag on Unit.cpp and set to true/false based on stealth state.:3
    this->hideCount--;
    return true;
}

bool StealthBot::useAbility(int x, int y) {
    return false;
}

bool StealthBot::move(int x, int y) {
    return false;
}
