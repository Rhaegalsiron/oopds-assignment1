#include "Unit.h"
#include "Directions.h"
#include "Evolutions.h"

Unit::Unit(AbstractGame *game, string name, int initialX, int initialY)
{
    this->Name = name;
    this->updatePos(initialX, initialY);
    this->game = game;
    this->field = this->game->field;
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
    this->field->isPosValid(newPosX, newPosY);
};

void Unit::move(int x, int y)
{
    int newPosY = this->posY;
    int newPosX = this->posX; 
    if (newPosX > 0){
        newPosX = 1;
    }
    else if (newPosX < 0){
        newPosX = -1;
    }
    if (newPosY > 0){
        newPosY = 1;
    }
    else if (newPosY < 0){
        newPosY = -1;
    }
    

};

void Unit::fire(int x, int y)
{
    Grid *targetGrid = this->field->getGrid(x, y);
    if (targetGrid->occupyingUnit != NULL)
    {
        bool successfulHit = rand() % 100 <= 30;
        if (successfulHit)
        {
            targetGrid->occupyingUnit->destroy();
            this->evolve();
        }
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
    Grid *grid = this->field->getGrid(this->posX, this->posY);
    grid->occupyingUnit = NULL;
    this->posX = -1;
    this->posY = -1;
    this->game->addToRespawn(this);
};

void Unit::updatePos(int x, int y)
{
    this->posX = x;
    this->posY = y;
};