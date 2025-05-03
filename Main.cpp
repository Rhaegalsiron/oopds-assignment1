#include <iostream>
#include "BattleField.h"
#include <vector>
#include <string>
#include "Unit.h"
using namespace std;

int main()
{

    int width = 10, height = 10;
    Battlefield battlefield1;
    battlefield1.generateMap(width, height);

    Grid *grid = battlefield1.getGrid(0, 0);
    grid->occupyingUnit = new Unit(battlefield1);
    Unit *tUnit = grid->occupyingUnit;
    grid = battlefield1.getGrid(0,1);
    grid->occupyingUnit = new Unit(battlefield1);
    battlefield1.displayMap();
    tUnit->fire(0,1);

    return 0;
}
