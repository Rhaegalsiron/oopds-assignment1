#include "tests.h"

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

    tUnit1->fire(0, 1);
    if (battlefield1->getGrid(0, 1)->occupyingUnit != NULL)
    {
        cout << "Unit still occupying 0,1 and not destroyed" << endl;
        return false;
    }

    if (tUnit2->posX != -1 && tUnit2->posY != -1)
    {
        return false;
    }

    return true;
};