#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>

class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    NewGameDialog(QWidget *parent = 0);

signals:
    void roleChanged(int);
    // Emits

    void startGame(QString word, int difficulty);
    // Emits the code word entered by the user in lineEdit

private slots:
    //void start(QString word);
    void setRole(int role);
    void setGame(bool test);
    void setValidation(int test);

private:
    QGroupBox *role;
    QLabel *codeLabel;
    QLineEdit *lineEdit;
    QButtonGroup *difficulty;
    QGroupBox *difficultyRadioBox;   
    QComboBox *playerRole;
    QPushButton *newGameButton;
    QPushButton *quitButton;

};

#endif // NEWGAMEDIALOG_H

