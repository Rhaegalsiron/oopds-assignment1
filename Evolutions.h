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
    int robot_type; // make sure this is set to the defined constant of your special bot
    Unit *unit;
    virtual void thinkRobot() { return; };
    virtual bool useAbility() { return false; };
    virtual bool useAbility(Unit *unit) { return false; };
    virtual bool useAbility(int x, int y) { return false; };
    virtual bool move(int x, int y) { return false; };
    virtual bool fire(int x, int y) { return false; };
    virtual bool look(int x, int y) { return false; };
    int clampToLimit(int currentPos, int targetPos, int limit);
};

// All special bots have must have a useAbility function that returns true if the ability is used, and false if the ability cannot be used.
// Override the polymorphic method that is marked virtual for your specific bot.

class MoveBot : public Robot
{
public:
    virtual bool useAbility() { return false; };             // for StealthBot
    virtual bool useAbility(int x, int y) { return false; }; // for JumpBot
};

class ActionBot : public Robot
{
public:
    virtual bool useAbility(int x, int y) = 0; // for LongShotBot and SemiAutoBot
};

class SeeingBot : public Robot
{
public:
    virtual bool useAbility() { return false; };           // for MapVisionBot
    virtual bool useAbility(Unit *unit) { return false; }; // for TrackerBot
};