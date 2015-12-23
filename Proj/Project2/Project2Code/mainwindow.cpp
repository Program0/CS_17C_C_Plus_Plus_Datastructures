
#include "mainwindow.h"

MainWindow::MainWindow():TRIES(10), DEFAULTDIFFICULTY(4){

    loginUser = NULL; // Start out logged out
    imageFiles = new QFile(":/text/code_options.txt");
    QMap<QString,QString> map = loadImages(*imageFiles);
    playSpace = new PlaySpace(map,DEFAULTDIFFICULTY,TRIES);
    playSpace->setStyleSheet("background-color: green;");
    setCentralWidget(playSpace);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();

    currentConnection = createConnection();
    loginDialog =  new LoginDialog(currentConnection, this);
    newUserDialog = new NewUserDialog;
    newGameDialog = new NewGameDialog(map,this);

    // Connect the dialogs and playSpace with this window
    connect(newGameDialog,SIGNAL(codeChanged(QString)),playSpace,SLOT(updatePlayspace(QString)));
    connect(playSpace,SIGNAL(gameFinished(bool)),newGameDialog,SLOT(setVisible(bool)));
    // Connect the newuser dialog with the add player and create new player
    connect(newUserDialog,SIGNAL(newPlayer(Player)),this,SLOT(addPlayer(Player)));
    connect(newUserDialog,SIGNAL(newPlayer(Player)),this,SLOT(createNewPlayer(Player)));
    connect(loginDialog,SIGNAL(acceptLogin(User)),this,SLOT(setLoggedUser(User)));


    //setAttribute(Qt::WA_DeleteOnClose);
    // Release memory when the application closes

    setWindowIcon(QIcon(":/images/bull-icon.png"));
    setCurrentFile("");
    newGameDialog->show();
}

void MainWindow::login(){
    loginDialog->show();
}

void MainWindow::addPlayer(const Player& player){
    if(!rankings.contains(player))
        rankings.insert(player);
}

void MainWindow::setLoggedUser(const User& user){

    if(loginUser){
        // Release the memory held by the current user
        delete loginUser;
        loginUser = new Player(user,0);
    }
    else{
        loginUser = new Player(user,0);
    }
}

Connection MainWindow::createConnection(){
    QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","QMYSQLCSC17B");
    // Create database object to access remote database

    // Set the login information
    db.setHostName("209.129.8.2");
    db.setDatabaseName("mastermind");
    db.setUserName("48941");
    db.setPassword("48941cis17b");


    Connection connection;
    connection.db = db;
    if (!db.open()) {
        QMessageBox msgBx;
        msgBx.setText("Error connecting to remote server.");
        msgBx.exec();
        connection.connected = false;
        return connection;
    }
    connection.connected = true;
    return connection;
}

