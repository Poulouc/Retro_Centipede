/**
 * @file game.h
 * @brief Defines the Game class, which represents the game management.
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <QRect>
#include "bullet.h"
#include "centipede.h"
#include "mushroom.h"
#include "player.h"
#include "typeDef.h"
#include "powerup.h"
#include "spider.h"

/**
 * @class Game
 * @brief Class representing the game management.
 *
 * This class manages the main elements of the game such as centipedes, mushrooms, the player, and the interactions between them.
 */
class Game
{
private:
    int itsScore; /**< The game score */
    std::vector<Centipede*>* itsCentipedes; /**< Pointer to the vector of centipedes */
    std::vector<Mushroom*>* itsMushrooms; /**< Pointer to the vector of mushrooms */
    std::vector<PowerUp*> itsPowerups; /**< Vector containing all active powerups */
    std::vector<Bullet*> itsBullets; /**< Vector containing bullets */
    Player* itsPlayer; /**< Pointer to the player */
    QRect itsBoard; /**< Rectangle representing the game board */
    QRect itsPlayerZone; /**< Rectangle representing the player's zone */
    QRect itsCentipedeZone; /**< Rectangle representing the centipede's zone */
    std::vector<Centipede*>* treatedCentipedes; /**< Pointer to the vector of treated centipedes */
    int itsCurrentLevel = 1; /**< The current level */
    bool isRafaleActive = false; /**< Flag indicating wether the 'rafale' powerup is active */
    bool isPiercingActive = false; /**< Flag indicating wether the 'piercing' powerup is active */
    bool isHerbicideActive = false; /**< Flag indicating wether the 'herbicide' powerup is active */
    bool rafalePickedUpFlag = false; /**< Flag indicating wether the 'rafale' powerup has been picked up */
    bool piercingPickedUpFlag = false; /**< Flag indicating wether the 'piercing' powerup has been picked up */
    bool herbicidePickedUpFlag = false; /**< Flag indicating wether the 'herbicide' powerup has been picked up */
    Spider* itsSpider; /**< Pointer to the spider */
    std::vector<Mushroom*> itsMarkedMushroom; /**< Vector containing marked mushrooms */

public:
    /**
     * @brief Constructor for the Game class.
     * @param board Rectangle representing the game board.
     */
    Game(QRect board);

    /**
     * @brief Destructor for the Game class.
     */
    ~Game();

    /**
     * @brief Spawns a centipede.
     */
    void spawnCentipede();

    /**
     * @brief Creates mushrooms on the game board.
     */
    void createMushrooms();

    /**
     * @brief Shoots a bullet.
     */
    void shoot();

    /**
     * @brief Moves the bullets.
     */
    void moveBullets();

    /**
     * @brief Checks for collision between a mushroom and the player.
     * @param mushroom Pointer to the mushroom.
     * @param player Pointer to the player.
     * @return True if a collision is detected, otherwise false.
     */
    bool isColliding(Mushroom* mushroom, Player* player);

    /**
     * @brief Checks for collision between a mushroom and a bullet.
     * @param mushroom Pointer to the mushroom.
     * @param bullet Pointer to the bullet.
     * @return True if a collision is detected, otherwise false.
     */
    bool isColliding(Mushroom* mushroom, Bullet* bullet);

    /**
     * @brief Checks for collision between a centipede and a bullet.
     * @param centipede Pointer to the centipede.
     * @param bullet Pointer to the bullet.
     * @return True if a collision is detected, otherwise false.
     */
    bool isColliding(Centipede* centipede, Bullet* bullet);

    /**
     * @brief Checks for collision between a centipede and a mushroom.
     * @param centipede Pointer to the centipede.
     * @param mushroom Pointer to the mushroom.
     * @return True if a collision is detected, otherwise false.
     */
    bool isColliding(Centipede* centipede, Mushroom* mushroom);

    /**
     * @brief Checks for collision between two rectangles.
     * @param hitbox1 The first rectangle.
     * @param hitbox2 The second rectangle.
     * @return True if a collision is detected, otherwise false.
     */
    bool isColliding(QRect hitbox1, QRect hitbox2);

    /**
     * @brief Checks for and handles all collisions in the game.
     */
    void checkCollisions();

    /**
     * @brief Slices a centipede when hit.
     * @param hittedPart Pointer to the hit body part of the centipede.
     * @param centipede Pointer to the centipede hit.
     */
    void sliceCentipede(BodyPart* hittedPart, Centipede* centipede);

    /**
     * @brief Moves the player in a specified direction.
     * @param direction Reference to the direction of movement.
     */
    void movePlayer(Direction &direction);

    /**
     * @brief Moves powerups.
     */
    void movePowerUps();

    /**
     * @brief Gets the vector of centipedes.
     * @return Pointer to the vector of centipedes.
     */
    std::vector<Centipede*>* getItsCentipedes();

