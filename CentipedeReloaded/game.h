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
    Bullet* itsBullet; /**< Pointer to the bullet */
    Player* itsPlayer; /**< Pointer to the player */
    QRect itsBoard; /**< Rectangle representing the game board */
    QRect itsPlayerZone; /**< Rectangle representing the player's zone */
    QRect itsCentipedeZone;
    std::vector<Centipede*>* treatedCentipedes;
    bool updatingCenti = false;

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
     * @brief Moves the bullet.
     */
    void moveBullet();

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
     * @param centipede Pointer to the centiped hit.
     */
    void sliceCentipede(BodyPart* hittedPart, Centipede* centipede);

    /**
     * @brief Moves the player in a specified direction.
     * @param direction Reference to the direction of movement.
     */
    void movePlayer(Direction &direction);

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
     * @brief Gets the bullet.
     * @return Pointer to the bullet.
     */
    Bullet* getItsBullet();

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
     * @brief Sets the game board rectangle.
     * @param board The new game board rectangle.
     */
    void setBoard(QRect board);

    /**
     * @brief Checks for collision between a centipede and a mushroom.
     * @param centipede Pointer to the centipede.
     * @return True if a collision is detected, otherwise false.
     */
    bool centipedeMushroomCollision(Centipede * centipede);

    /**
     * @brief Manages collision between two centipedes
     * @param centipede Pointer to the centipede.
     * @return True if there is a collision, otherwise false.
     */
    bool centipedeToCentipedeCollision(Centipede * centipede);

    /**
     * @brief Checks if the game has been won.
     * @return True if the game has been won, otherwise false.
     */
    bool isGameWon();

    /**
     * @brief Checks if the game has been lost.
     * @return True if the game has been lost, otherwise false.
     */
    bool isGameLosed();

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
    bool centipedeBoardCollision(Centipede * centipede, QRect board);
};

#endif // GAME_H
