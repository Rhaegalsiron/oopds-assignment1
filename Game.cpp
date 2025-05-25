#include "Game.h"

Game::Game()
{
    this->field = new Battlefield();
    srand(static_cast<unsigned>(time(0)));
};

void Game::addToRespawn(Unit *unit)
{
    if (unit->livesRemaining == 0) {
        return;
    }
    this->respawnQueue.insert(this->respawnQueue.begin(), unit);
};

void Game::respawnNext()
{
    Unit *unit = this->respawnQueue.back();
    while (true)
    {
        int randX = rand() % this->field->map[0].size();
        int randY = rand() % this->field->map.size();
        Grid *grid = this->field->getGrid(randX, randY);

        if (grid->occupyingUnit == NULL)
        {
            grid->occupyingUnit = unit;
            unit->updatePos(randX, randY);
            this->respawnQueue.pop_back();
            break;
        }
    }
};
