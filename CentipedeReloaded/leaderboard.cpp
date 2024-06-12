#include "leaderboard.h"

Leaderboard::Leaderboard(string fileName)
{
    itsFileName = fileName;
}

void Leaderboard::extract()
{
    itsBestScores = {};
    ifstream iFile(itsFileName);

    if(!iFile.is_open()) throw string("Error while trying to open " + itsFileName);

    while(!iFile.eof())
    {
        string username;
        int score;

        if(!(iFile >> username >> score)) throw string("Error while trying to extract data from " + itsFileName);

        itsBestScores.insert({username, score});
    }
}

void Leaderboard::save()
{
    ofstream oFile(itsFileName, ios::trunc);

    if(!oFile.is_open()) throw string("Error while trying to open " + itsFileName);

    for(pair<string,int> score : itsBestScores)
    {
        if(!(oFile << score.first << score.second)) throw string("Error while trying to save data in " + itsFileName);
    }
}

void Leaderboard::addScore(int newScore, string username)
{
    extract();
    if((itsBestScores.find(username) == itsBestScores.end()) || (itsBestScores.find(username)->second < newScore))
    {
        itsBestScores[username] = newScore;
    }
    save();
}

map<string, int> Leaderboard::getItsBestScores()
{
    return itsBestScores;
}
