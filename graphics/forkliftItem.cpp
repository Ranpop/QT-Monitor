#include "forkliftItem.h"
#include "../myapp.h"

forkliftItem::forkliftItem()
{
    QPixmap* temp = new QPixmap("forklift.jpg");
    pix = QPixmap(temp->width(), temp->height());
    pix.fill(QColor(255, 255, 255, 0));
    QPainter painter(&pix);
    painter.drawPixmap(0, 0, temp->width(), temp->height(), *temp);
    delete temp;
}

forkliftItem::~forkliftItem()
{
}

QRectF forkliftItem::boundingRect() const
{
    return QRectF(-2-pix.width()/2,-2-pix.height()/2,pix.width()+4, pix.height()+4);
}

void forkliftItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    QMutexLocker locker(&mutex);
    if(m_points.count() > 0){
        painter->setPen(QPen(Qt::blue,3,Qt::DashLine));
        for(int i = 0; i < m_points.count(); i++){
            painter->drawEllipse(m_points[i].x(),  m_points[i].y(), 3, 3);
        }
        painter->drawPixmap(m_points[m_points.count() - 1].x() - pix.width() / 2,  m_points[m_points.count() - 1].y() - pix.height() / 2,
                        pix.transformed(rotatematrix, Qt::SmoothTransformation));
    }
}

void forkliftItem::AddPosition(QPoint point)
{
    QMutexLocker locker(&mutex);
    while(m_points.count() > myApp::showPointNum){
        m_points.pop_front();
    }
    m_points.push_back(point);
}

void forkliftItem::AddPosture(double rotate)
{
    rotatematrix = QMatrix();
    rotatematrix.rotate(rotate);
}
