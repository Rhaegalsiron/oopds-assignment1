/**********|**********|**********|
Program: BattleField.h
Course: OOPDS
Trimester: 2410
Name: HERBERT PILO ANAK BITA / LOH YONG SHENG / MING SU ANN / HEW WEE BO
ID: 243UC247H9 / 251UC250GG / 243UC246N0 / 251UC250HB
Lecture Section: TC4L
Tutorial Section: T16L / T15L (Loh)
Email: HERBERT.PILO.ANAK@student.mmu.edu.my / LOH.YONG.SHENG@student.mmu.edu.my / MING.SU.ANN@student.mmu.edu.my / hew.wee.bo@student.mmu.edu.my
Phone: 013-4221107 / 0146666830 / 0146011335 / 0128803121
**********|**********|**********/

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
private:
    void generateMap(int sizeX, int sizeY);

public:
    Battlefield(int x, int y);
    vector<vector<Grid *>> map; // 2d vector array

    vector<string> displayMap();
    Grid *getGrid(int x, int y);
    bool isPosValid(int x, int y);
    int unitCounter();
    Vector2D clampToBattlefield(int x, int y);

};
