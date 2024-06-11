/**
 * @file typeDef.h
 * @brief Defines common typedefs and constants used in the game.
 */

#ifndef TYPEDEF_H
#define TYPEDEF_H

/**
 * @struct Position
 * @brief Struct representing a position with x and y coordinates.
 */
struct Position
{
    int posX; /**< The x-coordinate */
    int posY; /**< The y-coordinate */
};

/**
 * @struct Directionq
 * @brief Struct representing a direction with x and y components.
 */
struct Direction
{
    int dirX; /**< The x-component of the direction */
    int dirY; /**< The y-component of the direction */
};

// Variables for centipede
const int CENTIPEDE_SPEED = 1;
const int CENTIPEDE_LENGTH = 8;
const int CENTIPEDE_BODYPART_SIZE = 13;
const Position CENTIPEDE_SPAWN_POSITION = {15, 0};
const int CENTIPEDE_SPAWN_XPOS = 15;
const int CENTIPEDE_SPAWN_YPOS = 0;

// Variables for player
const int PLAYER_SPEED = 1; /**< The speed of the player */
const int PLAYER_SIZE = 5; /**< The size of the player */

// Variables for mushroom
const int MUSHROOM_SIZE = 10; /**< The size of the mushroom */

// Variables for bullet
const int BULLET_SPEED = 5; /**< The speed of the bullet */

// Variables for game
const int MUSHROOMS_AMOUNT = 0; /**< The number of mushrooms in the game */
const int BOARD_WIDTH = 30; /**< The width of the game board */
const int BOARD_HEIGHT = 31; /**< The height of the game board */

const int POWERUP_RATE = 100; /**< The chance in percent for a powerup to appear when a mushroom is broken by a bullet */

const bool SHOW_HITBOXES = true;

#endif // TYPEDEF_H
