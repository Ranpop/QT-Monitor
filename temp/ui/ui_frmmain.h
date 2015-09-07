/********************************************************************************
** Form generated from reading UI file 'frmmain.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMAIN_H
#define UI_FRMMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
//#include "mapwidget.h"
//#include "plotwidget.h"
#include "switchbutton.h"

QT_BEGIN_NAMESPACE

class Ui_frmMain
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_Main;
    QHBoxLayout *horizontalLayout_2;
    MapWidget *graphicsView;
    QTabWidget *tabWidget;
    QWidget *tab_warningInfo;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_Warning;
    QTableWidget *tableWidget_warning;
    QWidget *tab_kinect;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_kinect;
    QTableWidget *tableWidget_kinect;
    QWidget *tab_laneLine;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_laneline;
    QTableWidget *tableWidget_laneline;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_4;
    plotWidget *widgetParameter_Curve_4;
    plotWidget *widgetParameter_Curve_1;
    plotWidget *widgetParameter_Curve_0;
    plotWidget *widgetParameter_Curve_2;
    plotWidget *widgetParameter_Curve_6;
    plotWidget *widgetParameter_Curve_3;
    plotWidget *widgetParameter_Curve_7;
    plotWidget *widgetParameter_Curve_5;
    plotWidget *widgetParameter_Curve_8;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBox_liftForward;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBox_liftBack;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBox_liftUp;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_liftDown;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_liftleft;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox_liftRight;
    QPushButton *pushButton_setLiftConfig;
    QGridLayout *gridLayout_2;
    SwitchButton *pushButton_AutoManual;
    QDoubleSpinBox *doubleSpinBox_CarRight;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_CarLeft;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBox_CarForward;
    QPushButton *pushButton_SetCarConfig;
    QDoubleSpinBox *doubleSpinBox_CarBack;
    QLabel *label_4;
    QLabel *label_7;
    QLabel *label_6;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_Config;
    QPushButton *pushbutton_Close;
    QPushButton *pushButton_Connect;
    QPushButton *pushButton_min;

    void setupUi(QDialog *frmMain)
    {
        if (frmMain->objectName().isEmpty())
            frmMain->setObjectName(QStringLiteral("frmMain"));
        frmMain->resize(1278, 1068);
        frmMain->setMinimumSize(QSize(0, 0));
        frmMain->setSizeGripEnabled(false);
        layoutWidget = new QWidget(frmMain);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(8, 9, 1242, 1038));
        verticalLayout_Main = new QVBoxLayout(layoutWidget);
        verticalLayout_Main->setSpacing(6);
        verticalLayout_Main->setContentsMargins(11, 11, 11, 11);
        verticalLayout_Main->setObjectName(QStringLiteral("verticalLayout_Main"));
        verticalLayout_Main->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        graphicsView = new MapWidget(layoutWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMinimumSize(QSize(945, 402));
        graphicsView->setMaximumSize(QSize(16777215, 16777215));
        graphicsView->setAutoFillBackground(true);

        horizontalLayout_2->addWidget(graphicsView);

        tabWidget = new QTabWidget(layoutWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMaximumSize(QSize(350, 16777215));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tab_warningInfo = new QWidget();
        tab_warningInfo->setObjectName(QStringLiteral("tab_warningInfo"));
        verticalLayoutWidget = new QWidget(tab_warningInfo);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(7, 13, 271, 341));
        verticalLayout_Warning = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_Warning->setSpacing(6);
        verticalLayout_Warning->setContentsMargins(11, 11, 11, 11);
        verticalLayout_Warning->setObjectName(QStringLiteral("verticalLayout_Warning"));
        verticalLayout_Warning->setContentsMargins(0, 0, 0, 0);
        tableWidget_warning = new QTableWidget(verticalLayoutWidget);
        if (tableWidget_warning->columnCount() < 3)
            tableWidget_warning->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        tableWidget_warning->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        tableWidget_warning->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        tableWidget_warning->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget_warning->rowCount() < 2)
            tableWidget_warning->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        tableWidget_warning->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        tableWidget_warning->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_warning->setItem(0, 0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_warning->setItem(0, 1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_warning->setItem(0, 2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_warning->setItem(1, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_warning->setItem(1, 1, __qtablewidgetitem9);
        tableWidget_warning->setObjectName(QStringLiteral("tableWidget_warning"));
        tableWidget_warning->setLayoutDirection(Qt::LeftToRight);
        tableWidget_warning->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_warning->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_warning->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_warning->horizontalHeader()->setDefaultSectionSize(100);
        tableWidget_warning->horizontalHeader()->setStretchLastSection(true);
        tableWidget_warning->verticalHeader()->setVisible(false);
        tableWidget_warning->verticalHeader()->setHighlightSections(false);

        verticalLayout_Warning->addWidget(tableWidget_warning);

        tabWidget->addTab(tab_warningInfo, QString());
        tab_kinect = new QWidget();
        tab_kinect->setObjectName(QStringLiteral("tab_kinect"));
        verticalLayoutWidget_2 = new QWidget(tab_kinect);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 40, 160, 261));
        verticalLayout_kinect = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_kinect->setSpacing(6);
        verticalLayout_kinect->setContentsMargins(11, 11, 11, 11);
        verticalLayout_kinect->setObjectName(QStringLiteral("verticalLayout_kinect"));
        verticalLayout_kinect->setContentsMargins(0, 0, 0, 0);
        tableWidget_kinect = new QTableWidget(verticalLayoutWidget_2);
        if (tableWidget_kinect->columnCount() < 4)
            tableWidget_kinect->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_kinect->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_kinect->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_kinect->setHorizontalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_kinect->setHorizontalHeaderItem(3, __qtablewidgetitem13);
        if (tableWidget_kinect->rowCount() < 2)
            tableWidget_kinect->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_kinect->setVerticalHeaderItem(0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_kinect->setVerticalHeaderItem(1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_kinect->setItem(0, 0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_kinect->setItem(0, 1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_kinect->setItem(0, 2, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_kinect->setItem(0, 3, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_kinect->setItem(1, 0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_kinect->setItem(1, 1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_kinect->setItem(1, 2, __qtablewidgetitem22);
        tableWidget_kinect->setObjectName(QStringLiteral("tableWidget_kinect"));
        tableWidget_kinect->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_kinect->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_kinect->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_kinect->horizontalHeader()->setStretchLastSection(true);
        tableWidget_kinect->verticalHeader()->setVisible(false);

        verticalLayout_kinect->addWidget(tableWidget_kinect);

        tabWidget->addTab(tab_kinect, QString());
        tab_laneLine = new QWidget();
        tab_laneLine->setObjectName(QStringLiteral("tab_laneLine"));
        verticalLayoutWidget_3 = new QWidget(tab_laneLine);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(20, 30, 160, 321));
        verticalLayout_laneline = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_laneline->setSpacing(6);
        verticalLayout_laneline->setContentsMargins(11, 11, 11, 11);
        verticalLayout_laneline->setObjectName(QStringLiteral("verticalLayout_laneline"));
        verticalLayout_laneline->setContentsMargins(0, 0, 0, 0);
        tableWidget_laneline = new QTableWidget(verticalLayoutWidget_3);
        tableWidget_laneline->setObjectName(QStringLiteral("tableWidget_laneline"));
        tableWidget_laneline->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_laneline->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_laneline->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_laneline->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_laneline->addWidget(tableWidget_laneline);

        tabWidget->addTab(tab_laneLine, QString());

        horizontalLayout_2->addWidget(tabWidget);


        verticalLayout_Main->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        widgetParameter_Curve_4 = new plotWidget(layoutWidget);
        widgetParameter_Curve_4->setObjectName(QStringLiteral("widgetParameter_Curve_4"));

        gridLayout_4->addWidget(widgetParameter_Curve_4, 1, 1, 1, 1);

        widgetParameter_Curve_1 = new plotWidget(layoutWidget);
        widgetParameter_Curve_1->setObjectName(QStringLiteral("widgetParameter_Curve_1"));

        gridLayout_4->addWidget(widgetParameter_Curve_1, 0, 1, 1, 1);

        widgetParameter_Curve_0 = new plotWidget(layoutWidget);
        widgetParameter_Curve_0->setObjectName(QStringLiteral("widgetParameter_Curve_0"));

        gridLayout_4->addWidget(widgetParameter_Curve_0, 0, 0, 1, 1);

        widgetParameter_Curve_2 = new plotWidget(layoutWidget);
        widgetParameter_Curve_2->setObjectName(QStringLiteral("widgetParameter_Curve_2"));

        gridLayout_4->addWidget(widgetParameter_Curve_2, 0, 2, 1, 1);

        widgetParameter_Curve_6 = new plotWidget(layoutWidget);
        widgetParameter_Curve_6->setObjectName(QStringLiteral("widgetParameter_Curve_6"));

        gridLayout_4->addWidget(widgetParameter_Curve_6, 2, 0, 1, 1);

        widgetParameter_Curve_3 = new plotWidget(layoutWidget);
        widgetParameter_Curve_3->setObjectName(QStringLiteral("widgetParameter_Curve_3"));

        gridLayout_4->addWidget(widgetParameter_Curve_3, 1, 0, 1, 1);

        widgetParameter_Curve_7 = new plotWidget(layoutWidget);
        widgetParameter_Curve_7->setObjectName(QStringLiteral("widgetParameter_Curve_7"));

        gridLayout_4->addWidget(widgetParameter_Curve_7, 2, 1, 1, 1);

        widgetParameter_Curve_5 = new plotWidget(layoutWidget);
        widgetParameter_Curve_5->setObjectName(QStringLiteral("widgetParameter_Curve_5"));

        gridLayout_4->addWidget(widgetParameter_Curve_5, 1, 2, 1, 1);

        widgetParameter_Curve_8 = new plotWidget(layoutWidget);
        widgetParameter_Curve_8->setObjectName(QStringLiteral("widgetParameter_Curve_8"));

        gridLayout_4->addWidget(widgetParameter_Curve_8, 2, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMaximumSize(QSize(110, 16777215));

        gridLayout->addWidget(label_8, 0, 0, 1, 1);

        doubleSpinBox_liftForward = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_liftForward->setObjectName(QStringLiteral("doubleSpinBox_liftForward"));
        doubleSpinBox_liftForward->setEnabled(false);
        doubleSpinBox_liftForward->setMaximumSize(QSize(90, 16777215));
        doubleSpinBox_liftForward->setMinimum(-90);
        doubleSpinBox_liftForward->setMaximum(90);

        gridLayout->addWidget(doubleSpinBox_liftForward, 0, 1, 1, 1);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMaximumSize(QSize(110, 16777215));

        gridLayout->addWidget(label_9, 1, 0, 1, 1);

        doubleSpinBox_liftBack = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_liftBack->setObjectName(QStringLiteral("doubleSpinBox_liftBack"));
        doubleSpinBox_liftBack->setEnabled(false);
        doubleSpinBox_liftBack->setMaximumSize(QSize(90, 16777215));
        doubleSpinBox_liftBack->setMinimum(-90);
        doubleSpinBox_liftBack->setMaximum(90);

        gridLayout->addWidget(doubleSpinBox_liftBack, 1, 1, 1, 1);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMaximumSize(QSize(110, 16777215));

        gridLayout->addWidget(label_10, 2, 0, 1, 1);

        doubleSpinBox_liftUp = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_liftUp->setObjectName(QStringLiteral("doubleSpinBox_liftUp"));
        doubleSpinBox_liftUp->setEnabled(false);
        doubleSpinBox_liftUp->setMaximumSize(QSize(90, 16777215));

        gridLayout->addWidget(doubleSpinBox_liftUp, 2, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(110, 16777215));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        doubleSpinBox_liftDown = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_liftDown->setObjectName(QStringLiteral("doubleSpinBox_liftDown"));
        doubleSpinBox_liftDown->setEnabled(false);
        doubleSpinBox_liftDown->setMaximumSize(QSize(90, 16777215));

        gridLayout->addWidget(doubleSpinBox_liftDown, 3, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(110, 16777215));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        doubleSpinBox_liftleft = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_liftleft->setObjectName(QStringLiteral("doubleSpinBox_liftleft"));
        doubleSpinBox_liftleft->setEnabled(false);
        doubleSpinBox_liftleft->setMaximumSize(QSize(90, 16777215));

        gridLayout->addWidget(doubleSpinBox_liftleft, 4, 1, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(110, 16777215));

        gridLayout->addWidget(label, 5, 0, 1, 1);

        doubleSpinBox_liftRight = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_liftRight->setObjectName(QStringLiteral("doubleSpinBox_liftRight"));
        doubleSpinBox_liftRight->setEnabled(false);
        doubleSpinBox_liftRight->setMaximumSize(QSize(90, 16777215));

        gridLayout->addWidget(doubleSpinBox_liftRight, 5, 1, 1, 1);

        pushButton_setLiftConfig = new QPushButton(layoutWidget);
        pushButton_setLiftConfig->setObjectName(QStringLiteral("pushButton_setLiftConfig"));
        pushButton_setLiftConfig->setEnabled(false);
        pushButton_setLiftConfig->setMaximumSize(QSize(90, 16777215));
        pushButton_setLiftConfig->setAutoDefault(true);

        gridLayout->addWidget(pushButton_setLiftConfig, 6, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_AutoManual = new SwitchButton(layoutWidget);
        pushButton_AutoManual->setObjectName(QStringLiteral("pushButton_AutoManual"));

        gridLayout_2->addWidget(pushButton_AutoManual, 5, 1, 1, 1);

        doubleSpinBox_CarRight = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_CarRight->setObjectName(QStringLiteral("doubleSpinBox_CarRight"));
        doubleSpinBox_CarRight->setEnabled(false);
        doubleSpinBox_CarRight->setMaximumSize(QSize(90, 16777215));
        doubleSpinBox_CarRight->setMinimum(-90);
        doubleSpinBox_CarRight->setMaximum(90);

        gridLayout_2->addWidget(doubleSpinBox_CarRight, 3, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMaximumSize(QSize(110, 16777215));

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        doubleSpinBox_CarLeft = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_CarLeft->setObjectName(QStringLiteral("doubleSpinBox_CarLeft"));
        doubleSpinBox_CarLeft->setEnabled(false);
        doubleSpinBox_CarLeft->setMaximumSize(QSize(90, 16777215));
        doubleSpinBox_CarLeft->setMinimum(-90);
        doubleSpinBox_CarLeft->setMaximum(90);

        gridLayout_2->addWidget(doubleSpinBox_CarLeft, 2, 1, 1, 1);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMaximumSize(QSize(110, 16777215));

        gridLayout_2->addWidget(label_11, 5, 0, 1, 1);

        doubleSpinBox_CarForward = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_CarForward->setObjectName(QStringLiteral("doubleSpinBox_CarForward"));
        doubleSpinBox_CarForward->setEnabled(false);
        doubleSpinBox_CarForward->setMaximumSize(QSize(90, 16777215));

        gridLayout_2->addWidget(doubleSpinBox_CarForward, 0, 1, 1, 1);

        pushButton_SetCarConfig = new QPushButton(layoutWidget);
        pushButton_SetCarConfig->setObjectName(QStringLiteral("pushButton_SetCarConfig"));
        pushButton_SetCarConfig->setEnabled(false);
        pushButton_SetCarConfig->setMaximumSize(QSize(90, 16777215));

        gridLayout_2->addWidget(pushButton_SetCarConfig, 4, 1, 1, 1);

        doubleSpinBox_CarBack = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_CarBack->setObjectName(QStringLiteral("doubleSpinBox_CarBack"));
        doubleSpinBox_CarBack->setEnabled(false);
        doubleSpinBox_CarBack->setMaximumSize(QSize(90, 16777215));

        gridLayout_2->addWidget(doubleSpinBox_CarBack, 1, 1, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(110, 16777215));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(110, 16777215));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMaximumSize(QSize(110, 16777215));

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pushButton_Config = new QPushButton(layoutWidget);
        pushButton_Config->setObjectName(QStringLiteral("pushButton_Config"));
        pushButton_Config->setMaximumSize(QSize(90, 16777215));

        gridLayout_3->addWidget(pushButton_Config, 0, 1, 1, 1);

        pushbutton_Close = new QPushButton(layoutWidget);
        pushbutton_Close->setObjectName(QStringLiteral("pushbutton_Close"));
        pushbutton_Close->setMaximumSize(QSize(90, 16777215));
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushbutton_Close->setIcon(icon);

        gridLayout_3->addWidget(pushbutton_Close, 1, 1, 1, 1);

        pushButton_Connect = new QPushButton(layoutWidget);
        pushButton_Connect->setObjectName(QStringLiteral("pushButton_Connect"));
        pushButton_Connect->setMaximumSize(QSize(90, 16777215));
        pushButton_Connect->setFlat(false);

        gridLayout_3->addWidget(pushButton_Connect, 0, 0, 1, 1);

        pushButton_min = new QPushButton(layoutWidget);
        pushButton_min->setObjectName(QStringLiteral("pushButton_min"));

        gridLayout_3->addWidget(pushButton_min, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_3);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_Main->addLayout(horizontalLayout);


        retranslateUi(frmMain);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(frmMain);
    } // setupUi

    void retranslateUi(QDialog *frmMain)
    {
        frmMain->setWindowTitle(QApplication::translate("frmMain", "SmartForkliftMonitor", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_warning->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("frmMain", "\345\272\217\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_warning->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("frmMain", "\346\235\245\346\272\220", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_warning->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("frmMain", "\350\257\246\346\203\205", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_warning->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("frmMain", "New Row", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_warning->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("frmMain", "New Row", 0));

        const bool __sortingEnabled = tableWidget_warning->isSortingEnabled();
        tableWidget_warning->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_warning->item(0, 0);
        ___qtablewidgetitem5->setText(QApplication::translate("frmMain", "1", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_warning->item(0, 1);
        ___qtablewidgetitem6->setText(QApplication::translate("frmMain", "kinect", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_warning->item(0, 2);
        ___qtablewidgetitem7->setText(QApplication::translate("frmMain", "warning\357\274\232\345\217\211\345\244\264\344\275\215\347\275\256\345\201\217\347\247\273\350\266\205\345\207\272\351\230\210\345\200\274", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_warning->item(1, 0);
        ___qtablewidgetitem8->setText(QApplication::translate("frmMain", "2", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_warning->item(1, 1);
        ___qtablewidgetitem9->setText(QApplication::translate("frmMain", "\350\275\246\351\201\223\347\272\277", 0));
        tableWidget_warning->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab_warningInfo), QApplication::translate("frmMain", "\345\221\212\350\255\246\344\277\241\346\201\257", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_kinect->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("frmMain", "\345\272\217\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_kinect->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QApplication::translate("frmMain", "X", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_kinect->horizontalHeaderItem(2);
        ___qtablewidgetitem12->setText(QApplication::translate("frmMain", "Y", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_kinect->horizontalHeaderItem(3);
        ___qtablewidgetitem13->setText(QApplication::translate("frmMain", "\346\217\217\350\277\260", 0));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_kinect->verticalHeaderItem(0);
        ___qtablewidgetitem14->setText(QApplication::translate("frmMain", "New Row", 0));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_kinect->verticalHeaderItem(1);
        ___qtablewidgetitem15->setText(QApplication::translate("frmMain", "New Row", 0));

        const bool __sortingEnabled1 = tableWidget_kinect->isSortingEnabled();
        tableWidget_kinect->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_kinect->item(0, 0);
        ___qtablewidgetitem16->setText(QApplication::translate("frmMain", "1", 0));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_kinect->item(0, 1);
        ___qtablewidgetitem17->setText(QApplication::translate("frmMain", "30", 0));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_kinect->item(0, 2);
        ___qtablewidgetitem18->setText(QApplication::translate("frmMain", "50", 0));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_kinect->item(0, 3);
        ___qtablewidgetitem19->setText(QApplication::translate("frmMain", "\350\266\205\345\207\272\351\230\210\345\200\274", 0));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_kinect->item(1, 0);
        ___qtablewidgetitem20->setText(QApplication::translate("frmMain", "2", 0));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_kinect->item(1, 1);
        ___qtablewidgetitem21->setText(QApplication::translate("frmMain", "60", 0));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_kinect->item(1, 2);
        ___qtablewidgetitem22->setText(QApplication::translate("frmMain", "70", 0));
        tableWidget_kinect->setSortingEnabled(__sortingEnabled1);

        tabWidget->setTabText(tabWidget->indexOf(tab_kinect), QApplication::translate("frmMain", "kinect\346\243\200\346\265\213\344\277\241\346\201\257", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_laneLine), QApplication::translate("frmMain", "\350\275\246\351\201\223\347\272\277\346\243\200\346\265\213\344\277\241\346\201\257", 0));
        label_8->setText(QApplication::translate("frmMain", "\345\211\215\345\200\276\357\274\210\350\247\222\345\272\246\357\274\211\357\274\232", 0));
        label_9->setText(QApplication::translate("frmMain", "\345\220\216\345\200\276\357\274\210\345\272\246\346\225\260\357\274\211\357\274\232", 0));
        label_10->setText(QApplication::translate("frmMain", "\344\270\212\345\215\207\357\274\210\345\216\230\347\261\263\357\274\211\357\274\232", 0));
        label_2->setText(QApplication::translate("frmMain", "\344\270\213\351\231\215\357\274\210\345\216\230\347\261\263\357\274\211\357\274\232", 0));
        label_3->setText(QApplication::translate("frmMain", "\345\267\246\347\247\273\357\274\210\345\216\230\347\261\263\357\274\211\357\274\232", 0));
        label->setText(QApplication::translate("frmMain", "\345\217\263\347\247\273\357\274\210\345\216\230\347\261\263\357\274\211\357\274\232", 0));
        pushButton_setLiftConfig->setText(QApplication::translate("frmMain", "\345\217\211\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        pushButton_AutoManual->setText(QString());
        label_5->setText(QApplication::translate("frmMain", "\345\267\246\350\275\254\357\274\210\350\247\222\345\272\246\357\274\211\357\274\232", 0));
        label_11->setText(QApplication::translate("frmMain", "\346\211\213\345\212\250\346\250\241\345\274\217\357\274\232", 0));
        pushButton_SetCarConfig->setText(QApplication::translate("frmMain", "\350\275\246\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        label_4->setText(QApplication::translate("frmMain", "\345\211\215\350\277\233\357\274\210\345\216\230\347\261\263\357\274\211\357\274\232", 0));
        label_7->setText(QApplication::translate("frmMain", "\345\220\216\351\200\200\357\274\210\345\216\230\347\261\263\357\274\211\357\274\232", 0));
        label_6->setText(QApplication::translate("frmMain", "\345\217\263\350\275\254\357\274\210\350\247\222\345\272\246\357\274\211\357\274\232", 0));
        pushButton_Config->setText(QApplication::translate("frmMain", "\347\263\273\347\273\237\350\256\276\347\275\256", 0));
        pushbutton_Close->setText(QApplication::translate("frmMain", "\351\200\200\345\207\272\347\263\273\347\273\237", 0));
        pushButton_Connect->setText(QApplication::translate("frmMain", "\345\220\257\345\212\250\350\277\236\346\216\245", 0));
        pushButton_min->setText(QApplication::translate("frmMain", "\345\220\216\345\217\260\350\277\220\350\241\214", 0));
    } // retranslateUi

};

namespace Ui {
    class frmMain: public Ui_frmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMAIN_H
