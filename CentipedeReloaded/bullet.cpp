#include "bullet.h"

Bullet::Bullet(int x, int y)
    :itsHitBox(x, y, BULLET_SIZE, BULLET_SIZE), itsPosition({x, y})
{ }

Bullet::~Bullet()
{ }

void Bullet::updatePos()
{
    itsPosition.posY = itsPosition.posY - BULLET_SPEED;
    itsHitBox = {itsPosition.posX, itsPosition.posY, BULLET_SIZE, BULLET_SIZE};
}

QRect Bullet::getItsHitBox()
{
    return itsHitBox;
}

Position Bullet::getItsPosition()
{
    return itsPosition;
}
