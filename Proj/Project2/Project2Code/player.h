#ifndef PLAYER_H
#define PLAYER_H

#include "user.h"

class Player:public User{

public:
    // Main constructor for creating a player
    Player(const User& user, int score):User(user), score(score){}

    // Constructor for creating a player
    Player(const unsigned int &newId, const QString &first, const QString &middle, const QString &last,
           const QString &userN, const QString &passW, const QString &email, const QDate &birth,
           int currentScore):User(newId,first,middle,last,userN,passW,email,birth),score(currentScore){}

    virtual ~Player();

    // Updates the player score
    void updateScore(int newScore){score = newScore;}

    // Returns the curre player score
    int getScore(){return score;}

    // Returns whether one player has a higher score than another player
    bool operator < (const Player& player) const {return score<player.score;}

    // Returns whether one player has a lower score than another player
    bool operator >(const Player& player)const {return score > player.score;}

    // Determines whether two players are the same based on their userId
    bool isEqual(const Player& player)const;


private:
    int score;
};

#endif // PLAYER_H

