#include "bodypart.h"

BodyPart::BodyPart() {}

BodyPart::~BodyPart() {}

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
    itsPreviousPosition = itsPosition;
    itsPosition = pos;
    itsHitBox = {pos.posX, pos.posY, CENTIPEDE_BODYPART_SIZE, CENTIPEDE_BODYPART_SIZE};
}

Position BodyPart::getItsPreviousPosition()
{
    return itsPreviousPosition;
}

void BodyPart::setItsChild(BodyPart * child)
{
    itsChild = child;
}

void BodyPart::setItsParent(BodyPart * parent)
{
    itsParent = parent;
}
