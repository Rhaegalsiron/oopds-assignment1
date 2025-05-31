/**********|**********|**********|
Program: BlindBot.cpp
Course: OOPDS
Trimester: 2410
Name: HERBERT PILO ANAK BITA / LOH YONG SHENG / MING SU ANN / HEW WEE BO
ID: 243UC247H9 / 251UC250GG / 243UC246N0 / 251UC250HB
Lecture Section: TC4L
Tutorial Section: T16L / T15L (Loh)
Email: HERBERT.PILO.ANAK@student.mmu.edu.my / LOH.YONG.SHENG@student.mmu.edu.my / MING.SU.ANN@student.mmu.edu.my / hew.wee.bo@student.mmu.edu.my
Phone: 013-4221107 / 0146666830 / 0146011335 / 0128803121
**********|**********|**********/

#include "BlindBot.h"

BlindBot::BlindBot(Unit *unit)
{
    this->robot_type = BLIND_BOT;
    this->setUnit(unit);
}

bool BlindBot::useAbility()
{
    if (this->getUnit()->isRespawning)
    {
        return false;
    }

    // BlindBot is blind, a debuff in the game, so it cannot see or target any units.
    this->getUnit()->log(this->getUnit()->Name + " used its ability. It cannot see or target any units.");
    return true;
}

bool BlindBot::useAbility(int x, int y)
{
    return false;
}

bool BlindBot::look(int x, int y)
{
    return false;
}
