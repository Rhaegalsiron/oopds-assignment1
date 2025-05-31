/**********|**********|**********|
Program: GenericRobot.h
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
#include "Robot.h"
#include "MovingRobot.h"
#include "ShootingRobot.h"
#include "SeeingRobot.h"

class Unit;

class GenericRobot : public MovingRobot, public virtual ShootingRobot, public virtual SeeingRobot
{
public:
    GenericRobot(Unit *unit);
    bool useAbility();
    bool useAbility(int x, int y);
    bool move(int x, int y);
    bool fire(int x, int y);
    bool look(int x, int y);

protected:
    using Robot::clampToLimit;
    using Robot::getUnit;
    using Robot::setUnit;
};