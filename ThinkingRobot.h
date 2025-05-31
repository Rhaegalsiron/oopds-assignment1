/**********|**********|**********|
Program: ThinkingRobot.h
Course: OOPDS
Trimester: 2410
Name: HERBERT PILO ANAK BITA / LOH YONG SHENG / MING SU ANN / HEW WEE BO
ID: 243UC247H9 / 251UC250GG / 243UC246N0 / 251UC250HB
Lecture Section: TC4L
Tutorial Section: T16L / T15L (Loh)
Email: HERBERT.PILO.ANAK@student.mmu.edu.my / LOH.YONG.SHENG@student.mmu.edu.my / MING.SU.ANN@student.mmu.edu.my / hew.wee.bo@student.mmu.edu.my
Phone: 013-4221107 / 0146666830 / 0146011335 / 0128803121
**********|**********|**********/

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