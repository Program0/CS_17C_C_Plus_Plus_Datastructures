#ifndef GAME
#define GAME

#include <QString>
#include <QDataStream>
#include <QStack>

// User Libraries
#include "user.h"
#include "guess.h"


class Game{

public:

    Game();
    // Main constructor
    Game(QString map, const unsigned int id, const QString &word, const unsigned int &totalTries,
         const User &p1, const User &p2);

    // Mutators
    void setGuess(const QString &guess, const unsigned int &bull, const unsigned int &cow);
    // Adds a guess and its associated bull and cow to the stack of
    // guess in the current game

    void setFinished(const bool &complete);
    // Sets the finished state of the game

    void setWinner(const int &win);
    // Sets the winner of the game if the game is finished.
    // Accepts only the digits 1 or 2 as valid options

    void setPlayerRole(const int & role);
    // Sets the player role for the game.
    // Accepts only the digits 1 or 2 as valid options.

    // Accesors
    QString getCode() const {return codeWord;}
    bool isFinished() const {return finished;}

    User getPlayer1() const {return player1;}
    User getPlayer2() const {return player2;}
    unsigned int getWinner() const {return winner;}
    unsigned int getCodeBreaker() const {return codeBreaker;}
    unsigned int getTotalGuessesMade(){return guesses.size();}
    Guess getCurrentGuess() const {return guesses.top();}
    QStack<Guess> getGuesses() const;

private:

    // Overloaded operators
    friend QDataStream &operator << (QDataStream &stream, const Game &game);
    friend QDataStream &operator >> (QDataStream &stream, Game &game);

    // Available options for the code
    QString options;
    // GameId, code word, finished state, and number of tries
    unsigned int gameId;
    // Code word and guesses made
    QString codeWord;
    unsigned int maximumTries;
    // Players for the game
    User player1;
    User player2;
    bool finished; // If the game has been completed
    // Player roles and winner
    unsigned int codeBreaker;
    unsigned int winner;    
    QStack<Guess> guesses;
};

#endif // GAME

