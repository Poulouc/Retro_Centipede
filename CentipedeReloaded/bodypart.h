#include <QRect>
#include "typeDef.h"

#ifndef BODYPART_H
#define BODYPART_H

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
    QRect itsHitBox = QRect(0, 0, CENTIPEDE_BODYPART_SIZE, CENTIPEDE_BODYPART_SIZE); /**< Rectangle representing the hitbox */
    Position itsPosition = {}; /**< Position of the body part */

public:
    /**
     * @brief Constructor for the BodyPart class.
     */
    BodyPart();

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
     * @return The hitbox of the body part.
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
     * @brief Adds a child body part.
     * @param child Pointer to the child body part.
     */
    void addChild(BodyPart* child);

    /**
     * @brief Adds a set the hitBox of the bodyPart.
     * @param hitbox is QRect who replace the hitBox.
     */
    void setItsHitBox(QRect hitbox);
};

#endif // BODYPART_H
