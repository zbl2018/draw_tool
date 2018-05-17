#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintsubmap.h"
#include <QMouseEvent>
#include "coordinate.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QApplication>
#include <QVector>
#include <stdio.h>
#include <QMessageBox>
#include <QThread>
#include "interactive_view.h"
#include <QProgressDialog>
#include <pthread.h>
#define SUBMAP_FILE 1
#define LINE_FILE 2
#define REDRAW 1
#define ONCE_DRAW 2
#define SUBMAP_NUM 100
struct segment_pos{
    QString x,y,heading;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString EraseTailZero(QString str);
    map SetLineDataFromFile(QString file_index,int file_type,int head,int tail);
    bool isFileExist(QString fullFilePath);
    void draw_full_map(int status);
    static void * thead_AdjustAngle(void * arg);

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private slots:

    void getsignallocation(point);
    void GetDrawMapSignal(PaintSubMap*);
    void is_ReturnLastAngle(bool);
    void is_SkipNextAngle(bool);
    void is_SubMapPressKeyEvent(int);

    void on_read_file_clicked();

    void on_get_point_clicked();

    void on_exec_process_clicked();

    void on_draw_map_clicked();

private:
    Ui::MainWindow *ui;
     QGraphicsScene *submap_scene;
     QGraphicsScene *full_map_scene;
     PaintSubMap *item;
     coordinate *submap_coordinate_item;
     coordinate *full_map_coordinate_item;
     //int submap_num;
     PaintSubMap submap_item[SUBMAP_NUM];
     map submap;
     QString file_index;
     int submap_file_number;
     QString segments_index;
     segment_pos point_str[2];
     int segment_pos_num;//max is 2
     bool th_status;
     int submap_mum;//the number of submap now
     QVector<int>record_which_map_modeified;
     int modify_angle_step_loc;
     QString help_file_path;
};

#endif // MAINWINDOW_H
