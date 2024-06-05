#include "bodypart.h"

#ifndef CENTIPEDE_H
#define CENTIPEDE_H

class Centipede
{
private:
    BodyPart* itsHead;
    BodyPart* itsTail;
    Direction itsDirection;
    int distanceToGoDown = 0;
public:
    Centipede(BodyPart* head = new BodyPart());
    ~Centipede();
    void moveForward(int distance);
    BodyPart* getItsHead();
    BodyPart* getItsTail();
    void setItsTail(BodyPart* tail);
    void setItsDirection(Direction dir);
    Position getNextPosition();
    Direction getItsDirection();
};

#endif // CENTIPEDE_H
