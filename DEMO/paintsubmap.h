#ifndef PAINTSUBMAP_H
#define PAINTSUBMAP_H
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QVariant>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QMouseEvent>
#include <QtGui>
#include <QApplication>
#include <QDrag>
#include <QWidget>
#include <QObject>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>
struct point{
    double x;
    double y;
    double heading;
    int break_point = -1;
};
struct passage{
    int head;
    int tail;
};
struct map{
    QVector<point> map_data;
    QVector<passage> map_passage;
};

class PaintSubMap : public QObject,public QGraphicsItem
{
     Q_OBJECT
public:
   map submap;
   QString submap_name;
   QString submap_number;
   QString submaps_file_index;
   int optional_angle_index;
   QVector<QString>save_optional_angel;
   explicit PaintSubMap(QGraphicsItem *parent = 0);
   ~PaintSubMap();
   virtual QRectF boundingRect() const;
   QPainterPath shape() const;
   virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
   void SetMapData(map map,QString map_name);
   int FindMinPoint(QVector<point> map,point now_loc);
   void setRect(QVector<point> map_data);
   void ModifyAAngleInSubmapsFile(int line_number,QString angle);
   QString GetTheFirstAngleFromSubmapsFile(QString index,int line_num);

   static void PrintAttentionInfo(QString info);
   static QString ReadAllInfoFromFile(QString file_path);

Q_SIGNALS:
   void sendsignallocation(point);
   void SendDrawMapSignal(PaintSubMap*);
public slots:
   void RotateSubmapAngle();


protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event); //拖动进入事件
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event); //拖动离开事件
    void dropEvent(QGraphicsSceneDragDropEvent *event);  //放入事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    QColor color;
    bool dragOver;  //标志是否有拖动进入
    //QPen mouse_select_pen;
    QPen pen;
    point mouse_point;
    QColor qc;
    QRectF m_rect;
};
#endif // PAINTSUBMAP_H
