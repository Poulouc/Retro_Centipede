#include <random>
#include "game.h"

#include <iostream>

using namespace std;

void headLog(Centipede* centipede, Position newPos, BodyPart* head, QRect board)
{
    cout << "new head pos : (" << newPos.posX << ", " << newPos.posY <<
            ") [ break in (" << (newPos.posX - board.x()) % (board.width() / BOARD_WIDTH) << ", " <<
            (newPos.posY - board.y()) % (board.height() / BOARD_HEIGHT) << ") ] L: " << centipede->getWasMovingLeft() <<
            " - R: " << centipede->getWasMovingRight() << " - V: " << centipede->isVerticalDirection() << " | size: " <<
            head->getItsHitBox().width() << ", " << head->getItsHitBox().height() << endl;
}

void targetLog(Centipede* centipede)
{
    cout << "Targets of centipede:" << endl;
    int i = 0;
    for (BodyPart* actualPart = centipede->getItsHead(); actualPart != nullptr; actualPart = actualPart->getItsChild())
    {
        i++;
        Position targetPos = actualPart->getItsTarget();
        cout << "  " << i << ": (" << targetPos.posX << ", " << targetPos.posY << ")" << endl;
    }
}

Game::Game(QRect board)
    :itsScore(0), itsCentipedes(new vector<Centipede*>), itsMushrooms(new vector<Mushroom*>), itsPowerups({}), itsBullets({}),
    itsPlayer(new Player({board.x() + board.width()/2 - (board.width() / BOARD_WIDTH)/2, board.y() + board.height() - (board.width() / BOARD_WIDTH) - 1}, board.width() / BOARD_WIDTH)),
    itsBoard(board), itsPlayerZone(board.x(), board.y() + (4 * board.height()) / 5, board.width(), board.height() / 5), itsCentipedeZone(board),
    treatedCentipedes(new vector<Centipede*>), itsSpider(nullptr)
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

    // Deletion of powerups
    for(PowerUp* powerup : itsPowerups)
    {
        delete powerup;
    }

    // Deletion of bullets
    for(Bullet* bullet : itsBullets)
    {
        delete bullet;
    }

    // Deletion of the player
    delete itsPlayer;
    if(itsSpider != nullptr)
    {
        delete itsSpider;
    }
}

void Game::spawnCentipede()
{
    Centipede * newCentipede = new Centipede(new BodyPart(itsBoard.width() / BOARD_WIDTH));
    BodyPart * currentPart = newCentipede->getItsHead();
    Position newPos;
    Position oldPos;

    newPos.posX = itsBoard.x() + CENTIPEDE_SPAWN_XPOS * (itsBoard.width() / BOARD_WIDTH);
    newPos.posY = itsBoard.y() + CENTIPEDE_SPAWN_YPOS * (itsBoard.height() / BOARD_HEIGHT);
    currentPart->setItsPosition(newPos);

    oldPos.posX = newPos.posX - (itsBoard.width() / BOARD_WIDTH);
    oldPos.posY = newPos.posY;
    currentPart->setItsTargetPos(oldPos);

    newCentipede->setItsDirection({ -1, 0 });
    for(int i = 0; i < CENTIPEDE_LENGTH - 1; i++)
    {
        BodyPart * newPart = new BodyPart(itsBoard.width() / BOARD_WIDTH);
        oldPos.posX = newPos.posX;
        newPos.posX = newPos.posX + (itsBoard.width() / BOARD_WIDTH);
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
    uniform_int_distribution<int> randY(1, 31 - 1);

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
        for(Bullet* bullet : itsBullets)
        {
            if (isColliding(previewHitbox, bullet->getItsHitBox())) continue;
        }

        // Create the mushroom, must be executed only if the position is valid
        itsMushrooms->push_back(new Mushroom(genX, genY, mushroomSize, { randomX, randomY }));
    }
}

void Game::shoot()
{
    if (itsBullets.empty() || isRafaleActive)
    {
        int bulletSize = itsBoard.width()/100;
        int newX = itsPlayer->getItsPosition().posX + (itsBoard.width() / BOARD_WIDTH) / 2 - bulletSize / 2;
        int newY = itsPlayer->getItsPosition().posY;
        itsBullets.push_back(new Bullet(newX, newY, bulletSize));
    }
}

