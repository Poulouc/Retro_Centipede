#include "game.h"

Game::Game() {
}

Game::~Game() {
    delete itsCentipedes;
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
