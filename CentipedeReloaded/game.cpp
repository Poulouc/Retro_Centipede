#include <random>
#include "game.h"

using namespace std;

Game::Game(QRect board)
    :itsScore(0), itsCentipedes(new vector<Centipede*>), itsMushrooms(new vector<Mushroom*>), itsBullet(nullptr), itsPlayer(new Player), itsBoard(board)
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
    random_device rd;
    default_random_engine eng(rd());

    uniform_int_distribution<int> randX(0, itsBoard.width() / 30);
    uniform_int_distribution<int> randY(0, itsBoard.height() / 31);

    while (itsMushrooms->size() < MUSHROOMS_AMOUNT)
    {
        itsMushrooms->push_back(new Mushroom());
    }
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
