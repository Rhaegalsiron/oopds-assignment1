#include "Unit.h"
#include "Directions.h"
#include "Evolutions.h"

Unit::Unit(AbstractGame *game, string name, int initialX, int initialY)
{
    this->Name = name;
    this->game = game;
    this->field = this->game->field;
    this->defaultModule = new GenericRobot(this);
    this->updatePos(initialX, initialY);
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

    this->move(newPosX, newPosY);
};

void Unit::move(int x, int y)
{
    if (!(this->moveModule) && !(this->moveModule->move(x, y)))
    {
        this->defaultModule->move(x, y);
    };
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
    // Clamping x and y to the battlefield
    if (x > this->field->map[0].size())
    {
        x = this->field->map[0].size();
    }
    if (x < 0)
    {
        x = 0;
    }
    if (y > this->field->map.size())
    {
        y = this->field->map.size();
    }
    if (y < 0)
    {
        y = 0;
    }
    this->posX = x;
    this->posY = y;

    Grid *grid = this->game->field->getGrid(this->posX, this->posY);
    grid->occupyingUnit = NULL;
    grid = this->field->getGrid(x, y);
    grid->occupyingUnit = this;
};