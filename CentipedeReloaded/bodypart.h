#include <QRect>
#include "typeDef.h"

#ifndef BODYPART_H
#define BODYPART_H

class BodyPart
{
private:
    BodyPart* itsParent = nullptr;
    BodyPart* itsChild = nullptr;
    QRect itsHitBox;
    Position itsPosition = {};
public:
    BodyPart();
    ~BodyPart();
    Position getItsPosition();
    BodyPart* getItsChild();
    BodyPart* getItsParent();
    QRect getItsHitBox();
};

#endif // BODYPART_H
