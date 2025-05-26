#include "ThinkingRobot.h"
#include "Evolutions.h"
#include <algorithm>
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
    if (this->unit->isRespawning)
    {
        cout << "Unit is respawning, skipping thinking." << endl;
        return;
    }
    int choice = rand() % actionsOrder.size();
    vector<string> actions = actionsOrder[choice];
    int x = this->unit->currentGrid->x;
    int y = this->unit->currentGrid->y;

    for (const string &action : actions)
    {
        // MOVE
        if (action == "move")
        {
            int Direction = rand() % 9;
            if (this->unit->moveModule != NULL && this->unit->moveModule->robot_type == STEALTH_BOT)
            {
                int moveIndex = rand() % 2 + 1;
                switch (moveIndex)
                {
                case 1:
                    this->unit->moveModule->useAbility();
                    break;
                case 2:
                    this->unit->move(Direction);
                    break;
                }
            }
            else if (this->unit->moveModule != NULL && this->unit->moveModule->robot_type == JUMP_BOT)
            {
                int moveIndex = rand() % 2 + 1;
                switch (moveIndex)
                {
                case 1:
                    {
                    std::pair<int, int> newCoordinates = randomDirection(x, y, true); // Set the extended range to true for JUMP_BOT, so it can jump anywhere in the map if the location is not occupied
                    int newX = newCoordinates.first;                            
                    int newY = newCoordinates.second;    
                    this->unit->moveModule->useAbility(newX, newY);
                    break;
                    }
                case 2:
                    {
                    this->unit->move(Direction);
                    break;
                    }
                }
            }
            else
            {
                this->unit->move(Direction);
                cout << "Moving in direction: " << Direction << " from coordinates: (" << x << ", " << y << ")" << endl;
            };
        }
        // LOOK
        else if (action == "look")
        {
            std::pair<int, int> newCoordinates = randomDirection(x, y, false); //set false for extended range, it can ony look range +- 1
            int newX = newCoordinates.first;
            int newY = newCoordinates.second;
            if (this->unit->seeingModule != NULL && this->unit->seeingModule->robot_type == SCOUT_BOT)
            {
                int seeIndex = rand() % 2 + 1;
                switch (seeIndex)
                {
                case 1:
                    this->unit->seeingModule->useAbility();
                    break;
                case 2:
                    this->unit->look(newX, newY);
                    break;
                }
            }
            else if (this->unit->seeingModule != NULL && this->unit->seeingModule->robot_type == TRACKER_BOT)
            {
                int seeIndex = rand() % 2 + 1;
                switch (seeIndex)
                {
                case 1:
                    this->unit->seeingModule->useAbility(newX, newY);
                    break;
                case 2:
                    this->unit->look(newX, newY);
                    break;
                }
            }
            else
            {
                this->unit->look(newX, newY);
                cout << "Looking at coordinates: (" << newX << ", " << newY << ")" << endl;
            }
        }
        // FIRE
        else if (action == "fire")
        {
            if (detectedRobot){ // Starts with checking if the robot is detected
            fire(targetX, targetY);
            cout << "Firing at detected robot at coordinates: (" << targetX << ", " << targetY << ")" << endl;
            detectedRobot = false; // set it back to false after firing
            targetX = -1;          // set targetX and targetY to -1 after firing
            targetY = -1;
            return;} // end here after fire, no need to do the rest.

            if (this->unit->fireModule != NULL && this->unit->fireModule->robot_type == LONG_SHOT_BOT)
            {
                std::pair<int, int> newCoordinates = randomDirection(x, y, true); //set extened range to true for it can shot range +- 3
                int newX = newCoordinates.first;
                int newY = newCoordinates.second;
            }
            else if (this->unit->fireModule != NULL && this->unit->fireModule->robot_type == SEMI_AUTO_BOT)
            {
                std::pair<int, int> newCoordinates = randomDirection(x, y, false); //set extened range to false for it cant shot range +- 1
                int newX = newCoordinates.first;
                int newY = newCoordinates.second;
                this->unit->fireModule->useAbility(newX, newY);
            }
            else
            {   
                std::pair<int, int> newCoordinates = randomDirection(x, y, false); //set true for fire for it can shot range +- 1
                int newX = newCoordinates.first;
                int newY = newCoordinates.second;
                this->unit->fire(newX, newY);
                cout << "Firing at coordinates: (" << newX << ", " << newY << ")" << endl;
            };
        }
    }
}

