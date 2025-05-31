/**********|**********|**********|
Program: Configuration.h
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
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#define RANDOM_POSITION -99

using namespace std;

struct RobotParameters
{
    string name;
    int initialX;
    int initialY;
};

class Configuration
{
public:
    Configuration(string configurationFile);
    string nameOfFile;
    string name;
    int dimensionX;
    int dimensionY;
    int battlefieldSize;
    int simulationSteps;
    int robotCount;
    string parseFile(const string nameOfFile);
    string trimString(string input);
    vector<string> targetWords;
    vector<RobotParameters> robotLists;
    void parsedWords();
    void parseLine(string line);
};
