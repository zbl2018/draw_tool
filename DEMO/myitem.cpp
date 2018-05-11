#include"myitem.h"
myitem::myitem(){
    color = QColor(qrand() % 256, qrand() %256, qrand() % 256); //初始化随机颜色
}
QRectF myitem::boundingRect() const{
    qreal penWidth = 1;
       return QRectF(0 - penWidth / 2, 0 -penWidth / 2,
                  20 + penWidth, 20 + penWidth);
}
void myitem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*widget){
    Q_UNUSED(option);  //标明该参数没有使用
    Q_UNUSED(widget);
    //painter->setBrush(color);

    painter->drawEllipse(0, 0, 20, 20);
}
void myitem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   if(event->button() != Qt::LeftButton)
    {
       event->ignore();  //如果不是鼠标左键按下，则忽略该事件
       return;
    }
   setCursor(Qt::ClosedHandCursor); //如果是鼠标左键按下，改变光标形状
}


void myitem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   if(QLineF(event->screenPos(),event->buttonDownScreenPos(Qt::LeftButton))
       .length() < QApplication::startDragDistance())
{
//如果鼠标按下的点到现在的点的距离小于程序默认的拖动距离，表明没有拖动，则返回
       return;
    }
   QDrag *drag = new QDrag(event->widget()); //为event所在窗口部件新建拖动对象
   QMimeData *mime = new QMimeData; //新建QMimeData对象，它用来存储拖动的数据
   drag->setMimeData(mime); //关联
   mime->setColorData(color);  //放入颜色数据

   QPixmap pix(21,21);  //新建QPixmap对象，它用来重新绘制圆形，在拖动时显示
   pix.fill(Qt::white);
   QPainter painter(&pix);
   paint(&painter,0,0);
   drag->setPixmap(pix);

   drag->setHotSpot(QPoint(10, 15)); //我们让指针指向圆形的(10,15)点
   drag->exec();  //开始拖动
   setCursor(Qt::OpenHandCursor);   //改变光标形状
}


void myitem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
   setCursor(Qt::OpenHandCursor);   //改变光标形状
}
