#include <QJsonDocument>
#include <QJsonObject>
#include "qttcpsocket.h"
#include "getdatathread.h"
#include "../myapp.h"

#define MAX_DATA_LEN_BYTE 48*1024   //49152
#define MAGIC_DATA 0xbabababa
#define SLICE_FINISHED 1
#define SLICE_ON_FINISHED 0

#define Type "Type"
#define VerifyCode "VerifyCode"
#define AllLength "AllLength"
#define SsnLength "SsnLength"
#define nSn "nSn"
#define nSsn "nSsn"
#define nfed"nfed"
#define Data "Data"

QString host = "127.0.0.1";
int port = 3001;

TcpSocketThread::TcpSocketThread(QObject *parent) :
    QThread(parent)
{
    bStop = false;
    m_bConnected = false;

    connect(&m_qTcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&m_qTcpSocket, SIGNAL(disconnected()), this, SLOT(onDisConnected()));
    connect(&m_qTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(quit()));
    //connect(&m_qTcpSocket, SIGNAL(readyRead()), this, SLOT(tcpSocketRecvData()));

    if (!m_bConnected)
    {
        m_qTcpSocket.connectToHost(host, port);
        m_qTcpSocket.waitForConnected(10);
        //sleep(5);
    }
}

TcpSocketThread::~TcpSocketThread()
{

}

void TcpSocketThread::Stop()
{
    bStop = true;
}

void TcpSocketThread::Add(QVector<shared_forklift_state_st>& forkinfo)
{
    mutex_fork.lock();
    foreach(shared_forklift_state_st tempMarker, forkinfo){
        this->m_forkinfo.push_back(tempMarker);
    }
    forkinfo.clear();
    mutex_fork.unlock();
}

void TcpSocketThread::run()
{
    QVariantMap data;
    QString imagedata;
    while(!bStop){
       // structJsonData(data);
        if (0 != data.count())
        {
            sendDataToServer(data);
            data.clear();
        }

        getAndbase64ImageData(imagedata);
        QThread::msleep(50);
    }
}

void TcpSocketThread::getAndbase64ImageData(QString &base64data)
{
    long dataLength;
    QString fileName;
    //QString fileName = GetDataThread::GetInstance()->GetImageData();
#if 1
        static int filenum = 0;
        QString stfilenum;
        stfilenum.setNum(filenum);
        fileName = "/usr1/code/image1/" + stfilenum + ".jpg" ;
       if (filenum < 5193)
       {
           filenum += 1;
       }
       else
       {
           filenum = 0;
       }
#endif
    if (fileName.isNull())
    {
        return ;
    }

    qDebug()<<"UdpSocketThread file name is : "<<fileName;
    QFile qfile(fileName);
    if (!qfile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open failed";
        return ;
    }
    QByteArray dataBy;
    dataBy = qfile.readAll();
    qfile.close();
    dataLength = dataBy.length();
    //qDebug()<<"UdpSocketThread file length is : "<<dataBy;
    /* base64 code*/
    base64data = dataBy.toBase64();
    qDebug()<<"UdpSocketThread base64 string length is :"<<base64data.length();
#if 0
    QVariantMap dataTemp;
    dataTemp.insert(VerifyCode, MAGIC_DATA);
    dataTemp.insert(Type, 0);
    dataTemp.insert(AllLength, base64data.length());
    dataTemp.insert(Data, base64data);
    //dataTemp.insert(Data, "base64data");

    //send
    //sliceAndsendData(base64data);
    sendDataToServer(dataTemp);
    //qDebug()<<"UdpSocketThread sliceAndsendData length"<<dataLength<<"SN: "<<nSnNum<<" nSSn: "<<nSsnNum-1<<"data length:"<<temp.length();
    dataTemp.clear();
#endif

    QJsonObject json;
    //json.insert(VerifyCode, MAGIC_DATA);
    json.insert("FileName", fileName);
    json.insert(AllLength, base64data.length());
    json.insert(Data, base64data);


    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    m_qTcpSocket.write(byte_array, byte_array.size());
    m_qTcpSocket.waitForBytesWritten(500);
}

