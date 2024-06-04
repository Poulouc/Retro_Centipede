#ifndef TYPEDEF_H
#define TYPEDEF_H

struct Position
{
    int posX;
    int posY;
};

struct Direction
{
    int dirX;
    int dirY;
};

// Variables for centipede
const int CENTIPEDE_SPEED = 8;
const int CENTIPEDE_LENGTH = 8;
const int CENTIPEDE_BODYPART_SIZE = 5;

// Variables for player
const int PLAYER_SPEED = 8;
const int PLAYER_SIZE = 5;

// Variables for mushroom
const int MUSHROOM_SIZE = 5;

// Variables for bullet
const int BULLET_SPEED = 5;

#endif // TYPEDEF_H
