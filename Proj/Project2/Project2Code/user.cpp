/*
* File: user.cpp
* Implementation file for User class. The class inherits from QObject and
* implements signals and slots.
* Author: Marlo Zeroth
*/

#include "user.h"

User::User(){

}

// Main constructor
User::User(const unsigned int &newId, const QString &first, const QString &middle, const QString &last,
               const QString &userN, const QString &passW, const QString &email, const QDate &birth){
    // Used initialization list. Left empty on purpose.
    userID = newId;
    firstName = first;
    middleName = middle;
    lastName = last;
    userName = userN;
    password = passW;
    this->email = email;
    birthDate = birth;
}

User::~User(){

}

// Overloaded comparison operator
bool User::operator == (const User &user) const{
    return (userID-user.userID);
}

// isEqual function

bool User::isEqual(const User& user) const{
    return ( userID == user.userID);
}

// Updates the player information
void User::updatePlayer(unsigned int newId, QString first, QString middle, QString last,
                          QString userN, QString passW, QString email, QDate birth){
    userID = newId;
    firstName = first;
    middleName = middle;
    lastName = last;
    userName = userN;
    password = passW;
    this->email = email;
    birthDate = birth;
}

void User::updateUserID(const unsigned int &newId){
    if(userID!=newId){
        userID=newId;        
    }
}

// Following functions update individual member variables
void User::updateFirstName(const QString & first){
    if(first!=firstName){
        firstName=first;        
    }
}

void User::updateMiddleName(const QString & middle){
    if(middle!=middleName){
        middleName=middle;        
    }
}

void User::updateLastName(const QString & last){
    if(last!=lastName){
        lastName=last;        
    }
}

void User::updateUserName(const QString & user){
    if(user!=userName){
        userName=user;        
    }
}

void User::updatePassword(const QString &passW){
    if(passW!=password){
        password=passW;        
    }
}

void User::updateEmail(const QString & eMail){
    if(email!=eMail){
        email=eMail;        
    }
}

void User::updateBirthDate(const QDate &date){
    if(birthDate!=date){
        birthDate=date;        
    }
}

QDataStream & operator << (QDataStream &stream, const User &user){
    stream<<user.userID;
    stream<<user.firstName;
    stream<<user.middleName;
    stream<<user.lastName;
    stream<<user.userName;
    stream<<user.password;
    stream<<user.email;
    stream<<user.birthDate;
    return stream;
}

QDataStream & operator >> (QDataStream &stream, User &user){

    stream>>user.userID;
    stream>>user.firstName;
    stream>>user.middleName;
    stream>>user.lastName;
    stream>>user.userName;
    stream>>user.password;
    stream>>user.email;
    stream>>user.birthDate;
    return stream;
}
