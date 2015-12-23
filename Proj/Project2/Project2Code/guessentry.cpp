/*
* File: guessentry.cpp
* Implementation file for GuessEntry class. The class inherits from
* QWidget. It displays and accepts user entries for guesses for the
* game bulls and cows - a version predating mastermind.*
* Author: Marlo Zeroth
*/


#include <QMessageBox>
// For error output

#include "guessentry.h"

GuessEntry::GuessEntry(QMap<QString, QString> options, QPixmap bull, QPixmap cow, int size,
                       bool current, QWidget *parent, Qt::WindowFlags f):QWidget(parent,f){

    this->options = options; // Set the options available
    // Sets whether this is the current guess entry
    currentGuess = current;

    // Set the labels and images for the cow and bull labels
    bullLabel = new QLabel(parent);
    cowLabel = new QLabel(parent);    
    bullLabel->setPixmap(bull);
    bullLabel->setStyleSheet("background-color: green;");
    bullLabel->setFixedSize(50,50);
    cowLabel->setPixmap(cow);
    cowLabel->setStyleSheet("background-color: green;");
    cowLabel->setFixedSize(50,50);

    // Set the labels for the bull and cow counts
    cowCount = new QLabel(parent);
    bullCount = new QLabel(parent);
    cowCount->setStyleSheet("color: yellow; background-color: green; font: 18pt");
    bullCount->setStyleSheet("color: yellow; background-color: green; font: 18pt");
    cowCount->setFixedSize(50,50);
    cowCount->setAlignment(Qt::AlignCenter);
    bullCount->setAlignment(Qt::AlignCenter);
    bullCount->setFixedSize(50,50);
    cowCount->setText("");
    bullCount->setText("");

    // Prepare the guessAcceptor, guessView and push button
    guessAcceptor = new GuessScene(size,parent);
    guessView = new QGraphicsView;
    qreal width =guessAcceptor->sceneRect().width();
    qreal height=guessAcceptor->sceneRect().height();
    qreal padding = 10.0;
    guessView->setScene(guessAcceptor);
    guessView->setFixedSize(width+padding,height+padding);
    guessView->setSceneRect(0,0,width,height);
    guessView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    guessView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    checkButton = new QPushButton(tr("Check"));

    // By default set the button to hide and not enabled until
    // the entry is current
    checkButton->hide();
    guessView->setEnabled(false);    


    guessView->setStyleSheet("background-color: green;");

    // Set the checkButton to emit the guess when it is clicked
    connect(checkButton,SIGNAL(clicked(bool)),this,SLOT(guessFinished(bool)));

    // Create and set the layout
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(guessView,0,0);
    layout->addWidget(bullLabel,0,1);
    layout->addWidget(bullCount,0,2);
    layout->addWidget(cowLabel,0,3);
    layout->addWidget(cowCount,0,4);
    layout->addWidget(checkButton,0,5);
    layout->setMargin(1);
    //layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);

}

// Sets the GuessEntry current variable as true, enables checkButton,
// and guessAcceptor object.
void GuessEntry::setCurrent(bool status){
    if(status!=currentGuess){
        currentGuess = status;
        // Show the checkButton and enable the guessAcceptor
        guessView->setEnabled(status);
        checkButton->setVisible(status);
        emit current(currentGuess);
    }
}

// Sets the code word for the game.
void GuessEntry::setCodeWord(QString code){
    if(codeWord!=code){
        codeWord = code;
        emit codeWordChanged(code);
    }
}

// Resets the current and displayed QLabels
void GuessEntry::reset(){
    currentGuess = false;
    bullCount->setText("");
    cowCount->setText("");    
    guessAcceptor->reset();
    guessView->update();
    checkButton->setVisible(false);
}

