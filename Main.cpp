#include <iostream>
#include <string>
#include "Game.h"
#include "Unit.h"
#include "Configuration.h"
#include "BattleField.h"

using namespace std;

int main()
{
    Configuration *configSetting = new Configuration("configuration.txt");
    Game *game = new Game(configSetting);

    game->runSimulation();

    // runTests();
    return 0;
}
