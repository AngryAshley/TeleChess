#include "MatchMaker.h"
#include <iostream>

MatchMaker::MatchMaker()
{
    
}

void MatchMaker::checkForAvailablePlayers(IReferee* referee)
{
    const std::lock_guard<std::mutex> lock(mtx);
    IPlayer* availablePlayers[2] = {0};
    int count = 0;
    for (auto & player : players)
    {
            if (!player->GetInMatch() && count < 2)
            {
                availablePlayers[count] = player;
                count++;
            }
        
    }
    
    if (count == 2)
    {
        std::cout << "2 players found " << std::endl;
        NewMatch(referee, availablePlayers[0], availablePlayers[1]);
    }
}

void MatchMaker::NewMatch(IReferee* referee, IPlayer* playerWhite, IPlayer* playerBlack)
{
    Match* newMatch = new Match(referee, playerWhite, playerBlack);
    if (newMatch != nullptr)
    {
        playerWhite->EnterMatch(newMatch);
        playerBlack->EnterMatch(newMatch);
        matches.push_back(newMatch);
    }
}

void MatchMaker::AddPlayer(IPlayer* newPlayer)
{
    const std::lock_guard<std::mutex> lock(mtx);
    for (auto & player : players)
    {
        if (newPlayer->GetID() == player->GetID())
        {
            return;
        }
    }
    std::cout << "Player added " << newPlayer->GetID() << std::endl;
    players.push_back(newPlayer);
}

void MatchMaker::RemovePlayer(IPlayer* player)
{
    const std::lock_guard<std::mutex> lock(mtx);
    for (unsigned long int i = 0; i < players.size(); i++)
    {
        if (players[i] == player)
        {
            players.erase(players.begin() + i);
        }
    }
}