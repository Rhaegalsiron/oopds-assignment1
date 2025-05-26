#include "BattleField.h"
#include "Unit.h"

Grid::Grid(int x, int y)
{
    this->x = x;
    this->y = y;
    this->occupyingUnit = NULL;
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

void Battlefield::unitCounter()
{
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
    cout << "Robots: " << unitCount << endl;
}

void Battlefield::displayMap()
{
    cout << "M by N: " << this->map.size() << "X" << this->map[0].size() << endl;
    unitCounter();
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[0].size(); x++)
        {
            Grid *currentGrid = this->getGrid(x, y);
            if (currentGrid->occupyingUnit != NULL)
            {
                cout << currentGrid->occupyingUnit->Name[0] << " ";
            }
            else
                cout << "*" << " ";
            currentGrid = NULL;
        }
        cout << endl;
    }
    cout << "\n";
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
