#include "Unit.h"
#include "Directions.h"
#include "GenericRobot.h"
#include "ThinkingRobot.h"
#include "JumpBot.h"
#include "ThirtyShotBot.h"
#include "TrackerBot.h"
#include "ScoutBot.h"
#include "BlindBot.h"
#include "HawkingBot.h"
#include "DizzyShooterBot.h"

Unit::Unit(AbstractGame *game, string name)
{
    this->Name = name;
    this->game = game;
    this->field = this->game->field;
    this->defaultModule = new GenericRobot(this);
    this->thinkingModule = new ThinkingRobot(this);
    this->livesRemaining = 3;
    this->currentGrid = NULL;
    this->isRespawning = false;
    this->reset();
}

void Unit::turnReset()
{
    this->hasMoved = false;
    this->hasFired = false;
    this->hasLooked = false;
    this->seenUnit = NULL;
    this->isStealthed = false;
    this->messageLog.clear();
}

void Unit::reset()
{
    this->canEvolve = false;
    this->moveModule = NULL;
    this->fireModule = NULL;
    this->seeingModule = NULL;
    this->magazineSize = 10;
    this->shellsRemaining = this->magazineSize;
    if (this->currentGrid != NULL)
    {
        this->currentGrid->occupyingUnit = NULL;
    }
    this->currentGrid = NULL;
    this->turnReset();
}

bool Unit::move(int direction)
{
    int newPosY = this->currentGrid->y;
    int newPosX = this->currentGrid->x;
    switch (direction)
    {
    case DIRECTION_STAY:
        break;
    case DIRECTION_UP:
        newPosY -= 1;
        break;
    case DIRECTION_UP_RIGHT:
        newPosY -= 1;
        newPosX += 1;
        break;
    case DIRECTION_RIGHT:
        newPosX += 1;
        break;
    case DIRECTION_DOWN_RIGHT:
        newPosX += 1;
        newPosY -= 1;
        break;
    case DIRECTION_DOWN:
        newPosY += 1;
        break;
    case DIRECTION_DOWN_LEFT:
        newPosY += 1;
        newPosX -= 1;
        break;
    case DIRECTION_LEFT:
        newPosX -= 1;
        break;
    case DIRECTION_UP_LEFT:
        newPosX -= 1;
        newPosY -= 1;
        break;
    }

    return this->move(newPosX, newPosY);
};

bool Unit::move(int x, int y)
{
    if (this->hasMoved)
    {
        return true;
    }
    bool successfullyMoved = this->hasMoved = this->defaultModule->move(x, y);
    return successfullyMoved;
};

void Unit::onFiring(Unit *targetUnit, bool isSuccessfulHit, int x, int y)
{
    if (targetUnit == NULL)
    {
        this->log(this->Name + " fired at coordinates (" + to_string(x) + "," + to_string(y) + ") but nothing was there.");
    }

    if (targetUnit != NULL)
    {
        this->canEvolve = true;
        this->log(this->Name + " fired at coordinates (" + to_string(x) + "," + to_string(y) + ") targeting " + targetUnit->Name + ".");
        isSuccessfulHit = targetUnit->onHit();

        if (!isSuccessfulHit){
            this->log(this->Name + " fired at coordinates (" + to_string(x) + "," + to_string(y) + ") and missed.");
        }
    }

    this->shellsRemaining--;
    if (this->shellsRemaining == 0)
    {
        this->onMagazineEmpty();
    }
}

bool Unit::fire(int x, int y)
{
    bool isSuccessfulHit = this->defaultModule->fire(x, y);

    return isSuccessfulHit;
};

Unit *Unit::look(int x, int y)
{
    if (this->hasLooked)
    {
        return this->seenUnit;
    }

    Vector2D clampedCoordinates = this->field->clampToBattlefield(x, y);
    x = clampedCoordinates.x;
    y = clampedCoordinates.y;

    this->defaultModule->look(x, y);
    this->hasLooked = true;

    string message = this->Name + " looked at coordinates (" + to_string(x) + "," + to_string(y) + ")";

    if (this->seenUnit == NULL)
    {
        message += " and saw nothing.";
    }
    else
    {
        message += " and saw " + this->seenUnit->Name;
    }

    this->log(message);

    return this->seenUnit;
};

