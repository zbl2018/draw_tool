#ifndef MYITEM_H
#define MYITEM_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QtGui>
#include <QApplication>
#include <QDrag>
#include <QWidget>
class myitem : public QGraphicsItem
{
public:
    myitem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*widget);
protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
   QColor color;
};

#endif // MYITEM_H
