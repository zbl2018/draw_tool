#include "coordinate.h"
QRectF coordinate::boundingRect() const{
    qreal penWidth = 1;
    return QRectF(-300, -300,
               600, 600);
}
void coordinate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    int width = 300;
    Q_UNUSED(option);  //标明该参数没有使用
    Q_UNUSED(widget);
    QPen pen;
    //pen.setWidth(2); //设置宽度
    //pen.setBrush(Qt::blue); //设置颜色
    painter->setPen(pen); //选中画笔

    painter->drawLine(0,width,0,-width);  //绘制y轴
    painter->drawLine(-width,0,width,0); //绘制x轴
    int i;
    for(i = -width;i<width;i+=10)//x zhou
    {
        if(i%3==0){
            painter->drawLine(i,0,i,-5); //绘制x轴上的点
            painter->drawText(i-9,11,QString::number(i/3)); //绘制文本
        }
    }
    for(i=-width;i<width;i+=10)//y zhou
    {
         if(i%3==0&&i!=0){
         painter->drawLine(0,i,5,i); //绘制y轴上的点
         painter->drawText(-20,i+5,QString::number(-(i/3))); //绘制文本
         }
    }
    //painter->setBrush(Qt::red);
    //painter->drawRect(0,0,20,20);
}
//void coordinate::mousePressEvent(QMouseEvent *e)//鼠标单击
//{
//int x;
//int y;
//QPoint p; //坐标点
//p = e->pos(); //获取鼠标位置，保存在p中
//x = p.x(); //p的x坐标值
//y = p.y(); //p的y坐标值
//QString sx,sy; //字符串变量
//sx = QString::number(x); //x转换为字符串
//sy = QString::number(y); //y转换为字符串
////qDebug("sx:%s,sy:%sy\n",sx,sy);//
//qDebug()<<sx<<sy<<endl;
////ui->lineEdit->setText(sx); //文本框显示 x值
////ui->lineEdit_2->setText(sy); //文本框显示 y值

//}
