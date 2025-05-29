#pragma once
#include "Robot.h"
#include "Ability.h"

class SeeingRobot : public virtual Robot, public virtual NoParamAbility, public virtual CoordinateParamAbility
{
public:
    virtual bool look(int x, int y) = 0;
};