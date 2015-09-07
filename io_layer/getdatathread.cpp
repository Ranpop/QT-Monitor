#include "getdatathread.h"
#include "inoutfactory.h"
#include "../myapp.h"

GetDataThread* GetDataThread::m_pInstacne = NULL;

GetDataThread::GetDataThread(QObject *parent) :
    QThread(parent)
{
    bStop = false;
    m_pSaveImgThread = new SaveDataThread();
    m_pSaveImgThread->start();

    //m_pTcpSocketThread = new TcpSocketThread();
    //m_pTcpSocketThread->start();
    m_pUdpSocketThread = new UdpSocketThread();
    m_pUdpSocketThread->start();

}

GetDataThread::~GetDataThread()
{
    m_pSaveImgThread->Stop();
    QThread::sleep(myApp::saveImgTimeSpan * 5);
    delete m_pSaveImgThread;
    m_pSaveImgThread = NULL;

    m_pTcpSocketThread->Stop();
    QThread::sleep(100);
    delete m_pTcpSocketThread;
    m_pTcpSocketThread = NULL;

    m_pUdpSocketThread->Stop();
    QThread::sleep(100);
    delete m_pUdpSocketThread;
    m_pUdpSocketThread = NULL;
}

GetDataThread* GetDataThread::GetInstance()
{
    if(m_pInstacne == NULL) {
        m_pInstacne = new GetDataThread();
    }
    return m_pInstacne;
}

void GetDataThread::stop()
{
    bStop = true;
}

void GetDataThread::run()
{
    //IGetStatusData* getdata = InOutFactory::GetInstance()->GetDataInterface(in_test);
    //IGetStatusData* getdata = InOutFactory::GetInstance()->GetInterface(in_sharememory);
    IGetStatusData* getdata = InOutFactory::GetInstance()->GetInterface(in_test);

    while(!bStop){
        //the system is disconnect, just loop
        if (NULL == getdata){
            getdata = InOutFactory::GetInstance()->GetInterface(in_test);
            continue;
        }

        shared_img_st* result = getdata->GetImageInfo();
        if(result != 0){
            this->m_pSaveImgThread->Add(result);
            emit GetData(img);
        }

        shared_marker_st tempmarker;
        if(getdata->GetMarketInfo(tempmarker)){
            if(m_marketInfo.count() > myApp::normalDataInMemoryNum)
                m_pSaveImgThread->Add(m_marketInfo);
            m_marketInfo.push_back(tempmarker);
            emit GetData(marker);
        }

        shared_line_st templine;
        if(getdata->GetLineInfo(templine)){
            if(m_lineInfo.count() > myApp::normalDataInMemoryNum)
                m_pSaveImgThread->Add(m_lineInfo);
            m_lineInfo.push_back(templine);
            emit GetData(lineDetec);
        }

        shared_bracket_st tempbracket;
        if(getdata->GetBracketInfo(tempbracket)){
            if(m_bracketInfo.count() > myApp::normalDataInMemoryNum)
                m_pSaveImgThread->Add(m_bracketInfo);
            m_bracketInfo.push_back(tempbracket);
            emit GetData(bracket);
        }

        shared_obstacle_st tempobstacle;
        if(getdata->GetObstacleInfo(tempobstacle)){
            if(m_obstacleInfo.count() > myApp::normalDataInMemoryNum)
            {
                m_pSaveImgThread->Add(m_obstacleInfo);
            }
            m_obstacleInfo.push_back(tempobstacle);
            //emit GetData(obstacle);
        }

        shared_forklift_state_st tempforkinfo;
        if (getdata->GetForkRTInfo(tempforkinfo)){
            if (m_forkInfo.count() > 1)
            {
                //m_pTcpSocketThread->Add(m_forkInfo);
                m_pUdpSocketThread->Add(m_forkInfo);
            }
            m_forkInfo.push_back(tempforkinfo);
            //emit GetData(forkinfo);
        }

        //预计20ms读取一次，有丢包问题
        //QThread::msleep(myApp::getDataTimeSpan );
        QThread::msleep(10 );
    }
}

bool GetDataThread::GetData(shared_bracket_st& tempbracket)
{
    if(m_bracketInfo.count() > 0){
        tempbracket = m_bracketInfo[m_bracketInfo.count() - 1];
        return true;
    }
    return false;
}

QString GetDataThread::GetImageData()
{
    return this->m_pSaveImgThread->getImgFileName();
}

bool GetDataThread::GetData(shared_line_st& templine)
{
    if(m_lineInfo.count() > 0){
        templine = m_lineInfo[m_lineInfo.count() - 1];
        return true;
    }
    return false;
}

bool GetDataThread::GetData(shared_marker_st& tempmarker)
{
    if(m_marketInfo.count() > 0){
        tempmarker = m_marketInfo[m_marketInfo.count() - 1];
        return true;
    }
    return false;
}

bool GetDataThread::GetData(shared_obstacle_st& tempobstacle)
{
    if(m_obstacleInfo.count() > 0){
        tempobstacle = m_obstacleInfo[m_obstacleInfo.count() - 1];
        return true;
    }
    return false;
}

bool GetDataThread::GetData(shared_forklift_state_st &tempfork)
{
    if (m_forkInfo.count() > 0){
        tempfork = m_forkInfo[m_forkInfo.count() - 1];
        return true;
    }
    return false;
}

