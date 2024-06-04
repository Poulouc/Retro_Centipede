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

void Centipede::moveForward()
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
    newPos.posX = headPos.posX + CENTIPEDE_SPEED * itsDirection.dirX;
    newPos.posY = headPos.posY + CENTIPEDE_SPEED * itsDirection.dirY;
    currentPart->setItsPosition(newPos);
}

void Centipede::setItsDirection(Direction dir)
{
    itsDirection = dir;
}
