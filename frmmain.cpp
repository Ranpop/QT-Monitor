#include "frmmain.h"
#include "ui_frmmain.h"
#include "iconhelper.h"
#include "myhelper.h"
#include "myapp.h"
#include "io_layer/inoutfactory.h"
#include "io_layer/getdatathread.h"
#include "graphics/mapwidget.h"
#include "graphics/setforkinfo.h"

frmMain* frmMain::m_pInstacne = NULL;

frmMain::frmMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);

    this->InitStyle();
    this->InitForm();
    this->InitPlot();
    this->InitMenu();
    this->InitConnect();

    m_pInstacne = this;

    InOutFactory::GetInstance();
    SetForkInfo::GetInstance();
    GetDataThread::GetInstance()->start();
}

frmMain::~frmMain()
{
    delete ui;
}

frmMain* frmMain::GetInstance()
{
    return m_pInstacne;
}

void frmMain::InitStyle()
{
    this->setStyleSheet("QGroupBox#gboxMain{border-width:0px;}");
    this->setProperty("Form", true);
    //设置窗体标题栏隐藏--Qt::WindowStaysOnTopHint |
    if(myApp::topShow){
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);// | Qt::X11BypassWindowManagerHint);
    }
    else{
        this->setWindowFlags(Qt::FramelessWindowHint); // | Qt::WindowStaysOnTopHint);// | Qt::X11BypassWindowManagerHint);
    }

    this->showFullScreen();
}

void frmMain::InitForm()
{
    ui->graphicsView->installEventFilter(this);

    ui->pushButton_AutoManual->SetCheck(false);

    setLayout(ui->verticalLayout_Main);
    ui->tabWidget->widget(0)->setLayout(ui->verticalLayout_Warning);
    ui->tabWidget->widget(1)->setLayout(ui->verticalLayout_kinect);
    ui->tabWidget->widget(2)->setLayout(ui->verticalLayout_laneline);
}

void frmMain::InitPlot()
{
    currentPlotWidget = 0;
    plotWidgets.append(ui->widgetParameter_Curve_0);
    plotWidgets.append(ui->widgetParameter_Curve_1);
    plotWidgets.append(ui->widgetParameter_Curve_2);
    plotWidgets.append(ui->widgetParameter_Curve_3);
    plotWidgets.append(ui->widgetParameter_Curve_4);
    plotWidgets.append(ui->widgetParameter_Curve_5);
    plotWidgets.append(ui->widgetParameter_Curve_6);
    plotWidgets.append(ui->widgetParameter_Curve_7);
    //plotWidgets.append(ui->widgetParameter_Curve_8);

    for (int i = 0; i < myApp::ployNum; i++) {
        plotWidgets[i]->installEventFilter(this);
        plotWidgets[i]->setProperty("labParameter_Curve", true);
    }
    plotWidgets[0]->SetDataType(img);
    plotWidgets[1]->SetDataType(lineangle);
    plotWidgets[2]->SetDataType(linedistance);
    plotWidgets[3]->SetDataType(bracketx);
    plotWidgets[4]->SetDataType(brackety);
    plotWidgets[5]->SetDataType(bracketz);
    plotWidgets[6]->SetDataType(obstaclex);
    plotWidgets[7]->SetDataType(obstacley);
    //plotWidgets[8]->SetDataType(obstaclez);
}

