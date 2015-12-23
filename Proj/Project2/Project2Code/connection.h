#ifndef CONNECTION
#define CONNECTION

#include <QSqlDatabase>

// Struct for create database connections
struct Connection{
    QSqlDatabase db;
    bool connected;
};

#endif // CONNECTION

