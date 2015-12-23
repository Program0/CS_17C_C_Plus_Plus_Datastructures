/*
* File: mainwindow.h
* Interface file for MainWindow class. The class inherits from
* QWindow. It is the main class for displaying game.
* Author: Marlo Zeroth
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>

#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>

#include "playspace.h"
#include "logindialog.h"
#include "newuserdialog.h"
#include "newgamedialog.h"
#include "user.h"
#include "stack.h"
#include "queue"
#include "tree.h"
#include "connection.h"

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void newGame();
    void newSession();
    void newPlayer();
    void open();
    bool save();
    bool saveAs();
    void openRecentFile();
    void updateStatusBar();
    void gameModified();
    void about();
    void login(); // Opens the login dialog
    void createNewPlayer(const Player& player); // Creates a new player to register with the database
    void addPlayer(const Player &player);// Adds a player to the rankings tree
    void setLoggedUser(const User &user);

private:

    enum { MagicNumber = 0x7F51C883, DefaultTries = 10, DefaultDifficulty = 4 };

    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool okToContinue();    
    Connection createConnection();
    bool loadFile(const QString &file); // For loading an existing game stored locally
    QMap<QString,QString> loadImages(QFile &file); // For loading images to central widget
    bool saveFile(const QString &fileName); // Saving a game locally
    void setCurrentFile(const QString &fileName); // Sets the most current game at start up, if none it creates a new one    
    void updateRecentFileActions();
    QString strippedName(const QString &fileName);

    const unsigned int TRIES;
    const unsigned int DEFAULTDIFFICULTY;

    QFile *imageFiles;
    LoginDialog *loginDialog;
    NewUserDialog *newUserDialog;
    NewGameDialog *newGameDialog;
    PlaySpace *playSpace;
    Player *loginUser;
    Queue<Player> players;
    Tree<Player> rankings;
    List<Game> games;

    Connection currentConnection;

    QLabel *loginLabel;
    QLabel *currentMoveLabel;
    QStringList recentFiles;
    QString curFile;

    enum { MaxRecentFiles = 5 };
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QAction *newAction;
    QAction *newGameSession;
    QAction *addNewPlayer;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *loginAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
};


#endif // MAINWINDOW_H

