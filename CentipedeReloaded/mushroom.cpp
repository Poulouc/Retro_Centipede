#include "mushroom.h"

Mushroom::Mushroom(int x, int y, int size, Position gridPosition)
    : itsState(4), itsHitBox(x, y, size, size), itsGridPosition(gridPosition)
{ }

Mushroom::~Mushroom()
{ }

// Decreases the state of the mushroom when damaged.
void Mushroom::damage()
{
    itsState--;
}

// Returns the current state of the mushroom.
int Mushroom::getItsState()
{
    return itsState;
}

// Returns the hitbox of the mushroom.
QRect Mushroom::getItsHitBox()
{
    return itsHitBox;
}

// Returns the grid position of the mushroom.
Position Mushroom::getItsGridPosition()
{
    return itsGridPosition;
}

// Sets the hitbox of the mushroom.
void Mushroom::setItsHitBox(QRect hitBox)
{
    itsHitBox = hitBox;
}

// Sets the grid position of the mushroom.
void Mushroom::setItsGridPosition(Position position)
{
    itsGridPosition = position;
}
