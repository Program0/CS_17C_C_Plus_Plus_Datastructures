/*
* File: codedialog.h
* Interface file for CodeDialog class. The class inherits from
* QDialog. It used to get user generated codes for the game. It makes
* use of CodeScene and IconAcceptor objects which accept
* implement mousePressEvent, mouseMoveEvent, and mouseReleaseEvent
* and transport an icons text value during a drag event.
* Author: Marlo Zeroth
*/

#ifndef CODEDIALOG_H
#define CODEDIALOG_H

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

#include "codescene.h"
#include "guessscene.h"

class CodeDialog : public QDialog
{
    Q_OBJECT

public:
    CodeDialog(QMap<QString, QString> map, int length, QWidget *parent = 0);

public slots:
    void updateSize(const int &defaultTries);
    // Updates the size of the code generator view

    void setAllowDuplicates(bool dups);
    // Set whether to allow duplicates in the code generator view

signals:
    void startGame(QString word);
    // Emits the code word entered by the user in codeSetter

    void sizeChanged(int defaultTries)const;
    // Emits the new size

    void duplicatesChanged(bool);

private slots:
    void setGame(bool test);

private:
    bool duplicates;
    int defaultTries;
    QLabel *codeLabel;
    CodeScene *codeOptions;
    GuessScene *codeSetter;
    QGraphicsView *codeSceneView;
    QGraphicsView *guessSceneView;
    QPushButton *newGameButton;

    bool containsDuplicates(QString test);
    // Test the passed string for duplicate characters
};

#endif // CODEDIALOG_H

