#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QDate>
#include <QDateTime>

class Player{
public:
    Player(unsigned int iD, QString first, QString middle, QString, last, QString userN, QString passW
           ,unsigned int win, unsigned int loss);
public slots:
    // Updates the player info
    void updatePlayer(unsigned int iD, QString first, QString middle, QString, last, QString userN,
                      QString passW, unsigned int win, unsigned int loss);
    // Updates various player parameters
    void updateFirstName(const QString &);
    void updateMiddleName(const QString &);
    void updateLastName(const QString &);
    // Updates the players login information
    void updateUserName(const QString &);
    void updatePassword(const QString &);
    // Updates wins and losses
    void updateWin(const unsigned int &);
    void updateLoss(const unsigned int &);

signals:
    void winsChanged(const unsigned int &);
    void lossChanged(const unsigned int &);

private:
    unsigned int playerID;
    QString firstName;
    QString middleName;
    QString lastName;
    unsigned int age;
    QString userName;
    QString password;
};

#endif // PLAYER_H