void Game::moveBullets()
{
    vector<vector<Bullet*>::iterator> toDelete = {};
    for(vector<Bullet*>::iterator it = itsBullets.begin(); it != itsBullets.end(); ++it)
    {
        Bullet* bullet = *it;
        bullet->updatePos();
        //If the bullet left the board
        if(bullet->getItsPosition().posY < itsBoard.y())
        {
            toDelete.push_back(it);
        }
    }
    for(vector<Bullet*>::iterator it : toDelete)
    {
        Bullet* bullet = *it;
        itsBullets.erase(it);
        delete bullet;
    }
}

void Game::movePowerUps()
{
    vector<vector<PowerUp*>::iterator> toDelete;
    for(vector<PowerUp*>::iterator it = itsPowerups.begin(); it != itsPowerups.end(); ++it)
    {
        PowerUp* powerup = *it;
        if(powerup->getItsPosition().posY - powerup->getItsHitbox().height()*4 - 1 > itsBoard.width())
        {
            toDelete.push_back(it);
            delete powerup;
        }
        else
        {
            Position currentPos = powerup->getItsPosition();
            powerup->setItsPosition({currentPos.posX, currentPos.posY + 1});
        }
    }
    for(vector<PowerUp*>::iterator it : toDelete)
    {
        itsPowerups.erase(it);
    }
    toDelete.clear();
}

bool Game::isColliding(QRect hitbox1, QRect hitbox2)
{
    return hitbox1.intersects(hitbox2);
}

bool Game::isLevelWon()
{
    if (itsCentipedes->size() <= 0)
        {
            itsCurrentLevel++;
            return true;
        }
    return false;
}

bool Game::isGameLosed()
{
    return itsPlayer->getItsHp() <= 0;
}

