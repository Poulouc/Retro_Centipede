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
    Player(Position position);
    ~Player();
    void updatePos(Direction direction);
    Position getItsPosition();
    QRect getItsHitBox();
};

#endif // PLAYER_H
