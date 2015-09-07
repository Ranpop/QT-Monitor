#ifndef QTUDPSOCKET_H
#define QTUDPSOCKET_H

#include <QThread>
#include <QObject>
#include <QUdpSocket>
#include <QMutex>
#include <QTimer>
#include "ibasestruct.h"

enum DataType
{
    ForkPosition = 0x00,
    ForkRate = 0x01,
    ForkOrientation = 0x02,
    ForkLineDistance = 0x03,
    ForkImage = 0x04,
    ForkWorkStatus = 0x05,
    ForkWorkResult = 0x06,
    ForkWorkCmd = 0x07
};

class UdpSocketThread : public QThread
{
    Q_OBJECT
    static UdpSocketThread* m_pInstacne;
public:
    explicit UdpSocketThread(QObject *parent = 0);
    static UdpSocketThread* GetInstance();
    ~UdpSocketThread();

    void Add(QVector<shared_forklift_state_st>& forkinfo);
    void Add(QString fileName);
    void Stop();

public slots:
    void recvMessage();
    //void recvImageName();

public:
    QUdpSocket m_qUdpSocket;
    //QTimer dataTimer;

protected:
    void run();

private:
    volatile bool bStop;
    void sliceAndsendData(QString &sStringData);
    void getAndbase64ImageData(QString &base64data);

    void structAndsendSmallJsonData();
    void setJsonData(DataType type, QJsonArray &jsonArray, QString dataStr);

    void sendBigDataToServer(QJsonObject json);
    void sendSmallDataToServer(QJsonObject json);

    void compressFiles(QString &filename);
    QStringList m_fileNamsPing;
    QStringList m_fileNamsPang;
    QString m_zipfileName;
    bool boolPing;

    QVector<shared_forklift_state_st> m_forkinfo;
    QMutex mutex_fork;
};

#endif // QTUDPSOCKET_H

