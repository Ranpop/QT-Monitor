#ifndef PLOYLINEITEM_H
#define PLOYLINEITEM_H

#include <QGraphicsItem>
#include <QVector>
#include <QEasingCurve>

//叉车路径规划，增加、移动、删除、绘制叉车路径点迹
class forkliftPathItem : public QGraphicsItem
{
public:
    forkliftPathItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
    void AddPoint(QPointF& point);
    void SetCurrentPoint(QPointF& point);
    void RemovePoint(QPointF& point);
    void ClearPoint();
    void MovePoint(QPointF& point);

    QVector<QPointF> m_cargoPoints;

private:
    QVector<QPointF> m_linePoints;
    QVector<QPointF> m_drawPoints;
    QPainterPath m_path;

    int currentPointIndex;
};

#endif // PLOYLINEITEM_H
