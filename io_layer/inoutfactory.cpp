#include "inoutfactory.h"
#include "sharememory.h"
#include "testsenddata.h"
#include "../myapp.h"

InOutFactory* InOutFactory::m_pInstance = NULL;

InOutFactory::InOutFactory()
{

}

InOutFactory::~InOutFactory()
{
    for(int i = 0; i < m_getStatusDatas.count(); i++){
        delete m_getStatusDatas[i];
        m_getStatusDatas[i] = NULL;
    }

    for(int i = 0; i < m_setCommonds.count(); i++){
        delete m_setCommonds[i];
        m_setCommonds[i] = NULL;
    }
}

InOutFactory* InOutFactory::GetInstance()
{
    if(m_pInstance == NULL){
        m_pInstance = new InOutFactory();
    }
    return m_pInstance;
}

IGetStatusData* InOutFactory::GetInterface(IOType type)
{
    IGetStatusData* temp = NULL;
    if (!myApp::connectSysFlag){
        return NULL;
    }

    switch(type) {
        case in_sharememory:
            if (0 == m_getWriteReadInstance.count()){
                temp = new ShareMemory();
                temp->Initial();
                m_getStatusDatas.push_back(temp);
                m_getWriteReadInstance.push_back(temp);
            }
            else{
                temp = m_getWriteReadInstance[0];
            }
            break;
        case in_tcpsocket:
            break;
        case in_udpsocket:
            break;
        case in_http:
            break;
        case in_test:
            if (0 == m_getWriteReadInstance.count()){
                temp = new TestSendData();
                m_getStatusDatas.push_back(temp);
                m_getWriteReadInstance.push_back(temp);
            }
            else{
                temp = m_getWriteReadInstance[0];
            }

            break;
        default:
            break;
    }
    return temp;
}

IGetStatusData* InOutFactory::GetDataInterface(IOType type)
{
    IGetStatusData* temp = NULL;
    switch(type) {
        case in_sharememory:
            temp = new ShareMemory();
            temp->Initial();
            m_getStatusDatas.push_back(temp);
            break;
        case in_tcpsocket:
            break;
        case in_udpsocket:
            break;
        case in_http:
            break;
        case in_test:
            temp = new TestSendData();
            m_getStatusDatas.push_back(temp);
            break;
        default:
            break;
    }
    return temp;
}

ISetCommond* InOutFactory::GetCommondInterface(IOType type)
{
    ISetCommond* temp = NULL;
    switch(type){
            //temp = new ShareMemory();
           // m_setCommonds.push_back(temp);
            break;
        case in_tcpsocket:
            break;
        case in_udpsocket:
            break;
        case in_http:
            break;
        default:
            break;
    }
    return temp;
}
