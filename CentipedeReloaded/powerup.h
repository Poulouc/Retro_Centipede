/**
 * @file powerup.h
 * @brief Header file for the PowerUp class.
 */

#ifndef POWERUP_H
#define POWERUP_H

#include <QRect>    // Include header file for QRect class
#include "typeDef.h" // Include type definitions file

/**
 * @enum powerupType
 * @brief Enumeration representing different types of power-ups.
 */
enum powerupType {
    rafale,         /**< 'Rafale' power-up */
    transpercant,   /**< 'Transpercant' power-up */
    herbicide       /**< 'Herbicide' power-up */
};

/**
 * @class PowerUp
 * @brief Represents a power-up in the game with a hitbox and type.
 *
 * This class manages the position, hitbox, and type of power-ups within the game.
 */
class PowerUp {
private:
    powerupType itsType;    /**< The type of the power-up. */
    QRect itsHitBox;        /**< The hitbox of the power-up. */
    Position itsPos;        /**< The position of the power-up. */

public:
    /**
     * @brief Constructs a PowerUp object of a specified type.
     * @param type The type of the power-up.
     */
    PowerUp(powerupType type);

    /**
     * @brief Gets the position of the power-up.
     * @return The Position struct representing the power-up's position.
     */
    Position getItsPosition();

    /**
     * @brief Gets the hitbox of the power-up.
     * @return The QRect representing the power-up's hitbox.
     */
    QRect getItsHitbox();

    /**
     * @brief Gets the type of the power-up.
     * @return The powerupType enum representing the type of the power-up.
     */
    powerupType getItsType();

    /**
     * @brief Sets the position of the power-up.
     * @param newPos The new Position struct representing the power-up's position.
     */
    void setItsPosition(Position newPos);

    /**
     * @brief Sets the hitbox of the power-up.
     * @param newHitbox The new QRect representing the power-up's hitbox.
     */
    void setItsHitbox(QRect newHitbox);
};

#endif // POWERUP_H
