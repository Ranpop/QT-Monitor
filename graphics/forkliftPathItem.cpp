#include "forkliftPathItem.h"
#include "../myapp.h"
#include "lineItem.h"
#include <QPainter>
#include <qmath.h>

forkliftPathItem::forkliftPathItem()
{
    currentPointIndex = -1;
}

void forkliftPathItem::AddPoint(QPointF& point)
{
    m_linePoints.push_back(point);
    if (m_cargoPoints.count() < 5){
            m_cargoPoints.push_back(point);
    }
}

void forkliftPathItem::ClearPoint()
{
    m_linePoints.clear();
    m_cargoPoints.clear();
}

void forkliftPathItem::RemovePoint(QPointF &point)
{
    int index = -1;
    for(int i = 0; i < m_linePoints.count(); i++){
        if(qFabs(m_linePoints[i].x() - point.x())  < 5 && qFabs(m_linePoints[i].y() - point.y()) < 5){
            index = i;
            break;
        }
    }

    if(index >= 0){
        m_linePoints.remove(index);
    }
    for (int i=0; i < m_linePoints.count(); i++){
        if (i< 2){
            m_cargoPoints[i] = m_linePoints[i];
        }
        else{
            break;
        }
    }
}

QRectF forkliftPathItem::boundingRect() const
{    
    QPoint leftTop;
    QPoint rightButtom;

    for(QVector<QPointF>::const_iterator iterator = m_linePoints.begin(); iterator != m_linePoints.end(); ++iterator){
        if(iterator->x() < leftTop.x())
            leftTop.rx() =  iterator->x();
        if(iterator->y() < leftTop.y())
            leftTop.ry() =  iterator->y();
        if(iterator->x() > rightButtom.x())
            rightButtom.rx() =  iterator->x();
        if(iterator->y() > rightButtom.y())
            rightButtom.ry() =  iterator->y();
    }
    return QRectF(leftTop.x(), leftTop.y(),
          rightButtom.x() - leftTop.x(), rightButtom.y() - leftTop.y());
}

void forkliftPathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{    
    if(m_linePoints.count() == 0)
        return;

    painter->setPen(QPen(Qt::red, 2, Qt::SolidLine));
    for(int i = 0; i < m_linePoints.count(); i++){
        painter->drawEllipse(m_linePoints[i], 5, 5);
    }

    if(m_linePoints.count() == 2){
        painter->drawLine(m_linePoints[0], m_linePoints[1]);
    }
    if(m_linePoints.count() < 3)
        return;

    m_drawPoints.clear();
    m_drawPoints.push_back(m_linePoints[0]);
    for(int i = 0; i < m_linePoints.count(); i++){
        m_drawPoints.push_back(m_linePoints[i]);
    }
    m_drawPoints.push_back(m_linePoints[m_linePoints.count() - 1]);
    static int  Clip=20;
    int n = m_drawPoints.count();
    double t1,t2,t3,t,a,b,c,d,x,y;
    t=0.5f/Clip;
    QPointF startPoint = m_drawPoints[1];
    QPointF endPoint;

    for (int i = 0;i < n-3 ; i++){
          for(int j=1;j<Clip;j++){
                 t1 = j * t;
                 t2 = t1 * t1;
                 t3 = t2 * t1;
                 a = 4.0 * t2 - t1 - 4.0 * t3;
                 b = 1.0 - 10.0 * t2 + 12.0 * t3;
                 c = t1 + 8.0 * t2 - 12.0 * t3;
                 d = 4.0 * t3 - 2.0 * t2;
                 x = a * m_drawPoints[i].x() + b * m_drawPoints[i+1].x() + c * m_drawPoints[i+2].x() + d * m_drawPoints[i+3].x();
                 y = a * m_drawPoints[i].y() + b * m_drawPoints[i+1].y() + c * m_drawPoints[i+2].y() + d*m_drawPoints[i+3].y();
                 endPoint.rx() = x;
                 endPoint.ry() = y;
                 painter->drawLine(startPoint, endPoint);
                 startPoint = endPoint;
          }
          painter->drawLine(startPoint, m_drawPoints[i + 2]);
    }
}

void forkliftPathItem::SetCurrentPoint(QPointF &point)
{
    currentPointIndex = -1;
    for(int i = 0; i < m_linePoints.count(); i++){
        if(qFabs(m_linePoints[i].x() - point.x())  < 5 && qFabs(m_linePoints[i].y() - point.y()) < 5){
             currentPointIndex = i;
             break;
        }
    }
}

void forkliftPathItem::MovePoint(QPointF &point)
{
    if(currentPointIndex >= 0 && currentPointIndex < m_linePoints.count()){
        m_linePoints[currentPointIndex].rx() = point.x();
        m_linePoints[currentPointIndex].ry() = point.y();
    }
    for (int i=0; i < m_linePoints.count(); i++){
        if (i< 2){
            m_cargoPoints[i] = m_linePoints[i];
        }
        else{
            break;
        }
    }
}


