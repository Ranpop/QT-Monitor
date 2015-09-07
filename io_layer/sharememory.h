#ifndef SHAREMEMORY_H
#define SHAREMEMORY_H

#include "igetstatusdata.h"
#include "isetcommond.h"
#include "ibasestruct.h"
#include <QVector>

#define FT2M 0.3048
#define TINDEX 2
//共享内存类
class ShareMemory : public IGetStatusData
{
public:
    ShareMemory();
    ~ShareMemory();

    bool Initial();
    bool Realease();
    bool Deletebuffer();

    shared_img_st* GetImageInfo();
    bool GetMarketInfo(shared_marker_st& temp);
    bool GetLineInfo(shared_line_st& temp);
    bool GetBracketInfo(shared_bracket_st& temp);
    bool GetObstacleInfo(shared_obstacle_st& temp);
    bool GetForkRTInfo(shared_forklift_state_st& temp);
    bool SetCmdInfo(QVector<shared_subcmd_st> temp);

    void PrintfMem();

private:
    void *shm;
    struct shared_use_st *shared;
    int shmid;

    shared_marker_st m_premarker;
    shared_line_st m_preline;
    shared_bracket_st m_prebracker;
    shared_obstacle_st m_preobstacle;
    shared_forklift_state_st m_preforkinfo;
    shared_command_st m_precmd;
};

#endif // SHAREMEMORY_H
