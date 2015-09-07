#ifndef IGETSTATUSDATA_H
#define IGETSTATUSDATA_H

#include "ibasestruct.h"
#include <QVector>
//获取数据接口
class IGetStatusData
{
public:
    IGetStatusData();
    virtual ~IGetStatusData();

    virtual bool Initial() = 0;
    virtual bool Realease() = 0;
    virtual bool Deletebuffer();

    virtual shared_img_st* GetImageInfo() = 0;
    virtual bool GetMarketInfo(shared_marker_st& temp) = 0;
    virtual bool GetLineInfo(shared_line_st& temp) = 0;
    virtual bool GetBracketInfo(shared_bracket_st& temp) = 0;
    virtual bool GetObstacleInfo(shared_obstacle_st& temp) = 0;
    virtual bool GetForkRTInfo(shared_forklift_state_st& temp) = 0;
    virtual bool SetCmdInfo(QVector<shared_subcmd_st> temp) = 0;
};

#endif // IGETSTATUSDATA_H
