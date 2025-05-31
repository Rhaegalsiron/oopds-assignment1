/**********|**********|**********|
Program: ThirtyShotBot.cpp
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
#include "ThirtyShotBot.h"
#include "Unit.h"
using namespace std;

ThirtyShotBot::ThirtyShotBot(Unit *unit)
{
    this->robot_type = THIRTY_SHOT_BOT;
    this->setUnit(unit);
    this->magazineSize = 30;
    this->getUnit()->magazineSize = this->magazineSize;
    this->getUnit()->shellsRemaining = this->getUnit()->magazineSize;
}

bool ThirtyShotBot::useAbility(int x, int y)
{
    return this->fire(x, y);
}

bool ThirtyShotBot::fire(int x, int y)
{
    return false;
}

bool ThirtyShotBot::useAbility()
{
    return false;
}
