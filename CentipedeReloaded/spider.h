#include <QRect>
#include "typeDef.h"
#ifndef SPIDER_H
#define SPIDER_H

class Spider
{
private:
    QRect itsHitBox;
    Position itsPosition;
public:
    spider(int x, int y, int size);
    QRect getItsHitBox();
    void setItsHitBox(QRect hitbox);
    Position getItsPosition();
    void setItsPosition(Position position);
};

#endif // SPIDER_H
