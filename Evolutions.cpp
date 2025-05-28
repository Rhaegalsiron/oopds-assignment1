#include "Evolutions.h"

int Robot::clampToLimit(int currentPos,int targetPos, int limit)
{
    int deltaPos = abs(currentPos-targetPos);
    if(deltaPos <= limit)
    {
        return targetPos;
    }
    if(targetPos < currentPos)
    {
        return currentPos-limit;
    }
    return currentPos + limit;
}