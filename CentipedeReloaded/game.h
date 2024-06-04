#include <vector>
#include "bullet.h"
#include "centipede.h"
#include "mushroom.h"
#include "player.h"

#ifndef GAME_H
#define GAME_H

class Game
{
private:
    int itsScore;
    std::vector<Centipede*>* itsCentipedes;
    std::vector<Mushroom*>* itsMushrooms;
    Bullet* itsBullet;
    Player* itsPlayer;
    QRect itsBoard;
public:
    Game(QRect board);
    ~Game();
    void createMushrooms();
    void shoot();
    bool isColliding(QRect hitbox1, QRect hitbox2);
    void checkCollisions();
    void sliceCentipede(BodyPart* hittedPart);
    std::vector<Centipede*>* getItsCentipedes();
    std::vector<Mushroom*>* getItsMushrooms();
    Bullet* getItsBullet();
    Player* getItsPlayer();
};

#endif // GAME_H
