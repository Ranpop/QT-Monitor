#include "sharememory.h"
#include <sys/shm.h>
#include <stddef.h>
#include <QDebug>
#include "../myapp.h"
#include "../myhelper.h"
#include <QVector>

ShareMemory::ShareMemory()
{
    shm = NULL;
    shared = NULL;
    shmid = -1;
}

ShareMemory::~ShareMemory()
{

}

bool ShareMemory::Initial()
{
    // 创建共享内存
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);
    if(shmid == -1) {
        qDebug()<<"shmget failed\n";
        myHelper::ShowMessageBoxError("创建共享内存失败，请重启程序！");
        return false;
    }
    // 将共享内存连接到当前进程的地址空间
    shm = shmat(shmid, (void*)0, 0);
    if(shm == (void*)-1) {
            qDebug()<<"shmget failed\n";
            myHelper::ShowMessageBoxError("连接共享内存失败，请重启程序！");
            return false;
    }
    //printf("Memory attached at %X\n", (int)shm);
    // 设置共享内存
    shared = (struct shared_use_st*)shm;

    return true;
}

bool ShareMemory::Realease()
{
    // 释放buffer
    if(shm) {
        if (shmdt(shm) == -1) {
                qDebug()<<"shmdt failed\n";
                return false;
        }
        shm = NULL;
        shared = NULL;
    }
    return true;
}

bool ShareMemory::Deletebuffer()
{
    // 删除共享内存
    if(shmid > 0) {
        if (shmctl(shmid, IPC_RMID, 0) == -1) {
                qDebug()<<"shmctl(IPC_RMID) failed\n";
                return false;
        }
        shmid = -1;
    }
    return true;
}

shared_img_st* ShareMemory::GetImageInfo()
{
    if(shared == 0)
        return false;
    shared_img_st *result = 0;
    if(shared->sharedImg[TINDEX].written > 0) {
        result = new shared_img_st();
        result->written = shared->sharedImg[TINDEX].written;
        result->nHeight = shared->sharedImg[TINDEX].nHeight;
        result->nPixelFormat = 3;
        result->nWidth = shared->sharedImg[TINDEX].nWidth;
        result->size = shared->sharedImg[TINDEX].size;
        //result->bSaveImg = false;

        //memcpy(temp.fileName, shared->sharedImg.fileName, sizeof(temp.fileName));
        if(result->written & 0x0100 || result->written & 0x0001)
            memcpy(result->text, shared->sharedImg[TINDEX].text, TEXT_SZ);
        else if(result->written & 0x1000 || result->written & 0x0010)
            memcpy(result->text, shared->sharedImg[TINDEX].text2, TEXT_SZ);
    }
    return result;
}

bool ShareMemory::GetMarketInfo(shared_marker_st& temp)
{    
    if(shared == 0)
        return false;

 //   if(shared->sharedMarker.written != 0) {
//        if(abs(m_premarker.posX - shared->sharedMarker.posX) < myApp::dataCheckMin
//                && abs(m_premarker.posY - shared->sharedMarker.posY) < myApp::dataCheckMin)
//            return false;
        temp.posX = (shared->sharedMarker[TINDEX].posX)*FT2M;
        temp.posY = (shared->sharedMarker[TINDEX].posY)*FT2M;
        m_premarker = temp;
        //qDebug("The market is Ok ,shared marker addr is 0x%x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", &shared->sharedMarker);
        //qDebug("The market posX=%f, posY=%f",  (shared->sharedMarker[TINDEX].posX)*FT2M, (shared->sharedMarker.posY)*FT2M);
        //qDebug("The Mem addr is :0x%x", shared);
        //PrintfMem();
        return true;
 //   }
    return false;
}

bool ShareMemory::GetLineInfo(shared_line_st& temp)
{
    if(shared == 0)
        return false;

    if(shared->sharedLine[TINDEX].written != 0) {
//        if(abs(m_preline.angle - shared->sharedLine.angle) < myApp::dataCheckMin
//                && abs(m_preline.distance - shared->sharedLine.distance) < myApp::dataCheckMin)
//            return false;
        temp.angle = shared->sharedLine[TINDEX].angle;
        temp.distance = shared->sharedLine[TINDEX].distance;
        m_preline = temp;
        return true;
    }
    return false;
}

bool ShareMemory::GetBracketInfo(shared_bracket_st& temp)
{
    if(shared == 0)
        return false;

    if(shared->sharedBraket.written != 0) {
//        if(abs(m_prebracker.posX - shared->sharedBraket.posX) < myApp::dataCheckMin
//                && abs(m_prebracker.posY - shared->sharedBraket.posY) < myApp::dataCheckMin
//                && abs(m_prebracker.posZ - shared->sharedBraket.posZ) < myApp::dataCheckMin)
//            return false;
        temp.posX[0] = shared->sharedBraket.posX[0];
        temp.posY[0] = shared->sharedBraket.posY[0];
        temp.posZ[0] = shared->sharedBraket.posZ[0];
        m_prebracker = temp;
        return true;
    }
    return false;
}

bool ShareMemory::GetObstacleInfo(shared_obstacle_st& temp)
{
    if(shared == 0)
        return false;
    if(shared != NULL && shared->sharedObstacle.written != 0){
//        if(abs(m_preobstacle.posX - shared->sharedObstacle.posX) < myApp::dataCheckMin
//                && abs(m_preobstacle.posY - shared->sharedObstacle.posY) < myApp::dataCheckMin
//                && abs(m_preobstacle.posZ - shared->sharedObstacle.posZ) < myApp::dataCheckMin)
//            return false;
        temp.posX = shared->sharedObstacle.posX;
        temp.posY = shared->sharedObstacle.posY;
        temp.posZ = shared->sharedObstacle.posZ;
        m_preobstacle = temp;
        return true;
    }
    return false;
}

bool ShareMemory::GetForkRTInfo(shared_forklift_state_st &temp)
{
    if (0 == shared){
        return false;
    }

    if (NULL != shared){
        memcpy(&temp, &shared->sharedForkliftState, sizeof(shared_forklift_state_st));
        m_preforkinfo = temp;
        return true;
    }

    return false;
}

bool ShareMemory::SetCmdInfo(QVector<shared_subcmd_st> temp)
{
    if(shared == 0){
        return false;
    }

    if (shared != NULL && shared->sharedCmd.written == 0x00){
        memset(&shared->sharedCmd, 0, sizeof(shared_command_st));

        for(int i=0; i < temp.count(); i++){
            shared->sharedCmd.subcmd[i].cmdType = temp[i].cmdType;
            shared->sharedCmd.subcmd[i].pos = temp[i].pos;
        }

        shared->sharedCmd.written = 0x11;
        return true;
    }

    return false;
}

void ShareMemory::PrintfMem()
{
       unsigned int *pAddr = (unsigned int*)shared;
       int datasize = sizeof(shared_use_st);
       while (datasize)
       {
           int nCurSize = datasize > 4 ? 4 : datasize;
           qDebug("the mem data addr is:  0x%X", pAddr );

           // 输出16进制数据
           for (int i = 0; i < nCurSize; i++){
              qDebug("0x%x", pAddr[i]);
              //qDebug(" ");//补空白
           }
           qDebug("\n");//换行输出

           // 打印下一列
           datasize -= nCurSize;
           pAddr += nCurSize;
       }
}
