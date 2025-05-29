#include "SemiAutoBot.h"

SemiAutoBot::SemiAutoBot(Unit *unit)
{
    this->unit = unit;
    int hitChance = 70;
}

bool SemiAutoBot::useAbility(int x, int y)
{
    if (this->unit->isRespawning || this->unit->hasFired)
    {
        return false;
    }

    bool isSuccessfulHit = false;

    // Limit maxBurstSize to either the remaining shells or the burstSize attribute, whichever lower.
    int maxBurstSize = this->unit->shellsRemaining < this->burstSize
                           ? this->unit->shellsRemaining
                           : this->burstSize;
    for (int i = 0; i < maxBurstSize; i++)
    {
        isSuccessfulHit = isSuccessfulHit || rand() % 100 < this->hitChance;
    }

    x = this->clampToLimit(this->unit->currentGrid->x, x, 1);
    y = this->clampToLimit(this->unit->currentGrid->y, y, 1);
    Vector2D clampedCoordinates = this->unit->field->clampToBattlefield(x, y);
    x = clampedCoordinates.x;
    y = clampedCoordinates.y;

    Grid *targetGrid = this->unit->field->getGrid(x, y);
    Unit *targetUnit = targetGrid->occupyingUnit;
    this->unit->shellsRemaining -= maxBurstSize - 1; // To account for the extra shots taken.
    this->unit->onFiring(targetUnit, isSuccessfulHit, x, y);
    return isSuccessfulHit;
}
 