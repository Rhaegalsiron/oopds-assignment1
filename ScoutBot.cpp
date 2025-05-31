/**********|**********|**********|
Program: ScoutBot.cpp
Course: OOPDS
Trimester: 2410
Name: HERBERT PILO ANAK BITA / LOH YONG SHENG / MING SU ANN / HEW WEE BO
ID: 243UC247H9 / 251UC250GG / 243UC246N0 / 251UC250HB
Lecture Section: TC4L
Tutorial Section: T16L / T15L (Loh)
Email: HERBERT.PILO.ANAK@student.mmu.edu.my / LOH.YONG.SHENG@student.mmu.edu.my / MING.SU.ANN@student.mmu.edu.my / hew.wee.bo@student.mmu.edu.my
Phone: 013-4221107 / 0146666830 / 0146011335 / 0128803121
**********|**********|**********/

#include <iostream>
#include "ScoutBot.h"
#include "Unit.h"
using namespace std;

ScoutBot::ScoutBot(Unit *unit)
{
    this->robot_type = SCOUT_BOT;
    this->setUnit(unit);
    this->mapVisionCount = 3;
};

bool ScoutBot::useAbility(int x, int y)
{
    if (this->getUnit()->isRespawning)
    {
        return false;
    }
    if (mapVisionCount <= 0)
    {
        this->getUnit()->log("No map vision uses remaining!");
        // cout << "No map vision uses remaining!" << endl;
        return false;
    }

    // Get the grid at the specified coordinates
    Grid *targetGrid = this->getUnit()->field->getGrid(x, y);
    if (targetGrid == NULL)
    {
        this->getUnit()->log("Invalid grid coordinates");
        // cout << "Invalid grid coordinates" << endl;
        return false;
    }

    // Check if there is a unit at the target grid
    if (targetGrid->occupyingUnit != NULL)
    {
        Unit *targetUnit = targetGrid->occupyingUnit;
        this->getUnit()->log("Unit found at (" + to_string(x) + "," + to_string(y) + "): " + targetUnit->Name);
        // cout << "Unit found at (" << x << "," << y << "): " << targetUnit->Name << endl;
    }
    else
    {
        this->getUnit()->log("No unit found at (" + to_string(x) + "," + to_string(y) + ").");
        // cout << "No unit found at (" << x << "," << y << ")." << endl;
    }

    // Lower mapVisionCount after use
    mapVisionCount--;
    return true;
}

bool ScoutBot::useAbility()
{
    return false;
}

bool ScoutBot::look(int x, int y)
{
    return false;
}