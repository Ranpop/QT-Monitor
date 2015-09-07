#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include <QPointF>
#include <QPoint>
#include <QMutex>
#include "ibasestruct.h"

class TcpSocketThread : public QThread
{
    Q_OBJECT
public:
    explicit TcpSocketThread(QObject *parent = 0);
    ~TcpSocketThread();

    void Add(QVector<shared_forklift_state_st>& forkinfo);
    void Stop();

public slots:
    void onConnected();
    void onDisConnected();

public:
    QTcpSocket m_qTcpSocket;
    bool m_bConnected;

protected:
    void run();
    //接入数据转至内部坐标
    QPoint TransferToScene(QPointF& point);

private:
    volatile bool bStop;
    QPointF m_position;

    void sliceAndsendData(QString &sStringData);
    void getAndbase64ImageData(QString &base64data);
    void structJsonData(QVariantMap &data);
    void sendDataToServer(QVariantMap &data);
    QVector<shared_forklift_state_st> m_forkinfo;
    QMutex mutex_fork;
};

#endif // SOCKETTHREAD_H

