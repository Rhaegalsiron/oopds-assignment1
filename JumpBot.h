#pragma once
#include "MovingRobot.h"

class Unit;

class JumpBot : public MovingRobot
{
public:
    JumpBot(Unit *unit);
    int chargesRemaining = 3;
    bool useAbility(); // since JumpBot ability requires a coordinate
    bool useAbility(int x, int y);
    bool move(int x, int y);
};