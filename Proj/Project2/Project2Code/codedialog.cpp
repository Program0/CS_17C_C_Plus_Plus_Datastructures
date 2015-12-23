#ifndef CODEDIALOG_CPP
#define CODEDIALOG_CPP

#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>

#include "codedialog.h"

CodeDialog::CodeDialog(QMap<QString,QString> map,int length, QWidget *parent):QDialog(parent){

    // If the length is greater than 0 set size equal to it otherwise default it to 2
    length>0?defaultTries=length:defaultTries = 2;

    // Allow duplicates by default. Should be changed by slot/signal
    duplicates = true;

    // Set the code label and code options for the code
    codeLabel = new QLabel("&Create a code by dragging beasts from the available choices:",parent);
    codeOptions = new CodeScene(map,parent);
    codeSceneView = new QGraphicsView;
    codeSceneView->setScene(codeOptions);
    codeLabel->setBuddy(codeSceneView);

    // Create an ImageAcceptor scene to create the code
    codeSetter = new GuessScene(length,parent);
    guessSceneView = new QGraphicsView;
    guessSceneView ->setScene(codeSetter);

    QVBoxLayout *codeLayout = new QVBoxLayout;
    codeLayout->addWidget(codeLabel);
    codeLayout->addWidget(codeSceneView);
    codeLayout->addWidget(guessSceneView);


    newGameButton = new QPushButton("Set Code",parent);

    connect(newGameButton,SIGNAL(clicked(bool)),this,SLOT(setGame(bool)));

    QHBoxLayout *gameLayout = new QHBoxLayout;
    gameLayout->addWidget(newGameButton);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(codeLayout);
    mainLayout->addLayout(gameLayout);

    setWindowTitle("Enter Code For The New Game");
    setLayout(mainLayout);
    setModal(true);
}

// Changes the size on the guessAcceptor based on the selected option
// from the difficulty in the PlaySpace class QGroupButton class.
void CodeDialog::updateSize(const int &test){
    if(test!=defaultTries && test > 0){
        // Resize with the new size
        defaultTries = test;
        codeSetter->resize(defaultTries);
        emit sizeChanged(defaultTries);
    }
}

// Starts a new game with the entered code word and difficulty
// signal
void CodeDialog::setGame(bool test){
    if(!test){
        if(codeSetter->filled()){
            QString code = codeSetter->text();
            // If duplicates are allowed accept the generated code
            if(duplicates){
                emit startGame(code);
                close();
            }
            else{
                // If duplicates not allowed check the code for duplicates
                if(containsDuplicates(code)){
                    QMessageBox msgBx;
                    msgBx.setText(QString("The game has been set to not allow duplicates. "+
                                  QString("Please create a code without duplicates.")));
                    msgBx.exec();
                }
                else{
                    emit startGame(code);
                    close();
                }
            }
        }
        else{
            QMessageBox msgBx;
            msgBx.setText("Please create a code");
            msgBx.exec();
        }
    }
}

// Sets whether to accept duplicate entries in the code generator view
void CodeDialog::setAllowDuplicates(bool dups){
    if(dups!=duplicates){
        duplicates=dups;
        emit duplicatesChanged(duplicates);
    }
}

bool CodeDialog::containsDuplicates(QString test){
    // Test how many characters are in the test string
    QSet<QChar> testDups;
    for(int i = 0; i<test.size();i++)
        testDups.insert(test[i]);
    // If the size of the set is less than the size of
    // the string we have duplicates otherwise no duplicates
    return testDups.size()<test.size();
}

#endif // CODEDIALOG_CPP

