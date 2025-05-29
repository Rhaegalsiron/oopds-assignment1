#pragma once
#include "Robot.h"
#include "MovingRobot.h"
#include "ShootingRobot.h"
#include "SeeingRobot.h"

class Unit;

class GenericRobot : public MovingRobot, public virtual ShootingRobot, public virtual SeeingRobot
{
public:
    int robot_type = GENERIC_ROBOT;
    GenericRobot(Unit *unit);
    bool useAbility();
    bool useAbility(int x, int y);
    bool move(int x, int y);
    bool fire(int x, int y);
    bool look(int x, int y);

protected:
    using Robot::clampToLimit;
    using Robot::getUnit;
    using Robot::setUnit;
};