
#include "Evolutions.h"
#include "Types.h"
#include <iostream>
using namespace std;

Vector2D JumpBot::moveSpecial(int x, int y)
{
    if (chargesRemaining > 0)
    {
        chargesRemaining--;
        return Vector2D(x, y);
    }
    return Vector2D(INVALID_POSITION, INVALID_POSITION);
}