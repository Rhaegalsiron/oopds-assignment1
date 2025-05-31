/**********|**********|**********|
Program: DizzyScooterBot.cpp
Course: OOPDS
Trimester: 2410
Name: HERBERT PILO ANAK BITA / LOH YONG SHENG / MING SU ANN / HEW WEE BO
ID: 243UC247H9 / 251UC250GG / 243UC246N0 / 251UC250HB
Lecture Section: TC4L
Tutorial Section: T16L / T15L (Loh)
Email: HERBERT.PILO.ANAK@student.mmu.edu.my / LOH.YONG.SHENG@student.mmu.edu.my / MING.SU.ANN@student.mmu.edu.my / hew.wee.bo@student.mmu.edu.my
Phone: 013-4221107 / 0146666830 / 0146011335 / 0128803121
**********|**********|**********/

#include "DizzyShooterBot.h"
#include "Unit.h"

DizzyShooterBot::DizzyShooterBot(Unit *unit)
{
    this->robot_type = DIZZY_SHOOTER_BOT;
    this->setUnit(unit);
}

bool DizzyShooterBot::useAbility()
{
    if (this->getUnit()->isRespawning)
    {
        return false;
    }
    this->getUnit()->log(this->getUnit()->Name + " has spun around too much and is now dizzy. It cannot fire this turn.");
    return true;
}

bool DizzyShooterBot::useAbility(int x, int y)
{
    return false;
}

bool DizzyShooterBot::fire(int x, int y)
{
    return false;
}