#include "paintsubmap.h"
PaintSubMap::PaintSubMap(QGraphicsItem *parent){
//     setFlag(QGraphicsItem::ItemIsMovable);
//     setFlag(QGraphicsItem::ItemIgnoresTransformations);
     //setAcceptDrops(true);  //设置接收拖放
//     color = QColor(Qt::lightGray);
//     pen.setWidth(2); //设置宽度
//     pen.setBrush(Qt::blue); //设置颜色
//     painter->setPen(pen); //选中画笔
      //connect(item,SIGNAL(sendsignallocation(double,double)),this,SLOT(getsignallocation(double,double)));
     //connect()
     submaps_file_index = "MapGenerator_Cartographer/input/submaps.txt";
     optional_angle_index = 0;
     qc=QColor::fromHsl(rand()%360,rand()%256,rand()%200);
 }
PaintSubMap::~PaintSubMap(){}
QRectF PaintSubMap::boundingRect() const{
    return m_rect;
}
QPainterPath PaintSubMap::shape() const
{
    QPainterPath path;
    //qDebug()<<"map3:"<<submap.map_data.size()<<endl;
    if(submap.map_data.size()==0)
    {        
        path.addRect(boundingRect());
    }
    for(int i=0;i<submap.map_data.size();i++){
         path.lineTo(submap.map_data.at(i).x*3,-submap.map_data.at(i).y*3);
    }

    return path;
}
void PaintSubMap::setRect(QVector<point> map_data)
  {
    int x_min,x_max,y_min,y_max;
    x_min = x_max = map_data.at(0).x*3;
    y_min = y_max = -map_data.at(0).y*3;
    for(int i=0;i<map_data.size();i++){
            if(x_min>map_data.at(i).x*3)
                x_min = map_data.at(i).x*3;
            if(x_max<map_data.at(i).x*3)
                x_max=map_data.at(i).x*3;
            if(y_min>map_data.at(i).y*3)
                y_min=map_data.at(i).y*3;
            if(y_max<map_data.at(i).y*3)
                y_max=map_data.at(i).y*3;
    }
    //qDebug()<<"min:"<<x_min<<" "<<x_max<<" "<<y_min<<" "<<y_max<<endl;
    m_rect = QRectF(x_min, -y_max, fabs(x_max-x_min), fabs(y_max-y_min));
    prepareGeometryChange();
  }
void PaintSubMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    //qDebug()<<"map num:"<<submap.map_data.size()<<endl;
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPointF break_point;
    //Color c_example(qc.red(),qc.green(),qc.blue());
   // qDebug()<<"kkkkk:"<<submap.map_data.size()<<endl;
         for(int i=0;i<submap.map_data.size();i++)
         {
              if(-1 == submap.map_data.at(i).break_point){
                  pen.setWidth(2); //设置宽度
//                  painter_>setPen(QColor(0, 160, 230));
                  pen.setBrush(qc); //设置颜色
                  painter->setPen(pen); //选中画笔
                  painter->drawPoint(submap.map_data.at(i).x*3,-submap.map_data.at(i).y*3);
              }

              else {
                  pen.setWidth(2); //设置宽度
                  pen.setBrush(Qt::red); //设置颜色
                  painter->setPen(pen); //选中画笔
                  break_point.setX(submap.map_data.at(i).x*3);
                  break_point.setY(-submap.map_data.at(i).y*3);
                  painter->drawPoint(submap.map_data.at(i).x*3,-submap.map_data.at(i).y*3);
                  painter->drawText(break_point,QString::number(submap.map_data.at(i).break_point));
              }

     }
    if(mouse_point.x!=0||mouse_point.y!=0){
        pen.setBrush(Qt::yellow); //设置颜色
        pen.setWidth(5); //设置宽度
        painter->setPen(pen); //选中画笔
        painter->drawPoint(mouse_point.x*3,-mouse_point.y*3);
    }
}
void PaintSubMap::SetMapData(map map,QString map_name){
    submap = map;
    setRect(submap.map_data);
    submap_number = map_name;
    submap_name = QString("%1.txt").arg(map_name);
    //save the fisrt angle of map
    if(optional_angle_index == 0)
        //optional_angle_index++;
        save_optional_angel.append(GetTheFirstAngleFromSubmapsFile(submaps_file_index,submap_number.toInt()));
    //qDebug()<<"map:"<<submap.map_data.size()<<endl;
    //qDebug()<<"map2:"<<submap_name<<endl;
//    for(int i =0;i<submap.map_data.size();i++){
//        qDebug() <<"last node:"<<submap.map_data.at(i).x<<" "<<submap.map_data.at(i).y<<endl;
//    }
    update();
}
int PaintSubMap::FindMinPoint(QVector<point> map,point now_loc){
    int pos=0;
    double length, min=99999;
    for(int i=0;i<map.size();i++){
        //qDebug()<<"len:"<<map.at(i).x<<" "<<map.at(i).y<<endl;
         length = sqrt((now_loc.x-map.at(i).x)*(now_loc.x-map.at(i).x)+(now_loc.y-map.at(i).y)*(now_loc.y-map.at(i).y));
         if(min>length){
                min = length;
                pos = i;
           }

    }
    return pos;
}

void PaintSubMap::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
   if(event->mimeData()->hasColor()) //如果拖动的数据中有颜色数据，便接收
    {
       event->setAccepted(true);
       dragOver = true;
       update();
    }
   else event->setAccepted(false);
}

