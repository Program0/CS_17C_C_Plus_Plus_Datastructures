/*
* File: playspace.cpp
* Implementation file for the PlaySpace class. The class inherits from
* QWidget. It displays and accepts user created code and guess entries for the
* game bulls and cows - a version predating mastermind.
* Author: Marlo Zeroth
*/

#ifndef PLAYSPACE_CPP
#define PLAYSPACE_CPP

#include <QMessageBox>
#include "playspace.h"

PlaySpace::PlaySpace(QMap<QString, QString> map, unsigned int defaultDifficulty, unsigned int defaultTries,
                     QWidget *parent, Qt::WindowFlags f):QWidget(parent,f){

    // Total number of tries possible for one round
    totalGuesses = defaultTries;

    // This will be used when loading a saved game that is not finished
    // and for displaying the code after the game is finished
    codeComponents = map;

    // Set the bull and cow images
    QString image1(":/images/bull-icon.png");
    QString image2(":/images/cow-icon.png");
    QPixmap b1(image1);
    QPixmap c1 (image2);
    bull = b1;
    cow = c1;

    // Create an CodeScene object with images to drag and choose from
    codeScene = new CodeScene(map,parent);
    // Creates its view
    codeView = new QGraphicsView;
    codeView->setScene(codeScene);

    // Create the dummy view to display while game is not finished
    dummyView  = createDummyView(defaultDifficulty);

    // Set the top layout
    QLabel *codeDummy = new QLabel(parent);
    codeDummy->setText("Code to break: ");
    codeDummy->setStyleSheet("background-color: green; color: yellow; font: 18pt");
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(codeDummy);
    topLayout->addWidget(dummyView);

    QVBoxLayout *guessLayout = new QVBoxLayout;

    // Create GuessEntry objects and connect the bullsCows signal to their setBullsCows slots
    for(unsigned int i = 0; i<totalGuesses;i++){
        GuessEntry *entry = new GuessEntry(map,bull, cow, defaultDifficulty,false,parent);
        guessLayout->addWidget(entry);
        connect(this,SIGNAL(codeChanged(QString)),entry,SLOT(setCodeWord(QString)));
        connect(entry,SIGNAL(guessWord(QString,uint,uint)),this,SLOT(guessUpdate(QString,unsigned int,unsigned int)));
        guessInterface.prepend(entry);
    }

    // Iterators for current and its next GuessEntry object in the list
    List<GuessEntry*>::iterator next = guessInterface.begin();
    List<GuessEntry*>::iterator curr = next++;
    List<GuessEntry*>::iterator finish = guessInterface.end();

    // Go through each guessInterface object in the list and connect it to its adjacent
    // object so it knows when it is finished. Also connect each guessInterface object
    // with this so it knows when the code is cracked and it displays it.
    while(next!=finish){
        connect(*curr,SIGNAL(finished(bool)),*next,SLOT(setCurrent(bool)));
        connect(*curr,SIGNAL(solved(bool)),this,SLOT(showCode(bool)));
        curr++;
        next++;
    }

    // Add the codeView right below the guessEntry objects
    guessLayout->addWidget(codeView);

    // Also connect the last guessInterface object with this, so it knows when the
    // game is finished and shows the code
    connect(guessInterface.last(),SIGNAL(finished(bool)),this,SLOT(showCode(bool)));

    // Put all the layouts together
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(guessLayout);    

    // Set the main layout
    setLayout(mainLayout);
}

// Sets the game code and updates the individual guess entry interface
void PlaySpace::updatePlayspace(const QString &code){
    if(code!=codeWord){
        codeWord = code;
        // Reset the current status of the individual GuessEntry objects
        // Iterators for current and its next GuessEntry object in the list
        List<GuessEntry*>::iterator curr = guessInterface.begin();
        List<GuessEntry*>::iterator finish = guessInterface.end();

        // Go through each guessInterface object in the list and reset current to false
        while(curr!=finish){
            (*curr)->setSize(codeWord.length());// Set the size
            (*curr)->setCurrent(false);
            (*curr)->reset();
            curr++;
        }

        // Update the dummy code view
        updateDummyView(codeWord.length());

        // Set the first guessEntry as current
        guessInterface.first()->setCurrent(true);
        emit codeChanged(codeWord);
    }
}


