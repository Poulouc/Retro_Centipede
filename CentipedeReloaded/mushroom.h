/**
 * @file mushroom.h
 * @brief Defines the Mushroom class, which represents a mushroom in the game.
 */

#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <QRect>
#include "typeDef.h"

/**
 * @class Mushroom
 * @brief Class representing a mushroom in the game.
 */
class Mushroom
{
private:
    int itsState;                /**< The state of the mushroom */
    QRect itsHitBox;             /**< The hit box of the mushroom */
    Position itsGridPosition;    /**< The grid position of the mushroom */

public:
    /**
     * @brief Constructor for the Mushroom class.
     * @param x The x-coordinate of the mushroom.
     * @param y The y-coordinate of the mushroom.
     * @param size The size of the mushroom.
     * @param gridPosition The grid position of the mushroom.
     */
    Mushroom(int x, int y, int size, Position gridPosition);

    /**
     * @brief Destructor for the Mushroom class.
     */
    ~Mushroom();

    /**
     * @brief Damages the mushroom.
     */
    void damage();

    /**
     * @brief Gets the state of the mushroom.
     * @return The state of the mushroom.
     */
    int getItsState();

    /**
     * @brief Gets the hit box of the mushroom.
     * @return The hit box of the mushroom.
     */
    QRect getItsHitBox();

    /**
     * @brief Gets the grid position of the mushroom.
     * @return The grid position of the mushroom.
     */
    Position getItsGridPosition();

    /**
     * @brief Sets the hit box of the mushroom.
     * @param hitBox The new hit box of the mushroom.
     */
    void setItsHitBox(QRect hitBox);

    /**
     * @brief Sets the grid position of the mushroom.
     * @param position The new grid position of the mushroom.
     */
    void setItsGridPosition(Position position);
};

#endif // MUSHROOM_H
