/**
 * @file leaderboard.h
 * @brief Defines the Leaderboard class, which manages high scores in the game.
 */

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "typeDef.h"
#include <fstream>
#include <map>
#include <string>

using namespace std;

/**
 * @class Leaderboard
 * @brief Manages and stores high scores in a leaderboard.
 */
class Leaderboard
{
public:
    /**
     * @brief Constructor for the Leaderboard class.
     * @param filename The filename to load and save the leaderboard data.
     */
    Leaderboard(string filename);

    /**
     * @brief Retrieves the best scores from the leaderboard.
     * @return A map containing usernames and their corresponding best scores.
     */
    map<string, int> getItsBestScores();

    /**
     * @brief Adds a new score to the leaderboard.
     * @param newScore The new score to add.
     * @param username The username associated with the score.
     */
    void addScore(int newScore, string username);

    /**
     * @brief Extracts high scores from the file and updates the leaderboard.
     */
    void extract();

    /**
     * @brief Saves the current leaderboard data to the file.
     */
    void save();

private:
    string itsFileName;          /**< The filename used for saving and loading leaderboard data. */
    map<string, int> itsBestScores; /**< The map storing usernames and their corresponding best scores. */
};

#endif // LEADERBOARD_H
