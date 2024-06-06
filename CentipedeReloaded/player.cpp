#include "player.h"

Player::Player(Position position, int size)
    : itsHP(3), itsHitBox({position.posX, position.posY, size, size}), itsPosition(position)
{}

Player::~Player()
{ }

// Updates the position of the player based on the given direction.
void Player::updatePos(Direction direction)
{
    itsPosition.posX = itsPosition.posX + direction.dirX * PLAYER_SPEED;
    itsPosition.posY = itsPosition.posY + direction.dirY * PLAYER_SPEED;
    itsHitBox = {itsPosition.posX, itsPosition.posY, itsHitBox.width(), itsHitBox.height()};
}

// Decreases the HP of the player when hit.
void Player::hit()
{
    itsHP--;
}

// Returns the current position of the player.
Position Player::getItsPosition()
{
    return itsPosition;
}

// Returns the hitbox of the player.
QRect Player::getItsHitBox()
{
    return itsHitBox;
}

// Sets the position of the player.
void Player::setItsPosition(Position position)
{
    itsPosition = position;
}

// Returns the HP of the player.
int Player::getItsHp()
{
    return itsHP;
}

// Sets the hitbox of the player.
void Player::setItsHitBox(QRect hitBox)
{
    itsHitBox = hitBox;
}

// Sets the position of the player based on the given position.
void Player::setItsHitBox(Position position)
{
    itsPosition = {position.posX, position.posY};
}
