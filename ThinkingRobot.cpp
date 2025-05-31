/**********|**********|**********|
Program: ThinkingRobot.cpp
Course: OOPDS
Trimester: 2410
Name: HERBERT PILO ANAK BITA / LOH YONG SHENG / MING SU ANN / HEW WEE BO
ID: 243UC247H9 / 251UC250GG / 243UC246N0 / 251UC250HB
Lecture Section: TC4L
Tutorial Section: T16L / T15L (Loh)
Email: HERBERT.PILO.ANAK@student.mmu.edu.my / LOH.YONG.SHENG@student.mmu.edu.my / MING.SU.ANN@student.mmu.edu.my / hew.wee.bo@student.mmu.edu.my
Phone: 013-4221107 / 0146666830 / 0146011335 / 0128803121
**********|**********|**********/

#include "ThinkingRobot.h"
#include "StealthBot.h"
#include "ScoutBot.h"
#include "TrackerBot.h"
#include "BlindBot.h"
#include "LongShotBot.h"
#include "SemiAutoBot.h"
#include "DizzyShooterBot.h"
#include "ShootingRobot.h"
#include "Unit.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>

ThinkingRobot::ThinkingRobot(Unit *unit)
{

    this->setUnit(unit);
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

void ThinkingRobot::think()
{

    int choice = rand() % actionsOrder.size();
    vector<string> actions = actionsOrder[choice];

    for (const string &action : actions)
    {
        if (this->getUnit()->isRespawning)
        {
            // this->getUnit()->log(this->getUnit()->Name + " is respawning, skipping thinking."); // used the log method for any message that needs to be rendered to make sure that it doesnt mess up the battlefield render.
            return;
        }
        int x = this->getUnit()->currentGrid->x; // ISSUE FOUND: THE BOT WAS GETTING THE SAME COORDINATES FOR ALL ACTIONS, SO IT WAS NOT MOVING OR LOOKING PROPERLY
        int y = this->getUnit()->currentGrid->y;
        // MOVE
        if (action == "move")
        {
            int Direction = rand() % 9;
            if (this->getUnit()->moveModule != NULL && this->getUnit()->moveModule->robot_type == STEALTH_BOT)
            {
                StealthBot *module = static_cast<StealthBot *>(this->getUnit()->moveModule);
                int moveIndex = rand() % 2 + 1;
                switch (moveIndex)
                {
                case 1:
                    module->useAbility();
                    break;
                case 2:
                    this->getUnit()->move(Direction);
                    break;
                }
            }
            else if (this->getUnit()->moveModule != NULL && this->getUnit()->moveModule->robot_type == JUMP_BOT)
            {
                int moveIndex = rand() % 2 + 1;
                switch (moveIndex)
                {
                case 1:
                {
                    std::pair<int, int> newCoordinates = randomDirection(x, y, true); // Set the extended range to true for JUMP_BOT, so it can jump anywhere in the map if the location is not occupied
                    int newX = newCoordinates.first;
                    int newY = newCoordinates.second;
                    this->getUnit()->moveModule->useAbility(newX, newY);
                    break;
                }
                case 2:
                {
                    this->getUnit()->move(Direction);
                    break;
                }
                }
            }
            else if (this->getUnit()->moveModule != NULL && this->getUnit()->moveModule->robot_type == HAWKING_BOT) // HawkingBot is a debuff, so it cannot move
            {
                this->getUnit()->moveModule->useAbility();
            }
            else
            {
                this->getUnit()->move(Direction);
                this->getUnit()->log("Moving in direction: " + directionsAsNameVector[Direction] + " from coordinates: (" + to_string(x) + "," + to_string(y) + ")");
            };
        }
        // LOOK
        else if (action == "look")
        {
            std::pair<int, int> newCoordinates = randomDirection(x, y, false); // set false for extended range, it can ony look range +- 1
            int newX = newCoordinates.first;
            int newY = newCoordinates.second;
            if (this->getUnit()->seeingModule != NULL && this->getUnit()->seeingModule->robot_type == SCOUT_BOT)
            {
                ScoutBot *module = static_cast<ScoutBot *>(this->getUnit()->seeingModule);
                int seeIndex = rand() % 2 + 1;
                switch (seeIndex)
                {
                case 1:
                    module->useAbility();
                    break;
                case 2:
                    this->getUnit()->look(newX, newY);
                    break;
                }
            }
            else if (this->getUnit()->seeingModule != NULL && this->getUnit()->seeingModule->robot_type == TRACKER_BOT)
            {
                int seeIndex = rand() % 2 + 1;
                switch (seeIndex)
                {
                case 1:
                {
                    TrackerBot *module = static_cast<TrackerBot *>(this->getUnit()->seeingModule);
                    module->useAbility(newX, newY);
                    break;
                }
                case 2:
                    this->getUnit()->look(newX, newY);
                    break;
                }
            }
            else if (this->getUnit()->seeingModule != NULL && this->getUnit()->seeingModule->robot_type == BLIND_BOT) // debuffs
            {
                BlindBot *module = static_cast<BlindBot *>(this->getUnit()->seeingModule);
                module->useAbility();
            }
            else
            {
                this->getUnit()->look(newX, newY);
            }
        }
        // FIRE
        else if (action == "fire")
        {
            if (detectedRobot)
            { // Starts with checking if the robot is detected
                this->getUnit()->fire(targetX, targetY);
                //this->getUnit()->log("Firing at detected robot at coordinates: (" + to_string(targetX) + "," + to_string(targetY) + ")");
                detectedRobot = false; // set it back to false after firing
                targetX = -1;          // set targetX and targetY to -1 after firing
                targetY = -1;
                if (this->getUnit()->canEvolve)
                    {
                        vector<int> evolutionChoices = this->getUnit()->getEvolutionOptions();
                        if (!evolutionChoices.empty())
                        {
                            int evolveIndex = rand() % evolutionChoices.size();
                            this->getUnit()->evolve(evolutionChoices[evolveIndex]);
                        }
                        else
                        {
                            this->getUnit()->log(this->getUnit()->Name + "already has 3 upgrade. It cannot evolve anymore.");
                        }
                }
                return;
            } // end here after fire, no need to do the rest.

            if (this->getUnit()->fireModule != NULL && this->getUnit()->fireModule->robot_type == LONG_SHOT_BOT)
            {
                std::pair<int, int> newCoordinates = randomDirection(x, y, true); // set extened range to true for it can shot range +- 3
                int newX = newCoordinates.first;
                int newY = newCoordinates.second;
                LongShotBot *module = static_cast<LongShotBot *>(this->getUnit()->fireModule);
                module->useAbility(newX, newY);
            }
            else if (this->getUnit()->fireModule != NULL && this->getUnit()->fireModule->robot_type == SEMI_AUTO_BOT)
            {
                std::pair<int, int> newCoordinates = randomDirection(x, y, false); // set extened range to false for it cant shot range +- 1
                int newX = newCoordinates.first;
                int newY = newCoordinates.second;
                SemiAutoBot *module = static_cast<SemiAutoBot *>(this->getUnit()->fireModule);
                module->useAbility(newX, newY);
            }
            else if (this->getUnit()->fireModule != NULL && this->getUnit()->fireModule->robot_type == DIZZY_SHOOTER_BOT) // Debuff, so it cannot fire
            {
                int dizzyIndex = rand() % 2 + 1; // Randomly choose to use ability or not
                switch (dizzyIndex)
                {
                case 1:
                {
                    DizzyShooterBot *module = static_cast<DizzyShooterBot *>(this->getUnit()->fireModule);
                    module->useAbility();
                    break;
                }
                case 2:
                {
                    std::pair<int, int> newCoordinates = randomDirection(x, y, false); // set true for fire for it can shot range +- 1
                    int newX = newCoordinates.first;
                    int newY = newCoordinates.second;
                    this->getUnit()->fire(newX, newY);
                }
                }
            }
            else
            {
                std::pair<int, int> newCoordinates = randomDirection(x, y, false); // set true for fire for it can shot range +- 1
                int newX = newCoordinates.first;
                int newY = newCoordinates.second;
                this->getUnit()->fire(newX, newY);
            };
        }
    }
    if (this->getUnit()->canEvolve)
    {
        vector<int> evolutionChoices = this->getUnit()->getEvolutionOptions();
        if (!evolutionChoices.empty())
        {
            int evolveIndex = rand() % evolutionChoices.size();
            this->getUnit()->evolve(evolutionChoices[evolveIndex]);
        }
        else
        {
            this->getUnit()->log(this->getUnit()->Name + "already has 3 upgrade. It cannot evolve anymore.");
        }
    }
}

std::pair<int, int> ThinkingRobot::randomDirection(int x, int y, bool forExtendedRange)
{
    vector<pair<int, int>> directions = {
        {x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}, {x - 1, y - 1}, {x - 1, y + 1}, {x + 1, y - 1}, {x + 1, y + 1}}; // Range of +- 1 (It will not fire at itself)
    vector<pair<int, int>> validDirections;                                                                              // for normal look
    vector<pair<int, int>> validTargets;                                                                                 // for normal fire

    vector<pair<int, int>> directionsLong;      // Range of +- 3 for LONG_SHOT_BOT
    vector<pair<int, int>> validLongDirections; // for LONG_SHOT_BOT look
    vector<pair<int, int>> validLongTargets;    // for LONG_SHOT_BOT fire

    vector<pair<int, int>> directionsJumpBot;   // Range of whole map for JUMP_BOT
    vector<pair<int, int>> validJumpDirections; // for JUMP_BOT jump

    // Loop for +- 3 for LONG_SHOT_BOT
    for (int dx = -3; dx <= 3; ++dx)
    {
        for (int dy = -3; dy <= 3; ++dy)
        {
            if (dx == 0 && dy == 0)
                continue; // Skip the current position, it will not fire at itself
            int longX = x + dx;
            int longY = y + dy;
            directionsLong.push_back({longX, longY});
        }
    }

    // Loop for the whole map for JUMP_BOT
    for (int y = 0; y < this->getUnit()->field->map.size(); ++y) // TOFIX: This is not the way to get the map coordinates, just concept for now
    {
        for (int x = 0; x < this->getUnit()->field->map[0].size(); ++x) // TOFIX: This is not the way to get the map coordinates, just concept for now
        {
            // Store every position in the map, so JUMP_BOT can jump anywhere
            directionsJumpBot.push_back({x, y});
        }
    }

    // Check for valid positions in the directionsLong vector for LONG_SHOT_BOT
    for (const auto &dir : directionsLong)
    {
        if (this->getUnit()->field->isPosValid(dir.first, dir.second))
        {
            Grid *targetGrid = this->getUnit()->field->getGrid(dir.first, dir.second);
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
        if (this->getUnit()->field->isPosValid(dir.first, dir.second))
        {
            Grid *targetGrid = this->getUnit()->field->getGrid(dir.first, dir.second);
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
    for (const auto &dir : directionsJumpBot)
    {
        Grid *targetGrid = this->getUnit()->field->getGrid(dir.first, dir.second);
        if (this->getUnit()->field->isPosValid(dir.first, dir.second))
        {
            validJumpDirections.push_back(dir);
        }
    }

    std::pair<int, int> chosenDirection;
    if (forExtendedRange && this->getUnit()->fireModule != NULL && this->getUnit()->fireModule->robot_type == LONG_SHOT_BOT) // If this is long shot bot and its for Fire action, choose from validLongDirections to look or fire
    {
        int randomIndex = rand() % validLongDirections.size();
        chosenDirection = validLongDirections[randomIndex];
    }
    else if (forExtendedRange && this->getUnit()->moveModule != NULL && this->getUnit()->moveModule->robot_type == JUMP_BOT) // if this is JUMP_BOT and its for Move action, choose from validJumpDirections to jump
    {
        int randomIndex = rand() % validJumpDirections.size();
        chosenDirection = validJumpDirections[randomIndex];
    }
    else
    {
        int randomIndex = rand() % validDirections.size(); // if not LONG_SHOT_BOT or JUMP_BOT, choose from validDirections to look or fire
        chosenDirection = validDirections[randomIndex];
    }

    // This part is to set the targetX and targetY for the fire action, so it can be used later in the fire action.
    if (this->getUnit()->fireModule != NULL && this->getUnit()->fireModule->robot_type == LONG_SHOT_BOT)
    {
        if (std::find(validLongTargets.begin(), validLongTargets.end(), chosenDirection) != validLongTargets.end()) // if the choosen direction is in validLongTargets
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