#include "Unit.h"
#include "GenericRobot.h"
#include "ThinkingRobot.h"
#include "JumpBot.h"

Unit::Unit(AbstractGame *game, string name, int initialX, int initialY)
{
    this->Name = name;
    this->game = game;
    this->field = this->game->field;
    this->defaultModule = new GenericRobot(this);
    this->thinkingModule = new ThinkingRobot(this);
    this->magazineSize = 20;
    this->canEvolve = false;
    this->moveModule = NULL;
    this->fireModule = NULL;
    this->seeingModule = NULL;
    this->updatePos(initialX, initialY);
    this->reset();
}

void Unit::turnReset()
{
    this->hasMoved = false;
    this->hasFired = false;
    this->hasLooked = false;
    this->seenUnit = NULL;
}

void Unit::reset()
{
    this->turnReset();
    this->shellsRemaining = this->magazineSize;
}

bool Unit::move(int direction)
{
    int newPosY = this->currentGrid->y;
    int newPosX = this->currentGrid->x;
    switch (direction)
    {
    case Directions::STAY:
        break;
    case Directions::UP:
        newPosY -= 1;
        break;
    case Directions::UP_RIGHT:
        newPosY -= 1;
        newPosX += 1;
        break;
    case Directions::RIGHT:
        newPosX += 1;
        break;
    case Directions::DOWN_RIGHT:
        newPosX += 1;
        newPosY -= 1;
        break;
    case Directions::DOWN:
        newPosY += 1;
        break;
    case Directions::DOWN_LEFT:
        newPosY += 1;
        newPosX -= 1;
        break;
    case Directions::LEFT:
        newPosX -= 1;
        break;
    case Directions::UP_LEFT:
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
    this->messageLog.push_back(this->Name + " moved to coordinates ( " + to_string(x) + "," + to_string(y) + ").");
    return successfullyMoved;
};

void Unit::afterFiring(Unit *targetUnit, bool isSuccessfulHit, int x, int y)
{
    if (targetUnit == NULL)
    {
        this->messageLog.push_back(this->Name + " fired at coordinates ( " + to_string(x) + "," + to_string(y) + ") but nothing was there.");
    }

    if (targetUnit != NULL && isSuccessfulHit)
    {
        this->canEvolve = true;
        this->messageLog.push_back(this->Name + " fired at coordinates ( " + to_string(x) + "," + to_string(y) + ") and hit " + targetUnit->Name + ".");
    }

    if (targetUnit != NULL && !isSuccessfulHit)
    {
        this->messageLog.push_back(this->Name + " fired at coordinates ( " + to_string(x) + "," + to_string(y) + ") and missed.");
    }

    this->shellsRemaining--;
    if (this->shellsRemaining == 0)
    {
        this->messageLog.push_back(this->Name + " has emptied its magazine.");
        this->destroy();
    }
}

bool Unit::fire(int x, int y)
{
    Vector2D clampedCoordinates = this->field->clampToBattlefield(x, y);
    x = clampedCoordinates.x;
    y = clampedCoordinates.y;
    Grid *targetGrid = this->field->getGrid(x, y);
    bool isSuccessfulHit;
    Unit *targetUnit = targetGrid->occupyingUnit;
    if (this->hasFired)
    {
        return true;
    }

    isSuccessfulHit = this->defaultModule->fire(x, y);

    this->afterFiring(targetUnit, isSuccessfulHit, x, y);
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

    string message = this->Name + " looked at coordinates ( " + to_string(x) + "," + to_string(y) + ")";

    if (this->seenUnit == NULL)
    {
        message += " and saw nothing.";
    }
    else
    {
        message += " and saw " + this->seenUnit->Name;
    }

    this->messageLog.push_back(message);

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
    case STEALTH_BOT: // TODO: Implement the remaining evolution path
        break;
    case THIRTY_SHOT_BOT:
        break;
    case LONG_SHOT_BOT:
        break;
    case SEMI_AUTO_BOT:
        break;
    case TRACKER_BOT:
        break;
    case SCOUT_BOT:
        break;
    }
    this->messageLog.push_back("Evolving into " + selectedEvolution + ".");
    this->canEvolve = false;
};

void Unit::destroy()
{
    this->currentGrid->occupyingUnit = NULL;
    this->currentGrid = NULL;
    this->messageLog.push_back(this->Name + " is destroyed.");
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

    if (this->currentGrid)
    {
        this->currentGrid->occupyingUnit = NULL;
    }

    Grid *grid = this->game->field->getGrid(x, y);
    this->currentGrid = grid;
    this->currentGrid->occupyingUnit = this;
    return true;
};