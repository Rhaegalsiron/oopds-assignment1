#include "Unit.h"
#include "BattleField.h"
#include "Directions.h"

Unit::Unit(Battlefield field)
{
    this->field = field;
}

void Unit::move(int direction)
{
    int newPosY = this->posY;
    int newPosX = this->posX;
    switch (direction)
    {
    case Directions::STAY:
        break;
    case Directions::UP:
        newPosY -= 1;
        break;
    case Directions::UP_RIGHT:
        newPosY -= 1;
        newPosX += 1;
        break;
    case Directions::RIGHT:
        newPosX += 1;
        break;
    case Directions::DOWN_RIGHT:
        newPosX += 1;
        newPosY -= 1;
        break;
    case Directions::DOWN:
        newPosY += 1;
        break;
    case Directions::DOWN_LEFT:
        newPosY += 1;
        newPosX -= 1;
        break;
    case Directions::LEFT:
        newPosX -= 1;
        break;
    case Directions::UP_LEFT:
        newPosX -= 1;
        newPosY -= 1;
    }

    // TODO: COMPLETE HANDLING OF MOVEMENT
    this->field.isPosValid(newPosX, newPosY);
};
void Unit::fire(int x, int y)
{
    Grid *targetGrid = this->field.getGrid(x, y);
    if (targetGrid->occupyingUnit != NULL)
    {
        targetGrid->occupyingUnit->destroy();
        this->evolve();
        return;
    }
    cout << "No hit" << endl;
};
void Unit::look(int x, int y) {

};

void Unit::evolve()
{
    cout << "Evolving" << endl;
};
void Unit::destroy()
{
    cout << "destoyed" << endl;
};