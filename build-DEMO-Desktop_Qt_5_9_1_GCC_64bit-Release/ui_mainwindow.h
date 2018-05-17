/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "interactive_view.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_zbl;
    QWidget *centralWidget;
    InteractiveView *my_view;
    QLineEdit *lineEdit_y;
    QLineEdit *lineEdit_x;
    QLabel *label_2;
    QLabel *label;
    QPushButton *read_file;
    QLineEdit *lineEdit_heading;
    QLabel *label_3;
    QPushButton *get_point;
    QPushButton *exec_process;
    QLineEdit *lineEdit_file_name;
    QLabel *label_4;
    QPushButton *draw_map;
    InteractiveView *full_map_view;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1453, 569);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(250);
        sizePolicy.setVerticalStretch(250);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        action_zbl = new QAction(MainWindow);
        action_zbl->setObjectName(QStringLiteral("action_zbl"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        my_view = new InteractiveView(centralWidget);
        my_view->setObjectName(QStringLiteral("my_view"));
        my_view->setGeometry(QRect(0, 0, 561, 411));
        lineEdit_y = new QLineEdit(centralWidget);
        lineEdit_y->setObjectName(QStringLiteral("lineEdit_y"));
        lineEdit_y->setGeometry(QRect(190, 440, 113, 25));
        lineEdit_x = new QLineEdit(centralWidget);
        lineEdit_x->setObjectName(QStringLiteral("lineEdit_x"));
        lineEdit_x->setGeometry(QRect(50, 440, 113, 25));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(220, 420, 67, 17));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 420, 67, 17));
        read_file = new QPushButton(centralWidget);
        read_file->setObjectName(QStringLiteral("read_file"));
        read_file->setGeometry(QRect(580, 50, 101, 31));
        lineEdit_heading = new QLineEdit(centralWidget);
        lineEdit_heading->setObjectName(QStringLiteral("lineEdit_heading"));
        lineEdit_heading->setGeometry(QRect(330, 440, 113, 25));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(350, 420, 67, 17));
        get_point = new QPushButton(centralWidget);
        get_point->setObjectName(QStringLiteral("get_point"));
        get_point->setGeometry(QRect(580, 150, 101, 31));
        exec_process = new QPushButton(centralWidget);
        exec_process->setObjectName(QStringLiteral("exec_process"));
        exec_process->setGeometry(QRect(580, 200, 101, 31));
        lineEdit_file_name = new QLineEdit(centralWidget);
        lineEdit_file_name->setObjectName(QStringLiteral("lineEdit_file_name"));
        lineEdit_file_name->setGeometry(QRect(470, 440, 113, 25));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(490, 420, 67, 17));
        draw_map = new QPushButton(centralWidget);
        draw_map->setObjectName(QStringLiteral("draw_map"));
        draw_map->setGeometry(QRect(580, 100, 101, 31));
        full_map_view = new InteractiveView(centralWidget);
        full_map_view->setObjectName(QStringLiteral("full_map_view"));
        full_map_view->setGeometry(QRect(690, 0, 531, 411));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(250);
        sizePolicy1.setVerticalStretch(199);
        sizePolicy1.setHeightForWidth(full_map_view->sizePolicy().hasHeightForWidth());
        full_map_view->setSizePolicy(sizePolicy1);
        MainWindow->setCentralWidget(centralWidget);
        lineEdit_y->raise();
        lineEdit_x->raise();
        label_2->raise();
        label->raise();
        my_view->raise();
        read_file->raise();
        lineEdit_heading->raise();
        label_3->raise();
        get_point->raise();
        exec_process->raise();
        lineEdit_file_name->raise();
        label_4->raise();
        draw_map->raise();
        full_map_view->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1453, 28));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_F->menuAction());
        menu_F->addAction(action_zbl);
        menu_F->addSeparator();
        menu_F->addSeparator();
        menu_F->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "DRAW TOOL", Q_NULLPTR));
        action_zbl->setText(QApplication::translate("MainWindow", "zbl", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_zbl->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        label_2->setText(QApplication::translate("MainWindow", "y", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "x", Q_NULLPTR));
        read_file->setText(QApplication::translate("MainWindow", "load submap", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "heading", Q_NULLPTR));
        get_point->setText(QApplication::translate("MainWindow", "get point", Q_NULLPTR));
        exec_process->setText(QApplication::translate("MainWindow", "exec process", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "filename", Q_NULLPTR));
        draw_map->setText(QApplication::translate("MainWindow", "draw full map", Q_NULLPTR));
        menu_F->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
