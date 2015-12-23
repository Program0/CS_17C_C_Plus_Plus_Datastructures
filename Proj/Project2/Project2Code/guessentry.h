/*
* File: guessentry.cpp
* Interface file for GuessEntry class. The class inherits from
* QWidget. It displays and accepts user entries for guesses for the
* game bulls and cows - a version predating mastermind.*
* Author: Marlo Zeroth
*/


#ifndef GUESSENTRY_H
#define GUESSENTRY_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QPixmap>
#include <QGridLayout>
#include <QRegExp>
#include <QRegExpValidator>
#include <QSet>
#include <QChar>

#include "guessscene.h"
#include "guess.h"

class GuessEntry : public QWidget
{
    Q_OBJECT

public:    
    explicit GuessEntry(QMap<QString,QString> options, QPixmap bull, QPixmap cow, int defaultTries,
                        bool current, QWidget *parent = 0, Qt::WindowFlags f=0);

public slots:
    void setCurrent(bool status);
    // Sets the current member variable

    void setCodeWord(QString code);
    // Sets the current code word to test

    void setSize(int test);
    // Updates the view for guessScene

    void setGuess(QString guess, unsigned int bull, unsigned int cow);
    // Sets the values for the current guessScene

    void reset();
    // Resets the displayed widgets

private slots:

    void guessFinished(bool);
    // Connects to checkButton's clicked(bool) signal and
    // emits solved(true) if the codeWord matches the user guess
    // or emits finished(true) if the codeWord does not

signals:
    void finished(bool);
    // Emits if the processing the code and guess words is completed

    void solved(bool);
    // Emits whether the code word and guess are the same

    void current(bool);
    // Emits the value of the member variable current

    void guessWord(QString,unsigned int, unsigned int);
    // Emits the guess word and its bulls and cows

    void codeWordChanged(QString);
    // Emits the changed code word

private:
    QMap<QString,QString> options; // Options available to generate a guess
    QString codeWord; // Code to test the guess against
    QLabel *bullLabel;// To hold an image displaying a bull
    QLabel *cowLabel; // To hold an image displaying a cow
    QLabel *bullCount; // Show how many elements are in the set of a code and in the right place
    QLabel *cowCount; // Shows how many elements form a guess are also in the set of a code but wrong place
    QGraphicsView *guessView; // Will hold the guessAcceptor scene
    GuessScene *guessAcceptor; // Accepts icons with text values
    QPushButton *checkButton; // Button to process a guess - checks whether it matches a code
    bool currentGuess; // Determines whether this is the current guess in a set of guesses
};

#endif // GUESSENTRY_H
