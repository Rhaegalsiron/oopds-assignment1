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

    if (tUnit2->currentGrid != NULL)
    {
        return false;
    }

    return true;
};

bool test_evolve()
{
    Game *game = fixture_createGame();
    Battlefield *battlefield1 = game->field;

    Grid *grid = battlefield1->getGrid(0, 0);
    Unit *tUnit1 = grid->occupyingUnit = new Unit(game, "tUnit1", 0, 0);
    grid = battlefield1->getGrid(0, 1);
    Unit *tUnit2 = grid->occupyingUnit = new Unit(game, "tUnit2", 0, 1);

    if (tUnit1->moveModule != NULL)
    {
        log("moveModule is not NULL");
        return false;
    }

    tUnit1->defaultModule->hitChance = 0;
    tUnit1->fire(0, 1);
    if (tUnit1->canEvolve)
    {
        log("tUnit1 can evolve eventhough no Unit is destroyed");
        return false;
    }

    tUnit1->defaultModule->hitChance = 100;
    tUnit1->fire(0, 1);
    if (!tUnit1->canEvolve)
    {
        log("tUnit1 cannot evolve eventhough unit is destroyed");
        return false;
    }

    // to check whether all 7 evolution options are available
    if (tUnit1->getEvolutionOptions().size() != 7)
    {
        log("tUnit1 evolutionOptions is not 7");
        return false;
    }

    tUnit1->evolve(JUMP_BOT);
    // check if tUnit1 has evolved to JumpBot
    if (tUnit1->moveModule == NULL)
    {
        log("tUnit1 move module is still null even after evolution");
        return false;
    }

    if (tUnit1->getEvolutionOptions().size() > 5)
    {
        log("tUnit1 has more than 5 evolutionOptions even after evolving");
        return false;
    }

    vector<int> evolutionOptions = tUnit1->getEvolutionOptions();
    // To ensure JumpBot is no longer an available option
    if (std::find(evolutionOptions.begin(), evolutionOptions.end(), JUMP_BOT) != evolutionOptions.end())
    {
        log("JumpBot still in tUnit1 evolutionOptions");
        return false;
    }
    // To ensure StealthBot is no longer an available option
    if (std::find(evolutionOptions.begin(), evolutionOptions.end(), STEALTH_BOT) != evolutionOptions.end())
    {
        log("StealthBot still in tUnit1 evolutionOptions");
        return false;
    }

    tUnit1->moveModule->useAbility(2, 2);
    if (battlefield1->getGrid(2, 2)->occupyingUnit != tUnit1)
    {
        log("tUnit1 cannot use the JumpBot functionality");
        return false;
    }

    return true;
}

bool test_look()
{
    Game *game = fixture_createGame();
    Battlefield *battlefield1 = game->field;

    Grid *grid = battlefield1->getGrid(0, 0);
    Unit *tUnit1 = grid->occupyingUnit = new Unit(game, "tUnit1", 0, 0);
    grid = battlefield1->getGrid(0, 1);
    Unit *tUnit2 = grid->occupyingUnit = new Unit(game, "tUnit2", 0, 1);

    Unit *tLookUnit = tUnit1->look(0, 1);
    if (tLookUnit == NULL)
    {
        log("Unit not found.");
        return false;
    }

    if (tLookUnit != tUnit2)
    {
        log("Unit looked at is not the same as the Unit in that grid.");
        return false;
    }

    tUnit1->turnReset();
    grid = battlefield1->getGrid(0, 2);
    Unit *tUnit3 = grid->occupyingUnit = new Unit(game, "tUnit3", 0, 2);

    tLookUnit = tUnit1->look(0, 2);
    if (tLookUnit == tUnit3)
    {
        log("tUnit3 should be out of vision range.");
        return false;
    }
    if (tLookUnit != tUnit2)
    {
        log("Unit looked at is not tUnit2.");
        return false;
    }

    tUnit1->turnReset();
    tLookUnit = tUnit1->look(1, 0);
    if (tLookUnit != NULL)
    {
        log("No unit should be on looked at coordinates.");
        return false;
    }

    return true;
}

bool test_move()
{
    Game *game = fixture_createGame();
    Battlefield *battlefield1 = game->field;
    Grid *grid = battlefield1->getGrid(0, 0);
    Unit *tUnit1 = grid->occupyingUnit = new Unit(game, "tUnit1", 0, 0);

    tUnit1->move(Directions::RIGHT);
    if (battlefield1->getGrid(1, 0)->occupyingUnit != tUnit1)
    {
        log("Moved unit was not found in (1,0).");
        return false;
    }

    if (grid->occupyingUnit != NULL)
    {
        log("Pointer to tUnit1 still in (0,0).");
        return false;
    }

    Unit *tUnit2 = grid->occupyingUnit = new Unit(game, "tUnit2", 0, 0);
    tUnit1->turnReset();
    if (tUnit1->move(Directions::LEFT))
    {
        log("tUnit1 should not be able to move into space occupied by tUnit2.");
        return false;
    }

    return true;
}

void runTests()
{
    cout << "battlefield test " << (test_battlefield() ? "passed" : "failed") << endl;
    cout << "fire test " << (test_fire() ? "passed" : "failed") << endl;
    cout << "respawn test " << (test_respawn() ? "passed" : "failed") << endl;
    cout << "evolve test " << (test_evolve() ? "passed" : "failed") << endl;
    cout << "look test " << (test_look() ? "passed" : "failed") << endl;
    cout << "move test " << (test_move() ? "passed" : "failed") << endl;
    cout << testLogs.size() << " test log(s):" << endl;
    testLogs;
    for (int i = 0; i < testLogs.size(); i++)
    {
        cout << testLogs[i] << endl;
    }
}
