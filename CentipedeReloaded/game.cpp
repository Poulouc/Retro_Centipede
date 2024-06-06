#include <random>
#include "game.h"

using namespace std;

Game::Game(QRect board)
    :itsScore(0), itsCentipedes(new vector<Centipede*>), itsMushrooms(new vector<Mushroom*>), itsBullet(nullptr),
    itsPlayer(new Player({board.width()/2 - PLAYER_SIZE/2, board.height() - PLAYER_SIZE - 1})), itsBoard(board),
    itsPlayerZone(board.x(), board.y() + (4 * board.height()) / 5, board.width(), board.height() / 5)
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
    newCentipede->setItsDirection({-1,1});
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

        bool validPos = true;

        // Check if a mushroom already exist at the same position
        for (vector<Mushroom*>::iterator it = itsMushrooms->begin(); it < itsMushrooms->end(); it++)
        {
            if ((*it)->getItsPosition().posX == genX && (*it)->getItsPosition().posY == genY)
            {
                validPos = false;
                break;
            }
        }
        if (!validPos) continue;

        // Simulate the mushroom hitbox for next checks
        QRect previewHitbox = QRect(genX, genY, MUSHROOM_SIZE, MUSHROOM_SIZE);

        // Check if the mushroom want to spawn on a centipede
        for (vector<Centipede*>::iterator it = itsCentipedes->begin(); it < itsCentipedes->end(); it++)
        {
            for (BodyPart* actualPart = (*it)->getItsHead(); actualPart != nullptr; actualPart = actualPart->getItsChild())
            {
                if (isColliding(previewHitbox, actualPart->getItsHitBox()))
                {
                    validPos = false;
                    break;
                }
            }
        }
        if (!validPos) continue;

        // Check if the mushroom want to spawn on the player
        if (isColliding(previewHitbox, itsPlayer->getItsHitBox())) continue;

        // Check if the mushroom want to spawn on the bullet
        if (itsBullet != nullptr && isColliding(previewHitbox, itsBullet->getItsHitBox())) continue;

        // Create the mushroom, must be executed only if the position is valid
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

    if(itsBullet->getItsPosition().posY < itsBoard.y())
    {
        itsBullet = nullptr;
    }
}

bool Game::isColliding(QRect hitbox1, QRect hitbox2)
{
    return hitbox1.intersects(hitbox2);
}

bool Game::centipedeMushroomCollision(Centipede * centipede)
{
    QRect centipedeHitBox = {centipede->getNextPosition(CENTIPEDE_SPEED).posX, centipede->getNextPosition(CENTIPEDE_SPEED).posY, CENTIPEDE_BODYPART_SIZE, CENTIPEDE_BODYPART_SIZE};
    for(Mushroom * mushroom : *itsMushrooms)
    {
        int distance = 0;
        QRect mushroomHitBox = mushroom->getItsHitBox();
        if(isColliding(centipedeHitBox, mushroomHitBox))
        {
            if(centipede->getVerticalDirection())
            {
                delete mushroom;
            }
            else
            {
                distance = abs(mushroom->getItsPosition().posX - centipede->getItsHead()->getItsPosition().posX) - CENTIPEDE_BODYPART_SIZE;
                centipede->moveForward(distance);
                centipede->setVerticalDirection(true);
                centipede->moveForward(itsBoard.height()/31);
                centipede->setItsDirection({-centipede->getItsDirection().dirX, centipede->getItsDirection().dirY});
                return true;
            }
        }
    }
    return false;
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
                if ((*it)->getItsState() <= 0)
                {
                    delete *it;
                }
                itsBullet = nullptr;
                break;
            }
        }
    }

    for (vector<Centipede*>::iterator it = itsCentipedes->begin(); it < itsCentipedes->end(); it++)
    {
        for (BodyPart* centiPart = (*it)->getItsHead(); centiPart != nullptr; centiPart = centiPart->getItsChild())
        {
            if (itsBullet != nullptr && isColliding(centiPart->getItsHitBox(), itsBullet->getItsHitBox()))
            {
                sliceCentipede(centiPart);
                itsBullet = nullptr;
            }

            if (isColliding(centiPart->getItsHitBox(), itsPlayer->getItsHitBox()))
            {
                itsPlayer->hit();
                for (vector<Centipede*>::iterator it = itsCentipedes->begin(); it < itsCentipedes->end(); it++)
                {
                    delete *it;
                }
                itsPlayer->setItsPosition({ itsBoard.width() / 2 - PLAYER_SIZE / 2, itsBoard.height() - PLAYER_SIZE - 1 });
                spawnCentipede();
            }
        }
    }
}

