#include <QApplication>
#include "myhelper.h"
#include "frmmain.h"
#include "myapp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("smartForkliftMonitor");         //设置应用程序名称
    a.setApplicationVersion("V0.1"); //设置应用程序版本
    myHelper::SetUTF8Code();            //设置程序编码为UTF-8
    myHelper::SetChinese();             //设置程序为中文字库

    //赋值当前应用程序路径和桌面宽度高度
    myApp::AppPath = QApplication::applicationDirPath() + "/";
    myApp::DeskWidth = qApp->desktop()->availableGeometry().width();
    myApp::DeskHeight = qApp->desktop()->availableGeometry().height();

    //程序加载时先加载所有配置信息
    myApp::ReadConfig();

    //创建共享内存,判断是否已经运行程序
//    QSharedMemory mem("forkliftMonitor_");
//    if (!mem.create(1)) {
//        myHelper::ShowMessageBoxError("程序已运行,软件将自动关闭!");
//        return 1;
//    }

    frmMain w;
    w.show();
    w.setGeometry(qApp->desktop()->availableGeometry());

    return a.exec();
}
