


#include "game.h"

Game::Game(){

}

Game::Game(QString map, const unsigned int id, const QString &word,
           const unsigned int &totalTries, const User &p1, const User &p2):options(map),
    gameId(id),codeWord(word),maximumTries(totalTries), player1(p1), player2(p2), finished(false){
}

// Add all member variables into the stream. Could create a toString() function to handle most of this
QDataStream &operator << (QDataStream &stream, const Game &game){
    stream << game.gameId;
    stream << game.codeWord;
    stream << game.maximumTries;
    stream << game.player1;
    stream << game.player2;
    stream << game.finished;
    stream << game.codeBreaker;
    stream << game.winner;
    stream << game.guesses;
    return stream;
}

QDataStream & operator >> (QDataStream &stream, Game &game){
    stream >> game.gameId;
    stream >> game.codeWord;
    stream >> game.maximumTries;
    stream >> game.player1;
    stream >> game.player2;
    stream >> game.finished;
    stream >> game.codeBreaker;
    stream >> game.winner;
    stream >> game.guesses;
    return stream;
}

void Game::setGuess(const QString &guess, const unsigned int &bull, const unsigned int &cow){
    // Add a guess only if the game is not finished
    if(!finished){
        Guess temp;
        temp.bull=bull;
        temp.cow=cow;
        temp.guess = guess;
        guesses.push(temp);
    }
}

void Game::setFinished(const bool &complete){
    if(complete!=finished){
        finished=complete;
    }
}

void Game::setWinner(const int &win){
    if(finished && (win==1||win==2)){
        winner=win;
    }
}

void Game::setPlayerRole(const int &role){
    if(finished && (role==1||role==2)){
        codeBreaker=role;
    }
}

QStack<Guess> Game::getGuesses() const {
    QStack<Guess> temp(guesses);
    return temp;
}
