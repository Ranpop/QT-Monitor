#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include "../myapp.h"
#include "savedatathread.h"
#include "qtudpsocket.h"
#include <opencv2/opencv.hpp>
#include <JlCompress.h>
#include <quazip.h>
using namespace cv;

SaveDataThread* SaveDataThread::m_pInstacne = NULL;

bool SaveDataThread::m_imagePingPang = false;
SaveDataThread::SaveDataThread(QObject *parent) :
    QThread(parent)
{
    bStop = false;
    m_strDir = myApp::AppPath + "Datas";
    QDir directory(m_strDir);
    if(!directory.exists()){
        directory.setPath(myApp::AppPath);
        directory.mkdir("Datas");
    }

    this->AutoRemoveImageDatas(m_strDir);
    //removeDirectory(m_strDir);

    QDateTime dateTime(QDateTime::currentDateTime());
    directory.setPath(m_strDir + "/" +  dateTime.toString());
    if(!directory.exists()){
        directory.setPath(m_strDir);
        directory.mkdir(dateTime.toString());
    }
    m_strDir += "/" +  dateTime.toString();
    CreateDataFile();

    m_imgIndex = 0;

    //connect(this, SIGNAL(imageReady()), UdpSocketThread::GetInstance() , SLOT(recvImageName()), Qt::DirectConnection);
}

bool SaveDataThread::GetImagePingPangStatus()
{
    return m_imagePingPang;
}

SaveDataThread::~SaveDataThread()
{
    fileBracket.close();
    fileLine.close();
    fileMarker.close();
    fileObstacle.close();
}

void SaveDataThread::CreateDataFile()
{
    fileLine.setFileName(m_strDir + "/Line.txt");
    if(!fileLine.exists()){
        QFile tempFile(m_strDir + "/Line.txt");
        tempFile.open(QIODevice::WriteOnly);
        tempFile.close();
    }
    fileLine.open(QIODevice::WriteOnly | QIODevice::Text);

    fileMarker.setFileName(m_strDir + "/Marker.txt");
    if(!fileMarker.exists()){
        QFile tempFile(m_strDir + "/Marker.txt");
        tempFile.open(QIODevice::WriteOnly);
        tempFile.close();
    }
    fileMarker.open(QIODevice::WriteOnly | QIODevice::Text);

    fileBracket.setFileName(m_strDir + "/Bracket.txt");
    if(!fileBracket.exists()){
        QFile tempFile(m_strDir + "/Bracket.txt");
        tempFile.open(QIODevice::WriteOnly);
        tempFile.close();
    }
    fileBracket.open(QIODevice::WriteOnly | QIODevice::Text);

    fileObstacle.setFileName(m_strDir + "/Obstacle.txt");
    if(!fileObstacle.exists()){
        QFile tempFile(m_strDir + "/Obstacle.txt");
        tempFile.open(QIODevice::WriteOnly);
        tempFile.close();
    }
    fileObstacle.open(QIODevice::WriteOnly | QIODevice::Text);
}

void SaveDataThread::AutoRemoveImageDatas(QString strDir)
{
    QDir dir(strDir);
    if(!dir.exists()){
        return;
    }
    QFileInfoList fileInfoList = dir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;
        if(fileInfo.isDir()){
            qDebug("文件创建时间%d", fileInfo.created().daysTo(QDateTime::currentDateTime()));
            //if(fileInfo.created().daysTo(QDateTime::currentDateTime()) > myApp::dataAutoRemoveDeadLine){
            if(fileInfo.created().secsTo(QDateTime::currentDateTime()) > myApp::dataAutoRemoveDeadLine){
                QString tmpdir = "";
                tmpdir = strDir + ("/") + fileInfo.fileName();
                removeDirectory(tmpdir);
            }
        }
    }
}

