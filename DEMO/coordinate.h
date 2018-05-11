#ifndef COORDINATE_H
#define COORDINATE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
class coordinate : public QGraphicsItem
{
public:
    //PaintSubMap();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*widget);
public slots:
    //void mousePressEvent(QMouseEvent *e);//鼠标单击
    void zoom(bool b);
};
#endif // COORDINATE_H
