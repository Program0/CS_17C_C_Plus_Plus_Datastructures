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


class GuessEntry : public QWidget
{
    Q_OBJECT

public:    
    explicit GuessEntry(QPixmap bull, QPixmap cow,
                        bool current, QWidget *parent = 0, Qt::WindowFlags f=0);

public slots:
    void setCurrent(bool status);
    // Sets the current member variable

    void setCodeWord(QString code);
    // Sets the current code word to test

    void reset();
    // Resets the displayed widgets

private slots:

    void guessFinished(bool);
    // Connects to checkButton's clicked(bool) signal and
    // emits solved(true) if the codeWord matches the user guess
    // or emits finished(true) if the codeWord does not

    void enableCheck(const QString &guessWord);
    // Enables/disables the checkButton based on whether valid text
    // is entered in guessEntry

    void setValidation(int test);
    // Updates the validation for lineEdit

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
    QString codeWord;
    QLabel *bullLabel;
    QLabel *cowLabel;
    QLabel *bullCount;
    QLabel *cowCount;
    QLineEdit *lineEdit;
    QPushButton *checkButton;
    bool currentGuess;
};

#endif // GUESSENTRY_H
