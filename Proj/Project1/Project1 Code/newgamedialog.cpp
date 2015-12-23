#ifndef NEWGAMEDIALOG_CPP
#define NEWGAMEDIALOG_CPP

#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>

#include "newgamedialog.h"

NewGameDialog::NewGameDialog(QWidget *parent):QDialog(parent){
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
    connect(newGameButton,SIGNAL(clicked(bool)),this,SLOT(setGame(bool)));
    connect(difficulty,SIGNAL(buttonPressed(int)),this,SLOT(setValidation(int)));

    QHBoxLayout *gameLayout = new QHBoxLayout;
    gameLayout->addWidget(difficultyRadioBox);
    gameLayout->addWidget(role);
    gameLayout->addWidget(newGameButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(diffLayout);
    mainLayout->addLayout(roleLayout);
    mainLayout->addLayout(gameLayout);

    //setModal(true);
    setWindowTitle("New Game");
    //setFixedHeight(sizeHint().height());
    setLayout(mainLayout);
}

// Set the label and lineEdit for getting the code word
// visible or invisible
void NewGameDialog::setRole(int role){
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
void NewGameDialog::setValidation(int test){
    if(test>0){
        // Set a regular expression to ensure guesses entered are only the
        // required length from the radio buttons for difficulty
        QRegExp guessExp(QString("[A-Za-z]{")+QString::number(test)+QString("}"));
        lineEdit->setValidator(new QRegExpValidator(guessExp,this));
    }
}

// Starts a new game with the entered code word and difficulty
// signal
void NewGameDialog::setGame(bool test){
    if(!test){
        QString code = lineEdit->text();
        int diff = difficulty->checkedId();
        emit startGame(code,diff);
        QMessageBox msgBx;
        msgBx.setText(code);
        msgBx.exec();
    }
}

#endif // NEWGAMEDIALOG_CPP

