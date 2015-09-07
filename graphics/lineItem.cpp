#include "lineItem.h"
#include "../myapp.h"

QPoint lineItem::m_lineCroPos(200, 200);

lineItem::lineItem(int width, int height)
{
    m_width = width;
    m_height =  height;

    QLine horizonLine = QLine(4, height * 0.55, width - 4, height  * 0.55);
    m_linePos.push_back(horizonLine);
    QLine verticalLine = QLine(width * 0.19, 4, width * 0.19, height - 4);
    m_linePos.push_back(verticalLine);
    m_lineCroPos.rx() = (double)(width * 19/100);
    m_lineCroPos.ry() = (double)(height * 55 /100) ;
    qDebug("lineItem::lineItem %d, %d",  m_lineCroPos.rx(),  m_lineCroPos.ry());

}

lineItem::~lineItem()
{
}

QRectF lineItem::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void lineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->setPen(QPen(Qt::darkBlue, 2, Qt::SolidLine));
    for(int i = 0; i < m_linePos.count(); i++){
            painter->drawLine(m_linePos[i]);
    }
    if(m_linePos.count() > 0)
        painter->drawEllipse(m_linePos[m_linePos.count() - 1].x2(),  m_linePos[m_linePos.count() - 1].y2(), 6, 6);
}

double lineItem::CalAngle(double angle)
{
    return angle;
}
