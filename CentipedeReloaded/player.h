#include <QRect>
#include "typeDef.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
    int itsHP;
    QRect itsHitBox;
    Position itsPosition;
public:
    Player(Position position, int size);
    ~Player();
    void updatePos(Direction direction);
    void hit();
    Position getItsPosition();
    int getItsHp();
    QRect getItsHitBox();
    void setItsPosition(Position position);
    void setItsHitBox(QRect hitBox);
    void setItsHitBox(Position position);
};

#endif // PLAYER_H
