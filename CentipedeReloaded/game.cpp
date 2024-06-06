#include <random>
#include "game.h"

using namespace std;

Game::Game(QRect board)
    :itsScore(0), itsCentipedes(new vector<Centipede*>), itsMushrooms(new vector<Mushroom*>), itsBullet(nullptr),
    itsPlayer(new Player({board.x() + board.width()/2 - (board.width() / BOARD_WIDTH)/2, board.y() + board.height() - (board.width() / BOARD_WIDTH) - 1}, board.width() / BOARD_WIDTH)), itsBoard(board),
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

    uniform_int_distribution<int> randX(0, 30 - 1);
    uniform_int_distribution<int> randY(0, 31 - 1);
    int mushroomSize = (itsBoard.width() / BOARD_WIDTH);
    while (itsMushrooms->size() < MUSHROOMS_AMOUNT)
    {
        int randomX = randX(eng), randomY = randY(eng);

        // Generate a position
        int genX = itsBoard.x() + randomX * mushroomSize;
        int genY = itsBoard.y() + randomY * (itsBoard.height() / BOARD_HEIGHT);

        bool validPos = true;

        // Check if a mushroom already exist at the same position
        for (vector<Mushroom*>::iterator it = itsMushrooms->begin(); it < itsMushrooms->end(); it++)
        {
            if ((*it)->getItsHitBox().x() == genX && (*it)->getItsHitBox().y() == genY)
            {
                validPos = false;
                break;
            }
        }
        if (!validPos) continue;

        // Simulate the mushroom hitbox for next checks
        QRect previewHitbox = QRect(genX, genY, mushroomSize, mushroomSize);

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
        itsMushrooms->push_back(new Mushroom(genX, genY, mushroomSize, Position{randomX, randomY}));
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
    //dreturn hitbox1.contains(hitbox2);
    return hitbox1.intersected(hitbox2).isValid();
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

QRect Game::getItsBoard()
{
    return itsBoard;
}

void Game::setBoard(QRect board)
{
    //set the size of the mushrooms
    for (vector<Mushroom*>::iterator it = itsMushrooms->begin(); it < itsMushrooms->end(); it++)
    {
        //int randX = (genX - itsBoard.x()) / BOARD_WIDTH;
        //int randY = (genY - itsBoard.y()) / BOARD_HEIGHT;
        //int genX = itsBoard.x() + randomX * BOARD_WIDTH;
        //int genY = itsBoard.y() + randomY * BOARD_HEIGHT;

        (*it)->setItsHitBox(QRect((board.x() + (*it)->getItsGridPosition().posX * (board.width()/BOARD_WIDTH)),
                                  (board.y() + (*it)->getItsGridPosition().posY * (board.width()/BOARD_WIDTH)),
                                  board.width()/BOARD_WIDTH,
                                  board.width()/BOARD_WIDTH));
    }
    //set the size of the player
    itsPlayer->setItsHitBox(QRect(board.x() + board.width()/2 - (board.width() / BOARD_WIDTH)/2,
                                  board.y() + board.height() - (board.height() / BOARD_HEIGHT) - 1,
                                  board.width()/BOARD_WIDTH,
                                  board.width()/BOARD_WIDTH));
    //set the position of the player
    itsPlayer->setItsPosition({board.x() + board.width()/2 - (board.width() / BOARD_WIDTH)/2,
                               board.y() + board.height() - (board.height() / BOARD_HEIGHT) - 1});
    //set the playerZone
    itsPlayerZone = QRect(board.x(), board.y() + (4 * board.height()) / 5, board.width(), board.height() / 5);

    //faire une partie pour centipède


    //set the board
    itsBoard = board;
}

void Game::movePlayer(Direction & direction)
{
    if (itsPlayerZone.x() < itsPlayer->getItsHitBox().x() + direction.dirX * PLAYER_SPEED &&
        itsPlayerZone.x() + itsPlayerZone.width() > itsPlayer->getItsHitBox().x() + itsPlayer->getItsHitBox().width() + direction.dirX * PLAYER_SPEED
        && (direction.dirX == -PLAYER_SPEED or direction.dirX == PLAYER_SPEED))
    {
        itsPlayer->updatePos({direction.dirX, 0});
    }
    if(itsPlayerZone.y() < itsPlayer->getItsHitBox().y() + direction.dirY * PLAYER_SPEED &&
        itsPlayerZone.y() + itsPlayerZone.height() > itsPlayer->getItsHitBox().y() + itsPlayer->getItsHitBox().height() + direction.dirY * PLAYER_SPEED
        && (direction.dirY == -PLAYER_SPEED or direction.dirY == PLAYER_SPEED))
    {
        itsPlayer->updatePos({0, direction.dirY});
    }
}
