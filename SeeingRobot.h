#pragma once
#include "Robot.h"

class SeeingRobot : public virtual Robot
{
public:
    virtual bool useAbility() = 0;
    virtual bool useAbility(int x, int y) = 0;
    virtual bool look(int x, int y) = 0;
};