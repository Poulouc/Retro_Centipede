#include "centipede.h"

using namespace std;

// Constructor for the Centipede class.
Centipede::Centipede(BodyPart * head)
    : itsHead(head), itsTail(head)
{
    while (itsTail->getItsChild() != nullptr)
    {
        itsTail = itsTail->getItsChild();
    }
}

// Destructor for the Centipede class.
Centipede::~Centipede()
{
    /**
    for (BodyPart* actualPart = itsHead->getItsChild(); actualPart != nullptr; actualPart = actualPart->getItsChild())
    {
        delete actualPart->getItsParent();
    }
    delete itsTail;
    **/
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
    if (isGoingDown)
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
bool Centipede::isVerticalDirection()
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

void Centipede::setWasMovingRight(bool value)
{
    if (!wasMovingLeft)
    {
        wasMovingRight = value;
    }
    else
    {
        throw string("flag right but left already flagged");
    }
}

void Centipede::setWasMovingLeft(bool value)
{
    if (!wasMovingRight)
    {
        wasMovingLeft = value;
    }
    else
    {
        throw string("flag right but left already flagged");
    }
}

bool Centipede::getWasMovingRight()
{
    return wasMovingRight;
}

bool Centipede::getWasMovingLeft()
{
    return wasMovingLeft;
}
