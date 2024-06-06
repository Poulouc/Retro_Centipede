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
    BodyPart * currentPart = itsHead;
    Position headPos = itsHead->getItsPosition();
    Position newPos = {};
    if(isGoingDown)
    {
        newPos.posY = headPos.posY + distance * itsDirection.dirY;
        newPos.posX = headPos.posX;
        isGoingDown = false;
    }
    else
    {
        newPos.posX = headPos.posX + distance * itsDirection.dirX;
        newPos.posY = headPos.posY;
    }

    currentPart->setItsPosition(newPos);
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
