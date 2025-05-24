#pragma once
#define private public
#define protected public

#include <chrono>    // I use this for time
#include <algorithm> // included to check whether a value exists in a vector
#include "Unit.h"
#include "BattleField.h"
#include "Game.h"
using namespace std;
using namespace std::chrono;

Game *fixture_createGame();
bool test_thinking();