#include "powerup.h"

PowerUp::PowerUp(powerupType type) {
    itsType = type;
}

void PowerUp::setItsHitbox(QRect newHitbox)
{
    itsHitBox = newHitbox;
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
