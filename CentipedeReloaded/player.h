/**
 * @file player.h
 * @brief Defines the Player class, which represents the player in the game.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <QRect>
#include "typeDef.h"

/**
 * @class Player
 * @brief Class representing the player in the game.
 */
class Player
{
private:
    int itsHP; /**< The hit points of the player */
    QRect itsHitBox; /**< The hit box of the player */
    Position itsPosition; /**< The position of the player */

public:
    /**
     * @brief Constructor for the Player class.
     * @param position The initial position of the player.
     * @param size The size of the player.
     */
    Player(Position position, int size);

    /**
     * @brief Destructor for the Player class.
     */
    ~Player();

    /**
     * @brief Updates the position of the player based on the given direction.
     * @param direction The direction in which the player should move.
     */
    void updatePos(Direction direction);

    /**
     * @brief Decreases the hit points of the player when hit.
     */
    void hit();

    /**
     * @brief Gets the position of the player.
     * @return The position of the player.
     */
    Position getItsPosition();

    /**
     * @brief Gets the hit points of the player.
     * @return The hit points of the player.
     */
    int getItsHp();

    /**
     * @brief Gets the hit box of the player.
     * @return The hit box of the player.
     */
    QRect getItsHitBox();

    /**
     * @brief Sets the position of the player.
     * @param position The new position of the player.
     */
    void setItsPosition(Position position);

    /**
     * @brief Sets the hit box of the player.
     * @param hitBox The new hit box of the player.
     */
    void setItsHitBox(QRect hitBox);

    /**
     * @brief Sets the hit box of the player based on the given position.
     * @param position The new position of the player.
     */
    void setItsHitBox(Position position);
};

#endif // PLAYER_H
