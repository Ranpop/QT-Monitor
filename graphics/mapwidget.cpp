#include "mapwidget.h"
#include <QSlider>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>
#include <math.h>
#include <QDebug>
#include "../myapp.h"
#include "lineItem.h"
#include "../myhelper.h"

MapWidget* MapWidget::m_pInstacne = NULL;

MapWidget::MapWidget(QWidget * parent):QGraphicsView(parent)
{
    map.load("warehouse.jpg");

    myApp::graphicsViewWidth = map.width();
    myApp::graphicsViewHeigt = map.height();
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,myApp::graphicsViewWidth, myApp::graphicsViewHeigt);
    setScene(scene);
    setCacheMode(CacheBackground);

    //坐标值显示区
    viewCoord = new QLabel;
    sceneCoord = new QLabel;

    //坐标显示区布局
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(viewCoord,0,1);
    gridLayout->addWidget(sceneCoord,1,1);
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);

    QFrame *coordFrame = new QFrame;
    coordFrame->setLayout(gridLayout);

    //坐标显示区域布局
    QVBoxLayout *coordLayout = new QVBoxLayout;
    coordLayout->addWidget(coordFrame);
    coordLayout->addStretch();

    //主布局
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(coordLayout);
    mainLayout->addStretch();
    mainLayout->setMargin(30);
    mainLayout->setSpacing(10);
    setLayout(mainLayout);

    m_forkliftItem = new forkliftItem();
    scene->addItem(m_forkliftItem);
    m_forkliftItem->setPos(0,50);
    QPoint initialforkliftPos(-100, -100);
    m_forkliftItem->AddPosition(initialforkliftPos);
    m_forkliftItem->setFlag(QGraphicsItem::ItemIsMovable);

    m_forkliftPathItem = new forkliftPathItem();
    scene->addItem(m_forkliftPathItem);
    m_pathStatus =  noedit;

    m_lineItem = new lineItem(myApp::graphicsViewWidth, myApp::graphicsViewHeigt);  //生成车道交叉线
    scene->addItem(m_lineItem);

    m_pInstacne =this;

    connect(this, SIGNAL(setCmd()), ISetCommond::GetInstance(), SLOT(setCmdProc()));
    connect(GetDataThread::GetInstance(), SIGNAL(GetData(GetDataType)), this, SLOT(updateData(GetDataType)), Qt::DirectConnection);
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(updateDataSlot()));
    dataTimer.start(myApp::mapRefreshTimeSpan); // Interval 0 means to refresh as fast as possible
}

MapWidget* MapWidget::GetInstance()
{
    if(m_pInstacne == NULL){
        qDebug("MapWidget instance is null , It's a problem !");
    }
    return m_pInstacne;
}

MapWidget::~MapWidget()
{

}

void MapWidget::path_removePoint()
{
    m_pathStatus = removepoint;
}

void MapWidget::path_setcurrentPoint()
{
    m_pathStatus = movepoint;
}

void MapWidget::path_edit(bool editable)
{
    if(editable){
        m_pathStatus = addpoint;
    }else{
        m_pathStatus = noedit;
    }
}

void MapWidget::CalcCommand()
{
    shared_subcmd_st cmdtemp;

    if (!m_forkliftPathItem->m_cargoPoints.count()){
        myHelper::ShowMessageBoxInfo("请设置路径关键点再执行作业任务！");
        return;
    }

    QPoint carp, cargop0, cargop1;
    carp.rx() = myApp::meterTopixelWidth()*m_position.rx(); carp.ry() = myApp::meterTopixelHeight()*(myApp::warehouseHeight/1000 - m_position.ry());
    cargop0.rx() = m_forkliftPathItem->m_cargoPoints[0].rx(); cargop0.ry() = m_forkliftPathItem->m_cargoPoints[0].ry();
    cargop1.rx() = m_forkliftPathItem->m_cargoPoints[1].rx(); cargop1.ry() = m_forkliftPathItem->m_cargoPoints[1].ry();
    CalcCmdProc(carp, cargop0, cargop1);

    carp.rx() = m_forkliftPathItem->m_cargoPoints[1].rx(); carp.ry() = m_forkliftPathItem->m_cargoPoints[1].ry();
    cargop0.rx() = m_forkliftPathItem->m_cargoPoints[m_forkliftPathItem->m_cargoPoints.count() - 1].rx(); cargop0.ry() = m_forkliftPathItem->m_cargoPoints[m_forkliftPathItem->m_cargoPoints.count() - 1].ry();
    cargop1.rx() = m_forkliftPathItem->m_cargoPoints[m_forkliftPathItem->m_cargoPoints.count() - 2].rx(); cargop1.ry() = m_forkliftPathItem->m_cargoPoints[m_forkliftPathItem->m_cargoPoints.count() - 2].ry();
    CalcCmdProc(carp, cargop0, cargop1);

    cmdtemp.cmdType = 'N'; cmdtemp.pos = 0xffffffff;
    cmdtemp.posX = 88; cmdtemp.posY = 88;
    m_cmdDataInfo.push_back(cmdtemp);

    emit setCmd();
    return;
}

