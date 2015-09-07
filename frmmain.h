#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QDialog>
#include "graphics/mapwidget.h"
#include "graphics/plotwidget.h"
#include "io_layer/ibasestruct.h"

class QMenu;
class QLabel;
class QModelIndex;

namespace Ui
{
    class frmMain;
}

//主窗口，
class frmMain : public QDialog
{
    Q_OBJECT
    static frmMain* m_pInstacne;
public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

public:
    void setFormData(shared_forklift_state_st temp);
     static frmMain* GetInstance();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:
    void emergencyStop();
    void setformdata();

private slots:
    void screen_full();                  //全屏模式

    void delete_plot_one();         //删除当前曲线
    void delete_plot_all();           //删除所有曲线
    void show_paramter();         //显示指定索引的参数曲线

    void path_edit();
    void path_clear();
    void path_operate();
    void path_endEdit();
    void path_setcurrentPoint();
    void path_removePoint();

    void on_btnClose_clicked();
    void on_btnMin_clicked();
    void on_btnAutoManual_clicked();
    void on_btnConnect_clicked();
    void on_pushButton_Connect_clicked();

    void on_tableWidget_warning_windowTitleChanged(const QString &title);

    void on_tableWidget_warning_itemSelectionChanged();

    void PressRightEvent();

private:
    Ui::frmMain *ui;    

    QMenu *menu_graphics;               //地图菜单
    QMenu *menu_plot;                       //鼠标右键菜单对象

    MapWidget* currentMapWidget;        //当前地图窗体

    plotWidget* currentPlotWidget;          //绘制曲线窗体
    QList<plotWidget *> plotWidgets;       //显示曲线窗体集
    shared_forklift_state_st m_formdata;

    QTimer QtTimer;

    void InitStyle();                    //初始化无边框窗体
    void InitForm();                   //初始化窗体数据
    void InitPlot();                     //初始化视频布局载体数据
    void InitConnect();              //初始化信号、槽关联
    void InitMenu();                  //初始化菜单

    void destory();
    void Exit();                           //退出调用
};

#endif // FRMMAIN_H
