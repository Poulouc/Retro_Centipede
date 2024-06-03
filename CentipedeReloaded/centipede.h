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
<<<<<<< HEAD
    Centipede(BodyPart * head = new BodyPart());
=======
    Centipede(BodyPart* head = nullptr);
>>>>>>> b0237f07b44373736bbec5b813e1b1433ceabbbf
    ~Centipede();
    void moveForward();
    BodyPart* getItsHead();
};

#endif // CENTIPEDE_H
