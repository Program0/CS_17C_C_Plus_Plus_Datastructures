#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QWidget>
#include <QDialog>

// User Libraries
#include "codedialog.h"

class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameDialog(QMap<QString, QString> map, QWidget *parent = 0);

public slots:

    void newGame(bool start); // Connects the newGameButton with this object
    void setCode(const QString& entry); // Updates the code word

signals:
    void startGame(bool);
    void playerOneRole(int);
    void duplicatesAllowed(bool);
    void codeChanged(QString);
    void codeLength(int);
private:
    QLabel *codeLabel;
    QString codeOptions; // Available icons to choose from
    QMap<QString,QString> codeComponents; // Valid Components that can be used to generate a code and output images
    CodeDialog *codeEntry; // Used to get an user generated code
    QButtonGroup *difficulty; // Determines the size of the code
    QCheckBox *duplicates; // Determines whether duplicates are allowed in the code
    QComboBox *playerRole; // Determines whether a player generates or breaks the code
    QPushButton *newGameButton; // Starts/resets the game
    QPushButton *quitButton;

    /*Utility functions*/
    QString generateCode();
    // Generates a code if player is breaker

    QGroupBox* createDifficultyBox();
    // Creates a radion button group box with difficulty levels

    QGroupBox* createOptionsBox();
    // Creates a button group box with the player role and new game button
};

#endif // NEWGAMEDIALOG_H
