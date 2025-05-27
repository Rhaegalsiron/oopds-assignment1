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
