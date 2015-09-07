#ifndef TESTSENDDATA_H
#define TESTSENDDATA_H

#include "igetstatusdata.h"
#include <QPainter>
#include <QVector>

struct testpoint{
    double posX;
    double posY;
};

//测试发送数据类，仅供展示
class TestSendData : public IGetStatusData
{
public:
    TestSendData();

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

    testpoint ChangePiexToMeter(testpoint point);

    void PrintfMem(void *pAddress, int datasize);
    //QVector<QPoint> m_testpiex;
};

#endif // TESTSENDDATA_H
