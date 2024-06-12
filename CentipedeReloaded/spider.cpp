#include "spider.h"

Spider::Spider(int x, int y, int size):
    itsHitBox({x, y, size, size}), itsDirection({0, 0})
{}

QRect Spider::getItsHitBox()
{
    return itsHitBox;
}

void Spider::setItsHitBox(QRect hitbox)
{
    itsHitBox = hitbox;
}

Direction Spider::getItsDirection()
{
    return itsDirection;
}

void Spider::setItsDirection(Direction direction)
{
    itsDirection = direction;
}

int Spider::getItsHorizontaleDirection()
{
    return itsHorizontaleDirection;
}

void Spider::setItsHorizontaleDirection(int horizontalDirection)
{
    itsHorizontaleDirection = horizontalDirection;
}

void Spider::move()
{
    itsHitBox = QRect(itsHitBox.x() + itsDirection.dirX * SPIDER_SPEED, itsHitBox.y() + itsDirection.dirY * SPIDER_SPEED, itsHitBox.width(), itsHitBox.height());
}
