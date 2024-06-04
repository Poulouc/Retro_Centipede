#include "mushroom.h"

Mushroom::Mushroom()
    :itsState(4), itsHitBox(0, 0, 0, 0), itsPosition({0, 0})
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
