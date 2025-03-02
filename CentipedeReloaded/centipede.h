/**
 * @file centipede.h
 * @brief Defines the Centipede class, which represents a centipede entity in a game.
 */

#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include "bodypart.h"

/**
 * @class Centipede
 * @brief Represents a centipede entity in a game.
 *
 * This class manages the movement and characteristics of a centipede, including its head, tail,
 * movement direction, and state flags.
 */
class Centipede
{
private:
    BodyPart* itsHead; /**< Pointer to the head of the centipede. */
    BodyPart* itsTail; /**< Pointer to the tail of the centipede. */
    Direction itsDirection; /**< Direction of movement for the centipede. */
    bool isGoingDown = false; /**< Flag indicating whether the centipede is moving down. */
    bool reachedBottom = false; /**< Flag indicating whether the centipede has reached the bottom of the screen. */
    bool wasMovingRight = false; /**< Flag indicating whether the centipede was previously moving right. */
    bool wasMovingLeft = false; /**< Flag indicating whether the centipede was previously moving left. */

public:
    /**
     * @brief Constructs a new Centipede object.
     * @param head Pointer to the head BodyPart of the centipede.
     */
    Centipede(BodyPart* head);

    /**
     * @brief Destroys the Centipede object.
     */
    ~Centipede();

    /**
     * @brief Gets a pointer to the head BodyPart of the centipede.
     * @return Pointer to the head BodyPart of the centipede.
     */
    BodyPart* getItsHead();

    /**
     * @brief Gets a pointer to the tail BodyPart of the centipede.
     * @return Pointer to the tail BodyPart of the centipede.
     */
    BodyPart* getItsTail();

    /**
     * @brief Sets the tail BodyPart of the centipede.
     * @param tail Pointer to the tail BodyPart of the centipede.
     */
    void setItsTail(BodyPart* tail);

    /**
     * @brief Sets the direction of movement for the centipede.
     * @param dir The direction of movement for the centipede.
     */
    void setItsDirection(Direction dir);

    /**
     * @brief Calculates the next position of the centipede based on the current direction and distance to move.
     * @param distance The distance to move the centipede.
     * @return The calculated next position of the centipede.
     */
    Position getNextPosition(int distance);

    /**
     * @brief Gets the direction of movement for the centipede.
     * @return The direction of movement for the centipede.
     */
    Direction getItsDirection();

    /**
     * @brief Checks if the centipede has reached the bottom of the screen.
     * @return True if the centipede has reached the bottom of the screen, otherwise false.
     */
    bool hasReachedBottom();

    /**
     * @brief Checks if the centipede is moving in a vertical direction (up or down).
     * @return True if the centipede is moving down, otherwise false.
     */
    bool isVerticalDirection();

    /**
     * @brief Sets the vertical direction of movement for the centipede.
     * @param isCentipedeGoingDown True if the centipede is moving down, otherwise false.
     */
    void setVerticalDirection(bool isCentipedeGoingDown);

    /**
     * @brief Sets the flag indicating whether the centipede has reached the bottom of the screen.
     * @param hasReachedBottom True if the centipede has reached the bottom, otherwise false.
     */
    void setHasReachedBottom(bool hasReachedBottom);

    /**
     * @brief Sets the flag indicating whether the centipede was moving right.
     * @param value True if the centipede was moving right, otherwise false.
     */
    void setWasMovingRight(bool value);

    /**
     * @brief Sets the flag indicating whether the centipede was moving left.
     * @param value True if the centipede was moving left, otherwise false.
     */
    void setWasMovingLeft(bool value);

    /**
     * @brief Gets the flag indicating whether the centipede was moving right.
     * @return True if the centipede was moving right, otherwise false.
     */
    bool getWasMovingRight();

    /**
     * @brief Gets the flag indicating whether the centipede was moving left.
     * @return True if the centipede was moving left, otherwise false.
     */
    bool getWasMovingLeft();
};

#endif // CENTIPEDE_H
