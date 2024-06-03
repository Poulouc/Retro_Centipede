#include "centipede.h"

Centipede::Centipede(BodyPart * head) {
    itsHead = head;
}

BodyPart* Centipede::getItsHead()
{
    return itsHead;
}
