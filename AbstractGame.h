#pragma once
#include <vector>
#include "BattleField.h"

class AbstractGame
{

public:
    vector<Unit *> respawnQueue;
    Battlefield *field;
    virtual void addToRespawn(Unit *unit) = 0;
    virtual void respawnNext() = 0;
};