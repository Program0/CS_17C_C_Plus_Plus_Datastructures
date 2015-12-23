/*
* File: user.cpp
* Interface file for User class. The class inherits from QObject and
* implements signals and slots.
* Author: Marlo Zeroth
*/

#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>
#include <QDataStream> // For reading and writing to files

class User {

public:    

    User();

    // Main constructor
    User(const unsigned int &newId, const QString &first, const QString &middle, const QString &last,
           const QString &userN, const QString &passW, const QString &email, const QDate &birth);

    virtual ~User();

    // Overloaded comparison operat
    bool operator == (const User& user)const;

    // Accessors
    unsigned int getUserID() const {return userID;}
    QString getFirstName() const {return firstName;}
    QString getMiddleName() const {return middleName;}
    QString getLastName() const {return lastName;}
    QString getUserName() const {return userName;}
    QString getPassword() const {return password;}
    QString getEmail() const {return email;}
    QDate getBirthDate() const {return birthDate;}

    // Mutators

    // Updates all of the user info except for the userID
    void updatePlayer(unsigned int newId, QString first, QString middle, QString last, QString userN,
                      QString passW, QString email, QDate birth);

    // Updates various player parameters
    void updateUserID(const unsigned int &newId);
    void updateFirstName(const QString &first);
    void updateMiddleName(const QString &middle);
    void updateLastName(const QString &last);
    void updateBirthDate(const QDate & date);
    void updateEmail(const QString &eMail);

    // Updates the player's login information
    void updateUserName(const QString &user);
    void updatePassword(const QString &passW);
    virtual bool isEqual(const User& user) const;

private:

    friend QDataStream & operator << (QDataStream &stream, const User &user);
    friend QDataStream & operator >> (QDataStream &stream, User &user);

    unsigned int userID;
    QString firstName;
    QString middleName;
    QString lastName;    
    QString userName;
    QString password;
    QString email;
    QDate birthDate;
};

#endif // USER_H

