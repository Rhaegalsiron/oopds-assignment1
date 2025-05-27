#include "ThirtyShotBot.h"
#include <iostream>
using namespace std;

ThirtyShotBot::ThirtyShotBot(Unit *unit)
{
    this->unit = unit;
    this->magazineSize = 30;
    this->unit->magazineSize = this->magazineSize;
    this->unit->shellsRemaining = this->unit->magazineSize;
};
