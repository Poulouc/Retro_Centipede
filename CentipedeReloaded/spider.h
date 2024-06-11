/**
 * @file spider.h
 * @brief Header file for the Spider class.
 */

#include <QRect>
#include "typeDef.h"

#ifndef SPIDER_H
#define SPIDER_H

/**
 * @class Spider
 * @brief Represents a spider in the game with a hitbox and movement capabilities.
 */
class Spider
{
private:
    QRect itsHitBox; ///< The hitbox of the spider.
    Direction itsDirection; ///< The current direction of the spider.
    int itsHorizontaleDirection; ///< The current horizontal direction value of the spider.

public:
    /**
     * @brief Constructs a Spider object with specified position and size.
     * @param x The x-coordinate of the spider's initial position.
     * @param y The y-coordinate of the spider's initial position.
     * @param size The size of the spider.
     */
    Spider(int x, int y, int size);

    /**
     * @brief Gets the hitbox of the spider.
     * @return The QRect representing the spider's hitbox.
     */
    QRect getItsHitBox();

    /**
     * @brief Sets the hitbox of the spider.
     * @param hitbox The QRect representing the new hitbox of the spider.
     */
    void setItsHitBox(QRect hitbox);

    /**
     * @brief Gets the current direction of the spider.
     * @return The Direction representing the spider's movement direction.
     */
    Direction getItsDirection();

    /**
     * @brief Sets the direction of the spider.
     * @param direction The Direction representing the new movement direction of the spider.
     */
    void setItsDirection(Direction direction);

    /**
     * @brief Gets the horizontal direction value of the spider.
     * @return An integer representing the horizontal direction.
     */
    int getItsHorizontaleDirection();

    /**
     * @brief Sets the horizontal direction value of the spider.
     * @param horizontalDirection An integer representing the new horizontal direction.
     */
    void setItsHorizontaleDirection(int horizontalDirection);

    /**
     * @brief Moves the spider based on its current direction and speed.
     */
    void move();
};

#endif // SPIDER_H