std::pair<int, int> ThinkingRobot::randomDirection(int x, int y, bool forExtendedRange)
{
    vector<pair<int, int>> directions = {
        {x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}, {x - 1, y - 1}, {x - 1, y + 1}, {x + 1, y - 1}, {x + 1, y + 1}}; // Range of +- 1 (It will not fire at itself)
    vector<pair<int, int>> validDirections; //for normal look
    vector<pair<int, int>> validTargets; //for normal fire
    
    vector<pair<int, int>> directionsLong; //Range of +- 3 for LONG_SHOT_BOT
    vector<pair<int, int>> validLongDirections; //for LONG_SHOT_BOT look
    vector<pair<int, int>> validLongTargets; //for LONG_SHOT_BOT fire

    vector<pair<int, int>> directionsJumpBot; //Range of whole map for JUMP_BOT
    vector<pair<int, int>> validJumpDirections; //for JUMP_BOT jump

    //Loop for +- 3 for LONG_SHOT_BOT
    for (int dx = -3; dx <= 3; ++dx)
    {
        for (int dy = -3; dy <= 3; ++dy)
        {
            if (dx == 0 && dy == 0) continue; // Skip the current position, it will not fire at itself
            int longX = x + dx;
            int longY = y + dy;
            directionsLong.push_back({longX, longY});
        }
    }

    // Loop for the whole map for JUMP_BOT
    for (int y = 0; y < this->unit->field->map.size(); ++y) //TOFIX: This is not the way to get the map coordinates, just concept for now
    {
        for (int x = 0; x < this->unit->field->map[0].size(); ++x) //TOFIX: This is not the way to get the map coordinates, just concept for now
        {
            //Store every position in the map, so JUMP_BOT can jump anywhere
            directionsJumpBot.push_back({x, y});
        }
    }

    // Check for valid positions in the directionsLong vector for LONG_SHOT_BOT
    for (const auto &dir : directionsLong)
    {
        if (this->unit->field->isPosValid(dir.first, dir.second))
        {
            Grid *targetGrid = this->unit->field->getGrid(dir.first, dir.second);
            if (targetGrid->occupyingUnit != NULL)
            {
                validLongTargets.push_back(dir); // If the target grid has an occupying unit, add to validLongTargets for LONG_SHOT_BOT
            }
            else
            {
                detectedRobot = false;
            }
            validLongDirections.push_back(dir); // If the position is valid, add to validLongDirections for JUMP_BOT
        }
    }
    // Check for valid positions in the directions for SEMI_AUTO_BOT and THIRTY_SHOT_BOT
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

    // Check for valid positions in the directions for JUMP_BOT
    for (const auto &dir: directionsJumpBot)
    {
        Grid *targetGrid = this->unit->field->getGrid(dir.first, dir.second);
        if (this->unit->field->isPosValid(dir.first, dir.second))
        {
            validJumpDirections.push_back(dir);
        }
    }

    std::pair<int, int> chosenDirection;
    if (forExtendedRange && this->unit->fireModule != NULL && this->unit->fireModule->robot_type == LONG_SHOT_BOT) //If this is long shot bot and its for Fire action, choose from validLongDirections to look or fire
    {
        int randomIndex = rand() % validLongDirections.size(); 
        chosenDirection = validLongDirections[randomIndex];
    } 
    else if (forExtendedRange && this->unit->moveModule != NULL && this->unit->moveModule->robot_type == JUMP_BOT)//if this is JUMP_BOT and its for Move action, choose from validJumpDirections to jump
    {
        int randomIndex = rand() % validJumpDirections.size(); 
        chosenDirection = validJumpDirections[randomIndex];
    }
    else 
    {
        int randomIndex = rand() % validDirections.size();  //if not LONG_SHOT_BOT or JUMP_BOT, choose from validDirections to look or fire
        chosenDirection = validDirections[randomIndex];
    }

    //This part is to set the targetX and targetY for the fire action, so it can be used later in the fire action.
    if (this->unit->fireModule != NULL && this->unit->fireModule->robot_type == LONG_SHOT_BOT){
        if (std::find(validLongTargets.begin(), validLongTargets.end(), chosenDirection) != validLongTargets.end()) //if the choosen direction is in validLongTargets
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
    }
    else if (std::find(validTargets.begin(), validTargets.end(), chosenDirection) != validTargets.end())
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