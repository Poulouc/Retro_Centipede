#include "game.h"

using namespace std;

Game::Game()
    :itsScore(0), itsCentipedes(new vector<Centipede*>), itsMushrooms(new vector<Mushroom*>), itsBullet(nullptr), itsPlayer(new Player)
{ }

Game::~Game()
{
    // Deletion of centipedes' vector and each centipede inside
    for (vector<Centipede*>::iterator it = itsCentipedes->begin(); it < itsCentipedes->end(); it++)
    {
        delete *it;
    }
    delete itsCentipedes;

    // Deletion of mushrooms' vector and each mushroom inside
    for (vector<Mushroom*>::iterator it = itsMushrooms->begin(); it < itsMushrooms->end(); it++)
    {
        delete *it;
    }
    delete itsMushrooms;
    delete itsBullet;
    delete itsPlayer;
}

void Game::createMushrooms()
{

}

void Game::shoot()
{

}

bool Game::isColliding(Mushroom* mushroom, Player* player)
{
    return true;
}

bool Game::isColliding(Mushroom* mushroom, Bullet* bullet)
{
    return true;
}

bool Game::isColliding(Centipede* centipede, Bullet* bullet)
{
    return true;
}

bool Game::isColliding(Centipede* centipede, Mushroom* mushroom)
{
    return true;
}

std::vector<Centipede*>* Game::getItsCentipedes()
{
    return itsCentipedes;
}

std::vector<Mushroom*>* Game::getItsMushrooms()
{
    return itsMushrooms;
}

Bullet* Game::getItsBullet()
{
    return itsBullet;
}

Player* Game::getItsPlayer()
{
    return itsPlayer;
}