    /**
     * @brief Gets the vector of mushrooms.
     * @return Pointer to the vector of mushrooms.
     */
    std::vector<Mushroom*>* getItsMushrooms();

    /**
     * @brief Gets the bullet vector.
     * @return Vector containing all bullets.
     */
    std::vector<Bullet*> getItsBullets();

    /**
     * @brief Gets the player.
     * @return Pointer to the player.
     */
    Player* getItsPlayer();

    /**
     * @brief Gets the current game score.
     * @return The game score.
     */
    int getItsScore();

    /**
     * @brief Gets the game board rectangle.
     * @return The game board rectangle.
     */
    QRect getItsBoard();

    /**
     * @brief Gets the vector of powerups.
     * @return The vector containing all powerups.
     */
    std::vector<PowerUp*> getItsPowerups();

    /**
     * @brief Gets the current game level.
     * @return The current level of the game.
     */
    int getCurrentLevel();

    /**
     * @brief Sets the game board rectangle.
     * @param board The new game board rectangle.
     */
    void setBoard(QRect board);

    /**
     * @brief Checks for collision between a centipede and a mushroom.
     * @param centipede Pointer to the centipede.
     * @return True if a collision is detected, otherwise false.
     */
    bool centipedeMushroomCollision(Centipede* centipede);

    /**
     * @brief Manages collision between two centipedes.
     * @param centipede Pointer to the centipede.
     * @return True if there is a collision, otherwise false.
     */
    bool centipedeToCentipedeCollision(Centipede* centipede);

    /**
     * @brief Checks if the game has been won.
     * @return True if the game has been won, otherwise false.
     */
    bool isLevelWon();

    /**
     * @brief Checks if the game has been lost.
     * @return True if the game has been lost, otherwise false.
     */
    bool isGameLosed();

    /**
     * @brief Checks if the 'rafale' powerup is active.
     * @return True if the 'rafale' powerup is active, otherwise false.
     */
    bool getIsRafaleActive();

    /**
     * @brief Checks if the 'transpercant' powerup is active.
     * @return True if the 'transpercant' powerup is active, otherwise false.
     */
    bool getIsPiercingActive();

    /**
<<<<<<< HEAD
     * @brief Checks if the herbicide powerup is active.
     * @return True if the herbicide powerup is active, otherwise false.
     */
    bool getIsHerbicideActive();

    /**
     * @brief Checks if the rafale powerup was picked up.
     * @return True if the rafale powerup was picked up, otherwise false.
     */
    bool getRafalePickedUpFlag();

    /**
     * @brief Checks if the piercing powerup was picked up.
     * @return True if the piercing powerup was picked up, otherwise false.
     */
    bool getPiercingPickedUpFlag();

    /**
     * @brief Checks if the herbicide powerup was picked up.
     * @return True if the herbicide powerup was picked up, otherwise false.
     */
    bool getHerbicidePickedUpFlag();

    /**
     * @brief Sets the state of the rafalePickedUp flag.
     * @param state The new state of the flag.
     */
    void setRafalePickedUpFlag(bool state);

    /**
     * @brief Sets the state of the piercingPickedUp flag.
     * @param state The new state of the flag.
     */
    void setPiercingPickedUpFlag(bool state);

    /**
     * @brief Sets the state of the herbicidePickedUp flag.
     * @param state The new state of the flag.
     */
    void setHerbicidePickedUpFlag(bool state);

    /**
     * @brief Sets isRafaleActive to the given state.
     * @param isActive The state to set isRafaleActive to.
=======
     * @brief Sets the state of the 'rafale' powerup.
     * @param isActive The state to set for the 'rafale' powerup.
>>>>>>> V3
     */
    void setIsRafaleActive(bool isActive);

    /**
     * @brief Sets the state of the 'transpercant' powerup.
     * @param isActive The state to set for the 'transpercant' powerup.
     */
    void setIsPiercingActive(bool isActive);

    /**
     * @brief Sets isHerbicideActive to the given state.
     * @param isActive The state to set isHerbicideActive to.
     */
    void setIsHerbicideActive(bool isActive);

    /**
     * @brief Moves the centipede.
     */
    void moveCentipede();

    /**
     * @brief Checks for collision between a centipede and the game board.
     * @param centipede Pointer to the centipede.
     * @param board The game board rectangle.
     * @return True if a collision is detected, otherwise false.
     */
    bool centipedeBoardCollision(Centipede* centipede, QRect board);

    /**
     * @brief Creates a spider in the game.
     */
    void createSpider();

    /**
     * @brief Gets the spider in the game.
     * @return Pointer to the spider.
     */
    Spider* getItsSpider();

    /**
     * @brief Moves the spider in the game.
     */
    void moveSpider();
};

#endif // GAME_H
