#ifndef GETDATATHREAD_H
#define GETDATATHREAD_H

#include <QThread>
#include <QVector>
#include "ibasestruct.h"
#include "savedatathread.h"
#include "qttcpsocket.h"
#include "qtudpsocket.h"

//可通过第二位来判断数据类型
enum GetDataType { img = 0x00
                   ,marker   = 0x10
                   ,markerx = 0x11
                   ,markery = 0x12
                   ,lineDetec = 0x20
                   ,lineangle = 0x21
                   ,linedistance = 0x22
                   ,bracket    = 0x30
                   ,bracketx = 0x31
                   ,brackety = 0x32
                   ,bracketz = 0x33
                   ,obstacle  = 0x40
                   ,obstaclex = 0x41
                   ,obstacley = 0x42
                   ,obstaclez = 0x43
                   ,forkinfo = 0x44
                   ,nodata = 0x50};

//获取数据线程，定时获取共享内存数据，可扩展至socket、文件等
//线程运行函数内尽量不进行长时间操作调用
class GetDataThread : public QThread
{
    Q_OBJECT
    explicit GetDataThread(QObject *parent = 0);
    static GetDataThread* m_pInstacne;
public:
    ~GetDataThread();
    static GetDataThread* GetInstance();
    void stop();

    QString GetImageData();
    bool GetData(shared_marker_st& tempmarker);
    bool GetData(shared_line_st& templine);
    bool GetData(shared_bracket_st& tempbracket);
    bool GetData(shared_obstacle_st& tempobstacle);
    bool GetData(shared_forklift_state_st& tempfork);

signals:
    void GetData(GetDataType dataType);
protected:
    void run();
private:
    volatile bool bStop;
    QVector<shared_marker_st> m_marketInfo;
    QVector<shared_line_st> m_lineInfo;
    QVector<shared_bracket_st> m_bracketInfo;
    QVector<shared_obstacle_st> m_obstacleInfo;
    QVector<shared_forklift_state_st> m_forkInfo;

    TcpSocketThread* m_pTcpSocketThread;
    UdpSocketThread* m_pUdpSocketThread;
    SaveDataThread* m_pSaveImgThread;
};

#endif // GETDATATHREAD_H
