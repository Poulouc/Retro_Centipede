#include "powerup.h"

PowerUp::PowerUp(powerupType type) {
    itsType = type;
}

void PowerUp::setItsHitbox(QRect newHitbox)
{
    itsHitBox = newHitbox;
    itsPos = {newHitbox.x(), newHitbox.y()};
}

void PowerUp::setItsPosition(Position newPos)
{
    itsPos = newPos;
    itsHitBox = {newPos.posX, newPos.posY, itsHitBox.width(), itsHitBox.height()};
}

QRect PowerUp::getItsHitbox()
{
    return itsHitBox;
}

Position PowerUp::getItsPosition()
{
    return itsPos;
}

powerupType PowerUp::getItsType()
{
    return itsType;
}
