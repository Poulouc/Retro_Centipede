#include "bullet.h"

Bullet::Bullet()
    :itsHitBox(0, 0, 0, 0), itsPosition({0, 0})
{ }

Bullet::~Bullet()
{ }

void Bullet::updatePos()
{
    itsPosition.posY = itsPosition.posY - 0; // !-- Change 0 to speed const --!
}

QRect Bullet::getItsHitBox()
{
    return itsHitBox;
}

Position Bullet::getItsPosition()
{
    return itsPosition;
}
