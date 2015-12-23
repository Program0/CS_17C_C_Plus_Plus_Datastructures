#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QRegularExpression> // For testing regular expressions
#include <QRegularExpressionValidator>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QGridLayout>

#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>



#include "user.h"
#include "connection.h"

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(const Connection& connection,QWidget *parent = 0);
    //~LoginDialog();

private slots:
    //void checkUserPassword();

signals:
    void acceptLogin(User);
    void loginSuccess(bool);

public slots:
    void slotAcceptLogin(bool);

private:
    QLabel *passwordLabel;
    QLabel *userLabel;
    QLineEdit *userNameLine;
    QLineEdit *passwordLine;
    QCheckBox *rememberCheckBox;
    QDialogButtonBox *buttonBox;
    Connection currentConnection;
};

#endif // LOGINDIALOG_H
