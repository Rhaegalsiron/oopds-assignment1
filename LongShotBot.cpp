#include "LongShotBot.h"

LongShotBot::LongShotBot(Unit *unit)
{
    this->unit = unit;
}


bool LongShotBot::useAbility(int x, int y)
{
    if (this->unit->isRespawning || this->unit->hasFired)
    {
        return false;
    }

    x = this->clampToLimit(this->unit->currentGrid->x, x, 3);
    y = this->clampToLimit(this->unit->currentGrid->y, y, 3);
    Vector2D clampedCoordinates = this->unit->field->clampToBattlefield(x, y);
    x = clampedCoordinates.x;
    y = clampedCoordinates.y;

    Grid *targetGrid = this->unit->field->getGrid(x, y);
    Unit *targetUnit = targetGrid->occupyingUnit;
    bool isSuccessfulHit = rand() % 100 < this->hitChance;
    this->unit->onFiring(targetUnit, isSuccessfulHit, x, y);
    return isSuccessfulHit;
}
