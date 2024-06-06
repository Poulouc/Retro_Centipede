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
    bool isColliding(QRect hitbox1, QRect hitbox2);
    bool centipedeBoardCollision(Centipede * centipede, QRect board);
    bool centipedeMushroomCollision(Centipede * centipede);
    bool isGameWon();
    bool isGameLosed();
    void checkCollisions();
    void sliceCentipede(BodyPart* hittedPart);
    void movePlayer(Direction & direction);
    std::vector<Centipede*>* getItsCentipedes();
    std::vector<Mushroom*>* getItsMushrooms();
    Bullet* getItsBullet();
    Player* getItsPlayer();
    int getItsScore();
};

#endif // GAME_H
