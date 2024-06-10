#include <random>
#include "game.h"

#include <iostream>
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
    Position newPos;
    Position oldPos;

    newPos.posX = itsBoard.x() + CENTIPEDE_SPAWN_XPOS * (itsBoard.width() / BOARD_WIDTH);
    newPos.posY = itsBoard.y() + CENTIPEDE_SPAWN_YPOS * (itsBoard.height() / BOARD_HEIGHT);
    currentPart->setItsPosition(newPos);

    oldPos.posX = newPos.posX - CENTIPEDE_BODYPART_SIZE;
    oldPos.posY = newPos.posY;
    currentPart->setItsTargetPos(oldPos);

    newCentipede->setItsDirection({ -1, 0 });
    for(int i = 0; i < CENTIPEDE_LENGTH - 1; i++)
    {
        BodyPart * newPart = new BodyPart();
        oldPos.posX = newPos.posX;
        newPos.posX = newPos.posX + CENTIPEDE_BODYPART_SIZE;
        newPart->setItsPosition(newPos);
        newPart->setItsTargetPos(oldPos);

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
        itsMushrooms->push_back(new Mushroom(genX, genY, mushroomSize, { randomX, randomY }));
    }
}

void Game::shoot()
{
    if (itsBullet == nullptr)
    {
        int newX = itsPlayer->getItsPosition().posX + (itsBoard.width() / BOARD_WIDTH) / 2 - BULLET_SIZE / 2;
        int newY = itsPlayer->getItsPosition().posY;
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
                (*it)->damage();
                if ((*it)->getItsState() <= 0)
                {
                    itsScore += 4;
                    Mushroom* toDelete = *it;
                    itsMushrooms->erase(it);
                    delete toDelete;
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
                itsPlayer->setItsPosition({ itsBoard.x() + itsBoard.width()/2 - PLAYER_SIZE/2, itsBoard.y() + itsBoard.height() - PLAYER_SIZE - 2});
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
    // Check if the hitted part is the head
    if (hittedPart->getItsParent() != nullptr)
    {
        // Cut the hitted centipede
        hittedPart->getItsParent()->setItsChild(nullptr);

        // Check if the hitted part is NOT the tail
        if (hittedPart->getItsChild() != nullptr)
        {
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

        // Add a new mushroom at the position of the hitted part
        int posX = hittedPart->getItsPosition().posX - (hittedPart->getItsPosition().posX - itsBoard.x()) % (itsBoard.width() / BOARD_WIDTH);
        int posY = hittedPart->getItsPosition().posY - (hittedPart->getItsPosition().posY - itsBoard.y()) % (itsBoard.height() / BOARD_HEIGHT);
        int gridX = (posX - itsBoard.x()) / (itsBoard.width() / BOARD_WIDTH);
        int gridY = (posY - itsBoard.y()) / (itsBoard.height() / BOARD_HEIGHT);

        cout << " ---- CENTIPEDE  SLICED ----" << endl
             << "Hitted part pos: (" << hittedPart->getItsPosition().posX << ", " << hittedPart->getItsPosition().posY << ")" << endl
             << "Mushroom pos: (" << posX << ", " << posY << ")" << endl
             << "Mushroom grid pos: (" << gridX << ", " << gridY << ")" << endl
             << "Board pos: (" << itsBoard.x() << ", " << itsBoard.y() << ")" << endl
             << " ---------------------------" << endl;

        itsMushrooms->push_back(new Mushroom(posX, posY, itsBoard.width() / BOARD_WIDTH, { gridX, gridY }));

        // Deletion of the hitted part
        delete hittedPart;

        // Increase the score of 10
        itsScore += 10;
    }
    else // headshot
    {
        // Search the centipede that correspond to the hitted head
        for (vector<Centipede*>::iterator it = itsCentipedes->begin(); it < itsCentipedes->end(); it++)
        {
            Centipede * centipede = *it;
            if (centipede->getItsHead() == hittedPart)
            {
                // Store centipede to delete it and remove it from the vector
                Centipede* toDelete = *it;
                itsCentipedes->erase(it);

                // Generate a new mushroom at the position of the head of the centipede
                int posX = hittedPart->getItsPosition().posX - (hittedPart->getItsPosition().posX - itsBoard.x()) % (itsBoard.width() / BOARD_WIDTH);
                int posY = hittedPart->getItsPosition().posY - (hittedPart->getItsPosition().posY - itsBoard.y()) % (itsBoard.height() / BOARD_HEIGHT);
                int gridX = (posX - itsBoard.x()) / BOARD_WIDTH;
                int gridY = (posY - itsBoard.y()) / BOARD_HEIGHT;
                itsMushrooms->push_back(new Mushroom(posX, posY, itsBoard.width() / BOARD_WIDTH, { gridX, gridY }));

                delete toDelete;
                break;
            }
        }

        // Increase the score of 100
        itsScore += 100;
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

    // pour le tir aussi

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
    for (Centipede* centipede : *itsCentipedes)
    {
        // If the centipede has reached the bottom for the first time, change the zone to the player zone.
        if (zone == itsBoard && centipede->hasReachedBottom()) zone = itsPlayerZone;

        // Check for collisions with mushrooms and the game board.
        //bool first = centipedeMushroomCollision(centipede);
        //bool second = centipedeBoardCollision(centipede, zone);

        // -------------------

        BodyPart* centiHead = centipede->getItsHead();
        centiHead->updatePos();
        Position headPos = centiHead->getItsPosition();
        cout << "new head pos : (" << headPos.posX << ", " << headPos.posY <<
                ") [ break in (" << (headPos.posX - itsBoard.x()) % (itsBoard.width() / BOARD_WIDTH) << ", " <<
                (headPos.posY - itsBoard.y()) % (itsBoard.height() / BOARD_HEIGHT) << ") ] L: " << centipede->getWasMovingLeft() <<
                " - R: " << centipede->getWasMovingRight() << " - V: " << centipede->isVerticalDirection() << endl;
        if (((headPos.posX - itsBoard.x()) % (itsBoard.width() / BOARD_WIDTH) == 0) && ((headPos.posY - itsBoard.y()) % (itsBoard.height() / BOARD_HEIGHT) == 0))
        {
            if (centipede->isVerticalDirection())
            {
                if (!centipedeBoardCollision(centipede, zone))
                {
                    if (centipede->getWasMovingRight())
                    {
                        centipede->setItsDirection({ -1, 0 });
                        centipede->setWasMovingRight(false);
                    }
                    else if (centipede->getWasMovingLeft())
                    {
                        centipede->setItsDirection({ 1, 0 });
                        centipede->setWasMovingLeft(false);
                    }
                    centipede->setVerticalDirection(false);
                }
            }

            centipedeBoardCollision(centipede, zone);
            if (centipedeMushroomCollision(centipede)) centipedeMushroomCollision(centipede);

            cout << "< " << centipede->getItsDirection().dirX << " | " << centipede->getItsDirection().dirY << " >" << endl;
            centiHead->setItsTargetPos({ headPos.posX + centipede->getItsDirection().dirX * CENTIPEDE_BODYPART_SIZE,
                                         headPos.posY + centipede->getItsDirection().dirY * CENTIPEDE_BODYPART_SIZE});
        }

        BodyPart* prevBP = centiHead;
        for (BodyPart* bp = centiHead->getItsChild(); bp != nullptr; bp = bp->getItsChild())
        {
            bp->updatePos();
            Position bpPos = bp->getItsPosition();
            if (((bpPos.posX - itsBoard.x()) % (itsBoard.width() / BOARD_WIDTH) == 0) &&
                ((bpPos.posY - itsBoard.y()) % (itsBoard.height() / BOARD_HEIGHT) == 0))
            {
                bp->setItsTargetPos(prevBP->getItsPosition());
            }
            prevBP = bp;
        }
    }
}


bool Game::centipedeBoardCollision(Centipede * centipede, QRect board)
{
    QRect headNextHitBox = { centipede->getItsHead()->getNextTarget(centipede->getItsDirection(), (itsBoard.width() / BOARD_WIDTH)).posX,
                            centipede->getItsHead()->getNextTarget(centipede->getItsDirection(), (itsBoard.width() / BOARD_WIDTH)).posY,
                            CENTIPEDE_BODYPART_SIZE, CENTIPEDE_BODYPART_SIZE };

    if (headNextHitBox.x() < board.x()) // left side of the board
    {
        if (!centipede->hasReachedBottom())
        {
            centipede->setItsDirection({0, 1}); // Go down
        }
        else
        {
            centipede->setItsDirection({0, -1}); // Go up
        }
        centipede->setVerticalDirection(true);
        centipede->setWasMovingLeft(true);
        return true;
    }
    else if (headNextHitBox.x() + headNextHitBox.width() > board.x() + board.width()) // right side of the board
    {
        if (!centipede->hasReachedBottom())
        {
            centipede->setItsDirection({0, 1}); // Go down
        }
        else
        {
            centipede->setItsDirection({0, -1}); // Go up
        }
        centipede->setVerticalDirection(true);
        centipede->setWasMovingRight(true);
        return true;
    }
    else if (centipede->isVerticalDirection())
    {
        if (headNextHitBox.y() <= board.y()) // top of the board
        {
            centipede->setItsDirection({0, 1}); // Go down
            centipede->setHasReachedBottom(false);
            return true;
        }
        else if (headNextHitBox.y() + headNextHitBox.height() >= board.y() + board.height()) // bottom of the board
        {
            centipede->setItsDirection({0, 1}); // Go down
            centipede->setHasReachedBottom(true);
            return true;
        }
    }
    return false;
}

bool Game::centipedeMushroomCollision(Centipede * centipede)
{
    QRect headNextHitBox = { centipede->getItsHead()->getNextTarget(centipede->getItsDirection(), (itsBoard.width() / BOARD_WIDTH)).posX,
                            centipede->getItsHead()->getNextTarget(centipede->getItsDirection(), (itsBoard.width() / BOARD_WIDTH)).posY,
                            CENTIPEDE_BODYPART_SIZE, CENTIPEDE_BODYPART_SIZE };
    for(vector<Mushroom*>::iterator it = getItsMushrooms()->begin(); it != itsMushrooms->end(); ++it)
    {
        if (isColliding(headNextHitBox, (*it)->getItsHitBox()))
        {
            if (centipede->isVerticalDirection())
            {
                Mushroom* toDelete = *it;
                itsMushrooms->erase(it);
                delete toDelete;
                return false;
            }
            else
            {
                if (centipede->getItsDirection().dirX == -1) centipede->setWasMovingLeft(true);
                else if (centipede->getItsDirection().dirX == 1) centipede->setWasMovingRight(true);

                if (!centipede->hasReachedBottom())
                {
                    centipede->setItsDirection({0, 1}); // Go down
                }
                else
                {
                    centipede->setItsDirection({0, -1}); // Go up
                }
                centipede->setVerticalDirection(true);
                return true;
            }
        }
    }
    return false;
}
