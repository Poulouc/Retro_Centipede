#include "mushroom.h"

Mushroom::Mushroom(int x, int y)
    :itsState(4), itsHitBox(0, 0, 0, 0), itsPosition({x, y})
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
