#pragma once
#define private public
#define protected public

#include <chrono>
#include "Unit.h"
#include "BattleField.h"
#include "Game.h"
using namespace std;
using namespace std::chrono;

Game *fixture_createGame();
bool test_battlefield();
bool test_fire();
bool test_respawn();
void runTests();
