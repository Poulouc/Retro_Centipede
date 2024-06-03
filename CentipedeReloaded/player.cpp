#include "player.h"

Player::Player()
    :itsHP(3), itsHitBox(0, 0, 0, 0), itsPosition({0, 0})
{ }

Player::~Player()
{ }

void Player::updatePos(Direction direction)
{
    itsPosition.posX = itsPosition.posX + direction.dirX * PLAYER_SPEED;
    itsPosition.posY = itsPosition.posY + direction.dirY * PLAYER_SPEED;
}

Position Player::getItsPosition()
{
    return itsPosition;
}

QRect Player::getItsHitBox()
{
    return itsHitBox;
}
