#pragma once
#define INVALID_POSITION -999999999
#include <iostream>
#include "Types.h"
#include "AbstractRobot.h"
#include "Unit.h"
using namespace std;

class Robot : public AbstractRobot
{
public:
    Robot(Unit *unit);
    Unit *unit;
};

class GenericRobot : public Robot
{
public:
    using Robot::Robot;
    bool move(int x, int y);
    bool fire(int x, int y);
    bool look(int x, int y);
};

class MoveBot : public Robot
{
public:
    virtual bool move(int x, int y) = 0;
    bool fire(int x, int y) { return false; };
    bool look(int x, int y) { return false; };
};

class ActionBot : public Robot
{
public:
    virtual bool fire(int x, int y) = 0;
    bool move(int x, int y) { return false; };
    bool look(int x, int y) { return false; };
};

class SeeingBot : public Robot
{
public:
    virtual bool look(int x, int y) = 0;
    bool move(int x, int y) { return false; };
    bool fire(int x, int y) { return false; };
};

class JumpBot : public MoveBot
{
public:
    int chargesRemaining = 3;
    bool move(int x, int y);
};