void frmMain::InitConnect()
{
    connect(ui->pushbutton_Close, SIGNAL(clicked()), this, SLOT(on_btnClose_clicked()));
    connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(on_btnMin_clicked()));
    connect(ui->pushButton_AutoManual, SIGNAL(clicked()), this, SLOT(on_btnAutoManual_clicked()));
    connect(ui->pushButton_Connect, SIGNAL(clicked()), this, SLOT(on_btnConnect_clicked()));

    connect(this, SIGNAL(setformdata()), this, SLOT(on_tableWidget_warning_itemSelectionChanged()));
    connect(this, SIGNAL(emergencyStop()), MapWidget::GetInstance(), SLOT(emergencyStopCmd()));

    connect(&QtTimer, SIGNAL(timeout()), this, SLOT(PressRightEvent()));
    //QtTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void frmMain::InitMenu()
{
    menu_plot = new QMenu(this);
    menu_plot->setStyleSheet("font: 10pt \"微软雅黑\";");
    menu_plot->addAction("删除当前参数曲线", this, SLOT(delete_plot_one()));
    menu_plot->addAction("删除所有参数曲线", this, SLOT(delete_plot_all()));
    menu_plot->addSeparator();

    menu_plot->addAction("显示图像", this, SLOT(show_paramter()));
    QMenu *menuCarPos = menu_plot->addMenu("车位置信息");
    menuCarPos->addAction("车-X", this, SLOT(show_paramter()));
    menuCarPos->addAction("车-Y", this, SLOT(show_paramter()));

    QMenu *menuLine = menu_plot->addMenu("车道线信息");
    menuLine->addAction("角度", this, SLOT(show_paramter()));
    menuLine->addAction("距离", this, SLOT(show_paramter()));

    QMenu *menuLift = menu_plot->addMenu("托盘信息");
    menuLift->addAction("托盘-X", this, SLOT(show_paramter()));
    menuLift->addAction("托盘-Y", this, SLOT(show_paramter()));
    menuLift->addAction("托盘-Z", this, SLOT(show_paramter()));

    QMenu *menuDanager = menu_plot->addMenu("障碍物信息");
    menuDanager->addAction("障碍物-X", this, SLOT(show_paramter()));
    menuDanager->addAction("障碍物-Y", this, SLOT(show_paramter()));
    menuDanager->addAction("障碍物-Z", this, SLOT(show_paramter()));

    menu_graphics = new QMenu(this);
    menu_graphics->setStyleSheet("font: 10pt \"微软雅黑\";");

    menu_graphics->addAction("增加关键点", this, SLOT(path_edit()));
    menu_graphics->addAction("移动关键点", this, SLOT(path_setcurrentPoint()));
    menu_graphics->addAction("删除关键点", this, SLOT(path_removePoint()));
    menu_graphics->addSeparator();
    menu_graphics->addAction("结束编辑", this, SLOT(path_endEdit()));
    menu_graphics->addAction("清空路径", this, SLOT(path_clear()));
    menu_graphics->addAction("开始作业", this, SLOT(path_operate()));
}

void frmMain::setFormData(shared_forklift_state_st temp)
{
    static int count = 0;


    if (25 !=count){
        count++;
    }
    else{
        //qDebug("frmMain::setFormData(!!!!!!!!!!!!!!!");
        count = 0;
        memcpy(&m_formdata, &temp, sizeof(shared_forklift_state_st));
        emit setformdata();
    }
}

void frmMain::path_endEdit()
{
    currentMapWidget->path_edit(false);
}

void frmMain::path_edit()
{
        currentMapWidget->path_edit(true);
}

void frmMain::path_clear()
{
    currentMapWidget->path_clear();
}

void frmMain::path_operate()
{
    currentMapWidget->path_operate();
}

void frmMain::path_setcurrentPoint()
{
    currentMapWidget->path_setcurrentPoint();
}

void frmMain::path_removePoint()
{
    currentMapWidget->path_removePoint();
}

void frmMain::on_btnAutoManual_clicked()
{
    bool enabled = ui->pushButton_AutoManual->GetCheck();
    //car
    ui->doubleSpinBox_CarBack->setEnabled(enabled);
    ui->doubleSpinBox_CarForward->setEnabled(enabled);
    ui->doubleSpinBox_CarLeft->setEnabled(enabled);
    ui->doubleSpinBox_CarRight->setEnabled(enabled);
    ui->pushButton_SetCarConfig->setEnabled(enabled);

    //lift
    ui->doubleSpinBox_liftBack->setEnabled(enabled);
    ui->doubleSpinBox_liftDown->setEnabled(enabled);
    ui->doubleSpinBox_liftForward->setEnabled(enabled);
    ui->doubleSpinBox_liftleft->setEnabled(enabled);
    ui->doubleSpinBox_liftRight->setEnabled(enabled);
    ui->doubleSpinBox_liftUp->setEnabled(enabled);
    ui->pushButton_setLiftConfig->setEnabled(enabled);
}

void frmMain::on_btnConnect_clicked()
{
    static bool clicked = true;
    if (clicked){
        myApp::connectSysFlag = true;
        ui->pushButton_Connect->setText("断开连接");
        clicked = false;
    }
    else{
        myApp::connectSysFlag = false;
        emit emergencyStop();
        ui->pushButton_Connect->setText("启动连接");
        clicked = true;
    }

}

void frmMain::on_btnClose_clicked()
{
    Exit();
}

void frmMain::on_btnMin_clicked()
{
    this->showMinimized();
}

void frmMain::delete_plot_one()
{
    if(currentPlotWidget != NULL){
        currentPlotWidget->SetDataType(nodata);
    }
}

void frmMain::delete_plot_all()
{
    for(int i = 0; i < this->plotWidgets.count(); i++){
        plotWidgets[i]->SetDataType(nodata);
    }
}

void frmMain::screen_full()
{
    this->showFullScreen();
}

