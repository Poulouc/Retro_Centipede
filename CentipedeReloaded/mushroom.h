#include <QRect>
#include "typeDef.h"

#ifndef MUSHROOM_H
#define MUSHROOM_H

class Mushroom
{
private:
    int itsState;
    QRect itsHitBox;
    Position itsPosition;
public:
    Mushroom();
    ~Mushroom();
    void damage();
    int getItsState();
    QRect getItsHitBox();
    Position getItsPosition();
};

#endif // MUSHROOM_H
