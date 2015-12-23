/*
 * file: guessscene.cpp
* Implementation file for GuessScene class Inherits
* from QGraphicsScene and holds IconAcceptor class
* objects which accept drag and drop events
* Author: Marlo Zeroth
*/

#include "guessscene.h"

// Sets the default color to lightGray and accepts drop
IconAcceptor::IconAcceptor(QGraphicsItem *parent):QGraphicsObject(parent),
    DEFAULTIMAGE(QString(":/images/circle-icon.png")),
    pixmap(QString(":/images/circle-icon.png")),value(""), color(Qt::lightGray),  dragOver(false){
    setAcceptDrops(true);
}

// Overriden boundingRect from QGraphicsObject. Required for painting object.
QRectF IconAcceptor::boundingRect() const {
    return QRectF(QPointF(0,0),QSize(40,40));
}

// Overriden paint() function from QGraphicsObject. Required for painting/drawing object.
void IconAcceptor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(pixmap.isNull()){
        painter->setBrush(dragOver?color.light(130):color);
        painter->drawEllipse(QRectF(0,0,40,40));
    }
    else{
        painter->scale(1,1);
        painter->drawPixmap(QPoint(0,0),pixmap);
    }
}


// Resets the values to default. Clears the value string
void IconAcceptor::clear(){
    if(!pixmap.isNull()&& !value.isEmpty()){
        pixmap = DEFAULTIMAGE;
        value = QString("");        
    }
}

// Updates the pixmap and value of the pixmap
void IconAcceptor::updateImageValue(QString newValue, QPixmap newPix){
    value=newValue;
    pixmap=newPix;
}

// Sets behaviour when another object is dragged into this object
void IconAcceptor::dragEnterEvent(QGraphicsSceneDragDropEvent *event){
    if(event->mimeData()->hasImage()&&event->mimeData()->hasText()){
        event->setAccepted(true);
        dragOver = true;
        update();
    }
}

// Sets behaviour for when an object leaves this object during drag
void IconAcceptor::dragLeaveEvent(QGraphicsSceneDragDropEvent *event){
    Q_UNUSED(event);
    dragOver = false;
    update();
}

// Sets behavious for when another object is dropped into this object
void IconAcceptor::dropEvent(QGraphicsSceneDragDropEvent *event){

    if(event->mimeData()->hasImage()&&event->mimeData()->hasText()){
        dragOver = false;

        // Set the pixmap to the image dropped onto this widget
        pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());

        // Set the value to text dropped on this widget
        value = qvariant_cast<QString>(event->mimeData()->text());

        // Now update the image displayed
        update();
    }
}

// Main constructor
GuessScene::GuessScene(unsigned int size, QObject *parent):QGraphicsScene(parent){

    // Set the icon width, scene height and create a new scene
    iconWidth = 40;
    sceneHeight = 40;


    // Create new IconAcceptor objects and add them to the icons queue
    for(unsigned int i =0; i<size;i++){
        IconAcceptor *acceptor = new IconAcceptor;
        acceptor->setPos(i*(iconWidth+10),0);
        addItem(acceptor);
    }    
}

QString GuessScene::text() const{
    QString guess("");

   QList<QGraphicsItem *> list = items(Qt::AscendingOrder);
   // Iterate through each item and concatenate the guess QString
   foreach(QGraphicsItem *item,list){
       IconAcceptor *acceptor = qgraphicsitem_cast<IconAcceptor*>(item);
       guess=(guess+acceptor->getValue());
   }
    return guess;
}

// Resets each IconHolder object to default images
void GuessScene::reset(){
    // Iterate thorugh the list of IconAcceptor objects in the scene and reset
    QList<QGraphicsItem *> list = items(Qt::AscendingOrder);
    foreach(QGraphicsItem *item,list){
        IconAcceptor *acceptor = qgraphicsitem_cast<IconAcceptor*>(item);
        acceptor->clear();
    }
    update();
}

// Updates the scene with new images and values
void GuessScene::updateGuessScene(QMap<QString, QString> map, QString guess){
    QList<QGraphicsItem *> list = items(Qt::AscendingOrder);
    QString charOptions = guess;
    if(list.length()==guess.length()){
        // Iterate through the items and update their image paths and values
        foreach(QGraphicsItem *item,list){
            QString charToAdd;
            if(charOptions.size()>0){
                // Get the first letter in the guess
                charToAdd=charOptions[0];
                // Now set the image path and value in the graphics item
                IconAcceptor *acceptor = qgraphicsitem_cast<IconAcceptor*>(item);
                acceptor->updateImageValue(charToAdd,map.value(charToAdd));
                // Update the r
                if(charOptions.size()>1)
                    charOptions=charOptions.remove(charToAdd,Qt::CaseInsensitive);
            }
        }
        // Now update the scene with the new images
        update();
    }
}

// Returns true if the IconAcceptor objects in the scene have a value
bool GuessScene::filled()const{

    // Assume the IconAcceptor objects in the scene have received a string value
    bool complete=true;

    // Get a list of address of the items in the scene
    QList<QGraphicsItem *> list = items(Qt::AscendingOrder);

    // Now iterate through each of the addresses
    QList<QGraphicsItem *>::iterator i = list.begin();
    QList<QGraphicsItem *>::iterator finish = list.end();

    while(i!=finish && complete){
        // Cast to ensure we can use IconAcceptor getValue()
        IconAcceptor *acceptor = qgraphicsitem_cast<IconAcceptor*>(*i);
        // If the value is an empty string the set of objects in the scene
        // have not all received a string value
        if(acceptor->getValue().isEmpty())
            complete = false;
        i++;
    }

    return complete;
}

// Returns the total number of objects in the scene
int GuessScene::getSize() const{
    QList<QGraphicsItem *> list = items(Qt::AscendingOrder);
    return list.length();
}

// Clears the scene and add new IconHolder objects according to the new size
void GuessScene::resize(const int &newSize){

    clear(); // Clear the scene
    // Add new IconAcceptor items
    for(int i =0;i<newSize;i++){
        IconAcceptor *acceptor = new IconAcceptor;
        acceptor->setPos(i*(iconWidth+10),0);
        addItem(acceptor);
    }
}