static int nSnNum = 0;
void TcpSocketThread::sliceAndsendData(QString &sStringData)
{
    if (sStringData.isEmpty())
    {
        return;
    }
    static int count = 0;
    if (count > 0)
    {
        return ;
    }
    count++;
    //qDebug()<<"UdpSocketThread sliceAndsendData string length is :"<<sStringData;
    QVariantMap dataTemp;
    long dataLength = sStringData.length();
    long startPos = 0;
    int nSsnNum = 0;


    while (MAX_DATA_LEN_BYTE < dataLength)
    {
        //qDebug()<<"UdpSocketThread sliceAndsendData string length is : "<<dataLength<<" max: "<<MAX_DATA_LEN_BYTE<<"nSsnNum"<<nSsnNum;
        if (0 == nSsnNum)
        {
            dataTemp.insert(VerifyCode , MAGIC_DATA);
            dataTemp.insert(Type, 0);
            dataTemp.insert(AllLength, (int)dataLength);
            dataTemp.insert(SsnLength, MAX_DATA_LEN_BYTE);
            dataTemp.insert(nSn, nSnNum);
            dataTemp.insert(nSsn, nSsnNum);
            nSsnNum++;
            dataTemp.insert(nfed, SLICE_ON_FINISHED);
            QString temp = sStringData.mid(startPos, MAX_DATA_LEN_BYTE);
            startPos += MAX_DATA_LEN_BYTE;
            dataTemp.insert(Data, "temp");

            //send data
            sendDataToServer(dataTemp);
             qDebug()<<"UdpSocketThread sliceAndsendData all length"<<dataLength<<"SN: "<<nSnNum<<" nSSn: "<<nSsnNum-1<<"data length:"<<temp.length();
            dataTemp.clear();
        }
        else
        {
            dataTemp.insert(VerifyCode, MAGIC_DATA);
            dataTemp.insert(Type, 0);
            dataTemp.insert(AllLength, 0);
            dataTemp.insert(SsnLength, MAX_DATA_LEN_BYTE);
            dataTemp.insert(nSn, nSnNum);
            dataTemp.insert(nSsn, nSsnNum);
            nSsnNum++;
            dataTemp.insert(nfed, SLICE_ON_FINISHED);
            QString temp = sStringData.mid(startPos, MAX_DATA_LEN_BYTE);
            startPos += MAX_DATA_LEN_BYTE;
            dataTemp.insert(Data, "temp");

            //send
            sendDataToServer(dataTemp);
            qDebug()<<"UdpSocketThread sliceAndsendData length"<<MAX_DATA_LEN_BYTE<<"SN: "<<nSnNum<<" nSSn: "<<nSsnNum-1<<"data length:"<<temp.length();
            dataTemp.clear();
        }
        dataLength -= MAX_DATA_LEN_BYTE;
    }

    dataTemp.insert(VerifyCode, MAGIC_DATA);
    dataTemp.insert(Type, 0);
    dataTemp.insert(AllLength, (int)dataLength);
    dataTemp.insert(SsnLength, (int)dataLength);
    dataTemp.insert(nSn, nSnNum);
    dataTemp.insert(nSsn, nSsnNum);
    dataTemp.insert(nfed, SLICE_FINISHED);
    QString temp = sStringData.mid(startPos);
    //startPos += MAX_DATA_LEN_BYTE + 1;
    dataTemp.insert(Data, "temp");

    //send
    sendDataToServer(dataTemp);
    qDebug()<<"UdpSocketThread sliceAndsendData length"<<dataLength<<"SN: "<<nSnNum<<" nSSn: "<<nSsnNum-1<<"data length:"<<temp.length();
    dataTemp.clear();
    nSnNum++;
}

void TcpSocketThread::structJsonData(QVariantMap &data)
{
    QVariantList markerDataList;
    QVariantList lineDataList;
    QVariantList rateDataList;
    QVariantList orientationDataList;
    //QVariantMap dataMap;

    mutex_fork.lock();
    if (0 == m_forkinfo.count())
    {
        mutex_fork.unlock();
        return;
    }
    foreach (shared_forklift_state_st forkinfo,  m_forkinfo) {
        markerDataList.push_back(forkinfo.X0);
        markerDataList.push_back(forkinfo.Y0);

        lineDataList.push_back(forkinfo.lineDistance);

        rateDataList.push_back(forkinfo.v);

        orientationDataList.push_back(forkinfo.orientation);
    }
    m_forkinfo.clear();
    mutex_fork.unlock();

    data.insert("position", markerDataList);
    //data.insert("lineDistance", lineDataList);
    data.insert("rate", rateDataList);
    //data.insert("orientation", orientationDataList);
    data.insert("length", data.size());
    //qDebug()<<"The Json Data Structed Like this: "<<markerDataList;
}

void TcpSocketThread::sendDataToServer(QVariantMap &data)
{
    QJsonDocument document =  QJsonDocument::fromVariant(data);
    QString msg = QString::fromUtf8(document.toJson(QJsonDocument::Compact));

    //qDebug()<<"SEND DATA STRING: "<<msg;

    QByteArray block;
    //使用数据流写入数据
    //QDataStream out(&block,QIODevice::ReadWrite);
    //out.setVersion(QDataStream::Qt_5_2);
    //out.device()->seek(0);
    //out<<msg;
    m_qTcpSocket.write(block);
    m_qTcpSocket.waitForBytesWritten(300);
    //m_qTcpSocket.waitForReadyRead()
    //block.resize(0);
}

void TcpSocketThread::onConnected()
{
    static int connetCount = 0;
    m_bConnected = true; connetCount++;
    qDebug()<<"Client connectd to host  "<<connetCount;
}

void TcpSocketThread::onDisConnected()
{
    m_bConnected = false;
    while(!m_bConnected)
    {
        m_qTcpSocket.connectToHost(host, port);
        m_qTcpSocket.waitForConnected(10);
        //sleep(5);
    }
}

QPoint TcpSocketThread::TransferToScene(QPointF& point)
{
    QPoint result;
    result.rx() = myApp::meterTopixelWidth() * point.x();
    result.ry() = myApp::graphicsViewHeigt - myApp::meterTopixelHeight()*point.y() - 48.4;

    return result;
}
