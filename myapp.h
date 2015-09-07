#ifndef MYAPP_H
#define MYAPP_H

class QString;

//全局参数类
class myApp
{
public:
    static QString AppPath;                 //应用程序路径
    static int DeskWidth;                   //桌面可用宽度
    static int DeskHeight;                  //桌面可用高度
    static bool topShow;
    static bool connectSysFlag;

    static QString AppTitle;                //界面标题
    static QString LastConfig;              //软件最后配置信息

    static int showPlotTimeSpan;               //显示的曲线点个数
    static int showPointNum;                     //车轨迹点数

    static int imageInMemoryNum;           //图像数据驻留内存数
    static int normalDataInMemoryNum; //通用数据驻留内存数

    static int graphicsViewWidth;               //主视图宽
    static int graphicsViewHeigt;                //主视图高
    static int warehouseWidth;           //仓库宽（mm）
    static int warehouseHeight;          //仓库高（mm）

    static int getDataTimeSpan;                 //接收数据间隔
    static int saveImgTimeSpan;               //图像保存间隔
    static int mapRefreshTimeSpan;         //地图刷新间隔
    static int plotRefreshTimeSpan;          //曲线刷新间隔
    static int ployNum;                               //曲线个数
    static int dataAutoRemoveDeadLine; //数据自动删除时限（天）

    static double dataCheckMin;             //检查数据是否需要更新

    static void ReadConfig();               //读取配置文件
    static void WriteConfig();              //写入配置文件

    //每米具有多少个像素
    static double meterTopixelWidth()
    {
        return graphicsViewWidth * 1000 / warehouseWidth;
    }

    static double meterTopixelHeight()
    {
        return graphicsViewHeigt * 1000 / warehouseHeight;
    }
    //每像素多少毫米
    static double pixelTometerWidth()
    {
        //return warehouseWidth / 1000 / graphicsViewWidth;
        return warehouseWidth  / graphicsViewWidth;
    }
};

#endif // MYAPP_H
