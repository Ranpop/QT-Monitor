#include "plotwidget.h"
#include "../myapp.h"
#include <QDebug>

plotWidget::plotWidget(QWidget *parent) :
    QCustomPlot(parent)
{
     m_parentDataType = nodata;
     this->m_dataType = nodata;
    connect(GetDataThread::GetInstance(), SIGNAL(GetData(GetDataType)), this, SLOT(updateData(GetDataType)), Qt::DirectConnection);
}

void plotWidget::updateData(GetDataType dataType)
{
    if(focusType(dataType))
        return;

    switch(m_parentDataType){
        case img:
            m_imageFileName = GetDataThread::GetInstance()->GetImageData();
            break;
        case marker:
            shared_marker_st tempmark;
            if(GetDataThread::GetInstance()->GetData(tempmark)){
                if(m_dataType == markerx){
                    SetRealtimeData(tempmark.posX);
                }
                if(m_dataType == markery){
                    SetRealtimeData(tempmark.posY);
                }
            }
            break;
        case lineDetec:
            shared_line_st templine;
            if(GetDataThread::GetInstance()->GetData(templine)){
                if(m_dataType == lineangle){
                    SetRealtimeData(templine.angle);
                }
                if(m_dataType == linedistance){
                    SetRealtimeData(templine.distance);
                }
            }
            break;
        case bracket:
            shared_bracket_st tempbracket;
            if(GetDataThread::GetInstance()->GetData(tempbracket)){
                if(m_dataType == bracketx){
                    SetRealtimeData(tempbracket.posX[0]);
                }
                if(m_dataType == brackety){
                    SetRealtimeData(tempbracket.posY[0]);
                }
                if(m_dataType == bracketz){
                    SetRealtimeData(tempbracket.posZ[0]);
                }
            }
            break;
        case obstacle:
            shared_obstacle_st tempobstacle;
            if(GetDataThread::GetInstance()->GetData(tempobstacle)){
                if(m_dataType == obstaclex){
                    SetRealtimeData(tempobstacle.posX);
                }
                if(m_dataType == obstacley){
                    SetRealtimeData(tempobstacle.posY);
                }
                if(m_dataType == obstaclez){
                    SetRealtimeData(tempobstacle.posZ);
                }
            }
            break;
        default:
            break;
    }
}

void plotWidget::SetDataType(GetDataType dataType)
{
    m_dataType = dataType;
    switch(m_dataType){
    case img:
        demoName = "显示图像";
        //this->LoadImage();
        setupRealtimeData();
    break;
    case markerx:
        demoName = "marker检测X值";        
        setupRealtimeData();
    break;
    case markery:
        demoName = "marker检测Y值";
        setupRealtimeData();
    break;
    case lineangle:
        demoName = "车道线角度值";
        setupRealtimeData();
    break;
    case linedistance:
        demoName = "车道线距离值";
        setupRealtimeData();
    break;
    case bracketx:
        demoName = "托盘检测X值";
        setupRealtimeData();
    break;
    case brackety:
        demoName = "托盘检测Y值";
        setupRealtimeData();
    break;
    case bracketz:
        demoName = "托盘检测Z值";
        setupRealtimeData();
    break;
    case obstaclex:
        demoName = "障碍物检测X值";
        setupRealtimeData();
    break;
    case obstacley:
        demoName = "障碍物检测Y值";
        setupRealtimeData();
    break;
    case obstaclez:
        demoName = "障碍物检测Z值";
        setupRealtimeData();
    break;
    default:
        demoName = "无关联数据";
    break;
    }
}

bool plotWidget::focusType(GetDataType dataType)
{
    bool breturn = false;
    switch(dataType){
    case img:
        if(m_dataType == img){
            m_parentDataType = img;
            breturn = true;
        }
        break;
    case marker:
        if((m_dataType == marker) | (m_dataType == markerx) | (m_dataType == markery)){
            m_parentDataType =marker;
            breturn = true;
        }
        break;
    case lineDetec:
        if((m_dataType == lineDetec) | (m_dataType == lineangle) | (m_dataType == linedistance)){
            m_parentDataType = lineDetec;
            breturn = true;
        }
        break;
    case bracket:
        if((m_dataType == bracket) | (m_dataType == bracketx) | (m_dataType == brackety) | (m_dataType == bracketz)){
            m_parentDataType = bracket;
            breturn = true;
        }
        break;
    case obstacle:
        if((m_dataType == obstacle) | (m_dataType == obstaclex) | (m_dataType == obstacley) | (m_dataType == obstaclez)){
            m_parentDataType = obstacle;
            breturn = true;
        }
        break;
    default:
        break;
    }
    return breturn;
}

