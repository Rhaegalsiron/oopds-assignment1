#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Unit;

class Grid
{
public:
    Unit *occupyingUnit;
};

class Battlefield
{
public:
    vector<vector<Grid*>> map; // 2d vector array
    void generateMap(int sizeX, int sizeY);
    void displayMap();
    Grid* getGrid(int x, int y);
    bool isPosValid(int x, int y);
};