// Checks the guessAcceptor entry with the passed codeWord. It sets the
// cowCount and bullCount QLabels to the current bulls and cows
// in the code word and guess made by the user.
void GuessEntry::guessFinished(bool test){

    // If neither the text nor the guess are empty check
    if(!codeWord.isEmpty()&&currentGuess){

        if(guessAcceptor->filled()){

            // Hide the check button and disable the guess acceptor and set this
            // guess as not current. This prepares to go to the next guess
            checkButton->hide();
            guessView->setEnabled(false);
            currentGuess = false;

            // Get the guess entered and check it
            QString guess = guessAcceptor->text();

            int cows = 0; // If letters are in the puzzle, but wrong spot
            int bulls = 0; // If letters are in the puzzle and right spot

            // Maps and sets for the code and guess
            QMap<QChar,int> codeMap;
            QMap<QChar,int> guessMap;
            QSet<QChar> guessSet;
            QSet<QChar> codeSet;

            for (int i = 0; i < codeWord.length(); i++) {
                guessSet.insert(guess[i]);
                codeSet.insert(codeWord[i]);

                if (guess[i] == codeWord[i])
                    bulls++;
                // Fill the maps of the code and the guess
                // if the QChar is in the map update its value
                // for both code and guess
                if(!codeMap.contains(codeWord[i])){
                    codeMap.insert(codeWord[i],1);
                }

                else{
                    int count = codeMap.value(codeWord[i]);
                    codeMap.insert(codeWord[i],(count+1));
                }

                if(!guessMap.contains(guess[i])){
                    guessMap.insert(guess[i],1);
                }
                else{
                    int count = guessMap.value(guess[i]);
                    guessMap.insert(guess[i],(count+1));
                }
             }

            // Get the intersection between the puzzleSet and guessSet characters.
            QSet<QChar> intersection = codeSet.intersect(guessSet);

            // Iterate through the intersection and find the total that are
            // in the code and how often they appear in the code
            foreach(QChar i,intersection){
                if(codeMap.value(i)<guessMap.value(i))
                    cows+=codeMap.value(i);
                else
                    cows+=guessMap.value(i);
            }

            // The difference between those in the right position and the total
            // the show up in the code will be those that are in the wrong position
            // and show in the code - the cows
            cows = cows - bulls;

            bullCount->setText(QString::number(bulls));
            cowCount->setText(QString::number(cows));

            if(guess==codeWord){
                // Send out if the code word is broken
                emit solved(true);
            }

            // The default value from QPushButton clicked() is false. We need to send opposite
            // signal to show this guess entry is finished.
            emit finished(!test);

            // Send out the user entered guess
            emit guessWord(guess,bulls, cows);
        }
        else{
            QMessageBox msgBx;
            msgBx.setText("Please enter a guess");
            msgBx.exec();
        }
    }
}

// Changes the size of the guessAcceptor based on the selected option
// from the difficulty QGroupButton class
void GuessEntry::setSize(int test){
    if(test!=guessAcceptor->getSize()){
        guessAcceptor->resize(test);
        // Update the view
        qreal width =guessAcceptor->sceneRect().width();
        qreal height=guessAcceptor->sceneRect().height();
        qreal padding = 10.0;
        guessView->setScene(guessAcceptor);
        guessView->setFixedSize(width+padding,height+padding);
        guessView->setSceneRect(0,0,width,height);
        guessView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        guessView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        guessView->update();
    }    
}

// Updates the guessScene, bull and cow labels to to the passed parameters.
// Also emits if this matches the code word and emits that the current guess
// is finished.
void GuessEntry::setGuess(QString guess, unsigned int bull, unsigned int cow){
    // If this is the current guess
    if(currentGuess){
        // Update the guess scene
        guessAcceptor->updateGuessScene(options,guess);

        // Update the bull and cow label
        bullCount->setText(QString::number(bull));
        cowCount->setText(QString::number(cow));

        // If this finishes the game emit solved
        if(guess==codeWord)
            emit solved(true);

        // Emit this completes this guess
        emit finished(true);
    }
}


