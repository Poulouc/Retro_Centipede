#include "mushroom.h"

Mushroom::Mushroom(int x, int y)
    :itsState(4), itsHitBox(x, y, MUSHROOM_SIZE, MUSHROOM_SIZE), itsPosition({x, y})
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
