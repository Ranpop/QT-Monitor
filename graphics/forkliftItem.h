#ifndef PIXITEM_H
#define PIXITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QVector>
#include <QMutex>

//叉车，显示叉车角度、历史轨迹
class forkliftItem : public QGraphicsItem
{
public:
    forkliftItem();
    ~forkliftItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void AddPosition(QPoint point);
    void AddPosture(double rotate);
private:
    QPixmap pix;     		//作为图元显示的图片
    double angle;             //旋转角度
    QMatrix rotatematrix;
    QVector<QPoint> m_points;   //叉车坐标
    QMutex mutex;
};

#endif // PIXITEM_H
