#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QTimer>
#include "../qcustomPlot/qcustomplot.h"
#include "../io_layer/getdatathread.h"
#include <QVector>

//曲线显示
class plotWidget : public QCustomPlot
{
    Q_OBJECT
public:
    explicit plotWidget(QWidget *parent = 0);
    void SetDataType(GetDataType dataType);

public slots:
    void updateData(GetDataType dataType);

private slots:
    void SetRealtimeData();
    void SetRealtimeImg();
    void paintEvent(QPaintEvent *event);
private:
    void setupRealtimeData();
    bool focusType(GetDataType dataType);
    void SetRealtimeData(double value);

    QTimer dataTimer;
    GetDataType m_dataType;
    GetDataType m_parentDataType;

    QString demoName;

    QVector<double> m_datas;
    QMutex mutex;

    QString m_imageFileName;
};

#endif // PLOTWIDGET_H
