#include "player.h"

Player::Player(Position position, int size)
    :itsHP(3), itsHitBox({position.posX, position.posY, size, size}), itsPosition(position)
{}

Player::~Player()
{ }

void Player::updatePos(Direction direction)
{
    itsPosition.posX = itsPosition.posX + direction.dirX * PLAYER_SPEED;
    itsPosition.posY = itsPosition.posY + direction.dirY * PLAYER_SPEED;
    itsHitBox = {itsPosition.posX, itsPosition.posY, itsHitBox.width(), itsHitBox.height()};
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

void Player::setItsPosition(Position position)
{
    itsPosition = position;
}

int Player::getItsHp()
{
    return itsHP;
}

void Player::setItsHitBox(QRect hitBox)
{
    itsHitBox = hitBox;
}

void Player::setItsHitBox(Position position)
{
    itsPosition = {position.posX, position.posY};
}
