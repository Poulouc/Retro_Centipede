#include "bodypart.h"

#ifndef CENTIPEDE_H
#define CENTIPEDE_H

class Centipede
{
private:
    BodyPart* itsHead;
    BodyPart* itsTail;
    Direction itsDirection;
    bool isGoingDown = true;
    bool reachedBottom = false;
public:
    Centipede(BodyPart* head = new BodyPart());
    ~Centipede();
    void moveForward(int distance);
    BodyPart* getItsHead();
    BodyPart* getItsTail();
    void setItsTail(BodyPart* tail);
    void setItsDirection(Direction dir);
    Position getNextPosition(int distance);
    Direction getItsDirection();
    bool hasReachedBottom();
    void setVerticalDirection(bool isCentipedeGoingDown);
    bool getVerticalDirection();
};

#endif // CENTIPEDE_H
