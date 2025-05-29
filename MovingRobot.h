#pragma once
#include "Robot.h"
#include "Ability.h"

class MovingRobot : public virtual Robot, public virtual NoParamAbility, public virtual CoordinateParamAbility
{
public:
    virtual bool useAbility() = 0;
    virtual bool useAbility(int x, int y) = 0;
    virtual bool move(int x, int y) = 0;
};