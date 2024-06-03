#include "bodypart.h"
#include "typeDef.h"

#ifndef CENTIPEDE_H
#define CENTIPEDE_H

class Centipede
{
private:
    BodyPart* itsHead;
    Direction itsDirection;
public:
    Centipede(BodyPart * head = new BodyPart());
    ~Centipede();
    void moveForward();
    BodyPart* getItsHead();
};

#endif // CENTIPEDE_H
