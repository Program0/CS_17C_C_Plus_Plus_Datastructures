#include <QMessageBox>

#include "guessentry.h"

GuessEntry::GuessEntry(QPixmap bull, QPixmap cow,
                       bool current, QWidget *parent, Qt::WindowFlags f):QWidget(parent,f){

    // Sets whether this is the current guess entry
    currentGuess = current;

    // Set the labels and images for the cow and bull labels
    bullLabel = new QLabel(parent);
    cowLabel = new QLabel(parent);    
    bullLabel->setPixmap(bull);
    cowLabel->setPixmap(cow);

    // Set the labels for the bull and cow counts
    cowCount = new QLabel(parent);
    bullCount = new QLabel(parent);
    cowCount->setStyleSheet("color: blue; background-color: yellow; font: 18pt");
    bullCount->setStyleSheet("color: blue; background-color: yellow; font: 18pt");
    cowCount->setFixedSize(40,40);
    cowCount->setAlignment(Qt::AlignCenter);
    bullCount->setAlignment(Qt::AlignCenter);
    bullCount->setFixedSize(40,40);
    cowCount->setText("");
    bullCount->setText("");

    // Prepare the line edit and push button
    lineEdit = new QLineEdit;
    lineEdit->setStyleSheet("color:blue; background-color: yellow; font: 18pt");
    lineEdit->setFixedWidth(100);
    checkButton = new QPushButton(tr("Check"));

    // By default set the button to hide and not enabled until
    // the entry is current
    lineEdit->setEnabled(false);
    checkButton->hide();
    checkButton->setEnabled(false);

    // Set the guessEntry lineEdit to enable/disable the checkButton when it is filled/emptied
    connect(lineEdit,SIGNAL(textChanged(const QString &)),this,SLOT(enableCheck(const QString &)));
    // Set the checkButton to emit the guess when it is clicked
    connect(checkButton,SIGNAL(clicked(bool)),this,SLOT(guessFinished(bool)));

    // Create and set the layout
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(lineEdit,0,0);
    layout->addWidget(bullLabel,0,1);
    layout->addWidget(bullCount,0,2);

    layout->addWidget(cowLabel,0,3);
    layout->addWidget(cowCount,0,4);
    layout->addWidget(checkButton,0,5);
    layout->setMargin(1);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);

}

// Sets the GuessEntry current variable as true, enables checkButton,
// and guessEntry lineEdit.
void GuessEntry::setCurrent(bool status){
    if(status!=currentGuess){
        currentGuess = status;
        // Show the checkButton and enable the lineEdit
        lineEdit->setEnabled(status);
        checkButton->show();
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
    lineEdit->clear();
    lineEdit->setEnabled(false);
}

// Checks the lineEdit entry with the passed codeWord. It sets the
// cowCount and bullCount QLabels to the current bulls and cows
// in the code word and guess made by the user.
void GuessEntry::guessFinished(bool test){

    // If neither the text nor the guess are empty check
    if(!codeWord.isEmpty()&&currentGuess){

        checkButton->hide();
        lineEdit->setEnabled(false);
        currentGuess = false;

        QString guess = lineEdit->text().toUpper();
        unsigned int cows = 0; // If letters are in the puzzle, but wrong spot
        unsigned int bulls = 0; // If letters are in the puzzle and right spot

        // Maps for the guess and puzzle
        QSet<QChar> puzzleSet;
        QSet<QChar> guessSet;

        for (int i = 0; i < codeWord.length(); i++) {
            if (guess[i] == codeWord[i])
                bulls++;
                // Fill both sets with the frequency value for each letter key
                puzzleSet.insert(codeWord[i]);
                guessSet.insert(guess[i]);
             }

        // Get the intersection between the puzzleSet and guessSet characters.
        // The difference between the characters that are in the correct position
        // and the size of the intersection will the number of characters that
        // are in the code word, but wrong position.

        QSet<QChar> intersection = puzzleSet.intersect(guessSet);
        cows = intersection.size() - bulls;

        bullCount->setText(QString::number(bulls));
        cowCount->setText(QString::number(cows));

        if(guess==codeWord){
            // Send out if the code word is broken
            emit solved(true);
        }
        else{
            // The default value from QPushButton clicked() is false. We need to send opposite
            // signal to show this guess entry is finished.
            emit finished(!test);
        }
        // Send out the user entered guess
        emit guessWord(guess,bulls, cows);
    }
}

// Enables the check button only if the user has typed in
// valid text in the lineEdit control.
void GuessEntry::enableCheck(const QString &text){
     // Enable the button if the text is not empty
    checkButton->setEnabled(!text.isEmpty() && currentGuess);
}

// Changes the validation on the lineEdit based on the selected option
// from the difficulty QGroupButton class
void GuessEntry::setValidation(int test){
    if(test>0){
        // Set a regular expression to ensure guesses entered are only the
        // required length from the radio buttons for difficulty
        QRegExp guessExp(QString("[A-Za-z]{")+QString::number(test)+QString("}"));
        lineEdit->setValidator(new QRegExpValidator(guessExp,this));
    }
}


