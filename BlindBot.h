#pragma once
#include "Unit.h"
#include "SeeingRobot.h"

class BlindBot : public SeeingRobot
{
protected:
    using Robot::clampToLimit;
    using Robot::getUnit;
    using Robot::setUnit;

public:
    BlindBot(Unit *unit);
    bool useAbility();
    bool useAbility(int x, int y); // its blind so no need value for x and y
    bool look(int x, int y);
};