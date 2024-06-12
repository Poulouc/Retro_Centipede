#include <QRect>
#include "typeDef.h"
#include "mushroom.h"

#ifndef BULLET_H
#define BULLET_H

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
    vector<Mushroom*> itsHitMushrooms = {}; /**< Mushrooms the bullet hit during its lifetime */

public:
    /**
     * @brief Constructor for the Bullet class.
     * @param x The x-coordinate of the bullet's initial position.
     * @param y The y-coordinate of the bullet's initial position.
     */
    Bullet(int x, int y, int size);

    /**
     * @brief Destructor for the Bullet class.
     */
    ~Bullet();

    /**
     * @brief Updates the position of the bullet.
     */
    void updatePos();

    /**
     * @brief Gets the hitbox of the bullet.
     * @return The hitbox of the bullet.
     */
    QRect getItsHitBox();

    /**
     * @brief Gets the position of the bullet.
     * @return The position of the bullet.
     */
    Position getItsPosition();


    /**
     * @brief Sets the position of the bullet.
     */
    void setItsPosition(Position position);

    /**
     * @brief Sets the hitbox of the bullet.
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
