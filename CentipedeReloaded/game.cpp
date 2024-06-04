#include <random>
#include "game.h"

using namespace std;

Game::Game(QRect board)
    :itsScore(0), itsCentipedes(new vector<Centipede*>), itsMushrooms(new vector<Mushroom*>), itsBullet(nullptr), itsPlayer(new Player), itsBoard(board)
{
    spawnCentipede();
    createMushrooms();
}

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

void Game::spawnCentipede()
{
    Centipede * newCentipede = new Centipede();
    BodyPart * currentPart = newCentipede->getItsHead();
    currentPart->setItsPosition({500, 100});
    newCentipede->setItsDirection({-1,0});
    for(int i = 0; i < CENTIPEDE_LENGTH; i++)
    {
        BodyPart * newPart = new BodyPart();
        Position newPos;
        newPos.posX = currentPart->getItsPosition().posX + CENTIPEDE_BODYPART_SIZE;
        newPos.posY = currentPart->getItsPosition().posY;
        newPart->setItsPosition(newPos);
        currentPart->setItsChild(newPart);
        newPart->setItsParent(currentPart);
        currentPart = newPart;
    }
    itsCentipedes->push_back(newCentipede);
}

void Game::createMushrooms()
{
    random_device rd;
    default_random_engine eng(rd());

    uniform_int_distribution<int> randX(0, itsBoard.width() / 30);
    uniform_int_distribution<int> randY(0, itsBoard.height() / 31);

    while (itsMushrooms->size() < MUSHROOMS_AMOUNT)
    {
        // Generate a position
        int genX = itsBoard.x() + randX(eng) * 30;
        int genY = itsBoard.y() + randY(eng) * 31;

        // Check if a mushroom already exist at the same position
        for (vector<Mushroom*>::iterator it = itsMushrooms->begin(); it < itsMushrooms->end(); it++)
        {
            if ((*it)->getItsPosition().posX == genX && (*it)->getItsPosition().posY == genY) continue;
        }

        itsMushrooms->push_back(new Mushroom(genX, genY));
    }
}

void Game::shoot()
{
    if (itsBullet != nullptr)
    {
        int newX = itsPlayer->getItsPosition().posX + PLAYER_SIZE / 2 - BULLET_SIZE / 2;
        int newY = itsPlayer->getItsPosition().posY + PLAYER_SIZE / 2 - BULLET_SIZE / 2;
        itsBullet = new Bullet(newX, newY);
    }
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
