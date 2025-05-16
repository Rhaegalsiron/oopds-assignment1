#define INVALID_POSITION -999999999
#include <iostream>
#include "Types.h"
using namespace std;

class GenericBot{
    public:
    Vector2D move(int x, int y);
    void fire(int x, int y);
    void look(int x, int y);

};

class MoveBot{
    public:
        virtual Vector2D moveSpecial(int x, int y) = 0;
};

class ActionBot{
    public:
        virtual void fireSpecial(int x, int y) = 0;
};

class SeeingBot{
    public:
        virtual void lookSpecial(int x, int y) = 0;
};

class JumpBot: public MoveBot{
    public:
        int chargesRemaining = 3;
        Vector2D moveSpecial(int x,int y);
};