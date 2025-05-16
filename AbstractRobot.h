#pragma once
#include <iostream>
#include "Types.h"
using namespace std;

class AbstractRobot
{
public:
    virtual bool move(int x, int y) = 0;
    virtual bool fire(int x, int y) = 0;
    virtual bool look(int x, int y) = 0;
};