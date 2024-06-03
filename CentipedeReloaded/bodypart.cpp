#include "bodypart.h"

BodyPart::BodyPart() {}

Position BodyPart::getItsPosition()
{
    return itsPosition;
}

BodyPart * BodyPart::getItsChild()
{
    return itsChild;
}

BodyPart * BodyPart::getItsParent()
{
    return itsParent;
}

QRect BodyPart::getItsHitBox()
{
    return itsHitBox;
}

void BodyPart::addChild(BodyPart * child)
{
    itsChild = child;
    itsChild->itsParent = this;
}

void BodyPart::setItsPosition(Position pos)
{
    itsPosition = pos;
    itsHitBox.setX(pos.posX);
    itsHitBox.setY(pos.posY);
}

void BodyPart::setItsChild(BodyPart * child)
{
    itsChild = child;
}

void BodyPart::setItsParent(BodyPart * parent)
{
    itsParent = parent;
}
