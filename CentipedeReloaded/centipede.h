#include "bodypart.h"
#include "typeDef.h"

#ifndef CENTIPEDE_H
#define CENTIPEDE_H

class Centipede
{
private:
    int itsSpeed;
    BodyPart* itsHead;
    Direction itsDirection;
public:
    Centipede();
    ~Centipede();
    void moveForward();
    BodyPart* getItsHead();
};

#endif // CENTIPEDE_H
