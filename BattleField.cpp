#include "BattleField.h"

void Battlefield::generateMap(int sizeX, int sizeY)
{
    map.resize(sizeY, vector<Grid *>(sizeX, NULL));
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            this->map[y][x] = new Grid;
        }
    }
};

Grid *Battlefield::getGrid(int x, int y)
{
    return this->map[y][x];
};

void Battlefield::displayMap()
{
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[0].size(); x++)
        {
            Grid *currentGrid = this->getGrid(x, y);
            if (currentGrid->occupyingUnit != NULL)
            {
                cout << 'R' << " ";
            }
            else
                cout << "*" << " ";
            currentGrid = NULL;
        }
        cout << endl;
    }
    cout << "\n";
};

bool Battlefield::isPosValid(int x, int y)
{
    if (
        (y < this->map.size() && y >= 0) || (x < this->map[0].size() && x >= 0))
    {
        return true;
    }
    return false;
};