void Game::checkCollisions()
{
    vector<vector<Bullet*>::iterator> toDelete;
    for(vector<Bullet*>::iterator bit = itsBullets.begin(); bit != itsBullets.end(); ++bit)
    {
        Bullet* bullet = *bit;
        for (vector<Mushroom*>::iterator mit = itsMushrooms->begin(); mit < itsMushrooms->end(); mit++) // checks if the bullet touches a mushroom
        {
            if (isColliding((*mit)->getItsHitBox(), bullet->getItsHitBox()))
            {
                (*mit)->damage();
                if ((*mit)->getItsState() <= 0)
                {
                    itsScore += 4;
                    Mushroom* mushroom = *mit;

                    random_device rd;
                    default_random_engine eng(rd());
                    uniform_int_distribution<unsigned int> distr(1, 100);
                    if(distr(eng) > (100-POWERUP_DROPRATE))
                    {
                        uniform_int_distribution<unsigned int> typeDistr(0,2);
                        PowerUp* newPowerup = new PowerUp((powerupType)typeDistr(eng)); // selects a random powerup
                        int powerupWidth = itsBoard.width()/60;
                        newPowerup->setItsHitbox({0, 0, powerupWidth, powerupWidth});
                        int caseSize = itsBoard.width()/BOARD_WIDTH;
                        int xPos = itsBoard.x() + mushroom->getItsGridPosition().posX * caseSize;
                        int yPos = itsBoard.y() + mushroom->getItsGridPosition().posY * caseSize;
                        newPowerup->setItsPosition({xPos + caseSize/2 - powerupWidth/2, yPos + caseSize/2 - powerupWidth/2});
                        itsPowerups.push_back(newPowerup);
                    }

                    itsMushrooms->erase(mit);
                    delete mushroom;
                }
                if(!isPiercingActive) toDelete.push_back(bit);
                break;
            }
        }
    }
    for(vector<Bullet*>::iterator it : toDelete)
    {
        Bullet* bullet = *it;
        itsBullets.erase(it);
        delete bullet;
    }

    for(vector<PowerUp*>::iterator it = itsPowerups.begin(); it != itsPowerups.end(); ++it)
    {
        PowerUp* powerup = *it;
        if(isColliding(powerup->getItsHitbox(), itsPlayer->getItsHitBox())) // the player takes the powerup
        {
            switch(powerup->getItsType())
            {
            case rafale:
                isRafaleActive = true;
                break;
            case transpercant:
                isPiercingActive = true;
                break;
            case herbicide:
                break;
            }
            itsPowerups.erase(it);
            delete powerup;
            break;
        }
    }

    for(vector<Bullet*>::iterator it = itsBullets.begin(); it != itsBullets.end(); ++it)
    {
        Bullet* bullet = *it;
        if (itsSpider != nullptr and isColliding(itsSpider->getItsHitBox(), bullet->getItsHitBox()))
        {
            delete itsSpider;
            itsSpider = nullptr;
            itsScore += 300;
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
                //set the position of the player
                itsPlayer->setItsPosition({itsPlayerZone.x() + itsPlayerZone.width()/2 - (itsBoard.width() / BOARD_WIDTH)/2,
                                           itsPlayerZone.y() + itsPlayerZone.height() - (itsBoard.height() / BOARD_HEIGHT) - itsPlayerZone.height()/20});
                itsPlayer->updatePos({0,0});
                spawnCentipede();
                return;
            }

            for(vector<Bullet*>::iterator bit = itsBullets.begin(); bit != itsBullets.end(); ++bit)
            {
                Bullet* bullet = *bit;
                if (isColliding(centiPart->getItsHitBox(), bullet->getItsHitBox())) // centipede hit
                {
                    BodyPart * newTail = centiPart->getItsParent();
                    sliceCentipede(centiPart, centipede);
                    centipede->setItsTail(newTail);
                    if(!isPiercingActive)
                    {
                        itsBullets.erase(bit);
                        delete bullet;
                    }
                    return;
                }
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
                int gridX = (posX - itsBoard.x()) / (itsBoard.width() / BOARD_WIDTH);
                int gridY = (posY - itsBoard.y()) / (itsBoard.height() / BOARD_HEIGHT);
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

vector<Bullet*> Game::getItsBullets()
{
    return itsBullets;
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

int Game::getCurrentLevel()
{
    return itsCurrentLevel;
}

std::vector<PowerUp*> Game::getItsPowerups()
{
    return itsPowerups;
}

bool Game::getIsRafaleActive()
{
    return isRafaleActive;
}

bool Game::getIsPiercingActive()
{
    return isPiercingActive;
}

void Game::setIsRafaleActive(bool isActive)
{
    isRafaleActive = isActive;
}

void Game::setIsPiercingActive(bool isActive)
{
    isPiercingActive = isActive;
}

void Game::setBoard(QRect board)
{
    // Set the size of a single cell of the board
    int cellWidth = board.width() / BOARD_WIDTH;
    int cellHeight = board.height() / BOARD_HEIGHT;

    for (vector<Mushroom*>::iterator it = itsMushrooms->begin(); it < itsMushrooms->end(); it++)
    {
        (*it)->setItsHitBox(QRect(board.x() + cellWidth * (*it)->getItsGridPosition().posX,
                                  board.y() + cellWidth * (*it)->getItsGridPosition().posY,
                                  cellWidth, cellHeight));
    }
    //set the playerZone
    itsPlayerZone = QRect(board.x(), board.y() + (4 * board.height()) / 5,
                          board.width(), board.height() / 5);

    //set the size of the player and the new placement on the board
    itsPlayer->setItsHitBox(QRect(itsPlayerZone.x() + itsPlayerZone.width()/2 - cellWidth/2,
                                  itsPlayerZone.y() + itsPlayerZone.height() - cellHeight - itsPlayerZone.height()/20,
                                  cellWidth, cellHeight));
    //set the position of the player
    itsPlayer->setItsPosition({itsPlayerZone.x() + itsPlayerZone.width()/2 - cellWidth/2,
                               itsPlayerZone.y() + itsPlayerZone.height() - cellHeight - itsPlayerZone.height()/20});

    //**
    // Update centipede segments for proportional resizing
    for (vector<Centipede*>::iterator it = itsCentipedes->begin(); it != itsCentipedes->end(); ++it)
    {
        for (BodyPart* currentPart = (*it)->getItsHead(); currentPart != nullptr; currentPart = currentPart->getItsChild())
        {
            // Calculate new proportional coordinates
            int newX = board.x() + ((currentPart->getItsHitBox().x() - itsBoard.x() + 0.5) * board.width()) / itsBoard.width();
            int newY = board.y() + ((currentPart->getItsHitBox().y() - itsBoard.y() + 0.5) * board.height()) / itsBoard.height();

            //int newX = board.x() + ((currentPart->getItsPosition().posX - itsBoard.x()) * cellWidth) / (itsBoard.width() / BOARD_WIDTH);
            //int newY = board.y() + ((currentPart->getItsPosition().posY - itsBoard.y()) * cellHeight) / (itsBoard.height() / BOARD_HEIGHT);

            int newTargetX = board.x() + ((currentPart->getItsTarget().posX - itsBoard.x()) * cellWidth) / (itsBoard.width() / BOARD_WIDTH);
            int newTargetY = board.y() + ((currentPart->getItsTarget().posY - itsBoard.y()) * cellHeight) / (itsBoard.height() / BOARD_HEIGHT);

            // Update the hitbox and position of the segment
            currentPart->setItsPosition({newX, newY});
            currentPart->setItsHitBox(QRect(newX, newY, cellWidth, cellHeight));
            currentPart->setItsTargetPos({ newTargetX, newTargetY });
        }
    }
    //**/

    //set the size of the spider
    if(itsSpider != nullptr)
    {
        // Calculate new proportional coordinates
        int newX = board.x() + ((itsSpider->getItsHitBox().x() - itsBoard.x() + 0.5) * board.width()) / itsBoard.width();
        int newY = board.y() + ((itsSpider->getItsHitBox().y() - itsBoard.y() + 0.5) * board.height()) / itsBoard.height();

        itsSpider->setItsHitBox({newX, newY, cellWidth, cellWidth});
    }

    if (itsCentipedeZone.height() == (itsBoard.height() / 5))
    {
        itsCentipedeZone = itsPlayerZone;
    }
    else itsCentipedeZone = itsBoard;

    // Set the new board as actual
    itsBoard = board;
}

// Moves the player based on the provided direction.
void Game::movePlayer(Direction & direction)
{
    bool willItTouch = false;
    QRect nextPos = {itsPlayer->getItsHitBox().x() + direction.dirX * PLAYER_SPEED, itsPlayer->getItsHitBox().y() + direction.dirY * PLAYER_SPEED, itsPlayer->getItsHitBox().width(), itsPlayer->getItsHitBox().height()};
    for (vector<Mushroom*>::iterator it = itsMushrooms->begin(); it < itsMushrooms->end(); it++)
    {
        if(isColliding(nextPos, (*it)->getItsHitBox())){
            willItTouch = true;
            break;
        }
    }

    // Check if the player can move horizontally within the player zone
    if (!willItTouch && itsPlayerZone.x() < itsPlayer->getItsHitBox().x() + direction.dirX * PLAYER_SPEED &&
        itsPlayerZone.x() + itsPlayerZone.width() > itsPlayer->getItsHitBox().x() + itsPlayer->getItsHitBox().width() + direction.dirX * PLAYER_SPEED
        && (direction.dirX == -PLAYER_SPEED or direction.dirX == PLAYER_SPEED))
    {
        // Update the player's position in the horizontal direction
        itsPlayer->updatePos({direction.dirX, 0});
    }
    // Check if the player can move vertically within the player zone
    if(!willItTouch && itsPlayerZone.y() < itsPlayer->getItsHitBox().y() + direction.dirY * PLAYER_SPEED &&
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
    // Iterate through each centipede in the game.
    for (Centipede* centipede : *itsCentipedes)
    {
        bool alreadyTreated = false;
        for (vector<Centipede*>::iterator it = treatedCentipedes->begin(); it < treatedCentipedes->end(); it++)
        {
            if (centipede == (*it))
            {
                alreadyTreated = true;
                break;
            }
        }
        if (alreadyTreated) continue;

        // If the centipede has reached the bottom for the first time, change the zone to the player zone.
        if (itsCentipedeZone == itsBoard && centipede->hasReachedBottom()) itsCentipedeZone = itsPlayerZone;

        BodyPart* centiHead = centipede->getItsHead();
        centiHead->updatePos();

        Position headPos = centiHead->getItsPosition();

        //cout << "new head pos : (" << headPos.posX << ", " << headPos.posY <<
        //    ") [ break in (" << (headPos.posX - itsBoard.x()) % (itsBoard.width() / BOARD_WIDTH) << ", " <<
        //    (headPos.posY - itsBoard.y()) % (itsBoard.height() / BOARD_HEIGHT) << ") ] L: " << centipede->getWasMovingLeft() <<
        //        " - R: " << centipede->getWasMovingRight() << " - V: " << centipede->isVerticalDirection() << " | size: " <<
        //        centiHead->getItsHitBox().width() << ", " << centiHead->getItsHitBox().height() << endl;

        headLog(centipede, headPos, centiHead, itsBoard);
        //targetLog(centipede);

        if (((headPos.posX - itsBoard.x()) % (itsBoard.width() / BOARD_WIDTH) == 0) && ((headPos.posY - itsBoard.y()) % (itsBoard.height() / BOARD_HEIGHT) == 0))
        {
            if (centipede->isVerticalDirection())
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

            centipedeToCentipedeCollision(centipede);
            if (centipedeBoardCollision(centipede, itsCentipedeZone)) centipedeBoardCollision(centipede, itsCentipedeZone);
            if (centipedeMushroomCollision(centipede)) centipedeMushroomCollision(centipede);

            centiHead->setItsTargetPos({ headPos.posX + centipede->getItsDirection().dirX * (itsBoard.width() / BOARD_WIDTH),
                                         headPos.posY + centipede->getItsDirection().dirY * (itsBoard.width() / BOARD_WIDTH)});
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

        treatedCentipedes->push_back(centipede);
    }
    treatedCentipedes->clear();
}


bool Game::centipedeBoardCollision(Centipede * centipede, QRect board)
{
    QRect headNextHitBox = { centipede->getItsHead()->getNextTarget(centipede->getItsDirection(), (itsBoard.width() / BOARD_WIDTH)).posX,
                            centipede->getItsHead()->getNextTarget(centipede->getItsDirection(), (itsBoard.width() / BOARD_WIDTH)).posY,
                            (itsBoard.width() / BOARD_WIDTH), (itsBoard.height() / BOARD_HEIGHT) };

    if (centipede->isVerticalDirection())
    {
        if (headNextHitBox.y() <= board.y()) // top of the board
        {
            centipede->setItsDirection({0, 1}); // Go down
            centipede->setHasReachedBottom(false);
            return true;
        }
        else if (headNextHitBox.y() + headNextHitBox.height() >= board.y() + board.height()) // bottom of the board
        {
            centipede->setItsDirection({0, -1}); // Go up
            centipede->setHasReachedBottom(true);
            return true;
        }
    }
    else if (headNextHitBox.x() < board.x()) // left side of the board
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
    return false;
}

bool Game::centipedeMushroomCollision(Centipede * centipede)
{
    QRect headNextHitBox = { centipede->getItsHead()->getNextTarget(centipede->getItsDirection(), (itsBoard.width() / BOARD_WIDTH)).posX,
                            centipede->getItsHead()->getNextTarget(centipede->getItsDirection(), (itsBoard.width() / BOARD_WIDTH)).posY,
                            (itsBoard.width() / BOARD_WIDTH), (itsBoard.height() / BOARD_HEIGHT) };
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

bool Game::centipedeToCentipedeCollision(Centipede * centipede)
{
    for (vector<Centipede*>::iterator it = itsCentipedes->begin(); it < itsCentipedes->end(); it++)
    {
        Centipede* currentCenti = *it;
        if (currentCenti != centipede)
        {
            QRect headNextHitBox = { centipede->getItsHead()->getNextTarget(centipede->getItsDirection(), (itsBoard.width() / BOARD_WIDTH)).posX,
                                    centipede->getItsHead()->getNextTarget(centipede->getItsDirection(), (itsBoard.width() / BOARD_WIDTH)).posY,
                                    (itsBoard.width() / BOARD_WIDTH), (itsBoard.height() / BOARD_HEIGHT) };

            if (isColliding(/*centipede->getItsHead()->getItsHitBox()*/ headNextHitBox, currentCenti->getItsHead()->getItsHitBox()))
            {
                if (!centipede->isVerticalDirection() && centipede->getItsDirection().dirX == -currentCenti->getItsDirection().dirX)
                {
                    BodyPart* prevBP = currentCenti->getItsHead();
                    prevBP->updatePos();

                    for (Centipede* centi: { centipede, currentCenti })
                    {
                        if (centi->getItsDirection().dirX == -1) centi->setWasMovingLeft(true);
                        else if (centi->getItsDirection().dirX == 1) centi->setWasMovingRight(true);
                        centi->setItsDirection({ 0, 1 });
                        centipedeBoardCollision(centi, itsCentipedeZone);
                        centi->setVerticalDirection(true);
                    }

                    prevBP->setItsTargetPos({ prevBP->getItsPosition().posX + centipede->getItsDirection().dirX * (itsBoard.width() / BOARD_WIDTH),
                                              prevBP->getItsPosition().posY + centipede->getItsDirection().dirY * (itsBoard.height() / BOARD_HEIGHT)});

                    for (BodyPart* bp = prevBP->getItsChild(); bp != nullptr; bp = bp->getItsChild())
                    {
                        bp->updatePos();
                        bp->setItsTargetPos(prevBP->getItsPosition());
                    }

                    treatedCentipedes->push_back(currentCenti);
                }
                return true;
            }
        }
    }
    return false;
}

void Game::createSpider()
{
    itsSpider = new Spider(itsBoard.x() + 10,itsPlayer->getItsHitBox().y(), itsBoard.width()/BOARD_WIDTH);
    itsSpider->setItsDirection({1, 1});
}

Spider* Game::getItsSpider()
{
    return itsSpider;
}

void Game::moveSpider()
{
    //the next position of the spider
    QRect nextPos = {itsSpider->getItsHitBox().x() + itsSpider->getItsDirection().dirX * SPIDER_SPEED,
                     itsSpider->getItsHitBox().y() + itsSpider->getItsDirection().dirY * SPIDER_SPEED,
                     itsSpider->getItsHitBox().width(),
                     itsSpider->getItsHitBox().height()};

    // Collision with the sides of the PlayerZone
    if (nextPos.left() <= itsPlayerZone.left() || nextPos.right() >= itsPlayerZone.right())
    {
        if (rand() % 100 < 40)//The spider have 40% of chance to disappear of the PlayerZone when she touche the side of it
        {
            delete itsSpider;
            itsSpider = nullptr;
            return;
        }
        itsSpider->setItsHorizontaleDirection(-(itsSpider->getItsHorizontaleDirection()));
        itsSpider->setItsDirection({-itsSpider->getItsDirection().dirX, itsSpider->getItsDirection().dirY});
    }
    //Collision with the top of PlayerZone
    else if (nextPos.top() <= itsPlayerZone.top())
    {
        itsSpider->setItsDirection({itsSpider->getItsHorizontaleDirection(), -itsSpider->getItsDirection().dirY});
    }
    //Collision with the bottom of PlayerZone
    else if(nextPos.bottom() >= itsPlayerZone.bottom())
    {
        itsSpider->setItsHorizontaleDirection(itsSpider->getItsDirection().dirX);
        itsSpider->setItsDirection({0, -itsSpider->getItsDirection().dirY});
    }

    // Interaction with the mushroomms
    for (vector<Mushroom*>::iterator it = itsMushrooms->begin(); it < itsMushrooms->end(); it++)
    {
        //check if the mushroom is marked
        int isMarked = itsMarkedMushroom.size();
        for (int i = 0; i < itsMarkedMushroom.size(); i++)
        {
            if ((itsMarkedMushroom)[i] == (*it))
            {
                isMarked = i;
                break;
            }
        }
        //if the mushroom is not marked and if the spider touch the mushroom
        if (isMarked == itsMarkedMushroom.size() and nextPos.intersects((*it)->getItsHitBox()))
        {
            itsMarkedMushroom.push_back((*it)); // add the mushroom in the list of mushrooms tested
            if ((rand() % 100) < 50)
            {
                Mushroom* toDelete = (*it);
                itsMushrooms->erase(it);
                itsMarkedMushroom.erase(itsMarkedMushroom.begin() + isMarked);
                delete toDelete;
                break;
            }
        }
        // Check if the spider is no more on the mushroom
        if (isMarked != itsMarkedMushroom.size() and !nextPos.intersects((*it)->getItsHitBox()))
        {
            // Unmark the mushroom
            itsMarkedMushroom.erase(itsMarkedMushroom.begin() + isMarked);
        }
    }


    //check the collision between the player and the spider
    if(itsSpider->getItsHitBox().intersects(itsPlayer->getItsHitBox())){
        //remove one life
        itsPlayer->hit();
        //delete the centipede
        for (vector<Centipede*>::iterator itDel = itsCentipedes->begin(); itDel != itsCentipedes->end(); ++itDel)
        {
            delete *itDel;
        }
        itsCentipedes->clear();
        //set the position of the player
        itsPlayer->setItsPosition({itsPlayerZone.x() + itsPlayerZone.width()/2 - (itsBoard.width() / BOARD_WIDTH)/2,
                                   itsPlayerZone.y() + itsPlayerZone.height() - (itsBoard.height() / BOARD_HEIGHT) - itsPlayerZone.height()/20});
        itsPlayer->updatePos({0,0});
        //delete the spider
        delete itsSpider;
        itsSpider = nullptr;
        spawnCentipede();
        return;
    }

    // make the spider moving
    itsSpider->move();
}
