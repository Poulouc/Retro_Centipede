#include "bodypart.h"

#include <iostream>

using namespace std;

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
    itsHitBox = {pos.posX, pos.posY, itsHitBox.width(), itsHitBox.height()};
}

void BodyPart::setItsHitBox(QRect hitbox)
{
    itsHitBox = hitbox;
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

void BodyPart::setItsTargetPos(Position targetPos)
{
    itsTargetPos = targetPos;
}

void BodyPart::updatePos()
{
    if (itsPosition.posX != itsTargetPos.posX)
    {
        // Moving from left to right (->)
        if (itsPosition.posX < itsTargetPos.posX)
        {
            itsPosition.posX += (itsTargetPos.posX - itsPosition.posX < CENTIPEDE_SPEED)?(itsTargetPos.posX - itsPosition.posX):CENTIPEDE_SPEED;
        }
        // Moving from right to left (<-)
        else if (itsPosition.posX > itsTargetPos.posX)
        {
            itsPosition.posX -= (itsPosition.posX - itsTargetPos.posX < CENTIPEDE_SPEED)?(itsPosition.posX - itsTargetPos.posX):CENTIPEDE_SPEED;
        }
    }
    else if (itsPosition.posY != itsTargetPos.posY)
    {
        // Moving from top to bottom (v)
        if (itsPosition.posY < itsTargetPos.posY)
        {
            itsPosition.posY += (itsTargetPos.posY - itsPosition.posY < CENTIPEDE_SPEED)?(itsTargetPos.posY - itsPosition.posY):CENTIPEDE_SPEED;
        }
        // Moving from bottom to top (^)
        else if (itsPosition.posY > itsTargetPos.posY)
        {
            itsPosition.posY -= (itsPosition.posY - itsTargetPos.posY < CENTIPEDE_SPEED)?(itsPosition.posY - itsTargetPos.posY):CENTIPEDE_SPEED;
        }
    }
    else
    {
        cout << "(" << itsPosition.posX << ", " << itsPosition.posY << ") -> (" <<
                itsTargetPos.posX << ", " << itsTargetPos.posY << ")" << endl;
        throw string("L'un des BodyPart ne se déplace plus");
    }

    itsHitBox = { itsPosition.posX, itsPosition.posY, CENTIPEDE_BODYPART_SIZE, CENTIPEDE_BODYPART_SIZE };
}

Position BodyPart::getNextTarget(Direction centipedeDir, int caseLength)
{
    int xTarget = itsTargetPos.posX + centipedeDir.dirX * caseLength;
    int yTarget = itsTargetPos.posY + centipedeDir.dirY * caseLength;
    return { xTarget, yTarget };
}

Position BodyPart::getItsTarget()
{
    return itsTargetPos;
}
