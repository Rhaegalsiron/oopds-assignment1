#pragma once
#include "Robot.h"

class ShootingRobot : public virtual Robot
{
protected:
    int hitChance;

public:
    virtual bool useAbility() = 0;
    virtual bool useAbility(int x, int y) = 0;
    virtual bool fire(int x, int y) = 0;
};