vector<int> Unit::getEvolutionOptions() // use this for your thinking robot
{
    vector<int> evolutionOptions;
    if (this->moveModule == NULL)
    {
        for (int i = 0; i < this->movementEvolutionOptions.size(); i++)
        {
            evolutionOptions.push_back(this->movementEvolutionOptions[i]);
        }
    }
    if (this->fireModule == NULL)
    {
        for (int i = 0; i < this->actionEvolutionOptions.size(); i++)
        {
            evolutionOptions.push_back(this->actionEvolutionOptions[i]);
        }
    }
    if (this->seeingModule == NULL)
    {
        for (int i = 0; i < this->SeeingEvolutionOptions.size(); i++)
        {
            evolutionOptions.push_back(this->SeeingEvolutionOptions[i]);
        }
    }
    return evolutionOptions;
}

void Unit::evolve(int evolutionOption)
{
    if (!this->canEvolve) // If the Robot cannot evolve. just exit function early
    {
        return;
    }
    string selectedEvolution;
    switch (evolutionOption)
    {
    case JUMP_BOT:
        this->moveModule = new JumpBot(this);
        selectedEvolution = "JumpBot";
        break;
    case STEALTH_BOT:
        selectedEvolution = "StealthBot";
        break;
    case THIRTY_SHOT_BOT:
        // this->fireModule = new ThirtyShotBot(this); //needs a virtual function somewhere in the hierarchy to be able to use this
        selectedEvolution = "ThirtyShotBot";
        break;
    case LONG_SHOT_BOT:
        selectedEvolution = "LongShotBot";
        break;
    case SEMI_AUTO_BOT:
        selectedEvolution = "SemiAutoBot";
        break;
    case TRACKER_BOT:
        this->seeingModule = new TrackerBot(this);
        selectedEvolution = "TrackerBot";
        break;
    case SCOUT_BOT:
        this->seeingModule = new ScoutBot(this);
        selectedEvolution = "ScoutBot";
        break;
    case BLIND_BOT:
        this->seeingModule = new BlindBot(this); // debuff for look
        selectedEvolution = "BlindBot";
        break;
    case HAWKING_BOT:
        this->moveModule = new HawkingBot(this); // debuff for move
        selectedEvolution = "HawkingBot";
        break;
    case DIZZY_SHOOTER_BOT:
        this->fireModule = new DizzyShooterBot(this); // debuff for fire
        selectedEvolution = "DizzyShooterBot";
        break;
    }
    this->log(this->Name + " Is evolving into " + selectedEvolution + ".");
    this->canEvolve = false;
};

void Unit::destroy()
{
    this->livesRemaining--;
    this->reset();
    this->game->addToRespawn(this);
};

bool Unit::updatePos(int x, int y)
{
    Vector2D clampedCoordinates = this->field->clampToBattlefield(x, y);
    x = clampedCoordinates.x;
    y = clampedCoordinates.y;

    if (this->field->getGrid(x, y)->occupyingUnit != NULL)
    {
        return false;
    }

    if (this->currentGrid != NULL)
    {
        this->currentGrid->occupyingUnit = NULL;
    }

    Grid *grid = this->game->field->getGrid(x, y);
    this->currentGrid = grid;
    this->currentGrid->occupyingUnit = this;
    return true;
};

void Unit::log(string message)
{
    this->messageLog.push_back(message);
    this->game->log(message);
}

bool Unit::onHit()
{
    if (this->isStealthed)
    {
        this->log(this->Name + " is stealthed and dodged the shot.");
        return false;
    }
    this->log(this->Name + " is hit and destroyed.");

    this->destroy();
    return true;
}

void Unit::onMagazineEmpty()
{

    this->log(this->Name + " has emptied its magazine and self-destructed.");
    this->destroy();
}
