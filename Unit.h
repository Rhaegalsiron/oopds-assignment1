#include <iostream>
#include <string>
#include "BattleField.h"
using namespace std;

class Unit
{

private:
    int posX;
    int posY;
    Battlefield field;

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
    Unit(Battlefield field);
    void evolve();
    void move(int direction);
    void fire(int x, int y);
    void look(int x, int y);
    void destroy();
};