bool SaveDataThread::removeDirectory(QString dirName)
{
 QDir dir(dirName);
 QString tmpdir = "";
 if(!dir.exists()){
   return false;
 }

 QFileInfoList fileInfoList = dir.entryInfoList();
 foreach(QFileInfo fileInfo, fileInfoList){
   if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
     continue;

   if(fileInfo.isDir()){
     tmpdir = dirName + ("/") + fileInfo.fileName();
     removeDirectory(tmpdir);
     dir.rmdir(fileInfo.fileName()); /**< 移除子目录 */
   }
   else if(fileInfo.isFile()){
     QFile tmpFile(fileInfo.fileName());
     dir.remove(tmpFile.fileName());
   }
 }

 dir.cdUp();            /**< 返回上级目录，因为只有返回上级目录，才可以删除这个目录 */
 if(dir.exists(dirName)){
   if(!dir.rmdir(dirName))
     return false;
 }
 return true;
}

void SaveDataThread::Stop()
{
    bStop = true;
}

void SaveDataThread::Add(shared_img_st* imgdata)
{
    mutex_img.lock();
    this->m_imageBuffer.push_back(imgdata);
    mutex_img.unlock();
}

void SaveDataThread::Add(QVector<shared_bracket_st>& bracket)
{
    mutex_bracket.lock();
    foreach(shared_bracket_st tempBracket, bracket){
        this->m_bracketInfo.push_back(tempBracket);
    }
    bracket.clear();
    mutex_bracket.unlock();
}

void SaveDataThread::Add(QVector<shared_line_st>& line)
{
    mutex_line.lock();
    foreach(shared_line_st tempLine, line){
        this->m_lineInfo.push_back(tempLine);
    }
    line.clear();
    mutex_line.unlock();
}

void SaveDataThread::Add(QVector<shared_marker_st>& marker)
{
    mutex_market.lock();
    foreach(shared_marker_st tempMarker, marker){
        this->m_marketInfo.push_back(tempMarker);
    }
    marker.clear();
    mutex_market.unlock();
}

void SaveDataThread::Add(QVector<shared_obstacle_st>& obstacle)
{
    mutex_obstacle.lock();
    foreach(shared_obstacle_st tempObstacle, obstacle){
        this->m_obstacleInfo.push_back(tempObstacle);
    }
    obstacle.clear();
    mutex_obstacle.unlock();
}

QString SaveDataThread::getImgFileName()
{
    if (m_imagePingPang){
        m_imagePingPang = false;
        return m_imageFileNamePang;
    }
    else{
        m_imagePingPang = true;
        return m_imageFileNamePing;
    }
}

void SaveDataThread::run()
{
    while(!bStop){
        SaveImg();
        SaveMarker();
        SaveBracket();
        SaveLine();
        SaveObstacle();
        //预计100ms保存一次，以流畅显示为主
        //QThread::msleep(myApp::saveImgTimeSpan );
        //QThread::msleep(1);
    }
    //退出后保存一次，清理内存
    SaveImg();
    SaveMarker();
    SaveBracket();
    SaveLine();
    SaveObstacle();
}

