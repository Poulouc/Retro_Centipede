/**
 * @file typeDef.h
 * @brief Defines common typedefs and constants used in the game.
 */

#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <string>

/**
 * @struct Position
 * @brief Structure representing a position with x and y coordinates.
 */
struct Position
{
    int posX; /**< The x-coordinate */
    int posY; /**< The y-coordinate */
};

/**
 * @struct Direction
 * @brief Structure representing a direction with x and y components.
 */
struct Direction
{
    int dirX; /**< The x-component of the direction */
    int dirY; /**< The y-component of the direction */
};

// Variables for centipede
const int CENTIPEDE_LENGTH = 8; /**< The length of the centipede */
const int CENTIPEDE_BODYPART_SIZE = 13; /**< The size of each body part of the centipede */
const int CENTIPEDE_SPAWN_XPOS = 15; /**< The initial x-coordinate of the centipede */
const int CENTIPEDE_SPAWN_YPOS = 0; /**< The initial y-coordinate of the centipede */

// Variables for player
const int PLAYER_SPEED = 1; /**< The speed of the player */
const int PLAYER_SIZE = 5; /**< The size of the player */

// Variables for mushroom
const int MUSHROOM_SIZE = 10; /**< The size of the mushroom */

// Variables for bullet
const int BULLET_SPEED = 5; /**< The speed of the bullet */

// Variables for game
const int MUSHROOMS_AMOUNT = 30; /**< The number of mushrooms in the game */
const int BOARD_WIDTH = 30; /**< The width of the game board */
const int BOARD_HEIGHT = 31; /**< The height of the game board */

// Variables for powerups
const int POWERUP_DROPRATE = 100; /**< The chance in percent for a powerup to appear when a mushroom is broken by a bullet */
const int POWERUP_RAFALE_DURATION = 4; /**< The duration in seconds of the 'rafale' powerup */
const int POWERUP_RAFALE_FIRERATE = 4; /**< The number of shots per second of the 'rafale' powerup */
const int POWERUP_PIERCING_DURATION = 5; /**< The duration in second of the 'piercing' powerup */

const bool SHOW_HITBOXES = false; /**< Flag indicating whether to show hitboxes */

// Variables for the Spider
const int INCREMENT_INTERVAL = 5; /**< The interval for incrementing the spider's movement */
const int SPIDER_SPEED = 1; /**< The speed of the spider */

const std::string SAVEFILE_NAME = "leaderboard.txt"; /**< The name of the file to save leaderboard data */

#endif // TYPEDEF_H
