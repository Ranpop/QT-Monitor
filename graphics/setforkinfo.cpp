#include "setforkinfo.h"
#include "frmmain.h"

SetForkInfo* SetForkInfo::m_pInstacne = NULL;

SetForkInfo::SetForkInfo(QObject *parent) : QObject(parent)
{
    connect(GetDataThread::GetInstance(), SIGNAL(GetData(GetDataType)), this, SLOT(SetForkInfo2From(GetDataType)), Qt::DirectConnection);
}

SetForkInfo* SetForkInfo::GetInstance()
{
    if(m_pInstacne == NULL){
        m_pInstacne = new SetForkInfo();
    }
    return m_pInstacne;
}

SetForkInfo::~SetForkInfo()
{

}

void SetForkInfo::SetForkInfo2From(GetDataType dataType)
{
    if (forkinfo == dataType){
        shared_forklift_state_st temp;
        if (GetDataThread::GetInstance()->GetData(temp)){
            frmMain::GetInstance()->setFormData(temp);
        }
    }
}
