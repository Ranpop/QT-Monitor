#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtCore/QString>
#include <JlCompress.h>
#include "qtudpsocket.h"
#include "savedatathread.h"
#include "getdatathread.h"
#include "../myapp.h"

typedef quint32 UINT32 ;

#define MAGIC_DATA 0xbaba
#define VERITY_CODE "VerifyCode"
#define  BIG_SMALL_TYPE "BigSmallType"
#define BIG_TYPE "BigType"
#define SMALL_TYPE "SmallType"
#define PAYLOAD "PayLoad"

#define MAX_DATA_LEN_BYTE 1400//2*1024   //49152
#define SLICE_FINISHED 1
#define SLICE_UNFINISHED 0
#define TYPE "Type"
#define ALL_LENGTH "AllLength"
#define SSN_LENGTH "SsnLength"
#define NSN "nSn"
#define NSSN "nSsn"
#define NFED"nFed"
#define DATA "Data"

UdpSocketThread* UdpSocketThread::m_pInstacne = NULL;

QHostAddress serverAddress = QHostAddress("192.168.1.112");
UINT32 serverPort = 3002;

UdpSocketThread::UdpSocketThread(QObject *parent) :
    QThread(parent)
{
    bStop = false;
    boolPing = true;
    m_pInstacne = this;
    m_zipfileName = "";
    m_qUdpSocket.bind(serverPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(&m_qUdpSocket, SIGNAL(readyRead()), this, SLOT(recvMessage()));
    //connect(SaveDataThread::GetInstance(), SIGNAL(imageReady()), this , SLOT(recvImageName()), Qt::DirectConnection);
}

UdpSocketThread* UdpSocketThread::GetInstance()
{
    return m_pInstacne;
}

UdpSocketThread::~UdpSocketThread()
{

}

void UdpSocketThread::Stop()
{
    bStop = true;
}

void UdpSocketThread::Add(QString fileName)
{
    if (boolPing)
    {
        m_fileNamsPing.append(fileName);
    }
    else
    {
        m_fileNamsPang.append(fileName);
    }
}

void UdpSocketThread::Add(QVector<shared_forklift_state_st>& forkinfo)
{
    mutex_fork.lock();
    foreach(shared_forklift_state_st tempMarker, forkinfo){
        this->m_forkinfo.push_back(tempMarker);
    }
    forkinfo.clear();
    mutex_fork.unlock();
}

void UdpSocketThread::compressFiles(QString &filename)
{
    if (boolPing)
    {
        if (40 == m_fileNamsPing.count())
        {
            boolPing = false;
            QString targetbegin = m_fileNamsPing[0].mid(m_fileNamsPing[0].lastIndexOf("/")+1);
            QString targetend = m_fileNamsPing[m_fileNamsPing.count()-1].mid(m_fileNamsPing[m_fileNamsPing.count()-1].lastIndexOf("/")+1);
            targetbegin = targetbegin.mid(0, targetbegin.length() - targetbegin.mid(targetbegin.indexOf("-")).length());
             targetend = targetend.mid(0, targetend.length() - targetend.mid(targetend.indexOf("-")).length());

            QString target = myApp::AppPath + "Datas" + "/Compress/" +targetbegin + "-"+ targetend + ".zip";
            //qDebug()<<"path: "<<target;
            if (JlCompress::compressFiles(target, m_fileNamsPing))
            {
                filename = target;
                //qDebug("compress OK ");
            }
            else
            {
                //qDebug("compress Failed ");
            }
            m_zipfileName = target;
            m_fileNamsPing.clear();
        }
    }
    else
    {
        if (40 == m_fileNamsPang.count())
        {
            boolPing = true;
            QString targetbegin = m_fileNamsPang[0].mid(m_fileNamsPang[0].lastIndexOf("/")+1);
            QString targetend = m_fileNamsPang[m_fileNamsPang.count()-1].mid(m_fileNamsPang[m_fileNamsPang.count()-1].lastIndexOf("/")+1);
            targetbegin = targetbegin.mid(0, targetbegin.length() - targetbegin.mid(targetbegin.indexOf("-")).length());
            targetend = targetend.mid(0, targetend.length() - targetend.mid(targetend.indexOf("-")).length());

            //QDateTime dateTime(QDateTime::currentDateTime());
            QString target = myApp::AppPath + "Datas" + "/Compress/" +targetbegin + "-"+ targetend + ".zip";
            if (JlCompress::compressFiles(target, m_fileNamsPang))
            {
                filename = target;
                //qDebug("compress OK ");
            }
            else
            {
                //qDebug("compress Failed ");
            }
            m_zipfileName = target;
            m_fileNamsPang.clear();
        }
    }
}

void UdpSocketThread::run()
{
    QString StringData;
    QString compressFileName;
    while(!bStop){
        compressFiles(compressFileName);

        structAndsendSmallJsonData();
        QThread::usleep(250);

        getAndbase64ImageData(StringData);
        sliceAndsendData(StringData);

        QThread::usleep(250);
    }
}

void UdpSocketThread::recvMessage()
{

}

void UdpSocketThread::sendImageInfoToServer()
{
    if ()
    {

    }
}

void UdpSocketThread::getAndbase64ImageData(QString &base64data)
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

    //qDebug()<<"UdpSocketThread file name is : "<<fileName;
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
    //qDebug()<<"UdpSocketThread base64 string length is :"<<base64data.length();
}