// Creates a dummy to show while game is not finished
QGraphicsView* PlaySpace::createDummyView(int length){
    int total = length;

    dummy = new QGraphicsScene;

    QPixmap pixmap(":/images/question.png");
    int iconWidth = 40;

    for(int i =0;i<total;i++){
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
        item->setPos(i*iconWidth,0);
        dummy->addItem(item);
    }

    QGraphicsView *view = new QGraphicsView;
    view->setScene(dummy);
    //view->setMinimumSize(400,55);
    view->setMaximumSize(480,58);
    view->setStyleSheet("background-color: green;");
    return view;
}

// Updates the dummy view once the game is finished
void PlaySpace::updateDummyView(int newCodeLength){

        // Clear the scene - automatically deletes all items in the scene
        dummy->clear();

        QPixmap pixmap(":/images/question.png");// Default question mark image
        int iconWidth = 40; // Width of each image/icon

        // Iterate through the number provided in the difficulty radio
        // button box and create new items for the scene
        for(int i =0;i<newCodeLength;i++){
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
            item->setPos(i*iconWidth,0); // Set this item's position in the scene
            dummy->addItem(item);
        }

        // Update the view to show the new scene
        dummyView->update();

}

void PlaySpace::setGameFinished(bool complete){
    if(finished!=complete){
        finished=complete;
        emit gameFinished(finished);
    }
}

void PlaySpace::congratulate(bool win){
    QMessageBox msgBx;
    if(win){
        msgBx.setText("Congratulations you won!");
        msgBx.exec();
    }
    else{
        msgBx.setText("Better luck next time.");
        msgBx.exec();
    }
}

void PlaySpace::showCode(bool complete){
    if(complete){
        // Clear the scene to prepare to show the code
        dummy->clear();

        int total = codeWord.length();
        int iconWidth = 40; // Width of each image/icon

        // Iterate through the number provided in the difficulty radio
        // button box and create new items for the scene
        for(int i =0;i<total;i++){
            QString imagePath = codeComponents.value(QString(QChar(codeWord[i])));
            QPixmap pixmap(imagePath);// Show the image related to the code
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
            item->setPos(i*iconWidth,0); // Set this item's position in the scene
            dummy->addItem(item);
        }

        // Update the view to show the new scene
        dummyView->update();
    }
}

void PlaySpace::guessUpdate(QString guess,unsigned int bull, unsigned int cow){
    if(guess!=currentGuess){
        emit guessChanged(guess,bull,cow);
    }
}

void PlaySpace::loadGame(const Game &game){
    finished = game.isFinished();
    codeWord = game.getCode();
    QStack<Guess> guesses = game.getGuesses();

    // Reset the current status of the individual GuessEntry objects
    // Iterators for current and its next GuessEntry object in the list
    List<GuessEntry*>::iterator curr = guessInterface.begin();
    List<GuessEntry*>::iterator finish = guessInterface.end();

    int count = 0;
    // Go through each guessInterface object in the list and set its state
    while(curr!=finish){
        (*curr)->setSize(codeWord.length());// Set the size
        (*curr)->setCodeWord(codeWord);
        if(!guesses.isEmpty()){
            (*curr)->setGuess(guesses.top().guess,guesses.top().bull,guesses.top().cow);
            (*curr)->setCurrent(false);
            guesses.pop();
        }
        else{
            if(count<1){
                (*curr)->setCurrent(true);
                ++count;
            }else{
                (*curr)->setCurrent(false);
                (*curr)->reset();
            }

        }

        curr++;
    }

    // Update the dummy code view
    updateDummyView(codeWord.length());

    // Show the code if game is finished
    showCode(finished);

    emit codeChanged(codeWord);
    emit gameFinished(finished);
}

#endif // PLAYSPACE_CPP

