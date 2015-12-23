#ifndef GAME
#define GAME

#include <QString>
#include <QPair>

#include "player.h"
#include "stack.h"


class Game{
private:
    struct Guess{
        int bull;
        int cow;
        QString guess;
    };

    // Players for the game
    Player player1;
    Player player2;
    // Code word and guesses made
    QString codeWord;
    Stack<Guess> guesses;
    unsigned int difficulty;

public:
    Game();
    Game(QString word, Player p1, Player p2, unsigned int diff);
    void setGuess(QString guess, int bull, int cow);

};

#endif // GAME

