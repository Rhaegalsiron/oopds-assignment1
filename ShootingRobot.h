#pragma once
#include "Robot.h"
#include "Ability.h"

class ShootingRobot : public virtual Robot, public virtual CoordinateParamAbility, public virtual NoParamAbility
{
protected:
    int hitChance;

public:
    virtual bool fire(int x, int y) = 0;
};