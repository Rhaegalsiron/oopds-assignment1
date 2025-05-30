#include "BlindBot.h"

BlindBot::BlindBot(Unit *unit)
{
    this->robot_type = BLIND_BOT;
    this->setUnit(unit);
}

bool BlindBot::useAbility()
{
    if (this->getUnit()->isRespawning)
    {
        return false;
    }

    // BlindBot is blind, a debuff in the game, so it cannot see or target any units.
    this->getUnit()->log(this->getUnit()->Name + " used its ability. It cannot see or target any units.");
    return true;
}

bool BlindBot::useAbility(int x, int y)
{
    return false;
}

bool BlindBot::look(int x, int y)
{
    return false;
}