void SaveDataThread::SaveImg()
{
    mutex_img.lock();
    static int flag = 0;
    for(int i = 0; i < this->m_imageBuffer.count(); i++){
        this->m_imageProcess.push_back(m_imageBuffer[i]);
    }
    this->m_imageBuffer.clear();
    mutex_img.unlock();

    for(int i = 0; i < m_imageProcess.count(); i++){
        //图像转换
        /*
        for (int k=0; k < m_imageProcess[i]->nWidth; k++){
            for (int j=0; j < m_imageProcess[i]->nHeight; j++){
                unsigned char btemp = m_imageProcess[i]->text[j*m_imageProcess[i]->nWidth+k];
                unsigned char rtemp = m_imageProcess[i]->text[j*m_imageProcess[i]->nWidth+k+2];
                m_imageProcess[i]->text[j*m_imageProcess[i]->nWidth+k] = rtemp;
                m_imageProcess[i]->text[j*m_imageProcess[i]->nWidth+k+2] = btemp;
            }
        }*/
        //Mat imgtest =  cv::imread("test.jpg");
        Mat loadimg(m_imageProcess[i]->nHeight, m_imageProcess[i]->nWidth, CV_8UC3, m_imageProcess[i]->text);
//        if(m_imageProcess[i]->nPixelFormat == 1){
//            loadimg = Mat::zeros(m_imageProcess[i]->nHeight, m_imageProcess[i]->nWidth, CV_8UC1);
//        }else if(m_imageProcess[i]->nPixelFormat == 3){
//            loadimg = Mat::zeros(m_imageProcess[i]->nHeight, m_imageProcess[i]->nWidth, CV_8UC3);
//        }else{
//            delete m_imageProcess[i];
//            continue;
//        }
//        memcpy(loadimg., m_imageProcess[i]->text,
//               m_imageProcess[i]->nWidth * m_imageProcess[i]->nHeight * 3);
//        for(int m = 0; m < m_imageProcess[i]->nHeight; m++){
//            for(int j = 0; j < m_imageProcess[i]->nWidth; j++){
//                loadimg.data[m * m_imageProcess[i]->nWidth + j] = m_imageProcess[i]->text[m * m_imageProcess[i]->nWidth + j];
//            }
//        }

        //m_imageFileName = m_strDir + "/" + QString::number(m_imgIndex, 10) + ".jpg";
        if (flag == 0)
        {
            qDebug("flag =0000000000000000000");
            QDateTime dateTime(QDateTime::currentDateTimeUtc());
            m_imageFileNamePing = m_strDir + "/" + dateTime.toString() + "-"+ QString::number(m_imgIndex, 10)+ ".jpg";
             //m_imageFileNamePing = m_strDir + "/" + QString::number(m_imgIndex, 10) + ".jpg";
            cv::imwrite(m_imageFileNamePing.toStdString(), loadimg);
            //QDateTime dateTime(QDateTime::currentDateTime());
            m_imageFileNamePang = m_imageFileNamePing;//m_strDir + "/" + dateTime.toString() + ".jpg";
            //cv::imwrite(m_imageFileNamePang.toStdString(), loadimg);
            UdpSocketThread::GetInstance()->Add(m_imageFileNamePang);
            flag = 1;
        }
        else
        {
            if (m_imagePingPang)
            {
                QDateTime dateTime(QDateTime::currentDateTimeUtc());
                m_imageFileNamePing = m_strDir + "/" + dateTime.toString() + "-"+ QString::number(m_imgIndex, 10)+  ".jpg";
                cv::imwrite(m_imageFileNamePing.toStdString(), loadimg);
                UdpSocketThread::GetInstance()->Add(m_imageFileNamePing);
            }
            else{
                QDateTime dateTime(QDateTime::currentDateTimeUtc());
                m_imageFileNamePang = m_strDir + "/" + dateTime.toString() + "-"+ QString::number(m_imgIndex, 10)+  ".jpg";
                cv::imwrite(m_imageFileNamePang.toStdString(), loadimg);
                UdpSocketThread::GetInstance()->Add(m_imageFileNamePang);
            }
        }
        m_imgIndex++;
        delete m_imageProcess[i];
    }
    this->m_imageProcess.clear();
}

void SaveDataThread::SaveBracket()
{
    QTextStream ts(&fileBracket);
    mutex_bracket.lock();
    foreach(shared_bracket_st bracket, m_bracketInfo){
        ts<<"X: "<<bracket.posX<<" Y: "<<bracket.posY<<" Z: "<<bracket.posZ<<"\n";
    }
    m_bracketInfo.clear();
    mutex_bracket.unlock();
}

void SaveDataThread::SaveLine()
{
    QTextStream ts(&fileLine);
    mutex_line.lock();
    foreach(shared_line_st line, m_lineInfo){
        ts<<"Angle: "<<line.angle<<" Distance: "<<line.distance<<"\n";
    }
    m_lineInfo.clear();
    mutex_line.unlock();
}

void SaveDataThread::SaveMarker()
{
    QTextStream ts(&fileMarker);
    mutex_market.lock();
    foreach(shared_marker_st marker, m_marketInfo){
        ts<<"X: "<<marker.posX<<" Y: "<<marker.posY<<"\n";
    }
    m_marketInfo.clear();
    mutex_market.unlock();
}

void SaveDataThread::SaveObstacle()
{
    QTextStream ts(&fileObstacle);
    mutex_obstacle.lock();
    foreach(shared_obstacle_st obstacle, m_obstacleInfo){
        ts<<"X: "<<obstacle.posX<<" Y: "<<obstacle.posY<<" Z: "<<obstacle.posZ<<"\n";
    }
    m_obstacleInfo.clear();
    mutex_obstacle.unlock();
}
