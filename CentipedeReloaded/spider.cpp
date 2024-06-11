#include "spider.h"

Spider::spider(int x, int y, int size):
    itsHitBox({x, y, size, size}), itsPosition({x, y})
{}

QRect Spider::getItsHitBox()
{
    return itsHitBox;
}

void Spider::setItsHitBox(QRect hitbox)
{
    itsHitBox = hitbox;
}

Position Spider::getItsPosition()
{
    return itsPosition;
}

void Spider::setItsPosition(Position position)
{
    itsPosition = position;
}