void PaintSubMap::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
   Q_UNUSED(event);
   dragOver = false;
   update();
}

void PaintSubMap::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = false;
   if(event->mimeData()->hasColor())
//我们通过类型转换来获得颜色
    color =event->mimeData()->colorData().value<QColor>();
   update();
}
void PaintSubMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   if(event->button() != Qt::LeftButton)
    {
//       qc=Qt::yellow;
       //qDebug()<<"submap_name:"<<submap_name<<endl;
//       update();
//       QThread::sleep(1);
       //event->ignore();  //如果不是鼠标左键按下，则忽略该事件
       qc=QColor::fromHsl(rand()%360,rand()%256,rand()%200);
       update();
       return;
    }
   if(submap.map_data.empty()){
        event->ignore();
       return;
   }
   int pos;
   setCursor(Qt::ClosedHandCursor); //如果是鼠标左键按下，改变光标形状
   QPointF p = event->pos(); //获取鼠标位置，保存在p中
   point min_len_point;
   mouse_point.x = p.x()/3; //p的x坐标值
   mouse_point.y = -p.y()/3; //p的y坐标值
   pos = FindMinPoint(submap.map_data,mouse_point);
   min_len_point = submap.map_data.at(pos);
   mouse_point = min_len_point;
   //qDebug()<<qSetRealNumberPrecision(7)<<min_len_point.x<<" "<<min_len_point.y<<endl;
   emit sendsignallocation(min_len_point);
   update();
  /// qDebug() <<"111:"<< x/3<<" "<<y/3<<endl;
}

void PaintSubMap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
   setCursor(Qt::OpenHandCursor);   //改变光标形状
}
void PaintSubMap::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
   QMenu menu;
   QAction *action = menu.addAction(QString("rotate the angle of %1 submap ").arg(submap_name));
   connect(action,SIGNAL(triggered()),this,SLOT(RotateSubmapAngle()));
   menu.exec(event->screenPos()); //在按下鼠标左键的地方弹出菜单
}
void PaintSubMap::RotateSubmapAngle(){
    bool isOK;
    QString angle = QInputDialog::getText(NULL, QString("this is %1").arg(submap_name),
                                                       "Please input the angle",
                                                       QLineEdit::Normal,
                                                       save_optional_angel.at(optional_angle_index),
                                                       &isOK);
    if(isOK) {
              //record angel
              optional_angle_index++;
              if(optional_angle_index == save_optional_angel.size()){
                    save_optional_angel.append(angle);
              }
              else{
                  save_optional_angel.replace(optional_angle_index,angle);
              }
              ModifyAAngleInSubmapsFile(submap_number.toInt(),angle);
              emit SendDrawMapSignal(this);
//
              //qDebug()<<"debu:"<<optional_angle_index<<" "<<save_optional_angel.size()<<endl;
    }
    else{
         qDebug()<<"2222:"<<optional_angle_index<<" "<<save_optional_angel.size()<<endl;
    }
}
void PaintSubMap::ModifyAAngleInSubmapsFile(int line_number,QString angle){
    QFile file(submaps_file_index);
    int line_num = 1;
    QStringList line_str_list;
    QString line_str;
    QString file_temp;
    if(file.open(QIODevice::ReadOnly))
    {
        //qDebug()<<"open file successfully"<<endl;
        QTextStream in(&file);
        while(!in.atEnd())
        {
            line_str = in.readLine();
            if(line_str.compare("")==0)
                continue;
            if(line_num == line_number){
                line_str_list = line_str.split(" ");
                line_str = QString("%1 %2 %3 %4 %5 %6").arg(line_str_list.at(0)).arg(line_str_list.at(1)).arg(line_str_list.at(2)).arg(line_str_list.at(3)).arg(angle).arg(1);
                file_temp.append(line_str).append('\n');
            }
            else file_temp.append(line_str).append('\n');
            line_num++;
        }
        file.close();
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out<<file_temp;
        file.close();
        //qDebug()<<file_temp;
    }
    else{
       qDebug()<<"open file fail"<<endl;
       //return;
    }
}
QString PaintSubMap::GetTheFirstAngleFromSubmapsFile(QString index,int line_num){
    QFile file(submaps_file_index);
    int num = 1;
    QStringList line_str_list;
    QString line_str;
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        while(!in.atEnd()){
            if(line_num == num){
                line_str = in.readLine();
                line_str_list = line_str.split(" ");
                //qDebug()<<"debug:"<<line_str_list.at(4)<<endl;
                return line_str_list.at(4);
            }
            else {
                in.readLine();
                num ++;
            }

        }
    }
     else{
        qDebug()<<"fail to open the submaps file!"<<endl;
    }
}
void PaintSubMap::PrintAttentionInfo(QString info){
    QMessageBox::information(NULL, "Attention",
                              info,
                              QMessageBox::Yes ,
                              QMessageBox::Yes);
//    QMessageBox::about(NULL,"Attention",info);
}
QString PaintSubMap::ReadAllInfoFromFile(QString file_path){
    QFile file(file_path);
    if(file.open(QIODevice::ReadOnly)){
       QTextStream in(&file);
       return in.readAll();
    }
    else{
        PrintAttentionInfo(file_path.append(" this file isn't exist!"));
    }
}
