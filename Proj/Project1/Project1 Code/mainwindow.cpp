
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QApplication>

#include "mainwindow.h"

MainWindow::MainWindow(): TRIES(10),DEFAULTDIFFICULTY(3)
{
    QString image1(":/images/Bull-icon.png");
    QString image2(":/images/cow-icon.png");
    QPixmap bull(image1);
    QPixmap cow(image2);

    playSpace = new PlaySpace(bull, cow, TRIES);
    loginDialog = new LoginDialog;

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    setCentralWidget(playSpace);

    setWindowIcon(QIcon(":/images/bull-icon.png"));

}

void MainWindow::login(){
    loginDialog->show();
}

void MainWindow::newGame(){
    MainWindow *window = new MainWindow;
     window->show();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Bulls and Cows"),
            tr("<h2>Bulls and Cows 1.1</h2>"
               "<p>Copyright &copy; 2015 Marlo Zeroth."
               "<p>Bulls and Cows is a small application that "
               "demonstrates QNetwork, QMySQL, QAction, QMainWindow, QMenuBar, "
               "QStatusBar, QTableWidget, QToolBar, and many other "
               "Qt classes."));
}


void MainWindow::createActions(){

    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new bulls and cows game file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newGame()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the game to disk"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("Save &As..."), this);
    saveAsAction->setStatusTip(tr("Save the bulls and cows under a new "
                                  "name"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    loginAction = new QAction(tr("L&ogin"),this);
    loginAction->setIcon(QIcon(":/images/login-icon.png"));
    loginAction->setShortcut(tr("Ctrl+L"));
    loginAction->setStatusTip(tr("Login to the remote server"));
    connect(loginAction,SIGNAL(triggered()),this,SLOT(login()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(loginAction);
    separatorAction = fileMenu->addSeparator();
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createContextMenu(){

}

void MainWindow::createToolBars(){
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(loginAction);
}

void MainWindow::createStatusBar(){

    loginLabel = new QLabel(" Local Player - Not Logged in ");
    loginLabel->setAlignment(Qt::AlignHCenter);
    loginLabel->setMinimumSize(loginLabel->sizeHint());

    currentMoveLabel = new QLabel;
    currentMoveLabel->setIndent(3);

    statusBar()->addWidget(loginLabel);
    statusBar()->addWidget(currentMoveLabel, 1);

    updateStatusBar();
}

void MainWindow::updateStatusBar(){

}
