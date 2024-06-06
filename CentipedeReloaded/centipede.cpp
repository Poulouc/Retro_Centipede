#include "centipede.h"

Centipede::Centipede(BodyPart * head)
    :itsHead(head), itsTail(head)
{}

Centipede::~Centipede()
{

}

BodyPart* Centipede::getItsHead()
{
    return itsHead;
}

BodyPart* Centipede::getItsTail()
{
    return itsTail;
}

Direction Centipede::getItsDirection()
{
    return itsDirection;
}

void Centipede::moveForward(int distance)
{
    BodyPart * currentPart = itsTail;
    Position partPos = itsHead->getItsPosition();
    Position newPos;
    int bodyCounter = CENTIPEDE_LENGTH;

    while(currentPart != itsHead) // moves the body
    {
        newPos = currentPart->getItsParent()->getItsPosition();
        newPos.posX -= CENTIPEDE_BODYPART_SIZE * itsDirection.dirX;

        currentPart->setItsPosition(newPos);
        currentPart = currentPart->getItsParent();
    }

    if(isGoingDown) // moves the head
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

void Centipede::setItsDirection(Direction dir)
{
    itsDirection = dir;
}

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

bool Centipede::getVerticalDirection()
{
    return isGoingDown;
}

bool Centipede::hasReachedBottom()
{
    return reachedBottom;
}

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
