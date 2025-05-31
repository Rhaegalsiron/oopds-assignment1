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

#include "BattleField.h"
#include "Unit.h"

Grid::Grid(int x, int y)
{
    this->x = x;
    this->y = y;
    this->occupyingUnit = NULL;
}

Battlefield::Battlefield(int x, int y)
{
    this->generateMap(x, y);
}

void Battlefield::generateMap(int sizeX, int sizeY)
{
    map.resize(sizeY, vector<Grid *>(sizeX, NULL));
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            this->map[y][x] = new Grid(x, y);
        }
    }
};

Grid *Battlefield::getGrid(int x, int y)
{
    return this->map[y][x];
};

int Battlefield::unitCounter()
{
    int unitCount = 0;
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[0].size(); x++)
        {
            Grid *currentGrid = this->getGrid(x, y);
            if (currentGrid->occupyingUnit != NULL)
            {
                unitCount++;
            }
        }
    }
    return unitCount;
}

vector<string> Battlefield::displayMap()
{
    vector<string> message;

    message.push_back("M by N: " + to_string(this->map.size()) + "X" + to_string(this->map[0].size()));
    message.push_back("Robots: " + to_string(unitCounter()));
    for (int y = 0; y < map.size(); y++)
    {
        string currentLine = "";
        for (int x = 0; x < map[0].size(); x++)
        {
            Grid *currentGrid = this->getGrid(x, y);
            if (currentGrid->occupyingUnit != NULL)
            {
                currentLine += currentGrid->occupyingUnit->Name.substr(0, 1) + " ";
            }
            else
                currentLine += "* ";
            currentGrid = NULL;
        }
        message.push_back(currentLine);
    }
    return message;
};

bool Battlefield::isPosValid(int x, int y) // This for restricting the movement when the Robot touches the end of the battlefield range
{
    if (
        (y < this->map.size() && y >= 0) && (x < this->map[0].size() && x >= 0))
    {
        return true;
    }
    return false;
};

Vector2D Battlefield::clampToBattlefield(int x, int y)
{
    // Clamping x and y to the battlefield
    int newX = x, newY = y;
    if (x < 0)
    {
        newX = 0;
    }
    else if (x >= this->map[0].size())
    {
        newX = this->map[0].size() - 1;
    }

    if (y < 0)
    {
        newY = 0;
    }
    else if (y >= this->map.size())
    {
        newY = this->map.size() - 1;
    }

    Vector2D returnValue = {newX, newY};
    return returnValue;
}
