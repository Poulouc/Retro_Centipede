#include <random>
#include "game.h"
#include <iostream>
#include <QDebug>

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

    // Deletion of the bullet and the player
    delete itsBullet;
    delete itsPlayer;
}

void Game::spawnCentipede()
{
    Centipede * newCentipede = new Centipede();
    BodyPart * currentPart = newCentipede->getItsHead();
    currentPart->setItsPosition(CENTIPEDE_SPAWN_POSITION);
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
        newCentipede->setItsTail(currentPart);
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
    //If the bullet left the board
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
    for(vector<Mushroom*>::iterator it = getItsMushrooms()->begin(); it != itsMushrooms->end(); ++it)
    {
        Mushroom * mushroom = *it;
        int distance = 0;
        QRect mushroomHitBox = mushroom->getItsHitBox();
        if(isColliding(centipedeHitBox, mushroomHitBox))
        {
            if(centipede->getVerticalDirection())
            {
                itsMushrooms->erase(it);
                delete mushroom;
                return false;
            }
            else
            {
                distance = abs(mushroom->getItsHitBox().x() - centipede->getItsHead()->getItsPosition().posX) - CENTIPEDE_BODYPART_SIZE;
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

bool Game::isGameWon()
{
    return itsCentipedes->size() <= 0;
}

bool Game::isGameLosed()
{
    return itsPlayer->getItsHp() <= 0;
}

void Game::checkCollisions()
{
    if (itsBullet != nullptr)
    {
        for (vector<Mushroom*>::iterator it = itsMushrooms->begin(); it < itsMushrooms->end(); it++) // checks if the bullet touches a mushroom
        {
            if (isColliding((*it)->getItsHitBox(), itsBullet->getItsHitBox()))
            {
                Mushroom * mushroom = *it;
                (mushroom)->damage();
                if (mushroom->getItsState() <= 0)
                {
                    itsScore += 4;
                    itsMushrooms->erase(it);
                    delete mushroom;
                }
                itsBullet = nullptr;
                break;
            }
        }
    }

    for (vector<Centipede*>::iterator it = itsCentipedes->begin(); it != itsCentipedes->end(); ++it)
    {
        Centipede * centipede = *it;
        for (BodyPart* centiPart = centipede->getItsHead(); centiPart != nullptr; centiPart = centiPart->getItsChild())
        {
            if (isColliding(centiPart->getItsHitBox(), itsPlayer->getItsHitBox())) // player touched
            {
                itsPlayer->hit();
                for (vector<Centipede*>::iterator itDel = itsCentipedes->begin(); itDel != itsCentipedes->end(); ++itDel)
                {
                    delete *itDel;
                }
                itsCentipedes->clear();
                itsPlayer->setItsPosition({ itsBoard.x() + itsBoard.width()/2 - PLAYER_SIZE/2, itsBoard.y() + itsBoard.height() - PLAYER_SIZE*2 - 4});
                spawnCentipede();
                return;
            }

            else if (itsBullet != nullptr && isColliding(centiPart->getItsHitBox(), itsBullet->getItsHitBox())) // centipede hit
            {
                BodyPart * newTail = centiPart->getItsParent();
                sliceCentipede(centiPart, centipede);
                centipede->setItsTail(newTail);
                itsBullet = nullptr;
                return;
            }
        }
    }
}

void Game::sliceCentipede(BodyPart* hittedPart, Centipede * centipede)
{
    if (hittedPart->getItsParent() != nullptr) // body hit
    {
        // Cut the hitted centipede
        hittedPart->getItsParent()->setItsChild(nullptr);

        // Check if the hitted part is NOT the tail
        if (hittedPart->getItsChild() != nullptr)
        {
            Position headPos = centipede->getItsTail()->getItsPosition();
            // Set next part as the head for the new centipede ...
            BodyPart* newTail = hittedPart->getItsChild();
            hittedPart->setItsChild(nullptr);
            // ... and seperate it from the hitted part
            newTail->setItsParent(nullptr);

            // Search the head of the new centipede (tail of the old centipede)
            BodyPart* newHead = centipede->getItsTail();
            BodyPart* currentPart = newHead->getItsParent();
            BodyPart* currentParent = newHead;
            newHead->setItsParent(nullptr);
            newHead->setItsChild(currentPart);

            while(currentPart != nullptr)
            {
                BodyPart* nextPart = currentPart->getItsParent();
                currentPart->setItsChild(nextPart);
                currentPart->setItsParent(currentParent);
                currentParent = currentPart;
                currentPart = nextPart;
            }

            // Create a new centipede with the tail as the head
            Centipede * newCentipede = new Centipede(newHead);
            newCentipede->setItsTail(newTail);
            newTail->setItsChild(nullptr);
            itsCentipedes->push_back(newCentipede);
            newCentipede->setItsDirection({-centipede->getItsDirection().dirX, centipede->getItsDirection().dirY});
        }

        // Deletion of the hitted part
        delete hittedPart;
    }
    else // headshot
    {
        for (vector<Centipede*>::iterator it = itsCentipedes->begin(); it != itsCentipedes->end(); ++it)
        {
            Centipede * centipede = *it;
            if (centipede->getItsHead() == hittedPart)
            {
                itsCentipedes->erase(it);
                delete centipede;
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
    //set the size of the mushrooms and their new placement
    for (vector<Mushroom*>::iterator it = itsMushrooms->begin(); it < itsMushrooms->end(); it++)
    {
        (*it)->setItsHitBox(QRect((board.x() + (*it)->getItsGridPosition().posX * (board.width()/BOARD_WIDTH)),
                                  (board.y() + (*it)->getItsGridPosition().posY * (board.width()/BOARD_WIDTH)),
                                  board.width()/BOARD_WIDTH,
                                  board.width()/BOARD_WIDTH));
    }
    //set the playerZone
    itsPlayerZone = QRect(board.x(),
                          board.y() + (4 * board.height()) / 5,
                          board.width(),
                          board.height() / 5);

    //set the size of the player and the new placement on the board
    itsPlayer->setItsHitBox(QRect(itsPlayerZone.x() + itsPlayerZone.width()/2 - (board.width() / BOARD_WIDTH)/2,
                                  itsPlayerZone.y() + itsPlayerZone.height() - (board.height() / BOARD_HEIGHT) - itsPlayerZone.height()/20,
                                  board.width()/BOARD_WIDTH,
                                  board.width()/BOARD_WIDTH));
    //set the position of the player
    itsPlayer->setItsPosition({itsPlayerZone.x() + itsPlayerZone.width()/2 - (board.width() / BOARD_WIDTH)/2,
                               itsPlayerZone.y() + itsPlayerZone.height() - (board.height() / BOARD_HEIGHT) - itsPlayerZone.height()/20});

    //faire une partie pour centipède
    for (vector<Centipede *>::iterator it = itsCentipedes->begin(); it != itsCentipedes->end(); ++it)
    {
        BodyPart *currentPart = (*it)->getItsHead();
        while (currentPart != nullptr)
        {
            // Calcul des nouvelles coordonnées proportionnelles
            int newX = board.x() + ((currentPart->getItsHitBox().x() - itsBoard.x() + 0.5) * board.width()) / itsBoard.width();
            int newY = board.y() + ((currentPart->getItsHitBox().y() - itsBoard.y() + 0.5) * board.height()) / itsBoard.height();

            // Mise à jour de la hitbox et de la position du segment
            currentPart->setItsHitBox({newX, newY, (board.width() / BOARD_WIDTH), (board.height() / BOARD_HEIGHT)});
            currentPart->setItsPosition({newX, newY});

            // Passer au segment suivant
            currentPart = currentPart->getItsChild();
        }
    }


    //set the board
    itsBoard = board;
}

// Moves the player based on the provided direction.
void Game::movePlayer(Direction & direction)
{
    // Check if the player can move horizontally within the player zone
    if (itsPlayerZone.x() < itsPlayer->getItsHitBox().x() + direction.dirX * PLAYER_SPEED &&
        itsPlayerZone.x() + itsPlayerZone.width() > itsPlayer->getItsHitBox().x() + itsPlayer->getItsHitBox().width() + direction.dirX * PLAYER_SPEED
        && (direction.dirX == -PLAYER_SPEED or direction.dirX == PLAYER_SPEED))
    {
        // Update the player's position in the horizontal direction
        itsPlayer->updatePos({direction.dirX, 0});
    }
    // Check if the player can move vertically within the player zone
    if(itsPlayerZone.y() < itsPlayer->getItsHitBox().y() + direction.dirY * PLAYER_SPEED &&
        itsPlayerZone.y() + itsPlayerZone.height() > itsPlayer->getItsHitBox().y() + itsPlayer->getItsHitBox().height() + direction.dirY * PLAYER_SPEED
        && (direction.dirY == -PLAYER_SPEED or direction.dirY == PLAYER_SPEED))
    {
        // Update the player's position in the vertical direction
        itsPlayer->updatePos({0, direction.dirY});
    }
}

// Moves the centipede units.
void Game::moveCentipede()
{
    // Define the initial zone as the game board.
    QRect zone = itsBoard;

    // Iterate through each centipede in the game.
    for(Centipede * centipede : *itsCentipedes)
    {
        // If the centipede has reached the bottom, change the zone to the player zone.
        if(centipede->hasReachedBottom())
            zone = itsPlayerZone;

        // Check for collisions with mushrooms and the game board.
        bool first = centipedeMushroomCollision(centipede);
        bool second = centipedeBoardCollision(centipede, zone);
        bool third = centipedeToCentipedeCollision(centipede);

        // If there's no collision, move the centipede forward.
        if(!(first || second || third))
        {
            // If the centipede is moving vertically, move it by one step.
            if(centipede->getVerticalDirection())
            {
                centipede->moveForward(itsBoard.height()/31);
            }
            // If the centipede is moving horizontally, move it by its standard speed.
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
        Position newPos = {board.width() + board.x() - CENTIPEDE_BODYPART_SIZE - 1, centipede->getItsHead()->getItsPosition().posY};
        centipede->getItsHead()->setItsPosition(newPos);

        centipede->setItsDirection({-1, centipede->getItsDirection().dirY});
        centipede->setVerticalDirection(true);
        return true;
    }
    if(centipedeHitBox.y() <= board.y()) // top of the board
    {
        Position newPos = {centipede->getItsHead()->getItsPosition().posX, board.y() + 1};
        centipede->getItsHead()->setItsPosition(newPos);

        centipede->setItsDirection({centipede->getItsDirection().dirX, 1});
        centipede->setVerticalDirection(false);
        return true;
    }
    else if(centipedeHitBox.y() + centipedeHitBox.height() >= board.y() + board.height()) // bottom of the board
    {
        centipede->setHasReachedBottom(true);
        Position newPos = {centipede->getItsHead()->getItsPosition().posX, board.y() + board.height() - CENTIPEDE_BODYPART_SIZE - 1};
        centipede->getItsHead()->setItsPosition(newPos);

        centipede->setItsDirection({centipede->getItsDirection().dirX, -1});
        centipede->setVerticalDirection(false);
        return true;
    }
    return false;
}

bool Game::centipedeToCentipedeCollision(Centipede * centipede)
{
    for(Centipede * currentCenti : *itsCentipedes)
    {
        if(isColliding(centipede->getItsHead()->getItsHitBox(), currentCenti->getItsHead()->getItsHitBox()) && currentCenti != centipede)
        {
            if(centipede->getVerticalDirection())
            {
            }
            else
            {
                int distance = abs(currentCenti->getItsHead()->getItsHitBox().x() - centipede->getItsHead()->getItsPosition().posX) - CENTIPEDE_BODYPART_SIZE;
                centipede->moveForward(distance);
                centipede->setVerticalDirection(true);
                centipede->moveForward(itsBoard.height()/31);
                centipede->setItsDirection({-centipede->getItsDirection().dirX, centipede->getItsDirection().dirY});

                currentCenti->setVerticalDirection(true);
                currentCenti->moveForward(itsBoard.height()/31);
                currentCenti->setItsDirection({-currentCenti->getItsDirection().dirX, currentCenti->getItsDirection().dirY});
                return true;
            }
        }
    }
    return false;
}
