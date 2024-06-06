#include "centipede.h"

// Constructor for the Centipede class.
Centipede::Centipede(BodyPart * head)
    : itsHead(head), itsTail(head)
{}

// Destructor for the Centipede class.
Centipede::~Centipede()
{

}

// Returns the head of the centipede.
BodyPart* Centipede::getItsHead()
{
    return itsHead;
}

// Returns the tail of the centipede.
BodyPart* Centipede::getItsTail()
{
    return itsTail;
}

// Returns the direction of the centipede.
Direction Centipede::getItsDirection()
{
    return itsDirection;
}

// Moves the centipede forward by a certain distance.
void Centipede::moveForward(int distance)
{
    BodyPart * currentPart = itsTail;
    Position partPos = itsHead->getItsPosition();
    Position newPos;
    int bodyCounter = CENTIPEDE_LENGTH;

    // Move each body part of the centipede.
    while(currentPart != itsHead)
    {
        newPos = currentPart->getItsParent()->getItsPosition();
        newPos.posX -= CENTIPEDE_BODYPART_SIZE * itsDirection.dirX;

        currentPart->setItsPosition(newPos);
        currentPart = currentPart->getItsParent();
    }

    // Move the head of the centipede.
    if(isGoingDown)
    {
        newPos.posY = partPos.posY + distance * itsDirection.dirY;
        newPos.posX = partPos.posX;
        itsHead->setItsPosition(newPos);
        isGoingDown = false;
    }
    else
    {
        newPos.posX = partPos.posX + distance * itsDirection.dirX;
        newPos.posY = partPos.posY;
        itsHead->setItsPosition(newPos);
    }
}

// Sets the direction of the centipede.
void Centipede::setItsDirection(Direction dir)
{
    itsDirection = dir;
}

// Calculates and returns the next position of the centipede.
Position Centipede::getNextPosition(int distance)
{
    Position nextPos;
    Position currentPos = itsHead->getItsPosition();
    if(isGoingDown)
    {
        nextPos.posY = currentPos.posY + distance * itsDirection.dirY;
        nextPos.posX = currentPos.posX;
    }
    else
    {
        nextPos.posX = currentPos.posX + distance * itsDirection.dirX;
        nextPos.posY = currentPos.posY;
    }
    return nextPos;
}

// Returns true if the centipede is moving vertically downwards.
bool Centipede::getVerticalDirection()
{
    return isGoingDown;
}

// Returns true if the centipede has reached the bottom of the screen.
bool Centipede::hasReachedBottom()
{
    return reachedBottom;
}

// Sets the vertical direction of the centipede.
void Centipede::setVerticalDirection(bool isCentipedeGoingDown)
{
    isGoingDown = isCentipedeGoingDown;
}

void Centipede::setHasReachedBottom(bool hasReachedBottom)
{
    reachedBottom = hasReachedBottom;
}

void Centipede::setItsTail(BodyPart * tail)
{
    itsTail = tail;
}