static int nSnNum = 0;
void UdpSocketThread::sliceAndsendData(QString &sStringData)
{
    if (sStringData.isEmpty())
    {
        return;
    }

    //qDebug()<<"UdpSocketThread sliceAndsendData string length is :"<<sStringData;
    long dataLength = sStringData.length();
    long startPos = 0;
    int nSsnNum = 0;

    while (MAX_DATA_LEN_BYTE < dataLength)
    {
        if (0 == nSsnNum)
        {
            QJsonObject json;
            json.insert(VERITY_CODE , 0xbaba);
            json.insert(TYPE, ForkImage);
            json.insert(ALL_LENGTH, (int)dataLength);
            json.insert(SSN_LENGTH, MAX_DATA_LEN_BYTE);
            json.insert(NSN, nSnNum);
            json.insert(NSSN, nSsnNum);
            nSsnNum++;
            json.insert(NFED, SLICE_UNFINISHED);
            QString temp = sStringData.mid(startPos, MAX_DATA_LEN_BYTE);
            startPos += MAX_DATA_LEN_BYTE;
            json.insert(DATA, temp);

            sendBigDataToServer(json);
            //QJsonDocument document;
           // document.setObject(json);
            //QByteArray byte_array = document.toJson(QJsonDocument::Compact);
            //m_qUdpSocket.writeDatagram(byte_array.data(), byte_array.size(), serverAddress, serverPort);
            //m_qUdpSocket.waitForBytesWritten(300);
            QThread::usleep(350);
            //sendDataToServer(dataTemp);
             //qDebug()<<"UdpSocketThread sliceAndsendData 0 all length"<<dataLength<<"SN: "<<nSnNum<<" nSSn: "<<nSsnNum-1<<"data length:"<<temp.length();
        }
        else
        {
            QJsonObject json;
            json.insert(VERITY_CODE , 0xbaba);
            json.insert(TYPE, ForkImage);
            json.insert(ALL_LENGTH, 0);
            json.insert(SSN_LENGTH, MAX_DATA_LEN_BYTE);
            json.insert(NSN, nSnNum);
            json.insert(NSSN, nSsnNum);
            nSsnNum++;
            json.insert(NFED, SLICE_UNFINISHED);
            QString temp = sStringData.mid(startPos, MAX_DATA_LEN_BYTE);
            startPos += MAX_DATA_LEN_BYTE;
            json.insert(DATA, temp);

            sendBigDataToServer(json);

            //QJsonDocument document;
            //document.setObject(json);
           // QByteArray byte_array = document.toJson(QJsonDocument::Compact);
           // m_qUdpSocket.writeDatagram(byte_array.data(), byte_array.size(), serverAddress, serverPort);
            //m_qUdpSocket.waitForBytesWritten(300);
            QThread::usleep(350);
            //qDebug()<<"UdpSocketThread sliceAndsendData length"<<MAX_DATA_LEN_BYTE<<"SN: "<<nSnNum<<" nSSn: "<<nSsnNum-1<<"data length:"<<temp.length();
        }
        dataLength -= MAX_DATA_LEN_BYTE;
    }

    QJsonObject json;
    json.insert(VERITY_CODE , 0xbaba);
    json.insert(TYPE, ForkImage);
    json.insert(ALL_LENGTH, 0);
    json.insert(SSN_LENGTH, (int)dataLength);
    json.insert(NSN, nSnNum);
    json.insert(NSSN, nSsnNum);
    json.insert(NFED, SLICE_FINISHED);
    QString temp = sStringData.mid(startPos);
    json.insert(DATA, temp);

    sendBigDataToServer(json);
    //QJsonDocument document;
    //document.setObject(json);
   // QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    //m_qUdpSocket.writeDatagram(byte_array.data(), byte_array.size(), serverAddress, serverPort);
    //m_qUdpSocket.waitForBytesWritten(300);
    //qDebug()<<"UdpSocketThread sliceAndsendData length"<<dataLength<<"SN: "<<nSnNum<<" nSSn: "<<nSsnNum-1<<"data length:"<<temp.length();
    nSnNum++;
}

