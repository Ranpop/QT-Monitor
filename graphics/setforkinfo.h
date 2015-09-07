#ifndef SETFORKINFO_H
#define SETFORKINFO_H

#include "../io_layer/ibasestruct.h"
#include "../io_layer/getdatathread.h"
#include <QVector>
#include <QObject>
#include <QTableWidget>

class SetForkInfo:public QObject
{
    Q_OBJECT
     static SetForkInfo* m_pInstacne;
public:
    SetForkInfo(QObject * parent = 0);
    ~SetForkInfo();
    static SetForkInfo* GetInstance();

public slots:
    void SetForkInfo2From(GetDataType dataType);
};
#endif // SETFORKINFO_H

