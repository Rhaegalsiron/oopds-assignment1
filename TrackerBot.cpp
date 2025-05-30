#include "TrackerBot.h"
#include <iostream>
using namespace std;

TrackerBot::TrackerBot(Unit *unit)
{
    this->robot_type = TRACKER_BOT;
    this->setUnit(unit);
    this->trackerCount = 3; // Initialize tracker count
}

bool TrackerBot::useAbility(int x, int y)
{
    if (this->getUnit()->isRespawning)
    {
        return false;
    }
    revealLocation(); // Reveal locations of previously tracked robots
    if (trackerCount <= 0)
    {
        this->getUnit()->log("No trackers left to use.");
        return false;
    }

    // Get the grid at the specified coordinates
    Grid *targetGrid = this->getUnit()->field->getGrid(x, y);
    if (targetGrid == NULL || targetGrid->occupyingUnit == NULL)
    {
        this->getUnit()->log("No enemy to track at (" + to_string(x) + ", " + to_string(y) + ").");
        // cout << "No enemy to track at (" << x << ", " << y << ")." << endl;
        return false;
    }

    // Add the robot on the current grid to the tracked targets
    Unit *targetUnit = targetGrid->occupyingUnit;
    trackedTargets.push_back(targetUnit);
    trackerCount--; // Decrement tracker count
    this->getUnit()->log("Tracking robot: " + targetUnit->Name + " at (" + to_string(x) + ", " + to_string(y) + ").");
    // cout << "Tracking robot: " << targetUnit->Name << " at (" << x << ", " << y << ")." << endl;

    return true;
}

void TrackerBot::revealLocation()
{
    if (trackedTargets.empty())
    {
        this->getUnit()->log("No tracked robots to reveal.");
        // cout << "No tracked robots to reveal." << endl;
        return;
    }

    for (Unit *trackedUnit : trackedTargets)
    {
        if (trackedUnit->currentGrid != NULL)
        {
            int posX = trackedUnit->currentGrid->x;
            int posY = trackedUnit->currentGrid->y;
            this->getUnit()->log("Robot " + trackedUnit->Name + " revealed at position (" + to_string(posX) + ", " + to_string(posY) + ").");
            // cout << "Robot " << trackedUnit->Name << " revealed at position (" << posX << ", " << posY << ")." << endl;
        }
        else
        {
            this->getUnit()->log("Robot " + trackedUnit->Name + " is no longer on the battlefield.");
            // cout << "Robot " << trackedUnit->Name << " is no longer on the battlefield." << endl;
        }
    }
}

bool TrackerBot::look(int x, int y)
{
    return false;
}