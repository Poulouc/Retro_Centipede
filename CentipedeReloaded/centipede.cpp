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
    Position partPos = itsHead->getItsPosition();
    Position newPos;
    int bodyCounter = CENTIPEDE_LENGTH;

    // Move the head of the centipede.
    if(isGoingDown)
    {
        newPos.posY = partPos.posY + distance * itsDirection.dirY;
        newPos.posX = partPos.posX;
        itsHead->setItsPosition(newPos);
        //isGoingDown = false;
    }
    else
    {
        newPos.posX = partPos.posX + distance * itsDirection.dirX;
        newPos.posY = partPos.posY;
        itsHead->setItsPosition(newPos);
    }
    BodyPart * currentPart = itsTail;
    // Move each body part of the centipede.
    while(currentPart != itsHead)
    {
        Position currentPos = currentPart->getItsPosition();
        Position parentPos = currentPart->getItsParent()->getItsPosition();
        Direction newDir;
        if(currentPos.posX < parentPos.posX) newDir.dirX = 1;
        else if(currentPos.posX == parentPos.posX) newDir.dirX = 0;
        else newDir.dirX = -1;

        if(currentPos.posY < parentPos.posY) newDir.dirY = 1;
        else if(currentPos.posY == parentPos.posY) newDir.dirY = 0;
        else newDir.dirY = -1;
        if(currentPos.posY != parentPos.posY)
        {
            newPos.posX = parentPos.posX;
            int distanceY = abs(currentPos.posY - parentPos.posY) * newDir.dirY;
            newPos.posY = currentPos.posY + distanceY;
        }
        if(currentPos.posX != parentPos.posX)
        {
            newPos.posY = parentPos.posY;
            int distanceX = abs(currentPos.posX - parentPos.posX) * newDir.dirX;
            newPos.posX = currentPos.posX + distanceX;
        }


        currentPart->setItsPosition(newPos);
        currentPart = currentPart->getItsParent();
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
