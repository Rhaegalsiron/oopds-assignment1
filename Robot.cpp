/**********|**********|**********|
Program: Robot.cpp
Course: OOPDS
Trimester: 2410
Name: HERBERT PILO ANAK BITA / LOH YONG SHENG / MING SU ANN / HEW WEE BO
ID: 243UC247H9 / 251UC250GG / 243UC246N0 / 251UC250HB
Lecture Section: TC4L
Tutorial Section: T16L / T15L (Loh)
Email: HERBERT.PILO.ANAK@student.mmu.edu.my / LOH.YONG.SHENG@student.mmu.edu.my / MING.SU.ANN@student.mmu.edu.my / hew.wee.bo@student.mmu.edu.my
Phone: 013-4221107 / 0146666830 / 0146011335 / 0128803121
**********|**********|**********/

#include "Robot.h"

vector<string> robotNames = {"Generic Robot", "Jump Bot", "Stealth Bot", "Thirty Shot Bot", "Long Shot Bot", "Semi Auto Bot", "Tracker Bot", "Scout Bot", "Blind Bot", "Hawking Bot", "Dizzy Shooter Bot"};

string getRobotName(int robot_type) {
    return robotNames[robot_type];
}

int Robot::clampToLimit(int currentPos, int targetPos, int limit)
{
    int deltaPos = abs(currentPos - targetPos);
    if (deltaPos <= limit)
    {
        return targetPos;
    }
    if (targetPos < currentPos)
    {
        return currentPos - limit;
    }
    return currentPos + limit;
}

Unit *Robot::getUnit()
{
    return this->unit;
}

void Robot::setUnit(Unit *unit)
{
    this->unit = unit;
}