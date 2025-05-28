#include "Game.h"
#include "ThinkingRobot.h"

Game::Game(Configuration *config)
{

    this->field = new Battlefield(config->dimensionX, config->dimensionY);
    this->simulationSteps = config->simulationSteps;
    this->respawnQueue = {};
    this->units = {};
    this->messageLog = {};
    srand(static_cast<unsigned>(time(0)));

    for (
        int i = 0;
        i < (config->robotCount < config->robotLists.size()
                 ? config->robotCount
                 : config->robotLists.size());
        i++)
    {
        Unit *unit = new Unit(this, config->robotLists[i].name);
        this->addToGame(unit);
        if (config->robotLists[i].initialX == RANDOM_POSITION || config->robotLists[i].initialY == RANDOM_POSITION)
        {
            this->addToRespawn(unit);
            this->respawnNext();
        }
        if (config->robotLists[i].initialX != RANDOM_POSITION && config->robotLists[i].initialY == RANDOM_POSITION)
        {
            while (true)
            {
                Grid *grid = this->field->getGrid(config->robotLists[i].initialX, rand() % this->field->map.size());
                if (grid->occupyingUnit == NULL)
                {
                    unit->updatePos(grid->x, grid->y);
                    break;
                }
            }
        }
        if (config->robotLists[i].initialX == RANDOM_POSITION && config->robotLists[i].initialY != RANDOM_POSITION)
        {
            while (true)
            {
                Grid *grid = this->field->getGrid(rand() % this->field->map[0].size(), config->robotLists[i].initialY);
                if (grid->occupyingUnit == NULL)
                {
                    unit->updatePos(grid->x, grid->y);
                    break;
                }
            }
        }
        if (config->robotLists[i].initialX != RANDOM_POSITION && config->robotLists[i].initialY != RANDOM_POSITION)
        {
            unit->updatePos(config->robotLists[i].initialX, config->robotLists[i].initialY);
        }
    }
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
        this->permanentlyEliminated.push_back(unit);
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
            unit->log(unit->Name + " respawn at coordinates (" + to_string(randX) + "," + to_string(randY) + ") with " + to_string(unit->livesRemaining) + " lives remaining.");
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

void Game::runSimulation()
{
    this->log("Simulation start...");
    this->renderBattleField();
    this->messageLog.clear();

    for (int i = 0; i < this->simulationSteps; i++)
    {
        cout << endl
             << endl;
        cout << "Step: " << to_string(i + 1) << endl;
        this->respawnNext();
        this->executeTurn();
        this->renderBattleField();
        this->endTurn();
        if (this->isWinConditionAchieved())
        {
            vector<Unit *> winners = this->getActiveUnits();
            cout << endl
                 << endl;
            if (winners.size() < 1)
            {
                cout << "The simulation ended with no winners..." << endl;
            }
            else
            {
                cout << "Last man standing is:" << endl;
                cout << winners[0]->Name << endl;
            }
            break;
        }
    }

    if (!isWinConditionAchieved())
    {
        vector<Unit *> remainingActiveUnits = this->getActiveUnits();
        cout << endl
             << endl;
        cout << "Simulation step limit reached." << endl;
        cout << "Remaining active units:" << endl;
        for (int i = 0; i < remainingActiveUnits.size(); i++)
        {
            cout << remainingActiveUnits[i]->Name << endl;
        }
    }
}

bool Game::isWinConditionAchieved()
{
    return this->units.size() - this->permanentlyEliminated.size() <= 1;
}

vector<Unit *> Game::getActiveUnits()
{
    vector<Unit *> activeUnits;
    for (int j = 0; j < this->units.size(); j++)
    {
        bool isEliminated = false;
        for (int k = 0; k < this->permanentlyEliminated.size(); k++)
        {
            isEliminated = isEliminated || this->units[j] == this->permanentlyEliminated[k];
        }
        if (!isEliminated)
        {
            activeUnits.push_back(this->units[j]);
        }
    }
    return activeUnits;
}