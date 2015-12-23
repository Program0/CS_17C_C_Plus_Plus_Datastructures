/*
* File: playspace.h
* Interface file for PlaySpace class. The class inherits from
* QWidget. It displays and accepts user created code and guess entries for the
* game bulls and cows - a version predating mastermind.
* Author: Marlo Zeroth
*/

#ifndef PLAYSPACE_H
#define PLAYSPACE_H

#include <QWidget>
#include <QString>
#include <QList>
#include <QMap>
#include <QPixmap>
#include <QStringList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsView>

// User libraries
#include "guessentry.h"
#include "list.h" // User created templated doubly-linked list
#include "codescene.h"
#include "game.h"

class PlaySpace:public QWidget{

    Q_OBJECT

public:
    // Main constructor
    PlaySpace(QMap<QString, QString> map, unsigned int defaultDifficulty,
              unsigned int defaultTries, QWidget *parent=0, Qt::WindowFlags f=0);

public slots:

    void loadGame(const Game& game);
    // Loads a game

    void updatePlayspace(const QString &code);
    // Sets the new code and updates the game interface

private slots:    

    void showCode(bool complete);
    // Updates the dummy view to display the code if the game is finished

    void setGameFinished(bool complete);
    // Sets the game to complete

    void guessUpdate(QString guess,unsigned int bull,unsigned  int cow);
    // Receives a guess and its bulls and cows

    void congratulate(bool win);
    // Pops up a window wishing the player better luck next time    

signals:    
    void codeChanged(QString code);
    void gameFinished(bool );
    void guessChanged(QString, unsigned int,unsigned int); // Emits the current guess bull and cow

private:


    QPixmap cow; // To hold images for cows
    QPixmap bull; // To hold images for bulls
    QString codeWord; // Holds the current code to break    
    QString currentGuess; // Holds the current guess
    unsigned int totalGuesses; // Holds how many guess entries to generate    
    bool finished; // If the current game is complete
    QMap<QString,QString> codeComponents; // Valid Components that can be used to generate a code and output images
    QString options; // Holds the keys of codeComponents to easily generate code
    List<GuessEntry *> guessInterface; // Holds the guessing interface.

    QGraphicsScene *dummy; // Shows an graphics scene filled with question marks
    QGraphicsView *dummyView; // Holds the dummy scene
    QLabel *codeLabel; // Buddy label for iconView
    CodeScene *codeScene; // Holds icons elements to drop onto GuessEntry objects
    QGraphicsView *codeView; // Displays the iconScene

    /*Utility functions*/

    QGraphicsView* createDummyView(int length);
    // Creates a dummy code QGraphicsView while playing the game

    void updateDummyView(int newCodeLength);
    // Updates the size of the shown dummy code whenever the difficulty changes

};

#endif // PLAYSPACE_H

