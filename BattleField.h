#pragma once
#include <iostream>
#include <vector>
#include "Types.h"

using namespace std;

class Unit;

class Grid
{
public:
    Grid(int x, int y);
    int x;
    int y;
    Unit *occupyingUnit;
};

class Battlefield
{
public:
    vector<vector<Grid *>> map; // 2d vector array
    void generateMap(int sizeX, int sizeY);
    void displayMap();
    Grid *getGrid(int x, int y);
    bool isPosValid(int x, int y);
    void unitCounter();
    Vector2D clampToBattlefield(int x, int y);
};