void Game::sliceCentipede(BodyPart* hittedPart)
{
    if (hittedPart->getItsParent() != nullptr)
    {
        hittedPart->getItsParent()->setItsChild(nullptr);
        if (hittedPart->getItsChild() != nullptr)
        {
            BodyPart* newHead = hittedPart->getItsChild();
            while(newHead->getItsChild() != nullptr)
            {
                newHead = newHead->getItsChild();
            }
            itsCentipedes->push_back(new Centipede(newHead));
        }
    }
    else
    {
        for (vector<Centipede*>::iterator it = itsCentipedes->begin(); it < itsCentipedes->end(); it++)
        {
            if ((*it)->getItsHead() == hittedPart)
            {
                delete *it;
                break;
            }
        }
    }
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

int Game::getItsScore()
{
    return itsScore;
}

void Game::movePlayer(Direction & direction)
{
    if (itsPlayerZone.x() < itsPlayer->getItsHitBox().x() + direction.dirX * PLAYER_SPEED &&
        itsPlayerZone.x() + itsPlayerZone.width() > itsPlayer->getItsHitBox().x() + itsPlayer->getItsHitBox().width() + direction.dirX * PLAYER_SPEED &&
        itsPlayerZone.y() < itsPlayer->getItsHitBox().y() + direction.dirY * PLAYER_SPEED &&
        itsPlayerZone.y() + itsPlayerZone.height() > itsPlayer->getItsHitBox().y() + itsPlayer->getItsHitBox().height() + direction.dirY * PLAYER_SPEED)
    {
        itsPlayer->updatePos(direction);
    }
}

void Game::moveCentipede()
{
    for(Centipede * centipede : *itsCentipedes)
    {
        bool first = centipedeMushroomCollision(centipede);
        bool second = centipedeBoardCollision(centipede, itsBoard);
        if(!(first || second)) // if there's no collision
        {
            if(centipede->getVerticalDirection())
            {
                centipede->moveForward(itsBoard.height()/31);
            }
            else
            {
                centipede->moveForward(CENTIPEDE_SPEED);
            }
        }
    }
}

bool Game::centipedeBoardCollision(Centipede * centipede, QRect board)
{
    QRect centipedeHitBox;
    int distance = 0;
    if(centipede->getVerticalDirection())
    {
        centipedeHitBox = {centipede->getNextPosition(itsBoard.height()/31).posX, centipede->getNextPosition(itsBoard.height()/31).posY, CENTIPEDE_BODYPART_SIZE, CENTIPEDE_BODYPART_SIZE};
    }
    else
    {
        centipedeHitBox = {centipede->getNextPosition(CENTIPEDE_SPEED).posX, centipede->getNextPosition(CENTIPEDE_SPEED).posY, CENTIPEDE_BODYPART_SIZE, CENTIPEDE_BODYPART_SIZE};
    }

    if(centipedeHitBox.x() <= board.x()) // left side of the board
    {
        Position newPos = {board.x() + 1, centipede->getItsHead()->getItsPosition().posY};
        centipede->getItsHead()->setItsPosition(newPos);

        centipede->setItsDirection({1, centipede->getItsDirection().dirY});
        centipede->setVerticalDirection(true);
        return true;
    }
    else if(centipedeHitBox.x() + centipedeHitBox.width() >= board.x() + board.width()) // right side of the board
    {
        Position newPos = {board.width() - CENTIPEDE_BODYPART_SIZE - 1, centipede->getItsHead()->getItsPosition().posY};
        centipede->getItsHead()->setItsPosition(newPos);

        centipede->setItsDirection({-1, centipede->getItsDirection().dirY});
        centipede->setVerticalDirection(true);
        return true;
    }
    if(centipedeHitBox.y() <= board.y()) // top of the board
    {
        distance = abs(board.y() - centipede->getItsHead()->getItsPosition().posY) - 1;

        Position newPos = {centipede->getItsHead()->getItsPosition().posX, board.y() + 1};
        centipede->getItsHead()->setItsPosition(newPos);

        centipede->setItsDirection({centipede->getItsDirection().dirX, 1});
        centipede->setVerticalDirection(false);
        return true;
    }
    else if(centipedeHitBox.y() + centipedeHitBox.height() >= board.y() + board.height()) // bottom of the board
    {
        distance = abs(board.height() - centipede->getItsHead()->getItsPosition().posY) - CENTIPEDE_BODYPART_SIZE*2;

        Position newPos = {centipede->getItsHead()->getItsPosition().posX, board.height()};
        centipede->getItsHead()->setItsPosition(newPos);

        centipede->setItsDirection({centipede->getItsDirection().dirX, -1});
        centipede->setVerticalDirection(false);
        return true;
    }
    return false;
}
