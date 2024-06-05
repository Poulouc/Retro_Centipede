#include <random>
#include "game.h"
#include <QRect>

using namespace std;

Game::Game(QRect board)
    :itsScore(0), itsCentipedes(new vector<Centipede*>), itsMushrooms(new vector<Mushroom*>), itsBullet(nullptr),
    itsPlayer(new Player({board.width()/2 - PLAYER_SIZE/2, board.height() - PLAYER_SIZE - 1})), itsBoard(board),
    itsPlayerZone(0, (4 * board.height()) / 5, board.width(), board.height() / 5)
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
    currentPart->setItsPosition({500, 31});
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
    if (itsBullet == nullptr)
    {
        int newX = itsPlayer->getItsPosition().posX /*+ PLAYER_SIZE / 2 - BULLET_SIZE / 2*/;
        int newY = itsPlayer->getItsPosition().posY /*+ PLAYER_SIZE / 2 - BULLET_SIZE / 2*/;
        itsBullet = new Bullet(newX, newY);
    }
}

void Game::moveBullet()
{
    itsBullet->updatePos();

    if(itsBullet->getItsPosition().posY < 0)
    {
        itsBullet = nullptr;
    }
}

bool Game::isColliding(QRect hitbox1, QRect hitbox2)
{
    return hitbox1.intersected(hitbox2).isValid();
}

int Game::collidingDistance(Centipede * centipede)
{
    QRect centipedeHitBox = {centipede->getNextPosition().posX, centipede->getNextPosition().posY, CENTIPEDE_BODYPART_SIZE, CENTIPEDE_BODYPART_SIZE};
    for(Mushroom * mushroom : *itsMushrooms)
    {
        QRect mushroomHitBox = mushroom->getItsHitBox();
        if(isColliding(centipedeHitBox, mushroomHitBox))
        {
            return abs(mushroom->getItsPosition().posX - centipede->getItsHead()->getItsPosition().posX) - CENTIPEDE_BODYPART_SIZE;
        }
    }
    if(!itsBoard.contains(centipedeHitBox, true))
    {
        if(centipedeHitBox.x() <= 0) // left side of the board
        {
            return abs(itsBoard.x() - centipede->getItsHead()->getItsPosition().posX) - 1;
        }
        else
        {
            return abs(itsBoard.width() - centipede->getItsHead()->getItsPosition().posX) - CENTIPEDE_BODYPART_SIZE*2;
        }
    }
    return -1;
}

void Game::checkCollisions()
{
    if (itsBullet != nullptr)
    {
        for (vector<Mushroom*>::iterator it = itsMushrooms->begin(); it < itsMushrooms->end(); it++)
        {
            if (isColliding((*it)->getItsHitBox(), itsBullet->getItsHitBox()))
            {
                (*it)->damage();
                itsBullet = nullptr;
                break;
            }
        }
    }

    for (vector<Centipede*>::iterator it = itsCentipedes->begin(); it < itsCentipedes->end(); it++)
    {
        for (BodyPart* centiPart = (*it)->getItsHead(); centiPart != nullptr; centiPart = centiPart->getItsChild())
        {
            if (itsBullet != nullptr)
            {
                if (isColliding(centiPart->getItsHitBox(), itsBullet->getItsHitBox()))
                {
                    sliceCentipede(centiPart);
                    itsBullet = nullptr;
                }
            }

            if (isColliding(centiPart->getItsHitBox(), itsPlayer->getItsHitBox()))
            {
                itsPlayer->hit();
                for (vector<Centipede*>::iterator it = itsCentipedes->begin(); it < itsCentipedes->end(); it++)
                {
                    delete *it;
                }
            }
        }
    }
}

void Game::sliceCentipede(BodyPart* hittedPart)
{ }

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

void Game::movePlayer(Direction & direction)
{
    if(itsPlayerZone.x() < itsPlayer->getItsHitBox().x() + direction.dirX * PLAYER_SPEED and itsPlayerZone.x() + itsPlayerZone.width() > itsPlayer->getItsHitBox().x() + itsPlayer->getItsHitBox().width() + direction.dirX * PLAYER_SPEED
        and itsPlayerZone.y() < itsPlayer->getItsHitBox().y() + direction.dirY * PLAYER_SPEED and itsPlayerZone.y() + itsPlayerZone.height() > itsPlayer->getItsHitBox().y() + itsPlayer->getItsHitBox().height() + direction.dirY * PLAYER_SPEED)
    {
        itsPlayer->updatePos(direction);
    }
}

void Game::moveCentipede()
{
    for(Centipede * centipede : *itsCentipedes)
    {
        int distance = collidingDistance(centipede);
        if(distance != -1)
        {
            int xOriginalDirection = centipede->getItsDirection().dirX;
            centipede->moveForward(distance);
            centipede->setItsDirection({0,1});
            centipede->moveForward(itsBoard.height()/31);
            centipede->setItsDirection({-xOriginalDirection,0});
        } else {
            centipede->moveForward(CENTIPEDE_SPEED);
        }
    }
}
