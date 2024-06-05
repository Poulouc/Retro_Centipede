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
    Mushroom(int x, int y, int size);
    ~Mushroom();
    void damage();
    int getItsState();
    QRect getItsHitBox();
    Position getItsPosition();
    void setItsHitBox(QRect hitBox);
};

#endif // MUSHROOM_H
