#include <iostream>
#include "BattleField.h"
#include <vector>
#include <string>
#include "Unit.h"
#include "tests.h"
using namespace std;

#define private public
#define protected public

int main()
{

    Game *game = new Game();
    int width = 10, height = 10;
    game->field->generateMap(width, height);
    Unit *kidd = new Unit(game, "Kidd");
    Unit *jett = new Unit(game, "Jett");
    Unit *alpha = new Unit(game, "Alpha");
    Unit *beta = new Unit(game, "Beta");
    Unit *star = new Unit(game, "Star");

    game->addToGame(kidd);
    game->addToGame(jett);
    game->addToGame(alpha);
    game->addToGame(beta);
    game->addToGame(star);

    kidd->updatePos(5, 5); // use this to spawn a robot with specified location
    jett->updatePos(6, 7);
    alpha->updatePos(8, 6);
    beta->updatePos(2, 4);
    game->addToRespawn(star); // use this to randomize spawn location of a specific robot
    game->respawnNext();

    game->log("Simulation start...");
    game->renderBattleField();
    game->messageLog.clear();

    for (int i = 0; i < 10; i++)
    {
        cout << endl
             << endl;
        cout << "Step: " << to_string(i + 1) << endl;
        game->respawnNext();
        game->executeTurn();
        game->renderBattleField();
        game->endTurn();
    }

    cout << "main executed" << endl;

    // runTests();
    return 0;
}
