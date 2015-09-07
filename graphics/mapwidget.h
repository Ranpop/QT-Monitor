#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
#include <QtGui>
#include "forkliftItem.h"
#include "forkliftPathItem.h"
#include "lineItem.h"
#include "../io_layer/getdatathread.h"
#include "../io_layer/isetcommond.h"

//#define ERROR_RANGE(a, b) ((((a)-(b)>-50) || ((a)-(b)<50)) ? 0 : (a))
#define ERROR_RANGE 50

enum PathStatus{
                   noedit = 0x01
                   ,addpoint   = 0x10
                   ,movepoint = 0x11
                   ,removepoint = 0x12
};

//仓库视图
class MapWidget : public QGraphicsView
{
    Q_OBJECT
     static MapWidget* m_pInstacne;
public:
    MapWidget(QWidget * parent = 0);
    ~MapWidget();
    static MapWidget* GetInstance();

signals:
    void setCmd();

public slots:
    void updateData(GetDataType dataType);
    void emergencyStopCmd();

private slots:
    void updateDataSlot();

public:
    void path_clear();
    void path_operate();
    void path_setcurrentPoint();
    void path_removePoint();
    void path_edit(bool editable);
    void CalcCommand(); //计算路径命令，利用坐标计算
    void CalcCmdProc(QPoint carp, QPoint cargop0, QPoint cargop1);
    bool SetCommandData(QVector<shared_subcmd_st> &cmdtemp);
    bool JuageErrRange(double pos0, double pos1);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect); 		//完成地图显示的功能
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void scrollContentsBy(int dx, int dy);
    //接入数据转至内部坐标
    QPoint TransferToScene(QPointF& point);
    QPointF TransferToConTrol(QPoint& point);
private:
    QPixmap map;

    QLabel *viewCoord;
    QLabel *sceneCoord;
    QGraphicsScene *scene;

    forkliftItem *m_forkliftItem;
    forkliftPathItem *m_forkliftPathItem;
    lineItem *m_lineItem;

    QTimer dataTimer;

    QPointF m_position;
    int m_orientation;
    double angle;

    PathStatus m_pathStatus;
    QVector<shared_subcmd_st> m_cmdDataInfo;
};

#endif // MAPWIDGET_H
