#include "SemiAutoBot.h"

SemiAutoBot::SemiAutoBot(Unit *unit)
{
    this->unit = unit;
    int hitChance = 70;
}

bool SemiAutoBot::useAbility(int x, int y)
{

    if (this->unit->isRespawning) {
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
void SemiAutoBot::afterFiring(Unit *targetUnit, bool isSuccessfulHit, int x, int y)
{
    int magazineSize = 3;
    
    for (int i = 1; i < magazineSize; ++i)
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
    }

    if (shellsRemaining = 0)
    {
        this->unit->destroy();
    }
}
