/**********|**********|**********|
Program: YOUR_FILENAME.cpp / YOUR_FILENAME.h
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
#include <vector>
#include "BattleField.h"

class AbstractGame
{
protected:
    int simulationSteps;

public:
    vector<string> messageLog;
    vector<Unit *> respawnQueue;
    vector<Unit *> permanentlyEliminated;
    vector<Unit *> units;
    Battlefield *field;
    virtual void addToGame(Unit *unit) = 0;
    virtual void addToRespawn(Unit *unit) = 0;
    virtual void respawnNext() = 0;
    virtual void respawnAll() = 0;
    virtual void renderBattleField() = 0;
    virtual void executeTurn() = 0;
    virtual void endTurn() = 0;
    virtual void log(string message) = 0;
    virtual void runSimulation() = 0;
    virtual bool isWinConditionAchieved() = 0;
    virtual vector<Unit*> getActiveUnits() = 0;
};