#include <QRect>
#include "typeDef.h"

#ifndef BODYPART_H
#define BODYPART_H

class BodyPart
{
private:
    BodyPart* itsParent;
    BodyPart* itsChild;
    QRect itsHitBox;
public:
    BodyPart();
    ~BodyPart();
    Position getItsPosition();
    BodyPart* getItsChild();
    BodyPart* getItsParent();
    QRect getItsHitBox();
};

#endif // BODYPART_H
