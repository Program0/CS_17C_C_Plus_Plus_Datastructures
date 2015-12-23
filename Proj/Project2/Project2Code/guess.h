#ifndef GUESS_H
#define GUESS_H

#include <QString>
#include <QDataStream>

class Guess{
public:
    QString guess;
    unsigned int bull;
    unsigned int cow;    

    Guess(){}
    Guess(const QString& g, const unsigned int& b, const unsigned int& c):
        guess(g),bull(b),cow(c){}

    friend QDataStream& operator << (QDataStream &os, const Guess &obj){
        os << obj.guess << obj.bull << obj.cow;
        return os;
    }

    friend QDataStream& operator >> (QDataStream& is, Guess &obj){
        is >> obj.guess >> obj.bull >> obj.cow;
        return is;
    }

};

#endif // GUESS_H

