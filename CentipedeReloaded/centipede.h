/**
 * @file centipede.h
 * @brief Defines the Centipede class, which represents a centipede entity in a game.
 *
 * The Centipede class is used to model the behavior and movement of a centipede
 * within a game. It contains methods for manipulating the centipede's direction,
 * position, and state.
 */

#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include "bodypart.h"
#include "typeDef.h"

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
    bool wasMovingRight = false; /**< Flag indicating whether the centipede was moving right previously. */
    bool wasMovingLeft = false; /**< Flag indicating whether the centipede was moving left previously. */

public:
    /**
     * @brief Constructs a new Centipede object.
     * @param head Pointer to the head BodyPart of the centipede.
     *
     * This constructor initializes the centipede with its head BodyPart.
     */
    Centipede(BodyPart* head);

    /**
     * @brief Destroys the Centipede object.
     *
     * The destructor ensures that all dynamically allocated resources
     * are properly released.
     */
    ~Centipede();

    /**
     * @brief Gets a pointer to the head BodyPart of the centipede.
     * @return Pointer to the head BodyPart of the centipede.
     *
     * This method returns a pointer to the head BodyPart of the centipede.
     */
    BodyPart* getItsHead();

    /**
     * @brief Gets a pointer to the tail BodyPart of the centipede.
     * @return Pointer to the tail BodyPart of the centipede.
     *
     * This method returns a pointer to the tail BodyPart of the centipede.
     */
    BodyPart* getItsTail();

    /**
     * @brief Sets the tail BodyPart of the centipede.
     * @param tail Pointer to the tail BodyPart of the centipede.
     *
     * This method sets the tail BodyPart of the centipede.
     */
    void setItsTail(BodyPart* tail);

    /**
     * @brief Sets the direction of movement for the centipede.
     * @param dir The direction of movement for the centipede.
     *
     * This method sets the current direction of movement for the centipede.
     */
    void setItsDirection(Direction dir);

    /**
     * @brief Calculates the next position of the centipede based on the current direction and distance to move.
     * @param distance The distance to move the centipede.
     * @return The calculated next position of the centipede.
     *
     * This method calculates the next position of the centipede given a distance to move.
     */
    Position getNextPosition(int distance);

    /**
     * @brief Gets the direction of movement for the centipede.
     * @return The direction of movement for the centipede.
     *
     * This method returns the current direction of movement for the centipede.
     */
    Direction getItsDirection();

    /**
     * @brief Checks if the centipede has reached the bottom of the screen.
     * @return True if the centipede has reached the bottom of the screen, otherwise false.
     *
     * This method checks if the centipede has reached the bottom of the screen.
     */
    bool hasReachedBottom();

    /**
     * @brief Gets the vertical direction of movement for the centipede.
     * @return True if the centipede is moving down, otherwise false.
     *
     * This method checks if the centipede is currently moving down.
     */
    bool isVerticalDirection();

    /**
     * @brief Sets the vertical direction of movement for the centipede.
     * @param isCentipedeGoingDown True if the centipede is moving down, otherwise false.
     *
     * This method sets the flag indicating whether the centipede is moving down.
     */
    void setVerticalDirection(bool isCentipedeGoingDown);

    /**
     * @brief Sets the flag indicating whether the centipede has reached the bottom of the screen.
     * @param hasReachedBottom True if the centipede has reached the bottom, otherwise false.
     *
     * This method sets the flag indicating whether the centipede has reached the bottom of the screen.
     */
    void setHasReachedBottom(bool hasReachedBottom);

    /**
     * @brief Sets the flag indicating whether the centipede was moving right previously.
     * @param value True if the centipede was moving right, otherwise false.
     *
     * This method sets the flag indicating whether the centipede was moving right previously.
     */
    void setWasMovingRight(bool value);

    /**
     * @brief Sets the flag indicating whether the centipede was moving left previously.
     * @param value True if the centipede was moving left, otherwise false.
     *
     * This method sets the flag indicating whether the centipede was moving left previously.
     */
    void setWasMovingLeft(bool value);

    /**
     * @brief Gets the flag indicating whether the centipede was moving right previously.
     * @return True if the centipede was moving right, otherwise false.
     *
     * This method returns the flag indicating whether the centipede was moving right previously.
     */
    bool getWasMovingRight();

    /**
     * @brief Gets the flag indicating whether the centipede was moving left previously.
     * @return True if the centipede was moving left, otherwise false.
     *
     * This method returns the flag indicating whether the centipede was moving left previously.
     */
    bool getWasMovingLeft();
};

#endif // CENTIPEDE_H
