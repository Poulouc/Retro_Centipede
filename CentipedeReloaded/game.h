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
    int itsScore = 0;
    std::vector<Centipede*>* itsCentipedes = {};
    std::vector<Mushroom*>* itsMushrooms = {};
    Bullet* itsBullet = new Bullet();
    Player* itsPlayer = new Player();
    QRect itsBoard;
    QRect itsPlayerZone;
public:
    Game(QRect board);
    ~Game();
    void createMushrooms();
    void shoot();
    bool isColliding(Mushroom* mushroom, Player* player);
    bool isColliding(Mushroom* mushroom, Bullet* bullet);
    bool isColliding(Centipede* centipede, Bullet* bullet);
    bool isColliding(Centipede* centipede, Mushroom* mushroom);
    void movePlayer(Direction & direction);
    std::vector<Centipede*>* getItsCentipedes();
    std::vector<Mushroom*>* getItsMushrooms();
    Bullet* getItsBullet();
    Player* getItsPlayer();
};

#endif // GAME_H
