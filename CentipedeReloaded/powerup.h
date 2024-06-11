#ifndef POWERUP_H
#define POWERUP_H

#include <QRect>
#include "typeDef.h"

enum powerupType{
    rafale,
    transpercant,
    herbicide
};

class PowerUp
{
public:
    PowerUp(powerupType type);
    Position getItsPosition();
    QRect getItsHitbox();
    void setItsPosition(Position newPos);
    void setItsHitbox(QRect newHitbox);

private:
    powerupType itsType;
    QRect itsHitBox;
    Position itsPos;
};

#endif // POWERUP_H