void MainWindow::closeEvent(QCloseEvent *event){
    if (okToContinue()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newGame(){
    // Open multiple instances of the application    
    newGameDialog->show();
}

// Creates a new game window session
void MainWindow::newSession(){
    MainWindow *window = new MainWindow;
    window->show();
}

void MainWindow::newPlayer(){
    newUserDialog->show();
}

void MainWindow::createNewPlayer(const Player &player){
    QMessageBox msgBx;
    if(currentConnection.connected){
        QSqlQuery query;
        unsigned int userId = player.getUserID();
        QString userName = player.getUserName();
        QString passP = player.getPassword();
        QString first = player.getFirstName();
        QString last = player.getLastName();
        QString middle = player.getMiddleName();
        QString email = player.getEmail();
        QDate birth = player.getBirthDate();

        QString queryText(QString("INSERT INTO users (user_id, user_name, password, first_name, last_name, ")+
                          QString("middle_name, email, birthdate)") +
                          QString(" VALUES(:userId,:userName,:passP,:first,:last,:middle,:email,:birth)"));

        query.prepare(queryText);
        query.bindValue(":userId",userId);
        query.bindValue(":userName",userName);
        query.bindValue(":passP",passP);
        query.bindValue(":first",first);
        query.bindValue(":middle",middle);
        query.bindValue(":last",last);
        query.bindValue(":email",email);
        query.bindValue(":birth",birth);
        query.exec();

        currentConnection.db.close();
    }
    else{
        msgBx.setText("Not connected to server");
        msgBx.exec();
    }
}

void MainWindow::open(){
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open Bulls and Cows"), ".",
                                   tr("Bulls and Cows files (*.bc)"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}
bool MainWindow::save(){
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs(){
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Save game"), ".",
                               tr("Game files (*.bc)"));
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
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

void MainWindow::openRecentFile(){
    if (okToContinue()) {
        QAction *action = qobject_cast<QAction *>(sender());
        if (action)
            loadFile(action->data().toString());
    }
}

void MainWindow::updateStatusBar(){

}

void MainWindow::gameModified(){

}

void MainWindow::createActions(){

    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new bulls and cows game file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newGame()));

    newGameSession = new QAction(tr("New&Session"),this);
    newGameSession->setIcon(QIcon(":/images/new-session-icon.png"));
    newGameSession->setStatusTip("Open a new game session");
    connect(newGameSession, SIGNAL(triggered()), this, SLOT(newSession()));

    addNewPlayer = new QAction(tr("&AddPlayer"),this);
    addNewPlayer->setIcon(QIcon(":/images/new-player-icon.png"));
    addNewPlayer->setStatusTip("Open a new game session");
    connect(addNewPlayer, SIGNAL(triggered()), this, SLOT(newPlayer()));


    openAction = new QAction(tr("&Open..."), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing bulls and cows game file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the game to disk"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("Save &As..."), this);
    saveAsAction->setStatusTip(tr("Save the bulls and cows under a new "
                                  "name"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()),
                this, SLOT(openRecentFile()));
    }

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
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(loginAction);
    fileMenu->addAction(newGameSession);
    fileMenu->addAction(addNewPlayer);
    separatorAction = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
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
    fileToolBar->addAction(openAction);
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

void MainWindow::readSettings(){

}

void MainWindow::writeSettings(){

}

bool MainWindow::okToContinue(){
    return true;
}

bool MainWindow::loadFile(const QString &fileName){

    QFile file(fileName);

    // Test the file to ensure it opened
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        std::cerr<<"Cannot open file for reading "
                <<qPrintable(file.errorString())<<std::endl;

    // Iterate through the stream and load into the game
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_5);

    quint32 magic;
    in>>magic;
    if(magic!=MagicNumber){
        QMessageBox::warning(this, tr("Bulls and Cows Game"),
                             tr("The file is not a Bulls and Cows file."));
        return false;

    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    while(!in.atEnd()){
       Game game;
       in >>game;
       games.append(game);

    }
    QApplication::restoreOverrideCursor();
    playSpace->loadGame(games.first());
    return true;
}

QMap<QString, QString> MainWindow::loadImages(QFile &file){
    // Creates a value pair image key (a string) and image value path (path to icon)
    QMap<QString,QString> map;

    // Test the file to ensure it opened
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        std::cerr<<"Cannot open file for reading "
                <<qPrintable(file.errorString())<<std::endl;

    // Iterate through the text stream and load into the map
    QTextStream in(&file);

    while(!in.atEnd()){
       QString line = in.readLine();
       QStringList iconList;
       iconList=line.split("\t");
       std::cerr<<"Size of list "<<iconList.size()<<std::endl;
       QString iconValue = iconList.takeFirst();
       QString iconImage = QString(":/images/"+iconList.takeFirst());
       map.insert(iconValue,iconImage);
    }
    return map;
}

bool MainWindow::saveFile(const QString &fileName){

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Bulls and Cows"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint32(MagicNumber);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    List<Game>::iterator i;
    List<Game>::iterator finish = games.end();
    for (i=games.begin();i!=finish;i++) {
        out<<*i;
    }
    QApplication::restoreOverrideCursor();
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName){

}

void MainWindow::updateRecentFileActions(){

}

QString MainWindow::strippedName(const QString &fileName){
    QString a("a");
    return a;
}
