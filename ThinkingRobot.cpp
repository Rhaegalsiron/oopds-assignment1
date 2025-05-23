#include "ThinkingRobot.h"
#include "Evolutions.h"
#include <cstdlib>
#include <ctime>
#include <vector>

ThinkingRobot::ThinkingRobot(Unit *unit)
{
    this->unit = unit;
    targetX = -1;
    targetY = -1;
    this->detectedRobot = false;
    this->actionsOrder = {
        {"move", "fire", "look"},
        {"fire", "move", "look"},
        {"look", "fire", "move"},
        {"move", "look", "fire"},
        {"fire", "look", "move"},
        {"look", "move", "fire"}};
}

void ThinkingRobot::thinkRobot()
{
    int choice = rand() % actionsOrder.size();
    vector<string> actions = actionsOrder[choice];
    int x = this->unit->currentGrid->x;
    int y = this->unit->currentGrid->y;

    for (const string &action : actions)
    {
        // MOVE
        if (action == "move")
        {
            // hasMoved = false; //this part i tak faham // i will do this in version 2
            // if (this->unit->hasMoved = true)
            // TODO : Implement move.
            srand(static_cast<unsigned>(time(0)));
            int randomDirection = rand() % 9;
            if (this->unit->moveModule != NULL && this->unit->moveModule->robot_type == STEALTH_BOT) // edit this to access type via robot_type. also use ctrl+shift+i to keep the standard format
            {
                int moveIndex = rand() % 2 + 1;
                switch (moveIndex)
                {
                case 1:
                    this->unit->moveModule->useAbility();
                    break;
                case 2:
                    this->unit->defaultModule->move(randomDirection);
                    break;
                }
            }
            // you need to else if for jumpbot as well too
            else
            {
                this->unit->defaultModule->move(randomDirection); // added a polymorhphic def in abstractRobot
            };
        }
        // LOOK
        else if (action == "look")
        {
            std::pair<int, int> newCoordinates = randomDirection(x, y);
            int newX = newCoordinates.first;
            int newY = newCoordinates.second;
            srand(static_cast<unsigned>(time(0)));
            if (this->unit->seeingModule != NULL && this->unit->seeingModule == "MAP_VISION_BOT") // do the same as I did for you on line 40
            {
                int seeIndex = rand() % 2 + 1;
                switch (seeIndex)
                {
                case 1:
                    this->unit->seeingModule->useAbility();
                    break;
                case 2:
                    this->unit->defaultModule->look(newX, newY);
                    break;
                }
            }
            else if (this->unit->seeingModule != NULL && this->unit->seeingModule == "TRACKER_BOT")
            { // do the same as I did for you on line 40
                int seeIndex = rand() % 2 + 1;
                switch (seeIndex)
                {
                case 1:
                    this->unit->seeingModule->useAbility(newX, newY);
                    break;
                case 2:
                    this->unit->defaultModule->look(newX, newY);
                    break;
                }
            }
            else
            {
                this->unit->defaultModule->look(newX, newY);
            }
        }
        // FIRE
        else if (action == "fire")
        {
            if (detectedRobot) // Starts with checking if the robot is detected
                fire(targetX, targetY);
            detectedRobot = false; // set it back to false after firing
            targetX = -1;          // set targetX and targetY to -1 after firing
            targetY = -1;
            return; // end here after fire, no need to do the rest. LONG_SHOT_BOT part will be done in Version 2

            std::pair<int, int> newCoordinates = randomDirection(x, y);
            int newX = newCoordinates.first;
            int newY = newCoordinates.second;

            srand(static_cast<unsigned>(time(0)));
            if (this->unit->fireModule != NULL && this->unit->fireModule != "LONG_SHOT_BOT" && this->unit->fireModule != "SEMI_AUTO_BOT") // do the same as I did for you on line 40
            {
                int fireIndex = rand() % 2 + 1;
                switch (fireIndex)
                {
                case 1:
                    this->unit->fireModule->useAbility();
                    break;
                case 2:
                    this->unit->defaultModule->fire(newX, newY);
                    break;
                }
            }
            else
            {
                this->unit->defaultModule->fire(newX, newY);
            };
        }
    }
}

std::pair<int, int> ThinkingRobot::randomDirection(int x, int y) // TODO : Implement +3 for LONG_SHOT_BOT in version 2.
{
    vector<pair<int, int>> directions = {
        {x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}, {x - 1, y - 1}, {x - 1, y + 1}, {x + 1, y - 1}, {x + 1, y + 1}};

    vector<pair<int, int>> validDirections;
    vector<pair<int, int>> validTargets;

    for (const auto &dir : directions)
    {
        if (this->unit->field->isPosValid(dir.first, dir.second))
        {
            Grid *targetGrid = this->unit->field->getGrid(dir.first, dir.second);
            if (targetGrid->occupyingUnit != NULL)
            {
                validTargets.push_back(dir);
            }
            else
            {
                detectedRobot = false;
            }
            validDirections.push_back(dir);
        }
    }

    int randomIndex = rand() % validDirections.size();
    std::pair<int, int> chosenDirection = validDirections[randomIndex];
    if (std::find(validTargets.begin(), validTargets.end(), chosenDirection) != validTargets.end()) // You need to import #include <algorithm> to your header file to use find method
    {
        targetX = chosenDirection.first;
        targetY = chosenDirection.second;
        detectedRobot = true;
    }
    else
    {
        detectedRobot = false;
        targetX = -1;
        targetY = -1;
    }

    return chosenDirection;
}