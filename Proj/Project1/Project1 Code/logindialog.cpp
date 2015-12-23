#include "logindialog.h"
#include <QMessageBox>
#include <QPushButton>
#include <QGridLayout>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{
    // Regular expressions to check valid user name and input
    QRegExp userExp("^[a-z0-9_-@.]{3,15}$");
    QRegExp passwordExp("((?=.[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[@#$%]).{8,20})");

    // Initialize the username and password line edits
    userNameLine = new QLineEdit(this);
    passwordLine = new QLineEdit(this);

    // Set up up the validators for the user and password lines
    userNameLine->setValidator(new QRegExpValidator(userExp,this));
    passwordLine->setValidator(new QRegExpValidator(passwordExp,this));

    // Set the password line so that it does not show characters
    passwordLine->setEchoMode(QLineEdit::Password);

    // Initialize the labels and set their buddys
    userLabel = new QLabel(this);
    passwordLabel = new QLabel(this);
    userLabel->setText((tr("Username")));
    passwordLabel->setText((tr("Password")));
    userLabel->setBuddy(userNameLine);
    passwordLabel->setBuddy(passwordLine);

    // Initialize and set up the buttons
    buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Login"));
    buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));

    // Connect the buttons slots and signals
    connect(buttonBox->button(QDialogButtonBox::Cancel),SIGNAL(clicked()),this,SLOT(close()));
    connect(buttonBox->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(slotAcceptLogin()));

    // Now create and set the layout
    QGridLayout *formLayout = new QGridLayout(this);
    formLayout->addWidget(userLabel,0,0);
    formLayout->addWidget(userNameLine,0,1);
    formLayout->addWidget(passwordLabel,1,0);
    formLayout->addWidget(passwordLine,1,1);
    formLayout->addWidget(buttonBox,2,0,1,2);

    setLayout(formLayout);

    // Set the window title and whether it is modal>
    setWindowTitle(tr("User Login"));
    setModal(true);
}

void LoginDialog::slotAcceptLogin(bool){
    QMessageBox msgBx;
    msgBx.setText("Pressed Ok");
    msgBx.exec();

}
