#include "test2.h"
#include "ThinkingRobot.h"
#include "Unit.h"
#include "BattleField.h"
#include "Game.h"

#include <iostream>
#include <vector>
#include <cassert>

Game *fixture_createGame2()
{
    Game *game = new Game();
    int width = 50, height = 50;
    game->field->generateMap(width, height);
    return game;
};

bool test_thinking()
{
    Game *game = fixture_createGame2();
    Battlefield *battlefield1 = game->field;

    Grid *grid = battlefield1->getGrid(0, 0);
    Unit *tUnit1 = grid->occupyingUnit = new Unit(game, "tUnit1", 0, 0);
    grid = battlefield1->getGrid(0, 1);
    Unit *tUnit2 = grid->occupyingUnit = new Unit(game, "tUnit2", 0, 1);

    tUnit1->thinkRobot();
    
    ThinkingRobot *robot1 = new ThinkingRobot(tUnit1);

    for (int i = 0; i < 10 ; i++)
    {
        robot1->thinkRobot();
    }
    
}