#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // added this for you 
#include "BattleField.h"
#include "AbstractGame.h"
#include "Robot.h"

#include "Directions.h"
using namespace std;

class Unit;

class ThinkingRobot : public Robot

{
public:
    ThinkingRobot(Unit *unit); 
    int targetX, targetY;
    bool hasMoved;
    bool hasFired;
    vector<vector<string>> actionsOrder;

    void think();
    pair<int, int> randomDirection(int x, int y, bool forExtendedRange);

private:
    bool detectedRobot;

};