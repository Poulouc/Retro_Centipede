#include "mushroom.h"

Mushroom::Mushroom(int x, int y, int size, Position gridPosition)
    :itsState(4), itsHitBox(x, y, size, size), itsGridPosition(gridPosition)
{ }


Mushroom::~Mushroom()
{ }

void Mushroom::damage()
{
    itsState--;
}

int Mushroom::getItsState()
{
    return itsState;
}

QRect Mushroom::getItsHitBox()
{
    return itsHitBox;
}

Position Mushroom::getItsGridPosition()
{
    return itsGridPosition;
}

void Mushroom::setItsHitBox(QRect hitBox)
{
    itsHitBox = hitBox;
}

void Mushroom::setItsGridPosition(Position position)
{
    itsGridPosition = position;
}
