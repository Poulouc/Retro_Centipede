#include <QRect>
#include "typeDef.h"
#ifndef SPIDER_H
#define SPIDER_H

class Spider
{
private:
    QRect itsHitBox;
    Direction itsDirection;
    int itsHorizontaleDirection;
public:
    Spider(int x, int y, int size);
    QRect getItsHitBox();
    void setItsHitBox(QRect hitbox);
    Direction getItsDirection();
    void setItsDirection(Direction direction);
    int getItsHorizontaleDirection();
    void setItsHorizontaleDirection(int horizontalDirection);
    void move();
};

#endif // SPIDER_H
