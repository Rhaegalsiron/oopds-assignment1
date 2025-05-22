#pragma once
#include "Unit.h"
#include "Evolutions.h"

class JumpBot : public MoveBot
{
public:
    int robot_type = JUMP_BOT;
    JumpBot(Unit *unit);
    int chargesRemaining = 3;
    bool useAbility() { return false; }; // since JumpBot ability requires a coordinate
    bool useAbility(int x, int y);
};