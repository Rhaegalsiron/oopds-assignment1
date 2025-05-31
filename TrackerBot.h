/**********|**********|**********|
Program: TrackerBot.h
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
#include "Types.h"
#include "Robot.h"
#include "Unit.h"
#include "BattleField.h"
#include "AbstractGame.h"
#include "SeeingRobot.h"
#include "Directions.h"


class TrackerBot : public SeeingRobot
{
private:
    int trackerCount = 3; // Number of tracking attempts available
    vector<Unit *> trackedTargets; // List of tracked robots

public:
    TrackerBot(Unit *unit);
    bool useAbility() { return false; };
    bool useAbility(int x, int y); // Tracks a robot at the specified position
    void revealLocation(); // Reveals the locations of tracked robots
    bool look(int x, int y);
};
