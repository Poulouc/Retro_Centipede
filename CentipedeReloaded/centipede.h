#include "bodypart.h"

#ifndef CENTIPEDE_H
#define CENTIPEDE_H

class Centipede
{
private:
    BodyPart* itsHead;
    BodyPart* itsTail;
    Direction itsDirection;
public:
    Centipede(BodyPart* head = new BodyPart());
    ~Centipede();
    void moveForward();
    BodyPart* getItsHead();
    BodyPart* getItsTail();
    void setItsTail(BodyPart* tail);
};

#endif // CENTIPEDE_H