void MapWidget::CalcCmdProc(QPoint carp, QPoint cargop0, QPoint cargop1)
{
    shared_subcmd_st cmdtemp;
    double lcpx = lineItem::m_lineCroPos.rx(), lcpy =  lineItem::m_lineCroPos.ry();
    double carpiexx = carp.rx(), carpiexy = carp.ry();
    double cargopx0 = cargop0.rx(), cargopy0 = cargop0.ry();
    double cargopx1 = cargop1.rx(), cargopy1 = cargop1.ry();

    /*no turn line mode*/
    qDebug("removepointertyuio line straigtcarpx=%f, carpy=%f, cargopx1=%f cargopy1%f    !!!!!!!!!!!!!s", carpiexx, carpiexy, cargopx1, cargopy1 );
    if ((JuageErrRange(carpiexx, cargopx1)) || (JuageErrRange(carpiexy, cargopy1))){
        cmdtemp.cmdType = 'd';  cmdtemp.pos = (JuageErrRange(carpiexy, cargopy1) == true ? cargopx1/myApp::meterTopixelWidth() : (myApp::graphicsViewHeigt-cargopy1-8)/myApp::meterTopixelHeight());
        cmdtemp.posX = cargopx1;cmdtemp.posY=cargopy1;
        qDebug("removepointertyuio line straigt dd pos=%f X=%f, Y=%f", cmdtemp.pos, cmdtemp.posX, cmdtemp.posY);
        m_cmdDataInfo.push_back(cmdtemp);

        cmdtemp.cmdType = 't';
        /*weiyu Y zhou shang*/
        if (JuageErrRange(cargopx1, lcpx)){
            //huowu weiyu zuobian
            if (cargopx0 < lcpx){
                cmdtemp.pos = (-2 == m_orientation) ? 1 : -1;
            }
            else{
                cmdtemp.pos = (-2 == m_orientation) ? -1 : 1;
            }
        }
        else{ //huowu weiyu X zhou
            if (cargopy0 < lcpy){
                cmdtemp.pos = (-1 == m_orientation) ? -1 : 1;
            }
            else{
                cmdtemp.pos = (-1 == m_orientation) ? -1 : 1;
            }
        }
        //cmdtemp.pos =(JuageErrRange(carpiexy, cargopy1) == true)? ((carpiexx>cargopx1)?(cargopy1-cargopy0) : (cargopy0-cargopy1)) : ((carpiexy>cargopy1)?(cargopx0-cargopx1) : (cargopx1-cargopx0));
        cmdtemp.posX = 88; cmdtemp.posY = 88;
        qDebug("removepointertyuio line straigt tt pos=%f X=%f, Y=%f", cmdtemp.pos, cmdtemp.posX, cmdtemp.posY);
        m_cmdDataInfo.push_back(cmdtemp);
        cmdtemp.cmdType = 'f'; cmdtemp.pos = 0.03;
        cmdtemp.posX = 88; cmdtemp.posY = 88;
        qDebug("removepointertyuio line straigt ff pos=%f X=%f, Y=%f", cmdtemp.pos, cmdtemp.posX, cmdtemp.posY);
        m_cmdDataInfo.push_back(cmdtemp);

        cmdtemp.cmdType = 't'; cmdtemp.pos = 0 - m_cmdDataInfo[m_cmdDataInfo.count() - 2].pos;
        cmdtemp.posX = 88; cmdtemp.posY = 88;
        qDebug("removepointertyuio line straigt tt pos=%f X=%f, Y=%f", cmdtemp.pos, cmdtemp.posX, cmdtemp.posY);
        m_cmdDataInfo.push_back(cmdtemp);

        return;
    }

    /*run to cross point and then turn and then run and then turn and then fork */
    cmdtemp.cmdType = 'd'; cmdtemp.pos = JuageErrRange(lcpy ,carpiexy) == true ? lcpx/myApp::meterTopixelWidth() : (myApp::graphicsViewHeigt-lcpy -8)/myApp::meterTopixelHeight();//(myApp::warehouseHeight/1000 - myApp::pixelTometerWidth()*(myApp::graphicsViewHeigt-lcpy + 48.4)/1000);
    cmdtemp.posX = lcpx; cmdtemp.posY = lcpy;
    qDebug("removepointertyuio line straigt dd pos=%f X=%f, Y=%f", cmdtemp.pos, cmdtemp.posX, cmdtemp.posY);
    m_cmdDataInfo.push_back(cmdtemp);
    cmdtemp.cmdType = 't'; cmdtemp.pos = JuageErrRange(carpiexy ,lcpy) == true ?  (carpiexx > lcpx ? lcpy-cargopy1 : cargopy1-lcpy) : (lcpy > carpiexy ? carpiexx-cargopx1 : cargopx1-carpiexx);
    cmdtemp.posX = 88; cmdtemp.posY = 88;
    qDebug("removepointertyuio line straigt tt pos=%f X=%f, Y=%f", cmdtemp.pos, cmdtemp.posX, cmdtemp.posY);
    m_cmdDataInfo.push_back(cmdtemp);
    cmdtemp.cmdType = 'd'; cmdtemp.pos = JuageErrRange(lcpy ,cargopy1) == true ? cargopx1/myApp::meterTopixelWidth() :(myApp::graphicsViewHeigt-cargopy1-8)/myApp::meterTopixelHeight() ;//(myApp::warehouseHeight/1000 - myApp::pixelTometerWidth()*(myApp::graphicsViewHeigt-cargopy1 + 48.4)/1000);
    cmdtemp.posX = cargopx1; cmdtemp.posY = cargopy1;
    qDebug("removepointertyuio line straigt dd pos=%f X=%f, Y=%f", cmdtemp.pos, cmdtemp.posX, cmdtemp.posY);
    m_cmdDataInfo.push_back(cmdtemp);
    cmdtemp.cmdType = 't';
    /*weiyu Y zhou shang*/
    if (JuageErrRange(cargopx1, lcpx)){
        //huowu weiyu zuobian
        if (cargopx0 < lcpx){
            cmdtemp.pos = (-2 == m_orientation) ? 1 : -1;
        }
        else{
            cmdtemp.pos = (-2 == m_orientation) ? -1 : 1;
        }
    }
    else{ //huowu weiyu X zhou
        if (cargopy0 < lcpy){
            cmdtemp.pos = (-1 == m_orientation) ? -1 : 1;
        }
        else{
            cmdtemp.pos = (-1 == m_orientation) ? -1 : 1;
        }
    }
    //cmdtemp.pos = (JuageErrRange(lcpy, cargopy1) == true ? (cargopx1 > lcpx ? cargopy0-cargopy1 : cargopy1-cargopy0) : (cargopy1 > lcpy ? cargopx1-cargopx0 : cargopx0-cargopx1) );
    cmdtemp.posX = 88; cmdtemp.posY = 88;
    qDebug("removepointertyuio line straigt tt pos=%f X=%f, Y=%f", cmdtemp.pos, cmdtemp.posX, cmdtemp.posY);
    m_cmdDataInfo.push_back(cmdtemp);
    cmdtemp.cmdType = 'f'; cmdtemp.pos = 0.03;
    cmdtemp.posX = 88; cmdtemp.posY = 88;
    qDebug("removepointertyuio line straigt ff pos=%f X=%f, Y=%f", cmdtemp.pos, cmdtemp.posX, cmdtemp.posY);
    m_cmdDataInfo.push_back(cmdtemp);

    cmdtemp.cmdType = 't'; cmdtemp.pos = 0 - m_cmdDataInfo[m_cmdDataInfo.count() - 2].pos;
    cmdtemp.posX = 88; cmdtemp.posY = 88;
    qDebug("removepointertyuio line straigt tt pos=%f X=%f, Y=%f", cmdtemp.pos, cmdtemp.posX, cmdtemp.posY);
    m_cmdDataInfo.push_back(cmdtemp);
    return;
}

