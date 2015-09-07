#include "testsenddata.h"
#include <qglobal.h>
#include "../myapp.h"
#include <opencv2/opencv.hpp>
using namespace cv;

TestSendData::TestSendData()
{
}

bool TestSendData::Initial()
{
    return true;
}

bool TestSendData::Realease()
{
    return true;
}

bool TestSendData::Deletebuffer()
{
    return true;
}

shared_img_st* TestSendData::GetImageInfo()
{
    shared_img_st* result = new shared_img_st();
    //result->nWidth = 400;
    //result->nHeight = 400;
    result->nPixelFormat = 2;

    Mat img = cv::imread("test.jpg");
    memcpy(result->text, img.data, img.rows * img.cols*3);
    result->nWidth = img.rows;
    result->nHeight = img.cols;


    //Mat tempImg(400, 400, CV_8UC3, Scalar(qrand() % 255, qrand() % 255, qrand() % 255));
    //memcpy(result->text, tempImg.data, tempImg.rows * tempImg.cols * 3);
    //memcpy(result->text, L.data, tempImg.rows * tempImg.cols * 3);
    return result;
}
static QVector<testpoint> Position;
bool TestSendData::GetMarketInfo(shared_marker_st& temp)
{
/*
    QPoint piex0,  carpiex, cargopiex0, cargopiex1;
    static int flag = 2;
    piex0.rx() = 210.7; piex0.ry() = 221.1;//266.2;
    carpiex.rx() = 700; carpiex.ry() = 221.1;//266.2;
    cargopiex1.rx() = 210.7; cargopiex1.ry() = 221.1;

    if (flag == 0){
        temp.posX = (carpiex.rx()+4) * myApp::pixelTometerWidth()/1000;
        temp.posY = myApp::warehouseHeight/1000 - myApp::pixelTometerWidth()*(carpiex.ry()-8) / 1000;
        flag=2;
        return true;
    }else if (flag == 1){
        temp.posX = (piex0.rx()+4) * myApp::pixelTometerWidth()/1000;
        temp.posY = myApp::warehouseHeight/1000 - myApp::pixelTometerWidth()*(piex0.ry()-8) / 1000;
        flag=2;
        return true;
    }else if (flag==2){
        temp.posX = (cargopiex1.rx()+4) * myApp::pixelTometerWidth()/1000;
        //temp.posY = myApp::warehouseHeight/1000 - myApp::pixelTometerWidth()*(cargopiex1.ry()-8) / 1000;
        temp.posY =  myApp::warehouseHeight/1000 -  cargopiex1.ry()/30;
        qDebug("TestSendData::GetMarketInfo %f", (double)myApp::warehouseHeight/1000);
        qDebug("TestSendData::GetMarketInfo %f", (double)cargopiex1.ry());
        qDebug("TestSendData::GetMarketInfo %f", myApp::meterTopixelWidth());
        qDebug("TestSendData::GetMarketInfo %f", temp.posY);

        flag=2;
    }
*/

    static double x =6;//5.99
    static double y = 6;//2    7.672  /////6
    static int flag = 0;

    if (flag == 0){
        x = 12;
        y = 6;
        flag = 1;
    }
    else if (flag == 1){
        x = 20;
        y = 6;
        flag = 2;
    }
    else{
        x = 3;
        y = 6;
        flag = 0;
}
/*
    if (Position.count() > 0){
        if (flag < Position.count()){
            x = Position[flag].posX;
            y = Position[flag].posY;
            flag += 1;
        }
        else{
            x = Position[flag-2].posX;
            y = Position[flag-2].posY;
            Position.clear();
            flag = 0;
        }
    }
*/
    temp.posX = x;//5.9
    temp.posY = y;//6*/

    return true;
}

bool TestSendData::GetLineInfo(shared_line_st& temp)
{
    static double x = 0;
    static double y = 0;

    x += 0.1;
    temp.angle = x;//qrand() % 90;
    temp.distance = y++;//qrand() % 500;
    return true;
}

