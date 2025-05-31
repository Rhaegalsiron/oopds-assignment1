/**********|**********|**********|
Program: Directions.h
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
#define DIRECTION_STAY 0
#define DIRECTION_UP 1
#define DIRECTION_DOWN 2
#define DIRECTION_RIGHT 3
#define DIRECTION_LEFT 4
#define DIRECTION_UP_RIGHT 5
#define DIRECTION_DOWN_RIGHT 6
#define DIRECTION_UP_LEFT 7
#define DIRECTION_DOWN_LEFT 8

const vector<int> directionsAsIntVector = {0, 1, 2, 3, 4, 5, 6, 7, 8};
const vector<string> directionsAsNameVector = {"STAY", "UP", "DOWN", "RIGHT", "LEFT", "UP RIGHT", "DOWN RIGHT", "UP LEFT", "DOWN LEFT"};