void MapWidget::emergencyStopCmd()
{
    shared_subcmd_st cmdtemp;

    cmdtemp.cmdType = 'N'; cmdtemp.pos = 2;
    m_cmdDataInfo.push_back(cmdtemp);
    qDebug("MapWidget::emergencyStopCmd in !!!!!!!!!!!!!!!!");
    emit setCmd();
    return;
}

bool MapWidget::SetCommandData(QVector<shared_subcmd_st> &cmdtemp)
{
    if (m_cmdDataInfo.count() > 0){
        for (int i=0; i < m_cmdDataInfo.count(); i++){
           cmdtemp.push_back(m_cmdDataInfo[i]);
        }
        m_cmdDataInfo.clear();
        return true;
    }
    return false;
}


void MapWidget::updateData(GetDataType dataType)
{
    if(dataType == marker){
        shared_marker_st tempmark;
        if(GetDataThread::GetInstance()->GetData(tempmark)){
            m_position.rx() = tempmark.posX;
            m_position.ry() = tempmark.posY;
            m_forkliftItem->AddPosition(TransferToScene(m_position));
        }
    }

    if(dataType == lineDetec){
        shared_line_st templine;
        if(GetDataThread::GetInstance()->GetData(templine)){
            angle = templine.angle;
            m_forkliftItem->AddPosture(templine.angle);
        }
    }

    if (dataType == forkinfo){
        shared_forklift_state_st tempfork;
        if (GetDataThread::GetInstance()->GetData(tempfork)){
            m_orientation = tempfork.orientation;
        }
    }
}

