/*
* File: codescene.h
* Interface file for CodeScene class. The class inherits from
* QGraphicsScene. It stores IconHolder objects which accept
* implement mousePressEvent, mouseMoveEvent, and mouseReleaseEvent
* and transport an icons text value during a drag event
* Author: Marlo Zeroth
*/

#ifndef CODESCENE_H
#define CODESCENE_H

#include <QGraphicsItem>
#include <QList>
#include <QImage>
#include <QWidget>
#include <QGraphicsView>

#include "queue.h"

class IconHolder:public QGraphicsObject{
public:
    // Main constructor
    IconHolder(QString value, QString imagePath, QGraphicsItem *parent = 0);

    // Destructor
    //~IconHolder();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QString getValue() const {return imageValue;}
    // Returns the stored value

    QPixmap getPixmap() const {return pixmap;}
    // Returns the stored pixmap


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QPixmap pixmap;
    QString imageValue;
};

// Class to hold a queue of IconHolder objects.
class CodeScene:public QGraphicsScene{

    Q_OBJECT

public:
    // Main constructor
    CodeScene(QMap<QString,QString> map, QObject *parent=0);

    // Destructor
    //~ImageChooser();

    QString text() const;
    // Returns a text string of values IconChoooser objects

    void updateImages(QMap<QString,QString> map);
    // Updates the internal images of the IconHolder objects
private:

    int sceneHeight; // Determines the height of the scene
    int iconWidth; // Width of the icons. Determines how far apart icons will be

};

#endif // CODESCENE_H

