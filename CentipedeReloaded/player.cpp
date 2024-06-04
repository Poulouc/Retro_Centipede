#include "player.h"

Player::Player()
    :itsHP(3), itsHitBox({100, 100, PLAYER_SIZE, PLAYER_SIZE}), itsPosition({100, 100})
{ }

Player::~Player()
{ }

void Player::updatePos(Direction direction)
{
    itsPosition.posX = itsPosition.posX + direction.dirX * PLAYER_SPEED;
    itsPosition.posY = itsPosition.posY + direction.dirY * PLAYER_SPEED;
    itsHitBox = {itsPosition.posX, itsPosition.posY, PLAYER_SIZE, PLAYER_SIZE};
}

void Player::hit()
{
    itsHP--;
}

Position Player::getItsPosition()
{
    return itsPosition;
}

QRect Player::getItsHitBox()
{
    return itsHitBox;
}
