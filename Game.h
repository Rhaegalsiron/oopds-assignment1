#pragma once
#include <iostream>
#include "BattleField.h"
#include "AbstractGame.h"
#include "Unit.h"
#include <vector>
using namespace std;

class Game : public AbstractGame
{
public:
    Game();
    void addToRespawn(Unit *unit);
    void respawnNext();
    void respawnAll();
};
