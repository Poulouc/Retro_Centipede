#include "bullet.h"

Bullet::Bullet()
    :itsHitBox(0, 0, 0, 0), itsPosition({0, 0})
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
