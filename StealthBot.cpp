/**********|**********|**********|
Program: StealthBot.cpp
Course: OOPDS
Trimester: 2410
Name: HERBERT PILO ANAK BITA / LOH YONG SHENG / MING SU ANN / HEW WEE BO
ID: 243UC247H9 / 251UC250GG / 243UC246N0 / 251UC250HB
Lecture Section: TC4L
Tutorial Section: T16L / T15L (Loh)
Email: HERBERT.PILO.ANAK@student.mmu.edu.my / LOH.YONG.SHENG@student.mmu.edu.my / MING.SU.ANN@student.mmu.edu.my / hew.wee.bo@student.mmu.edu.my
Phone: 013-4221107 / 0146666830 / 0146011335 / 0128803121
**********|**********|**********/

#include "StealthBot.h"
#include "Unit.h"

StealthBot::StealthBot(Unit *unit)
{
    this->robot_type = STEALTH_BOT;
    this->setUnit(unit);
}

bool StealthBot::useAbility()
{
    if (this->getUnit()->isRespawning) {
        return false;
    }

    if (this->hideCount <= 0) {
        return false;
    }

    this->getUnit()->messageLog.push_back(this->getUnit()->Name + " is currently immune to all attacks.");
    this->getUnit()->isStealthed = true; // You just needed to add this flag on Unit.cpp and set to true/false based on stealth state.:3
    this->hideCount--;
    return true;
}

bool StealthBot::useAbility(int x, int y) {
    return false;
}

bool StealthBot::move(int x, int y) {
    return false;
}
