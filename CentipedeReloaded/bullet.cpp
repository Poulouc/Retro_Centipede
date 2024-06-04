#include "bullet.h"

Bullet::Bullet(int x, int y)
    :itsHitBox(0, 0, 0, 0), itsPosition({x, y})
{ }

Bullet::~Bullet()
{ }

void Bullet::updatePos()
{
    itsPosition.posY = itsPosition.posY - BULLET_SPEED;
}

QRect Bullet::getItsHitBox()
{
    return itsHitBox;
}

Position Bullet::getItsPosition()
{
    return itsPosition;
}
