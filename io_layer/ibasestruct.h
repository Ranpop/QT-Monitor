#ifndef IBASESTRUCT_H
#define IBASESTRUCT_H

#include<stdint.h>
#define TEXT_SZ 4043040//5043040//6043040//1543040//8192000
#define CAM_COUNT 6
#define CMD_SZ 20

//图像
struct shared_img_st {
        int written; // 作为一个标志，0x1111表示可读，0x00可写:
                            // 0x1000 text2 for marker
                            // 0x0100 text for marker
                            // 0x0010 text2 for line
                            // 0x0001 text for line
        int64_t size;
        int32_t nWidth;              //图像宽度
        int32_t nHeight;             //图像高
        int32_t nPixelFormat;
        unsigned char text[TEXT_SZ]; // 写入和读取
        unsigned char text2[TEXT_SZ];
        int index;
        //     bool waitNextImg;
        //bool bSaveImg;
        //存储图像路径，仅供UI程序使用
        //char fileName[200];// If the image is not shared from shared memory, line detector will share the image file name it used.
};

//车位置
struct shared_marker_st {
        int written;
        double posX;
        double posY;
};

struct shared_subcmd_st{
    char cmdType;  //"D", "T","F","N";
    double pos;
    double posX;
    double posY;
};

struct shared_command_st {
    int written;
    shared_subcmd_st subcmd[CMD_SZ];
};

//车道线距离角度
struct shared_line_st {
        int written;
        double angle;
        double distance;
};

//托盘位置
struct shared_bracket_st {
        int written;
        double posX[10];
        double posY[10];
        double posZ[10];
        double angleX[10];
        double angleZ[10];
};

//前方障碍物位置
struct shared_obstacle_st {
        int written;
        double posX;
        double posY;
        double posZ;
};

struct shared_forklift_state_st {
        double X0; // 车尾x坐标
        double Y0; // 车尾y坐标
        double wheelAngle; // 轮转向角
        double rightWheelAngle;
        double leftWheelAngle;
        double headingAngle; // 车身航向角
        double forkliftLength; // 车长度
        double forkliftWidthHead;
        double forkliftWidthTail;
        double v; // 车速
        double wTurnWheel;
        double lineDistance;
        int orientation; // -1, fork point to -x; 1, fork point to +x; -2, fork point to -y; 2, fork point to +y.
};

struct shared_use_st {
        struct shared_img_st sharedImg[CAM_COUNT];
        struct shared_marker_st sharedMarker[CAM_COUNT];
        struct shared_line_st sharedLine[CAM_COUNT];
        struct shared_bracket_st sharedBraket;
        struct shared_obstacle_st sharedObstacle;
        struct shared_command_st sharedCmd;
        struct shared_forklift_state_st sharedForkliftState;
};

#endif // IBASESTRUCT_H
