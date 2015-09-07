#ifndef LINEITEM_H
#define LINEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QVector>

//车道线
class lineItem : public QGraphicsItem
{
public:
    lineItem(int width, int height);
    ~lineItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //车道线angle转换至车库坐标系下
    double CalAngle(double angle);
private:
    QVector<QLine> m_linePos;

    int m_width;
    int m_height;
public:
    static QPoint m_lineCroPos;
};

#endif // PIXITEM_H
