#include "Game.h"

Game::Game()
{
    this->field = new Battlefield();
    srand(static_cast<unsigned>(time(0)));
};

void Game::addToRespawn(Unit *unit)
{
    unit->isRespawning = true;
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
            unit->updatePos(randX, randY);
            unit->isRespawning = false;
            this->respawnQueue.pop_back();
            break;
        }
    }
};

void Game::respawnAll() {
    int totalInQueue = this->respawnQueue.size();
    for (int i=0; i < totalInQueue; i++) {
        this->respawnNext();
    }
}
