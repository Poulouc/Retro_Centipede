#include "mushroom.h"

Mushroom::Mushroom(int x, int y, int size)
    :itsState(4), itsHitBox(x, y, size, size), itsPosition({x, y})
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

Position Mushroom::getItsPosition()
{
    return itsPosition;
}

void Mushroom::setItsHitBox(QRect hitBox)
{
    itsHitBox = hitBox;
}
