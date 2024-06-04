#include <QRect>
#include "typeDef.h"

#ifndef BODYPART_H
#define BODYPART_H

class BodyPart
{
private:
    BodyPart* itsParent = nullptr;
    BodyPart* itsChild = nullptr;
    QRect itsHitBox = QRect(0, 0, CENTIPEDE_BODYPART_SIZE, CENTIPEDE_BODYPART_SIZE);
    Position itsPosition =  {};
public:
    BodyPart();
    ~BodyPart();
    Position getItsPosition();
    BodyPart* getItsChild();
    BodyPart* getItsParent();
    QRect getItsHitBox();
    void setItsPosition(Position pos);
    void setItsChild(BodyPart* child);
    void setItsParent(BodyPart* parent);
    void addChild(BodyPart* child);
};

#endif // BODYPART_H
