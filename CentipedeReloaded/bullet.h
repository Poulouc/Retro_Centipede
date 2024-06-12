/**
 * @file bullet.h
 * @brief Defines the Bullet class, which represents a bullet in the game.
 */

#ifndef BULLET_H
#define BULLET_H

#include <QRect>
#include "typeDef.h"
#include "mushroom.h"

/**
 * @class Bullet
 * @brief Represents a bullet in the game.
 *
 * The Bullet class manages the properties and behavior of a bullet, including its position and hitbox.
 */
class Bullet
{
private:
    QRect itsHitBox; /**< Rectangle representing the hitbox of the bullet */
    Position itsPosition; /**< Position of the bullet */
    std::vector<Mushroom*> itsHitMushrooms = {}; /**< Mushrooms the bullet hit during its lifetime */

public:
    /**
     * @brief Constructor for the Bullet class.
     * @param x The x-coordinate of the bullet's initial position.
     * @param y The y-coordinate of the bullet's initial position.
     * @param size The size of the bullet.
     */
    Bullet(int x, int y, int size);

    /**
     * @brief Destructor for the Bullet class.
     */
    ~Bullet();

    /**
     * @brief Updates the position of the bullet.
     *
     * This function updates the position of the bullet based on its current direction and speed.
     */
    void updatePos();

    /**
     * @brief Gets the hitbox of the bullet.
     * @return The hitbox of the bullet as a QRect.
     */
    QRect getItsHitBox();

    /**
     * @brief Gets the position of the bullet.
     * @return The position of the bullet as a Position struct.
     */
    Position getItsPosition();


    /**
     * @brief Sets the position of the bullet.
     * @param position The new position of the bullet.
     */
    void setItsPosition(Position position);

    /**
     * @brief Sets the hitbox of the bullet.
     * @param hitbox The new hitbox of the bullet.
     */
    void setItsHitBox(QRect hitbox);


    /**
     * @brief Indicates wether a given mushroom was already hit by the bullet during its lifetime.
     * @param mushroom The mushroom to check.
     * @return True if the mushroom was already hit, otherwise false.
     */
    bool wasMushroomAlreadyHit(Mushroom* mushroom);
};

#endif // BULLET_H
