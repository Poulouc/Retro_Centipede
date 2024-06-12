/**
 * @file bodypart.h
 * @brief Defines the BodyPart class, which represents a part of the centipede's body.
 */

#ifndef BODYPART_H
#define BODYPART_H

#include <QRect>
#include "typeDef.h"

/**
 * @class BodyPart
 * @brief Represents a part of the centipede's body.
 *
 * The BodyPart class manages the individual segments of the centipede, including their position, hitbox, and relationships to other segments.
 */
class BodyPart
{
private:
    BodyPart* itsParent = nullptr; /**< Pointer to the parent body part */
    BodyPart* itsChild = nullptr; /**< Pointer to the child body part */
    QRect itsHitBox; /**< Rectangle representing the hitbox */
    Position itsPosition = {}; /**< Position of the body part */
    Position itsTargetPos = {}; /**< Target position for movement */
    Position itsPreviousPosition = {}; /**< Previous position of the body part */

public:
    /**
     * @brief Constructor for the BodyPart class.
     * @param size The size of the body part.
     */
    BodyPart(int size);

    /**
     * @brief Destructor for the BodyPart class.
     */
    ~BodyPart();

    /**
     * @brief Gets the position of the body part.
     * @return The position of the body part.
     */
    Position getItsPosition();

    /**
     * @brief Gets the previous position of the body part.
     * @return The previous position of the body part.
     */
    Position getItsPreviousPosition();

    /**
     * @brief Gets the child body part.
     * @return Pointer to the child body part.
     */
    BodyPart* getItsChild();

    /**
     * @brief Gets the parent body part.
     * @return Pointer to the parent body part.
     */
    BodyPart* getItsParent();

    /**
     * @brief Gets the hitbox of the body part.
     * @return The hitbox of the body part as a QRect.
     */
    QRect getItsHitBox();

    /**
     * @brief Sets the position of the body part.
     * @param pos The new position of the body part.
     */
    void setItsPosition(Position pos);

    /**
     * @brief Sets the child body part.
     * @param child Pointer to the child body part.
     */
    void setItsChild(BodyPart* child);

    /**
     * @brief Sets the parent body part.
     * @param parent Pointer to the parent body part.
     */
    void setItsParent(BodyPart* parent);

    /**
     * @brief Sets the hitbox of the body part.
     * @param hitbox The new hitbox of the body part.
     */
    void setItsHitBox(QRect hitbox);

    /**
     * @brief Sets the target position for the body part's movement.
     * @param targetPos The new target position.
     */
    void setItsTargetPos(Position targetPos);

    /**
     * @brief Updates the position of the body part based on its target position.
     */
    void updatePos();

    /**
     * @brief Calculates the next target position based on the centipede's direction and movement distance.
     * @param centipedeDir The direction of movement for the centipede.
     * @param caseLength The distance to move.
     * @return The next target position.
     */
    Position getNextTarget(Direction centipedeDir, int caseLength);

    /**
     * @brief Gets the target position of the body part.
     * @return The target position of the body part.
     */
    Position getItsTarget();

    /**
     * @brief addChild add a new bodypart child to the bodypart
     * @param child is his new bodypart
     */
    void addChild(BodyPart * child);
};

#endif // BODYPART_H
