#include <iostream>
#include "ThirtyShotBot.h"
#include "Unit.h"
using namespace std;

ThirtyShotBot::ThirtyShotBot(Unit *unit)
{
    this->setUnit(unit);
    this->magazineSize = 30;
    this->getUnit()->magazineSize = this->magazineSize;
    this->getUnit()->shellsRemaining = this->getUnit()->magazineSize;
}

bool ThirtyShotBot::useAbility(int x, int y)
{
    return this->fire(x, y);
}