void frmMain::show_paramter()
{
    QAction *action = (QAction *)sender();
    QString name = action->text();

    GetDataType dataType = nodata;
    if (name == "显示图像") {
        dataType = img;
    } else if (name == "车-X") {
        dataType = markerx;
    } else if (name == "车-Y") {
        dataType = markery;
    } else if (name == "角度") {
        dataType = lineangle;
    } else if (name == "距离") {
        dataType = linedistance;
    } else if (name == "托盘-X") {
        dataType = bracketx;
    } else if (name == "托盘-Y") {
        dataType = brackety;
    } else if (name == "托盘-Z") {
        dataType = bracketz;
    } else if (name == "障碍物-X") {
        dataType = obstaclex;
    } else if (name == "障碍物-Y") {
        dataType = obstacley;
    } else if (name == "障碍物-Z") {
        dataType = obstaclez;
    }
    if(currentPlotWidget != NULL){
        currentPlotWidget->SetDataType(dataType);
    }
}

void frmMain::keyPressEvent(QKeyEvent *event)
{
    //空格键进入全屏,esc键退出全屏
    switch(event->key()) {
    case Qt::Key_F1:
        screen_full();
        break;
    case Qt::Key_Escape:
        Exit();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
    case Qt::Key_Space:
        emit emergencyStop();
        break;
    default:
        QDialog::keyPressEvent(event);
        break;
    }
}

static QObject *thisobj;

bool frmMain::eventFilter(QObject *obj, QEvent *event)
{
    QMouseEvent *MouseEvent = static_cast<QMouseEvent *>(event);
    if ((event->type() == QEvent::MouseButtonDblClick) &&
            (MouseEvent->buttons() == Qt::LeftButton)) {
        return true;
    } else if (event->type() == QEvent::MouseButtonPress) {
        // qDebug("frmMain::PressRightEvent eventFilter");
        thisobj = obj;
        QtTimer.start(500);
        return true;

    }else if(event->type() == QEvent::MouseButtonRelease){
        if (QtTimer.isActive()){
            QtTimer.stop();
        }
    }

    return QObject::eventFilter(obj, event);
}

void frmMain::PressRightEvent()
{
    //qDebug("frmMain::PressRightEvent map");
    currentPlotWidget = qobject_cast<plotWidget *>(thisobj);
    if(currentPlotWidget != 0)
        menu_plot->exec(QCursor::pos());

    currentMapWidget = qobject_cast<MapWidget *>(thisobj);
    if(currentMapWidget != 0)
        menu_graphics->exec(QCursor::pos());

    if (QtTimer.isActive()){
        QtTimer.stop();
    }
}

void frmMain::destory()
{
    delete InOutFactory::GetInstance();
    GetDataThread::GetInstance()->stop();
    QThread::sleep(myApp::getDataTimeSpan * 5);
    delete GetDataThread::GetInstance();
}

void frmMain::Exit()
{
    if (myHelper::ShowMessageBoxQuesion("确定要退出吗?") == 1) {
        exit(0);
        destory();
    }
}

void frmMain::on_tableWidget_warning_windowTitleChanged(const QString &title)
{

}

void frmMain::on_pushButton_Connect_clicked()
{

}

void frmMain::on_tableWidget_warning_itemSelectionChanged()
{
      //qDebug("frmMain::setFormData 2222!!!!!!!!!!!!!!!");
    QString strtemp, strtemp1;
    strtemp1.setNum(m_formdata.Y0);
    strtemp.setNum(m_formdata.X0); strtemp+=" ; ";strtemp+=strtemp1;
    ui->tableWidget_warning->item(0,2)->setText(strtemp);
    strtemp.setNum(m_formdata.wheelAngle);
    ui->tableWidget_warning->item(1,2)->setText(strtemp);
    strtemp.setNum(m_formdata.rightWheelAngle);
    ui->tableWidget_warning->item(2,2)->setText(strtemp);
    strtemp.setNum(m_formdata.leftWheelAngle);
    ui->tableWidget_warning->item(3,2)->setText(strtemp);
    strtemp.setNum(m_formdata.headingAngle);
    ui->tableWidget_warning->item(4,2)->setText(strtemp);
    strtemp.setNum(m_formdata.forkliftLength);
    ui->tableWidget_warning->item(5,2)->setText(strtemp);
    strtemp.setNum(m_formdata.forkliftWidthHead);
    ui->tableWidget_warning->item(6,2)->setText(strtemp);
    strtemp.setNum(m_formdata.forkliftWidthTail);
    ui->tableWidget_warning->item(7,2)->setText(strtemp);
    strtemp.setNum(m_formdata.v);
    ui->tableWidget_warning->item(8,2)->setText(strtemp);
    strtemp.setNum(m_formdata.wTurnWheel);
    ui->tableWidget_warning->item(9,2)->setText(strtemp);
    strtemp.setNum(m_formdata.lineDistance);
    ui->tableWidget_warning->item(10,2)->setText(strtemp);
    strtemp.setNum(m_formdata.orientation);
    ui->tableWidget_warning->item(11,2)->setText(strtemp);
}
