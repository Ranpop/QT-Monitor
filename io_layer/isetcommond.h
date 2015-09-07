#ifndef ISETCOMMOND_H
#define ISETCOMMOND_H

#include "ibasestruct.h"
//#include <QGraphicsView>
#include <QVector>
#include <QObject>


//设置指令接口，有待进一步扩展
class ISetCommond : public QObject
{
    Q_OBJECT
    explicit ISetCommond(QObject *parent = 0);
     static ISetCommond* m_pInstacne;
public:
     //explicit  ISetCommond(QWidget *parent = 0);
    ~ISetCommond();
    static ISetCommond* GetInstance();

public slots:
    void setCmdProc();
};

#endif // ISETCOMMOND_H
