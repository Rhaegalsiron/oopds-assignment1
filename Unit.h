#pragma once
#include <iostream>
#include <string>
#include "BattleField.h"
#include "AbstractGame.h"
using namespace std;

class Unit
{

private:
    
    Battlefield *field;
    AbstractGame *game;
    vector<string> movementEvolutionOptions = {"JumpBot","StealthBot"};
    vector<string> actionEvolutionOptions = {"ThirtyShotBot","LongShotBot", "SemiAutoBot"};
    vector<string> SeeingEvolutionOptions = {"Tracker","MapVisionBot"};
    


protected:
    string Name;
    string Type;
    char ID;
    int livesRemaining;
    int shellsRemaining;
    int killsToEvolve;
    bool isScouting;
    bool isInvincible;
    vector<string> messageLog;

public:
    int posX;
    int posY;
    Unit(AbstractGame* game, string name, int initialX, int initialY);
    void updatePos(int x, int y);
    void evolve();
    void move(int direction);
    void move(int x, int y);
    void fire(int x, int y);
    void look(int x, int y);
    void destroy();
};
