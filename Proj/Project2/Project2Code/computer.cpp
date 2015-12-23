
#include <QDebug>
#include "computer.h"
#include <iostream>

#include "list"
void Computer::generate(int n, QString options, QList<QString>& mylist) {
    if (n == 1){
        mylist.append(options);

    }
    else {
        for (int i = 0; i < n - 1; i++) {
            generate(n - 1, options,mylist);
            if (n % 2 == 0) {
                swap(options[i], options[n - 1]);
            } else
                swap(options[0], options[n - 1]);
        }
        generate(n - 1, options,mylist);
    }
}

void Computer::swap(QChar a, QChar b) {
    QChar temp = a;
    a = b;
    b = temp;
}

void Computer::generateDups(QString options, QString output, int last, int index, QList<QString>& mylist){
      int i, len = options.size();

    // One by one fix all characters at the given index and recur for
    // the/ subsequent indexes
    for ( i=0; i<len; i++ )
    {
        // Fix the ith character at index and if this is not the last
        // index then recursively call for higher indexes
        output[index] = options[i] ;

        // If this is the last index then print the string stored in
        // data[]
        if (index == last)
            mylist.append(output);
        else // Recur for higher indexes
            generateDups(options, output, last, index+1,mylist);
    }
}
