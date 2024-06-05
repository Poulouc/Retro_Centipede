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
    while(currentPart->getItsParent() != nullptr)
    {
        Position newPos = currentPart->getItsParent()->getItsPosition();
        currentPart->setItsPosition(newPos);
        currentPart = currentPart->getItsParent();
    }
    Position headPos = itsHead->getItsPosition();
    Position newPos = {};
    newPos.posX = headPos.posX + distance * itsDirection.dirX;
    newPos.posY = headPos.posY + distance * itsDirection.dirY;
    currentPart->setItsPosition(newPos);
}

void Centipede::setItsDirection(Direction dir)
{
    itsDirection = dir;
}

Position Centipede::getNextPosition()
{
    Position nextPos;
    Position currentPos = itsHead->getItsPosition();
    nextPos.posX = currentPos.posX + CENTIPEDE_SPEED * itsDirection.dirX;
    nextPos.posY = currentPos.posY + CENTIPEDE_SPEED * itsDirection.dirY;
    return nextPos;
}
