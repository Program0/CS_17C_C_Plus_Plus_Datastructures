#ifndef NEWUSERDIALOG_H
#define NEWUSERDIALOG_H

#include <QDialog>

#include "ui_newuserdialog.h"
#include "player.h"

class NewUserDialog : public QDialog, public Ui::NewUserDialog
{
    Q_OBJECT

public:    
    explicit NewUserDialog(QWidget *parent = 0);
public slots:    
    void createPlayer();
private slots:
    void showOkButton(QString enable);
signals:
    void newPlayer(Player);

};

#endif // NEWUSERDIALOG_H