bool TestSendData::GetBracketInfo(shared_bracket_st& temp)
{
    temp.posX[0] = qrand() % 60;
    temp.posY[0] = qrand() % 60;
    temp.posZ[0] = qrand() % 60;
    return true;
}

bool TestSendData::GetObstacleInfo(shared_obstacle_st& temp)
{
    temp.posX = qrand() % 20;
    temp.posY = qrand() % 20;
    temp.posZ = qrand() % 20;
    return true;
}

bool TestSendData::GetForkRTInfo(shared_forklift_state_st& temp)
{
    static int flag = 0;

    if (flag == 0){
        temp.X0 = 60;
        temp.Y0 = 61;
        temp.lineDistance = 1;
        temp.wheelAngle = 20.10;
        temp.v = 211;
        flag = 1;
    }
    else if(flag ==1){
        temp.X0 = 70;
        temp.Y0 = 71;
        temp.lineDistance = 2;
        temp.wheelAngle = 100;
        temp.v = 7888;
        flag = 2;
    }
    else{
        temp.X0 = 200;
        temp.Y0 = 201;
        temp.lineDistance = 3;
        temp.wheelAngle = 31;
        temp.v = 54;
        flag = 0;
    }

    return true;
}

#define ERROR_RTEST(a, b) ((((a)-(b)>-10) || ((a)-(b)<10)) ? 0 : (a))
bool TestSendData::SetCmdInfo(QVector<shared_subcmd_st> temp)
{
    for (int i=0; i < temp.count(); i++){
        qDebug("removepointertyuio7878123; setcommand x=%f,y=%f", temp[i].posX, temp[i].posY);
    }
    qDebug("removepointertyuio7878123; setcommand temp.count=%d", temp.count());

    testpoint postemp;

    if (temp.count() > 0){
        Position.clear();
        for (int i=0; i < temp.count(); i++){
            if (88 == (int)temp[i].posX){
                qDebug("removepointertyuio7878123; setcommand continue!!!!!");
                continue;
            }
            qDebug("removepointertyuio7878123; setcommand continue 11 !!!!!");
            postemp.posX = temp[i].posX; postemp.posY = temp[i].posY;
            Position.push_back(ChangePiexToMeter(postemp));
        }
/*
        for (int i=0; i < Position.count(); i++){
            qDebug("removepointertyuio7878123; setcommand x=%f,y=%f", Position[i].posX, Position[i].posY);
            PrintfMem((void*)&Position[i], sizeof(testpoint));
        }
*/
        qDebug("removepointertyuio7878123; setcommand continue true!!!!!");
        return true;
    }

     return false;
}

testpoint TestSendData::ChangePiexToMeter(testpoint point)
{
    testpoint result;

    //result.posX = (point.posX+4) * myApp::pixelTometerWidth()/1000;
    //result.posY = myApp::warehouseHeight/1000-myApp::pixelTometerWidth()*(myApp::graphicsViewHeigt - point.posY+40) / 1000;
    result.posX  = point.posX / myApp::meterTopixelWidth();
    result.posY = (myApp::graphicsViewHeigt - point.posY) / myApp::meterTopixelHeight();

    return result;
}

void TestSendData::PrintfMem(void *pAddress, int datasize)
{
       unsigned int *pAddr = (unsigned int*)pAddress;
       qDebug("The mem data is like this:\n");

       while (datasize)
       {
           int nCurSize = datasize > 4 ? 4 : datasize;
           qDebug("The Addr is:  0x%X", pAddr );

           // 输出16进制数据
           for (int i = 0; i < nCurSize; i++){
              qDebug("0x%x", pAddr[i]);
              //qDebug(" ");//补空白
           }
           qDebug("\n");//换行输出

           // 打印下一列
           datasize -= nCurSize;
           pAddr += nCurSize;
       }
}
