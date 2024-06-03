#include <QRect>
#include "typeDef.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet
{
private:
    int itsSpeed;
    QRect itsHitBox;
    Position itsPosition;
public:
    Bullet();
    ~Bullet();
    void updatePos();
    QRect getItsHitBox();
    Position getItsPosition();
};

#endif // BULLET_H
