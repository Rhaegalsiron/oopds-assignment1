#include "Game.h"
#include "ThinkingRobot.h"

Game::Game()
{
    this->field = new Battlefield();
    this->respawnQueue = {};
    this->units = {};
    this->messageLog = {};
    srand(static_cast<unsigned>(time(0)));
};

void Game::addToGame(Unit *unit)
{
    this->units.push_back(unit);
}

void Game::addToRespawn(Unit *unit)
{
    unit->isRespawning = true;
    if (unit->livesRemaining == 0)
    {
        return;
    }
    this->respawnQueue.insert(this->respawnQueue.begin(), unit);
};

void Game::respawnNext()
{
    if (this->respawnQueue.size() < 1)
    {
        return;
    }
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
            unit->log(unit->Name + " respawn at coordinates (" + to_string(randX) + "," + to_string(randY) + ")");
            break;
        }
    }
};

void Game::respawnAll()
{
    int totalInQueue = this->respawnQueue.size();
    for (int i = 0; i < totalInQueue; i++)
    {
        this->respawnNext();
    }
}

void Game::renderBattleField()
{
    this->field->displayMap();
    for (int i = 0; i < this->messageLog.size(); i++)
    {
        cout << this->messageLog[i] << endl;
    }
}

void Game::executeTurn()
{
    for (int i = 0; i < this->units.size(); i++)
    {
        Unit *unit = this->units[i];
        unit->thinkingModule->thinkRobot();
    }
}

void Game::endTurn()
{
    for (int i = 0; i < this->units.size(); i++)
    {
        Unit *unit = this->units[i];
        unit->turnReset();
    }

    this->messageLog.clear();
}

void Game::log(string message)
{
    this->messageLog.push_back(message);
}
