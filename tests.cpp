#include "tests.h"

vector<string> testLogs;

void log(string message)
{
    int timestamp = system_clock::now().time_since_epoch().count();
    testLogs.push_back(to_string(timestamp) + ": " + message);
}

Game *fixture_createGame()
{
    Game *game = new Game();
    int width = 3, height = 3;
    game->field->generateMap(width, height);
    return game;
};

bool test_battlefield()
{
    Game *game = fixture_createGame();
    Battlefield *battlefield1 = game->field;

    // Check map is empty on generation.
    for (int i = 0; i < battlefield1->map.size(); i++)
    {
        for (int j = 0; j < battlefield1->map[i].size(); j++)
        {
            if (battlefield1->map[i][j]->occupyingUnit != NULL)
            {
                return false;
            }
        }
    }

    Grid *grid = battlefield1->getGrid(0, 0);
    Unit *tUnit1 = grid->occupyingUnit = new Unit(game, "tUnit1", 0, 0);

    // Check Unit occupies grid (0,0) on the map.
    if (battlefield1->map[0][0]->occupyingUnit == NULL)
    {
        return false;
    }

    grid = battlefield1->getGrid(0, 1);
    Unit *tUnit2 = grid->occupyingUnit = new Unit(game, "tUnit2", 0, 1);

    // Check Unit occupies grid (0,1) on the map;
    if (battlefield1->map[1][0]->occupyingUnit == NULL)
    {
        return false;
    }

    // Check Unit in (0,0) is not the same as Unit in (0,1)
    if (&(battlefield1->getGrid(0, 0)->occupyingUnit) == &(battlefield1->getGrid(0, 1)->occupyingUnit))
    {
        return false;
    }

    return true;
}

bool test_respawn()
{
    Game *game = fixture_createGame();
    Battlefield *battlefield1 = game->field;

    Grid *grid = battlefield1->getGrid(0, 0);
    Unit *tUnit1 = grid->occupyingUnit = new Unit(game, "tUnit1", 0, 0);
    grid = battlefield1->getGrid(0, 1);
    Unit *tUnit2 = grid->occupyingUnit = new Unit(game, "tUnit2", 0, 1);
    if (game->respawnQueue.size() != 0)
    {
        return false;
    }
    tUnit1->defaultModule->hitChance = 100;
    log("tUnit1 hitchance: " + to_string(tUnit1->defaultModule->hitChance));
    tUnit1->fire(0, 1);
    if (game->respawnQueue.size() < 1)
    {
        return false;
    }
    game->respawnNext();
    bool hasRespawnSuccessfully = false;
    for (int i = 0; i < battlefield1->map.size(); i++)
    {
        for (int j = 0; j < battlefield1->map[i].size(); j++)
        {
            if (battlefield1->map[i][j]->occupyingUnit == tUnit2)
            {
                hasRespawnSuccessfully = true;
            }
        }
    }
    if (!hasRespawnSuccessfully)
    {
        return false;
    }
    return true;
}

bool test_fire()
{
    Game *game = fixture_createGame();
    Battlefield *battlefield1 = game->field;

    Grid *grid = battlefield1->getGrid(0, 0);
    Unit *tUnit1 = grid->occupyingUnit = new Unit(game, "tUnit1", 0, 0);
    grid = battlefield1->getGrid(0, 1);
    Unit *tUnit2 = grid->occupyingUnit = new Unit(game, "tUnit2", 0, 1);

    tUnit1->defaultModule->hitChance = 0;
    log("tUnit1 hitchance: " + to_string(tUnit1->defaultModule->hitChance));

    tUnit1->fire(0, 1);
    if (battlefield1->getGrid(0, 1)->occupyingUnit == NULL)
    {
        log("Unit is not occupying (0,1) and destroyed.");
        return false;
    }

    tUnit1->defaultModule->hitChance = 100;
    log("tUnit1 hitchance: " + to_string(tUnit1->defaultModule->hitChance));
    tUnit1->fire(0, 1);
    if (battlefield1->getGrid(0, 1)->occupyingUnit != NULL)
    {
        log("Unit still occupying (0,1) and not destroyed.");
        return false;
    }

    if (tUnit2->posX != -1 && tUnit2->posY != -1)
    {
        return false;
    }

    return true;
};

void runTests()
{
    cout << "Battlefield test " << (test_battlefield() ? "passed" : "failed") << endl;
    cout << "fire test " << (test_fire() ? "passed" : "failed") << endl;
    cout << "respawn test " << (test_respawn() ? "passed" : "failed") << endl;
    cout << testLogs.size() << " test log(s):" << endl;
    testLogs;
    for (int i = 0; i < testLogs.size(); i++)
    {
        cout << testLogs[i] << endl;
    }
}