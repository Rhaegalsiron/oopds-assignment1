#include "Robot.h"

vector<string> robotNames = {"Generic Robot", "Jump Bot", "Stealth Bot", "Thirty Shot Bot", "Long Shot Bot", "Semi Auto Bot", "Tracker Bot", "Scout Bot", "Blind Bot", "Hawking Bot", "Dizzy Shooter Bot"};

string getRobotName(int robot_type) {
    return robotNames[robot_type];
}

int Robot::clampToLimit(int currentPos, int targetPos, int limit)
{
    int deltaPos = abs(currentPos - targetPos);
    if (deltaPos <= limit)
    {
        return targetPos;
    }
    if (targetPos < currentPos)
    {
        return currentPos - limit;
    }
    return currentPos + limit;
}

Unit *Robot::getUnit()
{
    return this->unit;
}

void Robot::setUnit(Unit *unit)
{
    this->unit = unit;
}