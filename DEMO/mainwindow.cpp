#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coordinate.h"
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QApplication>
#include "myitem.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    submap_file_number = 0;
    submap_mum = 0;
    segments_index = "MapGenerator_Cartographer/input/segments.txt";
    help_file_path = "help/help.txt";
    segment_pos_num =0 ;
    modify_angle_step_loc =-1;

    ui->setupUi(this);
    submap_scene = new QGraphicsScene;  //场景
    full_map_scene = new QGraphicsScene;
    item =new PaintSubMap;
    submap_coordinate_item =  new coordinate;
    full_map_coordinate_item = new coordinate;
    submap_scene->addItem(item);  //项添加到场景
    submap_scene->addItem(submap_coordinate_item);
    full_map_scene->addItem(full_map_coordinate_item);
    ui->my_view->setScene(submap_scene);  //视图关联场景
    ui->full_map_view->setScene(full_map_scene);
    ui->my_view->show();  //显示视图
    ui->full_map_view->show();
    connect(item,SIGNAL(sendsignallocation(point)),this,SLOT(getsignallocation(point)));
    connect(ui->full_map_view,SIGNAL(ReturnLastAngle(bool)),this,SLOT(is_ReturnLastAngle(bool)));
    connect(ui->full_map_view,SIGNAL(SkipNextAngle(bool)),this,SLOT(is_SkipNextAngle(bool)));
    connect(ui->full_map_view,SIGNAL(SubMapPressKeyEvent(int)),this,SLOT(is_SubMapPressKeyEvent(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}
void MainWindow::keyPressEvent(QKeyEvent *event){
    if ((event->modifiers() == Qt::ControlModifier)&&(event->key() == Qt::Key_H)){
            QString info = PaintSubMap::ReadAllInfoFromFile(help_file_path);
            QMessageBox::about(NULL,"help manual",info);
        }
}

QString MainWindow::EraseTailZero(QString str){
   int len = str.size();
   for(int i = len -1;i>0;i--){
        if(str[i]== '0')
            str.chop(1);
        else {
            return str;
        }
   }
   return str;
}

void MainWindow::getsignallocation(point loc)
{
//    qDebug()<<"12dsdas1:"<<EraseTailZero(QString::number(loc.heading,'f',10))<<endl;
//    qDebug()<<"pos:"<<qSetRealNumberPrecision(7)<<loc.x<<" "<<loc.y<<endl;
    ui->lineEdit_x->setText(EraseTailZero(QString::number(loc.x,'f',6)));
    ui->lineEdit_y->setText(EraseTailZero(QString::number(loc.y,'f',6)));
    ui->lineEdit_heading->setText(EraseTailZero(QString::number(loc.heading,'f',6)));
}
void * MainWindow::thead_AdjustAngle(void * arg){
    MainWindow * main = (MainWindow*)arg;
    FILE *fp;
    fp = popen("cd MapGenerator_Cartographer/&&./MapGenerator","r");
     //wait for the terminatation of subprocess
     while(true)
     {
         if(!feof(fp))
         {
             pclose(fp);
             break;
         }
     }
      main->th_status = true;
      //qDebug()<<"12dsdas1:"<<endl;
}

void MainWindow::GetDrawMapSignal(PaintSubMap* ob)
{
    //record which map had modified
    modify_angle_step_loc++;
    if(modify_angle_step_loc == record_which_map_modeified.size()){
        record_which_map_modeified.append(ob->submap_number.toInt());
    }
    else{
        record_which_map_modeified.replace(modify_angle_step_loc,ob->submap_number.toInt());
    }
    //qDebug()<<"mod:"<<record_which_map_modeified.at(modify_angle_step_loc-1)<<endl;
    //qDebug()<<"line1:"<<modify_angle_step_loc<<" "<<record_which_map_modeified.size()<<endl;
    on_exec_process_clicked();
}
void MainWindow::is_ReturnLastAngle(bool status){
    if(status){
        if(modify_angle_step_loc !=-1){
            int loc = record_which_map_modeified.at(modify_angle_step_loc)-1;//the last submap modified
            modify_angle_step_loc-- ;
            submap_item[loc].optional_angle_index--; //retreat a step
            //qDebug()<<"1:"<<submap_item[loc].optional_angle_index<<endl;
            submap_item[loc].ModifyAAngleInSubmapsFile(submap_item[loc].submap_number.toInt(),submap_item[loc].save_optional_angel.at(submap_item[loc].optional_angle_index));
            //qDebug()<<"2:"<<submap_item[loc].optional_angle_index<<endl;
            on_exec_process_clicked();
            }
        else{
            PaintSubMap::PrintAttentionInfo( "Cant't retreat!");
            }
        }
}

void MainWindow::is_SkipNextAngle(bool status){
    if(status){

        if(modify_angle_step_loc+1 != record_which_map_modeified.size()){
            int loc = record_which_map_modeified.at(++modify_angle_step_loc)-1;//the last submap modified
//            modify_angle_step_loc++ ;
            submap_item[loc].optional_angle_index++; //go-forward a step
            //qDebug()<<"1:"<<submap_item[loc].optional_angle_index<<endl;
            submap_item[loc].ModifyAAngleInSubmapsFile(submap_item[loc].submap_number.toInt(),submap_item[loc].save_optional_angel.at(submap_item[loc].optional_angle_index));
            //qDebug()<<"2:"<<submap_item[loc].optional_angle_index<<endl;
            on_exec_process_clicked();
            }
        else {
               PaintSubMap::PrintAttentionInfo("Can't Skip!");
        }
        }

}
void MainWindow::is_SubMapPressKeyEvent(int event_type){
    switch(event_type){
        case CTRL_H:{
            QString info = PaintSubMap::ReadAllInfoFromFile(help_file_path);
            QMessageBox::about(NULL,"help manual",info);
    }
    }
}

void MainWindow::on_read_file_clicked()
{
    point loc;
    QStringList node_list;
    QString str;
    submap_file_number++;
    file_index = QString("MapGenerator_Cartographer/input/%1.txt").arg(submap_file_number);
    if(isFileExist(file_index)){
     submap = SetLineDataFromFile(file_index,SUBMAP_FILE,-1,-1);
     ui->lineEdit_file_name->setText(QString("%1.txt").arg(submap_file_number));
    }
    else{
        qDebug()<<"open file fail"<<endl;
        submap_file_number = 1;
        file_index = QString("MapGenerator_Cartographer/input/%1.txt").arg(submap_file_number);
        submap = SetLineDataFromFile(file_index,SUBMAP_FILE,-1,-1);
    }
    ui->lineEdit_file_name->setText(QString("%1.txt").arg(submap_file_number));
    item->SetMapData(submap,QString::number(submap_file_number));
    submap.map_data.clear();
}

void MainWindow::on_get_point_clicked()
{
    if(ui->lineEdit_x->text() == NULL || ui->lineEdit_y->text() == NULL || ui->lineEdit_heading->text() == NULL)
        return;
    point_str[segment_pos_num].x =ui->lineEdit_x->text();
    point_str[segment_pos_num].y =ui->lineEdit_y->text();
    point_str[segment_pos_num].heading =ui->lineEdit_heading->text();
    segment_pos_num++;
    if(segment_pos_num==2){
//        int key = QMessageBox::information( this, "Application name here","The document contains unsaved changes","&Save", "&Discard", "&Cancel", 0,2 );
//        switch(key) {
//            case 0: // Save被点击或者Alt+S被按下或者Enter被按下。
//                qDebug()<<"0"<<endl;
//                break;
//            case 1: // Discard被点击或者Alt+D被按下。
//                // 不保存但退出
//                qDebug()<<"1"<<endl;
//                break;
//            case 2: // Cancel被点击或者Alt+C被按下或者Escape被按下。
//                qDebug()<<"2"<<endl;
//                // 不退出
//                break;
//        }
        bool isOK;
        QString point_name;
        QStringList point_name_list;
        point_name = QInputDialog::getText(NULL, QString("this is %1").arg(ui->lineEdit_file_name->text()),
                                                           "Please input the name of the points: ",
                                                           QLineEdit::Normal,
                                                           "1,2",
                                                           &isOK);
        if(isOK) {
                point_name_list = point_name.split(",");
                if(point_name_list.size() != 2||point_name_list.at(1)==NULL || point_name_list.at(0)==NULL ){
                    PaintSubMap::PrintAttentionInfo("the name is error! please get point again!");
                    segment_pos_num = 0;
                    return;
                }
        }
        else{
            segment_pos_num = 0;
            return;
             //qDebug()<<"2222:"<<optional_angle_index<<" "<<save_optional_angel.size()<<endl;
        }
        //save the point to segments file
        QString filename = QString("%1.txt").arg(submap_file_number);
        QFile file(segments_index);
        if(file.open(QIODevice::WriteOnly|QIODevice::Append))
        {
            QTextStream out(&file);
            out<<filename<<" "<<point_name_list.at(0)<<" "<<point_str[0].x<<" "<<point_str[0].y<<" "<<point_str[0].heading<<" "<<
                 point_name_list.at(1)<<" "<<point_str[1].x<<" "<<point_str[1].x<<" "<<point_str[1].heading<<endl;
            segment_pos_num = 0;
            PaintSubMap::PrintAttentionInfo("get the points successfully!");
            //qDebug()<<"open segments file successfully"<<endl;

        }
        else{
            qDebug()<<"open file fail"<<endl;

        }
        file.close();
    }

}

void MainWindow::on_exec_process_clicked()
{
    QProgressDialog status_process;
    status_process.setLabelText(tr("generating fullmap again..."));
    status_process.setRange(0,50000);
    status_process.setModal(true);
    status_process.setCancelButtonText(tr("cancel"));
    status_process.setMinimumDuration(0);
    pthread_t th_id;
    th_status = false;
    pthread_create(&th_id,NULL,thead_AdjustAngle,this);
    int i = 0;
    while(!th_status){
        for(int j=0;j<25000;j++);
        status_process.setValue(i);
        if(i!=49999)
            i++;
    }
    status_process.setValue(50000);
    on_draw_map_clicked();
    return;
}

void MainWindow::on_draw_map_clicked()
{
    if(submap_mum == 0){        
        draw_full_map(ONCE_DRAW);
    }
    else draw_full_map(REDRAW);
}
void MainWindow::draw_full_map(int status){
    QString str;
    QString txt_name;
    QStringList segments_list;
    QStringList txt_name_list;
    QString line_index;
    int head,tail;
    map line_data;
    QFile file(segments_index);
    int last_txt = 1;
    if(file.open(QIODevice::ReadOnly))
    {
        //qDebug()<<"open file successfully"<<endl;
        //QThread::sleep(3);
        QTextStream in(&file);
        while(!in.atEnd())
        {
            str = in.readLine();
            if(str.compare("")==0)
                continue;
            segments_list = str.split(" ");
            txt_name = segments_list.at(0);
            head = segments_list.at(1).toInt();
            tail = segments_list.at(5).toInt();
            txt_name_list = txt_name.split(".");
            txt_name = txt_name_list.at(0);
            //read a lines file
            line_index = QString("MapGenerator_Cartographer/lines/%1(%2-%3).txt").arg(txt_name).arg(head).arg(tail);
            //qDebug()<<"www:"<<line_index<<endl;
            if(!isFileExist(line_index))
            {
                continue;
            }
            line_data = SetLineDataFromFile(line_index,LINE_FILE,head,tail);
            if(last_txt == txt_name.toInt()){
                //qDebug()<<"last_txt:"<<last_txt<<" "<<txt_name.toInt()<<endl;
                 submap.map_data+=line_data.map_data;
                 submap.map_passage+=line_data.map_passage;
            }
            else{
                //set submap map_data
                submap_item[last_txt-1].SetMapData(submap,QString::number(txt_name.toInt()-1));
                //add submap
                if(status == ONCE_DRAW){
                    submap_mum++;
                    QObject::connect(&submap_item[last_txt-1],SIGNAL(SendDrawMapSignal(PaintSubMap*)),this,SLOT(GetDrawMapSignal(PaintSubMap*)));
                    full_map_scene->addItem(&submap_item[last_txt-1]);
                }
                submap.map_data.clear();
                submap.map_passage.clear();
                submap.map_data+=line_data.map_data;
                submap.map_passage+=line_data.map_passage;
                last_txt = txt_name.toInt();
            }
            str.clear();
        }
        submap_item[last_txt-1].SetMapData(submap,txt_name);
        if(status == ONCE_DRAW){
            submap_mum++;
            QObject::connect(&submap_item[last_txt-1],SIGNAL(SendDrawMapSignal(PaintSubMap*)),this,SLOT(GetDrawMapSignal(PaintSubMap*)));
            full_map_scene->addItem(&submap_item[last_txt-1]);
        }
        submap.map_data.clear();
        submap.map_passage.clear();
    }
    else{
        qDebug()<<"open file fail"<<endl;
    }
    submap.map_data.clear();
    submap.map_passage.clear();
    //qDebug()<<"num:"<<submap_mum<<endl;
}

map MainWindow::SetLineDataFromFile(QString file_index,int file_type,int head,int tail){
     QFile file(file_index);
     double x_pos,y_pos,heading_pos;
     map one_passage;
//     QVector<point> line_data;
     passage line_info;
     point loc;
     QString str;
     QStringList node_list;
     bool first_node = false;
     bool last_node =false;
     //QVector<passasge>submap_line;
     if(file.open(QIODevice::ReadOnly))
     {
         //qDebug()<<"open file successfully"<<endl;
         QTextStream in(&file);
         switch(file_type){
            case SUBMAP_FILE:{
                  x_pos = 0;
                  y_pos = 1;
                  heading_pos = 2;
                  break;
                  }
            case LINE_FILE:{
                   x_pos = 2;
                   y_pos = 4;
                   heading_pos = 7;
                   first_node = true;
                   last_node = true;
                   break;
                    }
                }
         while(!in.atEnd())
         {
             str = in.readLine();
             if(str.compare("")==0)
                 continue;
             node_list = str.split(" ");
             loc.x = node_list.at(x_pos).toDouble()-0.3;
             loc.y = node_list.at(y_pos).toDouble();
             loc.heading = node_list.at(heading_pos).toDouble();
             if(first_node){
                //qDebug() <<"first: "<<first_node<<endl;
                line_info.head = head;
                loc.break_point = head;
                one_passage.map_data.append(loc);
                loc.break_point = -1;
                first_node = false;
             }
             else one_passage.map_data.append(loc);
             //qDebug() <<"line:"<<  loc.x<<" "<<loc.y<<" "<< loc.heading<<" "<<loc.break_point<<endl;
             str.clear();
         }
         if(last_node){
             //the last point int this line
            (one_passage.map_data.end()-1)->break_point = tail;
             line_info.tail = tail;
             //qDebug() <<"last node:"<<  (line_data.end()-1)->x<<" "<<(line_data.end()-1)->y<<" "<< (line_data.end()-1)->heading<<" "<<(line_data.end()-1)->break_point<<endl;
         }
         one_passage.map_passage.append(line_info);
//         for(int i =0;i<one_passage.map_data.size();i++){
//             qDebug() <<"last node:"<<one_passage.map_data.at(i).x<<" "<<one_passage.map_data.at(i).y<<endl;
//         }

//         QFile fp("../DEMO/MapGenerator_Cartographer/input/temp.txt");
//         if(fp.open(QIODevice::WriteOnly))
//            {
//          //qDebug()<<"open file successfully"<<endl;
//          QTextStream out(&fp);
//          for(int i =0;i<one_passage.map_data.size();i++){
//              out<<one_passage.map_data.at(i).x<<" "<<one_passage.map_data.at(i).y<<" "<<one_passage.map_data.at(i).heading<<endl;
//          }
//        }
         return one_passage;
         }
     else{
        qDebug()<<"open file fail"<<endl;
        //return;
     }


 }
bool MainWindow::isFileExist(QString fullFilePath)
{
    QFileInfo fileInfo(fullFilePath);
    if(fileInfo.exists())
    {
        return true;
    }
    return false;
}