void UdpSocketThread::structAndsendSmallJsonData()
{
    QJsonObject jsonfather;
    QJsonArray jsonArray;
    jsonfather.insert(VERITY_CODE , MAGIC_DATA);
    jsonfather.insert(BIG_SMALL_TYPE, 0);

    //QVariantMap dataMap;

    mutex_fork.lock();
    if (0 == m_forkinfo.count())
    {
        mutex_fork.unlock();
        return;
    }
    foreach (shared_forklift_state_st forkinfo,  m_forkinfo) {
        QString temp; temp.setNum(forkinfo.X0); temp += ":";
        QString temp0; temp0.setNum(forkinfo.Y0); temp += temp0;

        setJsonData(ForkPosition, jsonArray, temp);

        temp.setNum(forkinfo.lineDistance);
        setJsonData(ForkLineDistance, jsonArray, temp);

        temp.setNum(forkinfo.v);
        setJsonData(ForkRate, jsonArray, temp);

        temp.setNum(forkinfo.orientation);
        setJsonData(ForkOrientation, jsonArray, temp);
    }
    m_forkinfo.clear();
    mutex_fork.unlock();
    jsonfather.insert(PAYLOAD, jsonArray);
    //qDebug()<<"Inser data: "<<jsonArray;

    sendSmallDataToServer(jsonfather);
}

void UdpSocketThread::setJsonData(DataType type, QJsonArray &jsonArray, QString dataStr)
{
    QJsonObject jsonChild;
    jsonChild.insert(TYPE, type);
    jsonChild.insert(DATA, dataStr);
    jsonArray.push_back(jsonChild);
    //qDebug()<<"Inser data: "<<jsonArray;
}

void UdpSocketThread::sendBigDataToServer(QJsonObject json)
{
    QJsonObject jsonfather;
    QJsonArray jsonArray;
    jsonfather.insert(VERITY_CODE, MAGIC_DATA);
    jsonfather.insert(BIG_SMALL_TYPE, 1);
    jsonArray.push_back(json);
    jsonfather.insert(PAYLOAD, jsonArray);

    QJsonDocument document;
    document.setObject(jsonfather);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    m_qUdpSocket.writeDatagram(byte_array.data(), byte_array.size(), QHostAddress::Broadcast, serverPort);
    //qDebug()<<"BroadCast data: Image";//<<byte_array;
    //m_qUdpSocket.waitForBytesWritten(300);
}

void UdpSocketThread::sendSmallDataToServer(QJsonObject json)
{
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    m_qUdpSocket.writeDatagram(byte_array.data(), byte_array.size() ,QHostAddress::Broadcast, serverPort);
    m_qUdpSocket.waitForBytesWritten(300);
    //qDebug()<<"BroadCast data:Small ";//<<byte_array;
}