void MapWidget::updateDataSlot()
{
    this->scene->invalidate();
    static int refresh = 0;
    if(refresh < 20){
        refresh ++;
    }
    else{
            viewCoord->setText("X:" + QString::number((m_position).rx())//m_position.x()//TransferToConTrol(m_lineItem->m_lineCroPos).rx()
                                                +","+ "Y = " + QString::number((m_position).ry()));//m_lineItem->m_lineCroPos.rx()
            sceneCoord->setText("角度:" + QString::number(angle));
            refresh = 0;
    }
}

void MapWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(int(sceneRect().left()),int(sceneRect().top()), map);
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
    if (m_pathStatus == noedit){
        return QGraphicsView::mousePressEvent(event);
    }
   // if(event->buttons() == Qt::RightButton)//
   //     return QGraphicsView::mousePressEvent(event);

    QPointF scenePoint = mapToScene(event->pos());
    if(m_pathStatus != noedit){
        m_forkliftPathItem->SetCurrentPoint(scenePoint);
    }
    if(m_pathStatus == addpoint){
        m_forkliftPathItem->AddPoint(scenePoint);
        updateDataSlot();
        m_pathStatus = noedit;
    }
    if(m_pathStatus == removepoint){
        m_forkliftPathItem->RemovePoint(scenePoint);
        updateDataSlot();
        m_pathStatus = noedit;
    }
}

void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pathStatus == movepoint) {
        QPointF scenePoint = mapToScene(event->pos());
         qDebug("mousemove x = %f, y = %f", scenePoint.x(), scenePoint.y());
        //m_forkliftPathItem->SetCurrentPoint(scenePoint);
        m_forkliftPathItem->MovePoint(scenePoint);
        updateDataSlot();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void MapWidget::scrollContentsBy(int dx, int dy)
{
    qDebug("Graphicsview x = %d, y = %d", dx, dy);
    QGraphicsView::scrollContentsBy(dx, dy);
}

QPoint MapWidget::TransferToScene(QPointF& point)
{
    QPoint result;
    result.rx() = myApp::meterTopixelWidth() * point.x();
    result.ry() = myApp::graphicsViewHeigt - myApp::meterTopixelHeight()*point.y() - 48.4;

    return result;
}

QPointF MapWidget::TransferToConTrol(QPoint& point)
{
    QPointF result;
    result.rx() = (point.rx()+4) * myApp::pixelTometerWidth()/1000;
    result.ry() = myApp::pixelTometerWidth()*(point.ry()+8) / 1000;

    return result;
}

bool MapWidget::JuageErrRange(double pos0, double pos1)
{
    double errrange = fabs(pos0 - pos1);
    if (errrange < ERROR_RANGE){
        return true;
    }
    else{
        return false;
    }
}

void MapWidget::path_clear()
{
    m_forkliftPathItem->ClearPoint();
}

void MapWidget::path_operate(){

    if (myApp::connectSysFlag){
        CalcCommand();
    }
    else{
        myHelper::ShowMessageBoxInfo("系统未连接，请连接系统！");
        return;
    }
}
