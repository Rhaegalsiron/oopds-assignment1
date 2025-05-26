#pragma once
#include <iostream>
#include "Types.h"
#include "AbstractRobot.h"
#include "Unit.h"
#include "BattleField.h"
#include "AbstractGame.h"
#include "Evolutions.h"
#include "Directions.h"


class TrackerBot : public SeeingBot
{
private:
    int trackerCount = 3; // Number of tracking attempts available
    vector<Unit *> trackedTargets; // List of tracked robots

public:
    TrackerBot(Unit *unit);
    bool lookSpecial(int x, int y); // Tracks a robot at the specified position
    void revealLocation(); // Reveals the locations of tracked robots
};
