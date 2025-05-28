#include "LongShotBot.h"

LongShotBot::LongShotBot(Unit *unit)
{
    this->unit = unit;
}


bool LongShotBot::useAbility(int x, int y)
{
    int curX = this->unit->currentGrid;
    int curY = this->unit->currentGrid;
    int distance = abs(curX - x) + abs(curY - y); // firing distance (x + y <= 3)

    if (this->unit->isRespawning) {
        return false;
    }

    if (distance > 3) {
        return false;
    }

    if (unit->shellsRemaining <= 0) {
        return false;
    }

    this->unit->hasFired = true;
    this->shellsRemaining--;
    return true;
}

// Logs message if the shot was successful or not
// After that, robot will self destruct if all bullets are used 
void LongShotBot::afterFiring(Unit *targetUnit, bool isSuccessfulHit, int x, int y)
{
    if (targetUnit != NULL)
    {
        bool isSuccessfulHit = rand() % 100 < this->hitChance;
        if (isSuccessfulHit) 
        {
            targetUnit->destroy();
            this->unit->messageLog.push_back(this->unit->Name + " has destroyed target at ( " + to_string(x) + "," + to_string(y) + ").");
            return true;
        }

        else
        {
            this->unit->messageLog.push_back("Shot missed. We'll get 'em next time.");
            return false;
        }
    }

    if (shellsRemaining = 0)
    {
        this->unit->destroy();
    }
}
