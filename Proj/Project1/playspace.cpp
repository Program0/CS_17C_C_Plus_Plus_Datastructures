#ifndef PLAYSPACE_CPP
#define PLAYSPACE_CPP

#include <QMessageBox>

#include "playspace.h"

PlaySpace::PlaySpace(QPixmap bull, QPixmap cow, unsigned int size, QWidget *parent, Qt::WindowFlags f):QWidget(parent,f){

    totalGuesses = size;
    currentGuess = 0;

    // Set the difficulty
    difficulty = new QButtonGroup;
    difficultyRadioBox = new QGroupBox(tr("Difficulty:"));
    QRadioButton *easy = new QRadioButton(tr("Easy: "));
    QRadioButton *medium = new QRadioButton(tr("Medium:"));
    QRadioButton *hard = new QRadioButton(tr("Hard:"));
    QRadioButton *harder = new QRadioButton(tr("Harder:"));

    medium->setChecked(true);
    // Add the buttons to the difficulty button group
    difficulty->addButton(easy);
    difficulty->addButton(medium);
    difficulty->addButton(hard);
    difficulty->addButton(harder);

    // Set the values for the difficulty
    difficulty->setId(easy,3);
    difficulty->setId(medium,4);
    difficulty->setId(hard,5);
    difficulty->setId(harder,6);

    // Create a layout for the difficulty
    QVBoxLayout *diffLayout = new QVBoxLayout;
    diffLayout->addWidget(easy);
    diffLayout->addWidget(medium);
    diffLayout->addWidget(hard);
    diffLayout->addWidget(harder);

    difficultyRadioBox->setLayout(diffLayout);

    role = new QGroupBox(tr("Player Role"));
    // Prepare the playerRole combo box
    playerRole = new QComboBox(parent);
    QStringList options;
    options<< "Breaker" <<"Creator";
    playerRole->addItems(options);

    // Set the code label and line edit for the code word
    codeLabel = new QLabel(parent);
    codeLabel->setText("Enter Code Word: ");
    lineEdit = new QLineEdit;
    lineEdit->setStyleSheet("color:blue; background-color: yellow; font: 18pt");
    lineEdit->setFixedWidth(100);
    codeLabel->setBuddy(lineEdit);

    QVBoxLayout *roleLayout = new QVBoxLayout;
    roleLayout->addWidget(playerRole);
    roleLayout->addWidget(codeLabel);
    roleLayout->addWidget(lineEdit);

    // Hide the codeLabel and lineEdit.
    codeLabel->setVisible(false);
    lineEdit->setVisible(false);
    // Set it so characters are hidden like in password entry
    lineEdit->setEchoMode(QLineEdit::Password);

    role->setLayout(roleLayout);

    newGameButton = new QPushButton("New Game",parent);

    connect(playerRole,SIGNAL(currentIndexChanged(int)),this,SLOT(setRole(int)));
    connect(newGameButton,SIGNAL(clicked(bool)),this,SLOT(newGame(bool)));
    connect(difficulty,SIGNAL(buttonPressed(int)),this,SLOT(setValidation(int)));

    QHBoxLayout *gameLayout = new QHBoxLayout;
    gameLayout->addWidget(difficultyRadioBox);
    gameLayout->addWidget(role);
    gameLayout->addWidget(newGameButton);

    QVBoxLayout *bottomLayout = new QVBoxLayout;
    bottomLayout->addLayout(diffLayout);
    bottomLayout->addLayout(roleLayout);
    bottomLayout->addLayout(gameLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout;

    // Create GuessEntry objects and connect the bullsCows signal to their setBullsCows slots
    for(unsigned int i = 0; i<size;i++){
        GuessEntry *entry = new GuessEntry(bull, cow, false,parent,f);
        rightLayout->addWidget(entry);
        connect(this,SIGNAL(codeChanged(QString)),entry,SLOT(setCodeWord(QString)));
        connect(difficulty,SIGNAL(buttonPressed(int)),entry,SLOT(setValidation(int)));
        guessInterface.prepend(entry);
    }

    // Iterators for current and its next GuessEntry object in the list
    List<GuessEntry*>::iterator next = guessInterface.begin();
    List<GuessEntry*>::iterator curr = next++;
    List<GuessEntry*>::iterator finish = guessInterface.end();

    // Go through each guessInterface object in the list and connect it to its adjacent
    // object
    while(next!=finish){
        connect(*curr,SIGNAL(finished(bool)),*next,SLOT(setCurrent(bool)));
        curr++;
        next++;
    }

    rightLayout->addLayout(bottomLayout);

    // Add the game start button and difficulty comboboxes
    // Set the first guess entry as the current entry    
    setLayout(rightLayout);
    //guessInterface.first()->setCurrent(true);
}

// Set the label and lineEdit for getting the code word
// visible or invisible
void PlaySpace::setRole(int role){
    if(role==1){
        codeLabel->setVisible(true);
        lineEdit->setVisible(true);
    }else{
        codeLabel->setVisible(false);
        lineEdit->setVisible(false);
    }
}

// Changes the validation on the lineEdit based on the selected option
// from the difficulty QGroupButton class
void PlaySpace::setValidation(int test){
    if(test>0){
        // Set a regular expression to ensure guesses entered are only the
        // required length from the radio buttons for difficulty
        QRegExp guessExp(QString("[A-Za-z]{")+QString::number(test)+QString("}"));
        lineEdit->setValidator(new QRegExpValidator(guessExp,this));
    }
}

// Starts a new game with the entered code word and difficulty
// signal
void PlaySpace::newGame(bool test){
    if(!test){
        QMessageBox msgBx;
        msgBx.setText("Test is true");
        msgBx.exec();
    }

    if(!test){
        // Set the code word for the game
        QString code = lineEdit->text().toUpper();
        emit codeChanged(code);

        // Reset the current status of the individual GuessEntry objects
        // Iterators for current and its next GuessEntry object in the list
        List<GuessEntry*>::iterator curr = guessInterface.begin();
        List<GuessEntry*>::iterator finish = guessInterface.end();

        // Go through each guessInterface object in the list and reset current to false
        while(curr!=finish){
            (*curr)->reset();
            curr++;
        }
        guessInterface.first()->setCurrent(true);
    }
}

/*
void PlaySpace::resetPlay(){


}
*/

#endif // PLAYSPACE_CPP

