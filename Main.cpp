#include <iostream>
#include "BattleField.h"
#include <vector>
#include <string>
#include "Unit.h"
#include "tests.h"
using namespace std;

int main()
{

    Game *game = new Game();
    int width = 10, height = 10;
    game->field->generateMap(width, height);
    Battlefield *battlefield1 = game->field;
    Grid *grid = battlefield1->getGrid(0, 0);
    Unit *tUnit1 = grid->occupyingUnit = new Unit(game, "Kid", 0, 0);
    grid = battlefield1->getGrid(0, 1);
    Unit *tUnit2 = grid->occupyingUnit = new Unit(game, "Jett", 0, 1);

    for (int i = 0; i < 11; i++)
    {   
        cout << "\nThinking iteration: " << i << endl;
        tUnit1->thinkingModule->thinkRobot();
        tUnit2->thinkingModule->thinkRobot();

        if (tUnit1->isRespawning) {
            cout << "tunit1 respawn" << endl;
        }
        else {
            int tUnit1MoveX = tUnit1->currentGrid->x;
            int tUnit1MoveY = tUnit1->currentGrid->y;
        }

        if (tUnit2->isRespawning) {
            cout << "tunit2 respawn" << endl;
        }
        else {
            int tUnit2MoveX = tUnit2->currentGrid->x;
            int tUnit2MoveY = tUnit2->currentGrid->y;
        }

        tUnit1->turnReset();
        tUnit2->turnReset();
        game->respawnAll();
        game->renderBattleField();
    }

    game->renderBattleField();
    cout << "main executed" << endl;

    // runTests();
    return 0;
}
