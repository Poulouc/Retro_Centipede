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
    int itsScore = 0;
    std::vector<Centipede*>* itsCentipedes = {};
    std::vector<Mushroom*>* itsMushrooms = {};
    Bullet* itsBullet = nullptr;
    Player* itsPlayer = new Player();
    QRect itsBoard;
public:
    Game(QRect board);
    ~Game();
    void spawnCentipede();
    void createMushrooms();
    void shoot();
    void moveBullet();
    bool isColliding(Mushroom* mushroom, Player* player);
    bool isColliding(Mushroom* mushroom, Bullet* bullet);
    bool isColliding(Centipede* centipede, Bullet* bullet);
    bool isColliding(Centipede* centipede, Mushroom* mushroom);
    std::vector<Centipede*>* getItsCentipedes();
    std::vector<Mushroom*>* getItsMushrooms();
    Bullet* getItsBullet();
    Player* getItsPlayer();
};

#endif // GAME_H
