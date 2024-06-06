#include <QRect>
#include "typeDef.h"

#ifndef MUSHROOM_H
#define MUSHROOM_H

class Mushroom
{
private:
    int itsState;
    QRect itsHitBox;
    Position itsGridPosition;
public:
    Mushroom(int x, int y, int size, Position gridPosition);
    ~Mushroom();
    void damage();
    int getItsState();
    QRect getItsHitBox();
    Position getItsGridPosition();
    void setItsHitBox(QRect hitBox);
    void setItsGridPosition(Position position);
};

#endif // MUSHROOM_H
