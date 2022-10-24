#ifndef IPLAYER_H
#define IPLAYER_H

class IPlayer
{
private:
    int playerID;
public:
    bool operator==(IPlayer other) const
    {
        return (playerID == other.playerID);
    }
    virtual ~IPlayer();
};

#endif