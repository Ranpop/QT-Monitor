/*
 * Copyright (C) 2015 vvme
 *
 * author   : Joseph Chen
 * e-mail   : chencunzhu@163.com
 * home page: 
 */
/*
 * shMem.h *
 * Created on: 2015-2-26
 * Author: Joseph Chen
 */

#ifndef SHMEM_H_
#define SHMEM_H_

#include <stdint.h>

#define TEXT_SZ 4043040//5043040//6043040//1543040//8192000  

//图像
struct shared_img_st {
        int written; // 作为一个标志，0x1111表示可读，0x00可写: 
		     // 0x1000 text2 for marker
                     // 0x0100 text for marker
		     // 0x0010 text2 for line
 		     // 0x0001 text for line  
        int64_t size;
        int32_t nWidth;              ///< Í¼ÏñµÄ¿í
        int32_t nHeight;             ///< Í¼ÏñµÄ¸ß
        int32_t nPixelFormat;
        unsigned char text[TEXT_SZ]; // 写入和读取  
        unsigned char text2[TEXT_SZ];
//        bool waitNextImg;
        char fileName[100];// If the image is not shared from shared memory, line detector will share the image file name it used.
};

//车位置
struct shared_marker_st {
        int written;
        double posX;
        double posY;
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
        double posX;
        double posY;
        double posZ;
};

//前方障碍物位置
struct shared_obstacle_st {
        int written;
        double posX;
        double posY;
        double posZ;
};

struct shared_use_st {
        struct shared_img_st sharedImg;
        struct shared_marker_st sharedMarker;
        struct shared_line_st sharedLine;
        struct shared_bracket_st sharedBraket;
        struct shared_obstacle_st sharedObstacle;
};

void *shm = NULL;
struct shared_use_st *shared = NULL;
int shmid = -1;

void initShMem(void) {
        // 创建共享内存  
        shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);
        if(shmid == -1) {
                fprintf(stderr, "shmget failed\n");
                exit(EXIT_FAILURE);
        }
        // 将共享内存连接到当前进程的地址空间  
        shm = shmat(shmid, (void*)0, 0);
        if(shm == (void*)-1) {
                fprintf(stderr, "shmat failed\n");
                exit(EXIT_FAILURE);
        }
        //printf("Memory attached at %X\n", (int)shm);
        // 设置共享内存  
        shared = (struct shared_use_st*)shm;
}

void releaseShMem(void) {
        // 释放buffer
        if(shm) {
                if (shmdt(shm) == -1) {
                        fprintf(stderr, "shmdt failed\n");
                        exit(EXIT_FAILURE);
                }
                shm = NULL;
                shared = NULL;
        }
}

void deleteShMem(void) {
	// 删除共享内存  
        if(shmid > 0) {
                if (shmctl(shmid, IPC_RMID, 0) == -1) {
                        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
                        exit(EXIT_FAILURE);
                }
		shmid = -1;
	}
}
                   
#endif /* SHMEM_H_ */

