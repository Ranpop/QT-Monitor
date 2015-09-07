#include "myapp.h"
#include "myhelper.h"

QString myApp::AppPath = "";
int myApp::DeskWidth = 1204;//1204
int myApp::DeskHeight = 768;

QString myApp::AppTitle = "智能叉车状态监控软件";

//最后配置信息,画面数
QString myApp::LastConfig = "1";

int myApp::showPlotTimeSpan = 12;
int myApp::showPointNum = 30;

int myApp::imageInMemoryNum = 20;
int myApp::normalDataInMemoryNum = 50;

int myApp::graphicsViewHeigt = 400;
int myApp::graphicsViewWidth = 900;
int myApp::warehouseWidth = 31500;
int myApp::warehouseHeight = 13400;

int myApp::getDataTimeSpan = 20;
int myApp::saveImgTimeSpan = 100;
int myApp::mapRefreshTimeSpan = 0;  //0为最快
int myApp::plotRefreshTimeSpan = 0;   //0为最快
int myApp::ployNum = 8;
int myApp::dataAutoRemoveDeadLine = 6000; //60s
bool myApp::topShow = false;
bool myApp::connectSysFlag = false;

double myApp::dataCheckMin = 0.0001;

//读取配置文件
void myApp::ReadConfig()
{
    QString fileName = myApp::AppPath + "config.txt";
    //如果配置文件不存在,则以初始值继续运行
    if (!myHelper::FileIsExist(fileName)) {
        //对应中文转成正确的编码
        myApp::AppTitle = myApp::AppTitle.toLatin1();
        return;
    }

    QSettings *set = new QSettings(fileName, QSettings::IniFormat);

    set->beginGroup("AppConfig");
    myApp::AppTitle = set->value("AppTitle").toString();
    myApp::LastConfig = set->value("LastConfig").toString();
    set->endGroup();
}

//写入配置文件
void myApp::WriteConfig()
{
    QString fileName = myApp::AppPath + "config.txt";
    QSettings *set = new QSettings(fileName, QSettings::IniFormat);

    set->beginGroup("AppConfig");
    set->setValue("AppTitle", myApp::AppTitle);
    set->setValue("LastConfig", myApp::LastConfig);
    set->endGroup();
}
