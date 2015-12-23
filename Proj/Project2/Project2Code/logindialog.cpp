#include <QMessageBox>
#include <QPushButton>
#include <QGridLayout>

#include "logindialog.h"


LoginDialog::LoginDialog(const Connection& connection, QWidget *parent) :
    QDialog(parent)
{
    // Set the connection to test
    currentConnection = connection;

    // Regular expressions to check valid user name and input
    QRegularExpression userExp("^[a-zA-Z0-9_@.-]{3,15}$");
    QRegularExpression passwordExp("^((?=.*[0-9])(?=.*[a-zA-Z])[a-zA-Z0-9!@#$%&*]{6,20})$");

    // Initialize the username and password line edits
    userNameLine = new QLineEdit(this);
    passwordLine = new QLineEdit(this);

    // Set up up the validators for the user and password lines
    userNameLine->setValidator(new QRegularExpressionValidator(userExp,this));
    passwordLine->setValidator(new QRegularExpressionValidator(passwordExp,this));
    passwordLine->setEchoMode(QLineEdit::Password);

    // Set the password line so that it does not show characters
   // passwordLine->setEchoMode(QLineEdit::Password);

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
    connect(buttonBox->button(QDialogButtonBox::Ok),SIGNAL(clicked(bool)),this,SLOT(slotAcceptLogin(bool)));

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
    if(currentConnection.connected){
        QSqlQuery query;
        unsigned int userId ;
        QString name;
        QString passP;
        QString first;
        QString last;
        QString middle;
        QString emailAddress;
        QDate birth;

        query.exec("SELECT user_id, user_name, password, first_name, last_name, middle_name, email, birthdate FROM users");
        while (query.next()) {
            userId = query.value(0).toUInt();
            name = query.value(1).toString();
            passP = query.value(2).toString();
            first = query.value(3).toString();
            last = query.value(4).toString();
            middle = query.value(5).toString();
            emailAddress = query.value(6).toString();
            birth = query.value(7).toDate();
        }

        if(name!=userNameLine->text()|| passP!=passwordLine->text()){
            msgBx.setText("Error: Please enter a valid username and password");
            msgBx.exec();
            emit loginSuccess(false);
        }
        else{
            User currentUser(userId,first,middle,last,name,passP,emailAddress,birth);
            emit acceptLogin(currentUser);
            emit loginSuccess(true);
        }

        currentConnection.db.close();
    }
    else{
        msgBx.setText("Not connected to server");
        msgBx.exec();
    }

}
