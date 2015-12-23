#include "newgamedialog.h"

NewGameDialog::NewGameDialog(QMap<QString,QString> map, QWidget *parent) : QDialog(parent){

    codeComponents = map;
    // Iterate through the map to get the available code options
    QMap<QString,QString>::iterator i;
    QMap<QString,QString>::iterator end = codeComponents.end();
    for(i=codeComponents.begin();i!=end;i++){
        codeOptions = codeOptions+i.key();
    }

    // Create the difficulty radio button group
    QGroupBox *difficultyRadioBox = createDifficultyBox();
    QGroupBox *groupOptionsBox = createOptionsBox();

    // Set the bottom layout
    QVBoxLayout *bottomLayout = new QVBoxLayout;
    bottomLayout->addWidget(difficultyRadioBox);
    bottomLayout->addWidget(groupOptionsBox);


    // Create a dialog for entering the code
    codeEntry = new CodeDialog(map,difficulty->checkedId(),parent);

    // Connect the slots for several of the objects such as when the newGameButton is pressed
    // a new game starts
    connect(newGameButton,SIGNAL(clicked(bool)),this,SLOT(newGame(bool)));
    connect(difficulty,SIGNAL(buttonPressed(int)),codeEntry,SLOT(updateSize(int)));
    connect(codeEntry,SIGNAL(startGame(QString)),this,SLOT(setCode(QString)));
    connect(duplicates,SIGNAL(toggled(bool)),codeEntry,SLOT(setAllowDuplicates(bool)));
    connect(codeEntry,SIGNAL(startGame(QString)),this,SLOT(setCode(QString)));

    setLayout(bottomLayout);
    setWindowTitle("Start New Game");
    setModal(true);

}

void NewGameDialog::setCode(const QString &entry){
    emit codeChanged(entry);
}

void NewGameDialog::newGame(bool start){

    if(!start){
        emit playerOneRole(playerRole->currentIndex());
        emit duplicatesAllowed(duplicates->isChecked());
        emit codeLength(difficulty->checkedId());
        // Get the code word for the game
        if(playerRole->currentIndex()==1){
            codeEntry->show();
        }
        else{
            emit codeChanged(generateCode());
        }
        setVisible(false);
    }
}

// Generates a QString code based on available code components
QString NewGameDialog::generateCode(){

    QString randomCode("");
    int optionSize = codeComponents.size();
    QString optionString = codeOptions;
    int codeSize = difficulty->checkedId();
    if(!duplicates->isChecked()){
        QString charOptions = optionString;
        // Iterate through the available options and concatenate a string based
        // on a pseudo-random choice of its letters until the requested sized
        // string is generated.
        for(int i = 0; i<codeSize;i++){
            QString charToAdd;
            if(charOptions.size()>1)
                charToAdd=QString(charOptions[qrand()% (charOptions.size()-1)]);
            else
                charToAdd=QString(charOptions[0]);
            randomCode = (randomCode+charToAdd);
            if(charOptions.size()>1)
                charOptions=charOptions.remove(charToAdd,Qt::CaseInsensitive);
        }
    }

    else{
        // Iterate through the available options and concatenate a string based
        // on a pseudo-random choice of its letters.
        for(int i = 0; i<codeSize;i++){
            randomCode = (randomCode+QString(optionString[qrand()% (optionSize-1)]));
        }
    }
    return randomCode;
}

// Creates a difficulty QGroupBox of radio buttons
QGroupBox* NewGameDialog::createDifficultyBox(){

    // Length of code and guess entries accepted
    int easyDiff = 4;
    int midDiff = 6;
    int hardDiff = 8;

    // Set the difficulty
    difficulty = new QButtonGroup;
    QGroupBox *difficultyRadioBox = new QGroupBox(tr("Difficulty:"));
    QRadioButton *easy = new QRadioButton(tr("Easy: "));
    QRadioButton *medium = new QRadioButton(tr("Medium:"));
    QRadioButton *hard = new QRadioButton(tr("Hard:"));

    // Make it be an exclusive group box
    easy->setChecked(true);
    // Add the buttons to the difficulty button group
    difficulty->addButton(easy);
    difficulty->addButton(medium);
    difficulty->addButton(hard);

    // Set the values for the difficulty
    difficulty->setId(easy,easyDiff);
    difficulty->setId(medium,midDiff);
    difficulty->setId(hard,hardDiff);

    // Create a layout for the game options difficulty
    QHBoxLayout *diffLayout = new QHBoxLayout;
    diffLayout->addWidget(easy);
    diffLayout->addWidget(medium);
    diffLayout->addWidget(hard);

    difficultyRadioBox->setLayout(diffLayout);

    return difficultyRadioBox;
}

// Creates a QGroupBox of a QComboBox and QPushButton
QGroupBox* NewGameDialog::createOptionsBox(){

    // Prepare the playerRole combo box
    playerRole = new QComboBox;
    QStringList options;
    options<< "Breaker" <<"Creator";
    playerRole->addItems(options);

    codeLabel = new QLabel;
    codeLabel->setText(tr("Player Role:"));
    codeLabel->setBuddy(playerRole);

    duplicates = new QCheckBox(tr("Allow &duplicates?"));
    duplicates->setChecked(true);

    // Create a new game button
    newGameButton = new QPushButton("New Game");


    // Create a layout for the role and new game button
    QHBoxLayout *roleLayout = new QHBoxLayout;
    roleLayout->addWidget(codeLabel);
    roleLayout->addWidget(playerRole);
    roleLayout->addWidget(duplicates);
    roleLayout->addWidget(newGameButton);

    // Create the button group
     QGroupBox *groupBox = new QGroupBox(tr("Player Options:"));

    groupBox->setLayout(roleLayout);
    return groupBox;
}
