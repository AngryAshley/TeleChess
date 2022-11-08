#include "MatchMaker.h"
#include <iostream>

MatchMaker::MatchMaker()
{
    
}

void MatchMaker::checkForAvailablePlayers(IReferee* referee)
{
    IPlayer* availablePlayers[2];
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
        std::cout << "2 players found \n";
        NewMatch(referee, availablePlayers[0], availablePlayers[1]);
    }
}

void MatchMaker::NewMatch(IReferee* referee, IPlayer* playerWhite, IPlayer* playerBlack)
{
    Match* newMatch = new Match(referee, playerWhite, playerBlack);
    playerWhite->EnterMatch(newMatch);
    playerBlack->EnterMatch(newMatch);
    matches.push_back(newMatch);
}

void MatchMaker::AddPlayer(IPlayer* newPlayer)
{
    for (auto & player : players)
    {
        if (newPlayer == player)
        {
            return;
        }
    }
    std::cout << "Player added " << newPlayer->GetID() << std::endl;
    players.push_back(newPlayer);
}

void MatchMaker::RemovePlayer(IPlayer* player)
{
    for (unsigned long int i = 0; i < players.size(); i++)
    {
        if (players[i] == player)
        {
            players.erase(players.begin() + i);
        }
    }
}