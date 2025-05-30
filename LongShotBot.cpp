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
