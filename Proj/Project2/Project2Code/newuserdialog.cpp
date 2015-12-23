#include <QRegularExpression>
#include <QRegExpValidator>
#include <QPushButton>

#include "newuserdialog.h"

NewUserDialog::NewUserDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    // Set validation for the QLineEdit objects for the fields
    QRegExp nameExp("[A-Za-z]{40}"); // Regular expression for names
    firstNameEdit->setValidator(new QRegExpValidator(nameExp,this));
    middleNameEdit->setValidator(new QRegExpValidator(nameExp,this));
    lastNameEdit->setValidator(new QRegExpValidator(nameExp,this));


    // Regular expressions to check valid user name, password and email
    QRegExp userExp("^[a-z0-9_@.]{4,40}$");
    QRegExp passwordExp("\\A((?=.*\\d)(?=.*[a-zA-Z])[a-zA-Z0-9!@#$%^&*]{6,20})\\z");
    QRegExp emailExp("^[a-z0-9_@.]{4,40}$"); // Regular expression for email
    // Set the validators
    userNameEdit->setValidator(new QRegExpValidator(userExp,this));
    passwordEdit->setValidator(new QRegExpValidator(userExp,this));
    passwordEdit->setEchoMode(QLineEdit::Password);
    emailEdit->setValidator(new QRegExpValidator(emailExp,this));

    connect(buttonBox,SIGNAL(accepted()),this,SLOT(createPlayer()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    connect(userNameEdit,SIGNAL(textChanged(QString)),this,SLOT(showOkButton(QString)));
}

void NewUserDialog::showOkButton(QString enable){
    if( !firstNameEdit->text().isEmpty() && !middleNameEdit->text().isEmpty()
            && !lastNameEdit->text().isEmpty() && !userNameEdit->text().isEmpty()
            && !passwordEdit->text().isEmpty() && !emailEdit->text().isEmpty()){
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void NewUserDialog::createPlayer(){
    Player newUser(0,firstNameEdit->text(),middleNameEdit->text(),lastNameEdit->text(),
                 userNameEdit->text(),passwordEdit->text(),emailEdit->text(),QDate::currentDate(),0);
    emit newPlayer(newUser);
    accept();
}
