/**********|**********|**********|
Program: Robot.h
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
#define GENERIC_ROBOT 0
#define JUMP_BOT 1    // Im Redefining it to an integer so its easy to call for
#define STEALTH_BOT 2 // your thinking bot later on
#define THIRTY_SHOT_BOT 3
#define LONG_SHOT_BOT 4
#define SEMI_AUTO_BOT 5
#define TRACKER_BOT 6
#define SCOUT_BOT 7
#define BLIND_BOT 8
#define HAWKING_BOT 9
#define DIZZY_SHOOTER_BOT 10
#include <iostream>
#include <vector>
#include "Types.h"
using namespace std;

string getRobotName(int robot_type);

class Unit;

class Robot
{
private:
    Unit *unit;

protected:
    Unit *getUnit();
    void setUnit(Unit *unit);
    int clampToLimit(int currentPos, int targetPos, int limit);

public:
    int robot_type; // make sure this is set to the defined constant of your special bot
};