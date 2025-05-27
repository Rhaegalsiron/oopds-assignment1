#include "BlindBot.h"

BlindBot::BlindBot(Unit *unit)
{
    this->unit = unit;
}

bool BlindBot::useAbility()
{
    if (this->unit->isRespawning)
    {
        return false;
    }

    // BlindBot is blind, a debuff in the game, so it cannot see or target any units.
    this->unit->log(this->unit->Name + " used its ability. It cannot see or target any units.");
    return true;
}


