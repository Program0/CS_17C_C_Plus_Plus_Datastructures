

#ifndef COMPUTER_H
#define COMPUTER_H

#include <QString>
#include <QList>

class Computer{
public:
    void generate(int n, QString options, QList<QString>& mylist);
    // Fills a list with all permutations without repetition based on an input string of
    // valid characters. Code implemented from:
    // https://en.wikipedia.org/wiki/Heap's_algorithm

    void generateDups(QString options, QString output, int last, int index,QList<QString>& mylist);
    // Fills a list will all possible permutations with repetitions based on string of valid
    // character options. Code implemented from:
    //http://www.geeksforgeeks.org/print-all-permutations-with-repetition-of-characters/

private:
    void swap(QChar a, QChar b);
};
#endif // COMPUTER_H

