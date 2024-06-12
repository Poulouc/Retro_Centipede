#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "typeDef.h"
#include <fstream>
#include <map>
using namespace std;

class Leaderboard
{
public:
    Leaderboard(string filename);
    map<string, int> getItsBestScores();
    void addScore(int newScore, string username);
    void extract();
    void save();

private:
    string itsFileName;
    map<string, int> itsBestScores;
};

#endif // LEADERBOARD_H
