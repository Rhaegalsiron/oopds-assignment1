#pragma once

class NoParamAbility
{
public:
    virtual bool useAbility() = 0;
};

class CoordinateParamAbility
{
public:
    virtual bool useAbility(int x, int y) = 0;
};
