

#include "player.h"

Player::~Player(){

}

// Determines whether two players are the same based on their userId
bool Player::isEqual(const Player &player) const{
    bool val;
    val= User::isEqual(player);
    return val;
}
