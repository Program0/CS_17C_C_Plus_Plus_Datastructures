/*
* File: codescene.h
* Implementation file for CodeScene class. The class inherits from
* QGraphicsScene. It stores IconHolder objects which accept
* implement mousePressEvent, mouseMoveEvent, and mouseReleaseEvent
* and transport an icons text value during a drag event
* Author: Marlo Zeroth
*/

#include <QtWidgets>
#include "codescene.h"

// Main constructor
IconHolder::IconHolder(QString value, QString imagePath, QGraphicsItem *parent):QGraphicsObject(parent),
    pixmap(imagePath),imageValue(value){

    // Tool tip to show when the left mouse button is pressed on image
    setToolTip(QString("Click and drag this animal onto the slot!"));
    // Set the cursor to show an open hand when the left mouse button is pressed
    setCursor(Qt::OpenHandCursor);
    // Set it so only the left mouse button can be pressed
    setAcceptedMouseButtons(Qt::LeftButton);    
}

// Used to set the bounding rectangle when the icons are drawn.
// Overrides the QGraphicsObject boudingRect() function
QRectF IconHolder::boundingRect() const{
    return QRectF(QPointF(0,0),QSize(40,40));
}

// Used to paint the icons. Overrides the QGraphicsObject paint function
void IconHolder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    // Overrides the paint event for QGraphicsObject
    // Set the unused macro for option and widget so wont complain at compile
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // If there is no image, display a circle bounded by a rectangle 40 by 40
    if(pixmap.isNull()){
        painter->setBrush(QColor("red"));
        painter->drawEllipse(QRectF(0,0,40,40));
    }
    else{
        painter->scale(1,1);
        painter->drawPixmap(QPointF(0,0),pixmap);
    }
}

void IconHolder::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);
    // Set the cursor to be closed hand when the left mouse button is pressed
    setCursor(Qt::ClosedHandCursor);
}

void IconHolder::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    // Test to make sure the position of the mouseMoveEvent is valid
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }

    // Create a drag event and its mime data
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    mime->setText(imageValue);
    mime->setImageData(pixmap);
    drag->setMimeData(mime);

    // Set image that will be draged
    drag->setPixmap(QPixmap(pixmap.scaled(40,40)));
    drag->setHotSpot(QPoint(15,30));

    // Execute the drag event
    drag->exec();

    // Set the cursor to be open hand
    setCursor(Qt::OpenHandCursor);

}

void IconHolder::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);
    // Set the cursor to show an open hand when it is realeased
    setCursor(Qt::OpenHandCursor);
}

// Accepts a map whose key is the first letter of an animal and value is the file path to its image.
CodeScene::CodeScene(QMap<QString, QString> map, QObject *parent):QGraphicsScene(parent){

    // Set the icon width, scene height and create a new scene
    iconWidth = 40;
    sceneHeight = 40;

    // Iterate through the map, create a new IconHolder object and add it to the scene
    QMap<QString,QString>::iterator i;

    int count = 0;
    for(i = map.begin(); i!=map.end();i++){
        // Create an IconHolder object with the image value and image path
        IconHolder *chooser = new IconHolder(i.key(),i.value());
        chooser->setPos(count*iconWidth,0);

        // Add the new chooser to the scene and icons queue
        addItem(chooser);

        // Increment the count to adjust the spacing
        count++;
    }
}

// Updates the ImageChooser to the map of image paths and values
void CodeScene::updateImages(QMap<QString, QString> map){

    // Empty the scene
    clear();

    // Iterate through the map, create a new IconHolder object and add it to the scene and
    // internal icons queue
    QMap<QString,QString>::iterator i;

    int count = 0;
    for(i = map.begin(); i!=map.end();i++){
        IconHolder *chooser = new IconHolder(i.key(),i.value());
        chooser->setPos(count*iconWidth,0);

        // Add the new chooser to the scene
        addItem(chooser);

        // Increment the count to adjust the spacing
        count++;
    }
}

// Returns a concatenanted QString with the value assigned to each of the IconHolder objects
// in the scene
QString CodeScene::text()const{
    QString optionString("");

    // Iterate through the icons and concatenate the QString
    QList<QGraphicsItem *> list = items(Qt::AscendingOrder);

    foreach (QGraphicsItem *item, list) {
        IconHolder *holder = qgraphicsitem_cast<IconHolder*>(item);
        optionString=(optionString+holder->getValue());
    }

    return optionString;
}
