/**********|**********|**********|
Program: GenericRobot.cpp
Course: OOPDS
Trimester: 2410
Name: HERBERT PILO ANAK BITA / LOH YONG SHENG / MING SU ANN / HEW WEE BO
ID: 243UC247H9 / 251UC250GG / 243UC246N0 / 251UC250HB
Lecture Section: TC4L
Tutorial Section: T16L / T15L (Loh)
Email: HERBERT.PILO.ANAK@student.mmu.edu.my / LOH.YONG.SHENG@student.mmu.edu.my / MING.SU.ANN@student.mmu.edu.my / hew.wee.bo@student.mmu.edu.my
Phone: 013-4221107 / 0146666830 / 0146011335 / 0128803121
**********|**********|**********/

#include "GenericRobot.h"
#include "Unit.h"
#include "BattleField.h"

GenericRobot::GenericRobot(Unit *unit)
{
    this->robot_type = GENERIC_ROBOT;
    this->setUnit(unit);
    this->hitChance = 70;
}

bool GenericRobot::move(int x, int y)
{
    if (this->getUnit()->isRespawning)
    {
        return false;
    }

    int deltaX = abs(this->getUnit()->currentGrid->x - x);
    int deltaY = abs(this->getUnit()->currentGrid->y - y);

    if (deltaX > 1 && x > this->getUnit()->currentGrid->x)
    {
        x = this->getUnit()->currentGrid->x + 1;
    }
    if (deltaX > 1 & x < this->getUnit()->currentGrid->x)
    {
        x = this->getUnit()->currentGrid->x - 1;
    }

    if (deltaY > 1 && y > this->getUnit()->currentGrid->y)
    {
        y = this->getUnit()->currentGrid->y + 1;
    }
    if (deltaY > 1 & y < this->getUnit()->currentGrid->y)
    {
        y = this->getUnit()->currentGrid->y - 1;
    }

    Vector2D clampedCoordinates = this->getUnit()->field->clampToBattlefield(x, y);
    x = clampedCoordinates.x;
    y = clampedCoordinates.y;

    bool isSuccefullyMoved = this->getUnit()->updatePos(x, y);

    if (isSuccefullyMoved)
    {
        this->getUnit()->log(this->getUnit()->Name + " moved to coordinates (" + to_string(x) + "," + to_string(y) + ").");
    }

    return isSuccefullyMoved;
}

bool GenericRobot::fire(int x, int y)
{
    if (this->getUnit()->isRespawning || this->getUnit()->hasFired)
    {
        return false;
    }

    x = this->clampToLimit(this->getUnit()->currentGrid->x, x, 1);
    y = this->clampToLimit(this->getUnit()->currentGrid->y, y, 1);
    Vector2D clampedCoordinates = this->getUnit()->field->clampToBattlefield(x, y);
    x = clampedCoordinates.x;
    y = clampedCoordinates.y;

    Grid *targetGrid = this->getUnit()->field->getGrid(x, y);
    Unit *targetUnit = targetGrid->occupyingUnit;
    bool isSuccessfulHit = rand() % 100 < this->hitChance;
    this->getUnit()->onFiring(targetUnit, isSuccessfulHit, x, y);
    return isSuccessfulHit;
}

bool GenericRobot::look(int x, int y)
{
    if (this->getUnit()->isRespawning)
    {
        return false;
    }

    int deltaX = abs(this->getUnit()->currentGrid->x - x);
    int deltaY = abs(this->getUnit()->currentGrid->y - y);

    if (deltaX > 1 && x > this->getUnit()->currentGrid->x)
    {
        x = this->getUnit()->currentGrid->x + 1;
    }
    if (deltaX > 1 & x < this->getUnit()->currentGrid->x)
    {
        x = this->getUnit()->currentGrid->x - 1;
    }

    if (deltaY > 1 && y > this->getUnit()->currentGrid->y)
    {
        y = this->getUnit()->currentGrid->y + 1;
    }
    if (deltaY > 1 & y < this->getUnit()->currentGrid->y)
    {
        y = this->getUnit()->currentGrid->y - 1;
    }

    this->getUnit()->seenUnit = this->getUnit()->field->getGrid(x, y)->occupyingUnit;
    return this->getUnit()->seenUnit != NULL;
}

bool GenericRobot::useAbility()
{
    return false;
}

bool GenericRobot::useAbility(int x, int y)
{
    return false;
}