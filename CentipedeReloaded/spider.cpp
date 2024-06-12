#include "spider.h"

// Constructor initializes the spider's hitbox and sets initial direction to (0, 0)
Spider::Spider(int x, int y, int size):
    itsHitBox({x, y, size, size}), itsDirection({0, 0})
{}

// Returns the current hitbox of the spider
QRect Spider::getItsHitBox()
{
    return itsHitBox;
}

// Sets the hitbox of the spider to the provided hitbox
void Spider::setItsHitBox(QRect hitbox)
{
    itsHitBox = hitbox;
}

// Returns the current movement direction of the spider
Direction Spider::getItsDirection()
{
    return itsDirection;
}

// Sets the movement direction of the spider to the provided direction
void Spider::setItsDirection(Direction direction)
{
    itsDirection = direction;
}

// Returns the current horizontal movement direction of the spider
int Spider::getItsHorizontaleDirection()
{
    return itsHorizontaleDirection;
}

// Sets the horizontal movement direction of the spider to the provided direction
void Spider::setItsHorizontaleDirection(int horizontalDirection)
{
    itsHorizontaleDirection = horizontalDirection;
}

// Moves the spider based on its current direction and a predefined speed (SPIDER_SPEED)
void Spider::move()
{
    // Update the spider's hitbox position based on its direction and speed
    itsHitBox = QRect(itsHitBox.x() + itsDirection.dirX * SPIDER_SPEED,
                      itsHitBox.y() + itsDirection.dirY * SPIDER_SPEED,
                      itsHitBox.width(),
                      itsHitBox.height());
}
