/**********|**********|**********|
Program: LongShotBot.cpp
Course: OOPDS
Trimester: 2410
Name: HERBERT PILO ANAK BITA / LOH YONG SHENG / MING SU ANN / HEW WEE BO
ID: 243UC247H9 / 251UC250GG / 243UC246N0 / 251UC250HB
Lecture Section: TC4L
Tutorial Section: T16L / T15L (Loh)
Email: HERBERT.PILO.ANAK@student.mmu.edu.my / LOH.YONG.SHENG@student.mmu.edu.my / MING.SU.ANN@student.mmu.edu.my / hew.wee.bo@student.mmu.edu.my
Phone: 013-4221107 / 0146666830 / 0146011335 / 0128803121
**********|**********|**********/

#include "LongShotBot.h"
#include "Unit.h"

LongShotBot::LongShotBot(Unit *unit)
{
    this->robot_type = LONG_SHOT_BOT;
    this->setUnit(unit);
}

bool LongShotBot::useAbility(int x, int y)
{
    if (this->getUnit()->isRespawning || this->getUnit()->hasFired)
    {
        return false;
    }

    x = this->clampToLimit(this->getUnit()->currentGrid->x, x, 3);
    y = this->clampToLimit(this->getUnit()->currentGrid->y, y, 3);
    Vector2D clampedCoordinates = this->getUnit()->field->clampToBattlefield(x, y);
    x = clampedCoordinates.x;
    y = clampedCoordinates.y;

    Grid *targetGrid = this->getUnit()->field->getGrid(x, y);
    Unit *targetUnit = targetGrid->occupyingUnit;
    bool isSuccessfulHit = rand() % 100 < this->hitChance;
    this->getUnit()->onFiring(targetUnit, isSuccessfulHit, x, y);
    return isSuccessfulHit;
}

bool LongShotBot::useAbility()
{
    return false;
}

bool LongShotBot::fire(int x, int y)
{
    return false;
}
