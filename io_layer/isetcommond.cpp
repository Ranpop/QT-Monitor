#include "isetcommond.h"
#include "igetstatusdata.h"
#include "inoutfactory.h"
#include "../graphics/mapwidget.h"
#include "../myhelper.h"

ISetCommond* ISetCommond::m_pInstacne = NULL;

ISetCommond::ISetCommond(QObject *parent) : QObject(parent)
{
        //connect(MapWidget::GetInstance(), SIGNAL(setCmd()), this, SLOT(setCmdProc()), Qt::DirectConnection);
        //connect(MapWidget::GetInstance(), SIGNAL(setCmd()), this, SLOT(setCmdProc()));
}

ISetCommond* ISetCommond::GetInstance()
{
    if(m_pInstacne == NULL){
        m_pInstacne = new ISetCommond();
    }
    return m_pInstacne;
}

ISetCommond::~ISetCommond()
{
}


void ISetCommond::setCmdProc()
{
    QVector<shared_subcmd_st> cmdtemp;

    if(MapWidget::GetInstance()->SetCommandData(cmdtemp)){
        qDebug("ISetCommond::setCmdProc success, cmd data is ok!  N=%d", cmdtemp[0].cmdType);
        IGetStatusData* getdata = InOutFactory::GetInstance()->GetInterface(in_test);
        //if (NULL == getdata){
       //     myHelper::ShowMessageBoxInfo("系统未连接，请连接系统！");
       //     return;
        //}
        //IGetStatusData* getdata = InOutFactory::GetInstance()->GetInterface(in_sharememory);
        if (getdata->SetCmdInfo(cmdtemp)){
            //successfuly
            qDebug("ISetCommond::setCmdProc success, cmd data is ok!");
        }
        else{
            //failed
            qDebug("ISetCommond::setCmdProc failed, can not get the cmd data!");
        }
    }

}
