#include <vector>
#include "bullet.h"
#include "centipede.h"
#include "mushroom.h"
#include "player.h"
#include "typeDef.h"

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
    QRect itsPlayerZone;
public:
    Game(QRect board);
    ~Game();
    void spawnCentipede();
    void createMushrooms();
    void shoot();
    void moveBullet();
    void moveCentipede();
    bool isColliding(Mushroom* mushroom, Player* player);
    bool isColliding(Mushroom* mushroom, Bullet* bullet);
    bool isColliding(Centipede* centipede, Bullet* bullet);
    bool isColliding(Centipede* centipede, Mushroom* mushroom);
    bool isColliding(QRect hitbox1, QRect hitbox2);
    bool centipedeBoardCollision(Centipede * centipede, QRect board);
    bool centipedeMushroomCollision(Centipede * centipede);
    void checkCollisions();
    void sliceCentipede(BodyPart* hittedPart);
    void movePlayer(Direction & direction);
    std::vector<Centipede*>* getItsCentipedes();
    std::vector<Mushroom*>* getItsMushrooms();
    Bullet* getItsBullet();
    Player* getItsPlayer();
};

#endif // GAME_H
