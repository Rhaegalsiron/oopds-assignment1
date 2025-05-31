/**********|**********|**********|
Program: JumpBot.cpp
Course: OOPDS
Trimester: 2410
Name: HERBERT PILO ANAK BITA / LOH YONG SHENG / MING SU ANN / HEW WEE BO
ID: 243UC247H9 / 251UC250GG / 243UC246N0 / 251UC250HB
Lecture Section: TC4L
Tutorial Section: T16L / T15L (Loh)
Email: HERBERT.PILO.ANAK@student.mmu.edu.my / LOH.YONG.SHENG@student.mmu.edu.my / MING.SU.ANN@student.mmu.edu.my / hew.wee.bo@student.mmu.edu.my
Phone: 013-4221107 / 0146666830 / 0146011335 / 0128803121
**********|**********|**********/

#include "JumpBot.h"
#include "Unit.h"

JumpBot::JumpBot(Unit *unit)
{
    this->robot_type = JUMP_BOT;
    this->setUnit(unit);
}

bool JumpBot::useAbility(int x, int y)
{
    if (this->getUnit()->isRespawning)
    {
        return false;
    }

    if (this->chargesRemaining <= 0)
    {
        return false;
    }
    if (this->getUnit()->field->getGrid(x, y)->occupyingUnit != NULL)
    {
        return false;
    }
    this->getUnit()->updatePos(x, y);
    this->getUnit()->hasMoved = true; // set this flag hasMoved to true since the robot has moved.
    this->getUnit()->log(this->getUnit()->Name + " jumped to coordinates (" + to_string(x) + "," + to_string(y) + ").");
    this->chargesRemaining--;
    return true;
}

bool JumpBot::useAbility()
{
    return false;
}

bool JumpBot::move(int x, int y)
{
    return false;
}