#include "bullet.h"

// Constructor for the Bullet class.
Bullet::Bullet(int x, int y, int size)
    : itsHitBox(x, y, size, size), itsPosition({x, y})
{ }

// Destructor for the Bullet class.
Bullet::~Bullet()
{ }

// Updates the position of the bullet based on its speed.
void Bullet::updatePos()
{
    itsPosition.posY = itsPosition.posY - BULLET_SPEED; // Move the bullet upwards
    itsHitBox = {itsPosition.posX, itsPosition.posY, itsHitBox.width(), itsHitBox.height()}; // Update the hit box
}

// Returns the hit box of the bullet.
QRect Bullet::getItsHitBox()
{
    return itsHitBox;
}

// Returns the position of the bullet.
Position Bullet::getItsPosition()
{
    return itsPosition;
}
