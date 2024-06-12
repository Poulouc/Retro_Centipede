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

    string username;
    int score;
    if(!(iFile >> username >> score)) return;
    else itsBestScores.insert({username, score});

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

    for(map<string,int>::iterator it = itsBestScores.begin(); it != itsBestScores.end(); ++it)
    {
        if(!(oFile << it->first << " " << it->second)) throw string("Error while trying to save data in " + itsFileName);
        if(it != --itsBestScores.end())
        {
            if(!(oFile << endl)) throw string("Error while trying to save data in " + itsFileName);
        }
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
