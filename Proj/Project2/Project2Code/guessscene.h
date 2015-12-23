/*
* File: guessscene.h
* Interface file for the GuessScene class.
* The class inherits from QGraphicsScene and is a storage
* for IconAcceptor objects which accept drag and drop events
* Author: Marlo Zeroth
*
*/

#ifndef GUESSSCENE_H
#define GUESSSCENE_H

#include <QWidget>
#include <QtWidgets>
#include <QGraphicsItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPixmap>
#include <QString>

#include "list.h"

class IconAcceptor:public QGraphicsObject{

public:
    IconAcceptor(QGraphicsItem *parent=0);
    // Main constructor

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;
    // Paints/redraws the image each time

    void clear();
    // Resets the default image and text.

    QString getValue() const {return value;}
    // Returns the stored value

    QPixmap getPixmap() const {return pixmap;}
    // Returns the stored pixmap

    QColor getColor(){return color;}
    // Returns the stored color       

    void updateImageValue(QString newValue, QPixmap newPix);

protected:    

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    // Executes when an item is dragged over the instantiated object

    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    // Executes when an item being dragged over the instatntiated object leaves
    // the areas

    void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    // Executes when an item is dropped into the instantiated object.
    // If the data passed is valid, it overrides the pixmap and the
    // value member variables and updates the displayed image
    // and value associated with the new image.

private:
    const QPixmap DEFAULTIMAGE; // Constant for the default image to display.
    QPixmap pixmap; // Image to display
    QString value; // Value of the image    
    QColor color;
    bool dragOver;
};

class GuessScene:public QGraphicsScene{
    Q_OBJECT

public:
    // Main constructor
    GuessScene(unsigned int size, QObject *parent = 0);

    QString text()const;
    // Returns a text string of values IconAcceptors

    void updateGuessScene(QMap<QString,QString> map, QString guess);
    // Updates the scene with new image values and respective paths

    int getSize() const;
    // Returns the current number of IconAcceptor objects stored

    void reset();
    // Resets the IconAcceptor object images  

    bool filled() const;
    void resize(const int &newSize);
    // Resizes and redraws the scene based on the input size

private:
    int iconWidth;
    int sceneHeight;
};

#endif // ICONSCENE_H

