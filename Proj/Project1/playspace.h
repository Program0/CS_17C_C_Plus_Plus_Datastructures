#ifndef PLAYSPACE_H
#define PLAYSPACE_H

#include <QWidget>
#include <QString>
#include <QList>
#include <QStack>
#include <QVector>
#include <QPixmap>
#include <QComboBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QStringList>
#include <QVBoxLayout>
#include <QHBoxLayout>

// User libraries
#include "guessentry.h"
#include "list.h"

class PlaySpace:public QWidget{

    Q_OBJECT

public:

    // Main constructor
    PlaySpace(QPixmap bull, QPixmap cow, unsigned int size, QWidget *parent=0, Qt::WindowFlags f=0);

public slots:

    // Slot to pass the code word to GuessEntry object
    //void startPlay(QString code, int difficulty);
private slots:

    void setRole(int role);
    // Hides and unhides the code lineEdit if user is breaker or creator

    void setValidation(int test);
    // Sets the validation for the lineEdit for code word.

    void newGame(bool test);
    // Starts a new game


signals:
    //void myHandler(QString codeWord);
    void codeChanged(QString code);
    void gameFinished(bool );

private:

    QPixmap cow; // To hold images for cows
    QPixmap bull; // To hold images for bulls
    QString codeWord; // Holds the current code to break
    unsigned int currentGuess; // Holds the current guess made
    unsigned int totalGuesses; // Holds how many guess entries to generate
    bool finished; // If the current game is complete
    List<GuessEntry *> guessInterface; // Holds the guessing interface.

    // For the new game entry
    QGroupBox *role;
    QLabel *codeLabel;
    QLineEdit *lineEdit;
    QButtonGroup *difficulty;
    QGroupBox *difficultyRadioBox;
    QComboBox *playerRole;
    QPushButton *newGameButton;
    QPushButton *quitButton;

};

#endif // PLAYSPACE_H

