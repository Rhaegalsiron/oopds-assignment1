#pragma once
#include <iostream>
#include "Types.h"
#include "Robot.h"
#include "Unit.h"
#include "BattleField.h"
#include "AbstractGame.h"
#include "SeeingRobot.h"
#include "Directions.h"


class TrackerBot : public SeeingRobot
{
private:
    int trackerCount = 3; // Number of tracking attempts available
    vector<Unit *> trackedTargets; // List of tracked robots

public:
    TrackerBot(Unit *unit);
    int robot_type = TRACKER_BOT;
    bool useAbility() { return false; };
    bool useAbility(int x, int y); // Tracks a robot at the specified position
    void revealLocation(); // Reveals the locations of tracked robots
    bool look(int x, int y);
};
