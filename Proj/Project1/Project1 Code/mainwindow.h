#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QAction>
#include <QMenu>

#include "playspace.h"
#include "logindialog.h"

class MainWindow:public QMainWindow
{
    Q_OBJECT

public:    
    MainWindow();

private slots:
    void newGame();
    void about();
    void login(); // Opens the login dialog


private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void updateStatusBar();

    const unsigned int TRIES;
    const unsigned int DEFAULTDIFFICULTY;

    QLabel *loginLabel;
    QLabel *currentMoveLabel;
    LoginDialog *loginDialog;
    PlaySpace *playSpace;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;

    QAction *separatorAction;
    QAction *newAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *loginAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
};

#endif // MAINWINDOW_H
