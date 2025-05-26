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
    Unit *tUnit1 = new Unit(game, "Kid", 0, 0);
    Unit *tUnit2 = new Unit(game, "Jett", 0, 1);
    game->addToGame(tUnit1);
    game->addToGame(tUnit2);
    game->log("Simulation start...");
    game->renderBattleField();
    game->messageLog.clear();

    for (int i = 0; i < 10; i++)
    {
        cout << endl
             << endl;
        cout << "Step: " << to_string(i+1) << endl;
        game->respawnNext();
        game->executeTurn();
        game->renderBattleField();
        game->endTurn();
    }

    cout << "main executed" << endl;

    // runTests();
    return 0;
}
