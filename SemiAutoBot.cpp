/**********|**********|**********|
Program: SemiAutoBot.cpp
Course: OOPDS
Trimester: 2410
Name: HERBERT PILO ANAK BITA / LOH YONG SHENG / MING SU ANN / HEW WEE BO
ID: 243UC247H9 / 251UC250GG / 243UC246N0 / 251UC250HB
Lecture Section: TC4L
Tutorial Section: T16L / T15L (Loh)
Email: HERBERT.PILO.ANAK@student.mmu.edu.my / LOH.YONG.SHENG@student.mmu.edu.my / MING.SU.ANN@student.mmu.edu.my / hew.wee.bo@student.mmu.edu.my
Phone: 013-4221107 / 0146666830 / 0146011335 / 0128803121
**********|**********|**********/
#include "SemiAutoBot.h"

SemiAutoBot::SemiAutoBot(Unit *unit)
{
    this->robot_type = SEMI_AUTO_BOT;
    this->setUnit(unit);
    int hitChance = 70;
}

bool SemiAutoBot::useAbility(int x, int y)
{
    if (this->getUnit()->isRespawning || this->getUnit()->hasFired)
    {
        return false;
    }

    bool isSuccessfulHit = false;

    // Limit maxBurstSize to either the remaining shells or the burstSize attribute, whichever lower.
    int maxBurstSize = this->getUnit()->shellsRemaining < this->burstSize
                           ? this->getUnit()->shellsRemaining
                           : this->burstSize;
    for (int i = 0; i < maxBurstSize; i++)
    {
        isSuccessfulHit = isSuccessfulHit || rand() % 100 < this->hitChance;
    }

    x = this->clampToLimit(this->getUnit()->currentGrid->x, x, 1);
    y = this->clampToLimit(this->getUnit()->currentGrid->y, y, 1);
    Vector2D clampedCoordinates = this->getUnit()->field->clampToBattlefield(x, y);
    x = clampedCoordinates.x;
    y = clampedCoordinates.y;

    Grid *targetGrid = this->getUnit()->field->getGrid(x, y);
    Unit *targetUnit = targetGrid->occupyingUnit;
    this->getUnit()->shellsRemaining -= maxBurstSize - 1; // To account for the extra shots taken.
    this->getUnit()->onFiring(targetUnit, isSuccessfulHit, x, y);
    return isSuccessfulHit;
}

bool SemiAutoBot::useAbility()
{
    return false;
}

bool SemiAutoBot::fire(int x, int y)
{
    return false;
}