/**
 * @file centipede.h
 * @brief Defines the Centipede class, which represents a centipede entity in a game.
 */

#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include "bodypart.h"

/**
 * @brief The Centipede class represents a centipede entity in a game.
 */
class Centipede
{
private:
    BodyPart* itsHead; /**< Pointer to the head of the centipede. */
    BodyPart* itsTail; /**< Pointer to the tail of the centipede. */
    Direction itsDirection; /**< Direction of movement for the centipede. */
    bool isGoingDown = false; /**< Flag indicating whether the centipede is moving down. */
    bool reachedBottom = false; /**< Flag indicating whether the centipede has reached the bottom of the screen. */

public:
    /**
     * @brief Constructs a new Centipede object.
     * @param head Pointer to the head BodyPart of the centipede.
     */
    Centipede(BodyPart* head = new BodyPart());

    /**
     * @brief Destroys the Centipede object.
     */
    ~Centipede();

    /**
     * @brief Moves the centipede forward by a specified distance.
     * @param distance The distance to move the centipede forward.
     */
    void moveForward(int distance);

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
     * @brief Gets the vertical direction of movement for the centipede.
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
};

#endif // CENTIPEDE_H
