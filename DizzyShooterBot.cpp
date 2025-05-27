#include "dizzyshooterbot.h"

bool DizzyShooterBot::useAbility() {
    if (this->unit->isRespawning) {
        return false;
    }
    this->unit->log(this->unit->Name + " has spun around too much and is now dizzy. It cannot fire this turn.");
    return true;
}