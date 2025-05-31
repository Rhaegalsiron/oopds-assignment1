/**********|**********|**********|
Program: ThirtyShotBot.h
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
#include "Types.h"
#include "ShootingRobot.h"
#include "BattleField.h"
#include "AbstractGame.h"

#include "Directions.h"

class Unit;

class ThirtyShotBot : public ShootingRobot
{
private:
    int magazineSize; // Magazine size for the bot

public:
    ThirtyShotBot(Unit *unit);
    bool useAbility();
    bool useAbility(int x, int y); // Override the pure virtual function.
    bool fire(int x, int y);
};