void plotWidget::setupRealtimeData()
{
    if(this->m_dataType == img || this->m_dataType == nodata){
        connect(&dataTimer, SIGNAL(timeout()), this, SLOT(SetRealtimeImg()));
        dataTimer.start(myApp::plotRefreshTimeSpan); // Interval 0 means to refresh as fast as possible
        return;
    }
    else{
        this->addGraph(); // blue line
        this->graph(0)->setPen(QPen(Qt::blue));
        this->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

        this->addGraph(); // blue dot
        this->graph(1)->setPen(QPen(QColor(255, 100, 0)));
        this->graph(1)->setLineStyle(QCPGraph::lsLine);
        this->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);

        this->xAxis->setTickLabelType(QCPAxis::ltDateTime);
        this->xAxis->setDateTimeFormat("hh:mm:ss");
        this->xAxis->setAutoTickStep(false);
        this->xAxis->setTickStep(2);
        this->axisRect()->setupFullAxesBox();

        // make left and bottom axes transfer their ranges to right and top axes:
        connect(this->xAxis, SIGNAL(rangeChanged(QCPRange)), this->xAxis2, SLOT(setRange(QCPRange)));
        connect(this->yAxis, SIGNAL(rangeChanged(QCPRange)), this->yAxis2, SLOT(setRange(QCPRange)));

        connect(&dataTimer, SIGNAL(timeout()), this, SLOT(SetRealtimeData()));
        dataTimer.start(myApp::plotRefreshTimeSpan); // Interval 0 means to refresh as fast as possible
        this->yAxis->setLabel(demoName);
        this->replot();
    }
}

void plotWidget::SetRealtimeImg()
{
    this->update();
    if(this->m_dataType == img){
        QPainter painter(this);
        QString fileName = GetDataThread::GetInstance()->GetImageData();
        if(!fileName.isNull() && !fileName.isEmpty()){
            QPixmap pixmap(fileName);
            if(!pixmap.isNull()){
                painter.drawPixmap(this->rect(),pixmap);
            }
        }
    }
}

void plotWidget::paintEvent(QPaintEvent *event)
{
    if(this->m_dataType == img){
        QPainter painter(this);
        QString fileName = GetDataThread::GetInstance()->GetImageData();
        if(!fileName.isNull() && !fileName.isEmpty()){
            QPixmap pixmap(fileName);
            if(!pixmap.isNull()){
                painter.drawPixmap(this->rect(),pixmap);
            }
        }
    }else{
        QCustomPlot::paintEvent(event);
    }
}

void plotWidget::SetRealtimeData()
{
    QMutexLocker locker(&mutex);
    for(int i = 0; i < m_datas.count(); i++){
        double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
        static double lastPointKey = 0;
        if (key-lastPointKey > 0.1) // at most add point every 100 ms
        {
          // add data to lines:
          this->graph(0)->addData(key, m_datas[i]);
          // set data of dots:
          //this->graph(1)->clearData();
          this->graph(1)->addData(key, m_datas[i]);
          // remove data of lines that's outside visible range:
          this->graph(0)->removeDataBefore(key-myApp::showPlotTimeSpan);
          this->graph(1)->removeDataBefore(key-myApp::showPlotTimeSpan);
          // rescale value (vertical) axis to fit the current data:
          this->graph(0)->rescaleValueAxis();
          this->graph(1)->rescaleValueAxis(true);
          lastPointKey = key;
        }
        // make key axis range scroll with the data (at a constant range size of myApp::showPlotNum):
        this->xAxis->setRange(key+0.25, myApp::showPlotTimeSpan, Qt::AlignRight);
        this->replot();

        // calculate frames per second:
        static int frameCount;
        ++frameCount;
    }
    m_datas.clear();
}

void plotWidget::SetRealtimeData(double value)
{
    mutex.lock();
    this->m_datas.push_back(value);
    mutex.unlock();
}
