#ifndef INOUTFACTORY_H
#define INOUTFACTORY_H

#include <QVector>
#include "igetstatusdata.h"
#include "isetcommond.h"

enum IOType{in_sharememory = 0x00
                   ,in_tcpsocket   = 0x01
                   ,in_udpsocket    = 0x02
                   ,in_http  = 0x04
                   ,in_test = 0x05};

//输入输出工厂类，创建输入输出实体
class InOutFactory
{
private:
    InOutFactory();
    static InOutFactory* m_pInstance;

public:
     ~InOutFactory();
    static InOutFactory* GetInstance();

    IGetStatusData* GetDataInterface(IOType type);
    ISetCommond* GetCommondInterface(IOType type);
    IGetStatusData* GetInterface(IOType type);

private:
    QVector<IGetStatusData*> m_getStatusDatas;
    QVector<ISetCommond*> m_setCommonds;
    QVector<IGetStatusData*> m_getWriteReadInstance;

};

#endif // INOUTFACTORY_H
