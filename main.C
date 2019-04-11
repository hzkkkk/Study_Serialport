/*********************************************************************
 *
 *  Copyright (c) 2019, WildWolfTeam_hzk
 *  All rights reserved.
 *
 *  @Project  : Serial Communicationt DEBUG
 *  @FileName : main.C
 *  @Abstract : Sending data through serial port
 *  @Log      : Add comment to essential codes
 *
 *  @Vertion  : 2.1
 *  @Author   : HZK
 *  @Date     : 2019.01.09
 *
 *  @Legacy   : 2.0a
 *  @Author   : HZK
 *  @Date     : 2018.12.12
 *
 *********************************************************************/
#include "config.h"
unsigned char Checksum_CRC8(char *buf, unsigned short  len);
#include <iostream>
#include <stdio.h>
/*****配置所需头文件******/
#include <fcntl.h>      /*文件控制定义*/
#include <termios.h>    /*PPSIX终端控制定义*/
/*****Write所需头文件******/
#include <unistd.h>     /*Unix标准函数定义*/

#define SendBuf_LIMIT 20

using namespace std;

#ifdef SLEEP_MODE_1
//延时函数，防止发送过快
void Sleep_us(unsigned int secs);
#endif
//原文：https://blog.csdn.net/flfihpv259/article/details/53786604
int main()
{
    int fd,wr_num=0;
    struct termios oldstate, newstate;

   //char * buf = new char[40];//这种申请空间的方法，要注意下面：SIZEOF，如果是BUF的话是会反问

    int ifRecoginitionSuccess_FLAG = 0;    //ifRecoginitionSuccess
    int ifSendSuccess_FLAG = 0;            //ifSendSuccess
    int SendBuf_COUNT = 0;                 //ifSendSuccess

    //                    读、写打开|非阻塞方式|不作为控制终端|防低电平睡眠
    fd=open(DEVICE_NAME, O_RDWR|O_NONBLOCK|O_NOCTTY|O_NDELAY);    //打开串口
    if(fd==-1)
          perror("Can't Open Serial Port");
    else
          printf("Open COM ok!\n");


   if(fcntl(fd, F_SETFL, 0) <0 ) //改为阻塞模式
      printf("fcntl failed\n");
    else
      printf("fcntl=%d\n", fcntl(fd, F_SETFL, 0));

    //获取串口
    tcgetattr(fd, &newstate);

    cfsetispeed(&newstate, BANDRATE);
    cfsetospeed(&newstate, BANDRATE);

    //储存目前的序列埠设定值
    tcgetattr(fd,&oldstate);

    //串口设置
    //设定新的序列埠为标准输入程序
    newstate.c_cflag |= (CLOCAL | CREAD);
    //奇数校验位

    //NOTE : PARMODE 是否启用校验位
#ifdef PARMODE_0
    newstate.c_cflag &= ~PARENB;  //启用校验位
    newstate.c_cflag &= ~CSTOPB; //设置停止位1
#endif

#ifdef PARMODE_1
    newstate.c_cflag |= PARENB; //启用校验位
    newstate.c_cflag |= PARODD; //设置奇校验位
    newstate.c_cflag |= INPCK; //禁用校验检查
#endif

#ifdef PARMODE_2
    newstate.c_cflag |= PARENB; //启用校验位
    newstate.c_cflag &= ~PARODD; //设置偶校验位
    newstate.c_cflag |= INPCK; //禁用校验检查

#endif

    newstate.c_cflag &= ~CSIZE;
    newstate.c_cflag |= CS8; //设置数据位
    newstate.c_cc[VTIME]=0;//阻塞模式的设置
    newstate.c_cc[VMIN] = READWAITTIME;
    //清空输入、输出缓冲
    tcflush(fd, TCIFLUSH);
    //激活新配置
    tcsetattr(fd, TCSANOW, &newstate);


    clock_t startTime, endTime;

    for(int i = 0; i < LOOP; i++)
    {
        //NOTE : RUNTIME 计算时间
        startTime = clock();//计时开始

        int x = 320,y = 240,z = 72;
        int x_flag = 0, y_flag = 0, z_flag = 0;

///SEND_NONE_SIMU_0
#ifdef SEND_NONE_SIMU_0
    ifRecoginitionSuccess_FLAG = 1;
#endif //SEND_NONE_SIMU_0


#ifdef SEND_NONE_SIMU_1

        if( i % 10000 < 5000 )
        {
            ifRecoginitionSuccess_FLAG = 1;
        }
        else
        {
            ifRecoginitionSuccess_FLAG = 0;
            SendBuf_COUNT++;
        }
#endif //SEND_NONE_SIMU_1

#ifdef SEND_SIMU_1
        if( i % 10 < 5 )
        {
            x = 10, y = 10;
            z = 72;
            x_flag = 1;
            y_flag = 1;
            z_flag = 1;
        }
        else
        {
            x = 230, y = 320;
            z = 5;
            x_flag = 0;
            y_flag = 0;
            z_flag = 0;
        }
#endif //SEND_SIMU_1

#ifdef SEND_SIMU_0
        x = 230, y = 320;
        z = 5;
        x_flag = 0;
        y_flag = 0;
        z_flag = 0;
#endif //SEND_SIMU_0


//TODO: MODE_SELECT 选择通讯协议
#ifdef TX_MODE_1
    #ifdef PARMODE_CRC_1
        //通讯协议1
            char BUF[DATABIT];
            char BUF_TEMP[DATABIT_TEMP];
            sprintf(BUF_TEMP, "%c%1d%03d%1d%03d%1d%03d%c", 'S', x_flag, x, y_flag, y, z_flag, z, 'E');
            uint8_t CRC = Checksum_CRC8(BUF_TEMP, sizeof(BUF_TEMP));
            printf("CRC:%d\n", CRC);
            sprintf(BUF, "%c%1d%03d%1d%03d%1d%03d%03d%c", 'S', x_flag, x, y_flag, y, z_flag, z, CRC, 'E');
    #endif

    #ifdef PARMODE_CRC_0
        //通讯协议1
            char BUF[DATABIT];
            sprintf(BUF, "%c%03d%03d%03d%c", 'S', 320, 240, 0, 'E');
            //sprintf(BUF, "%s", "N1000000000");
    #endif
#endif


#ifdef TX_MODE_2
    //通讯协议2
    #ifdef PARMODE_CRC_0
        uint16_t BUF[DATABIT];
        uint16_t x_16 = x;
        uint16_t y_16 = y;

        BUF[0] = 0xB2A1;
        BUF[1] = x_16;
        BUF[2] = y_16;
        BUF[3] = x_16;
        BUF[4] = 0xD4C3;
    #endif
#endif



#ifdef TX_MODE_3
    #ifdef PARMODE_CRC_0
        uint8_t BUF[8];
        uint16_t x_16 = x;
        uint16_t y_16 = y;

        BUF[0] = 0xA1;
        BUF[1] = 0x11;
        BUF[2] = 0x22;
        BUF[3] = 0x33;
        BUF[4] = 0x44;
        BUF[5] = 0x55;
        BUF[6] = 0x66;
        BUF[7] = 0xFF;
    #endif
#endif //MODE_3


#ifdef TX_MODE_4
#endif //MODE_4


#ifdef DEBUG_FORMAT_FORCHAR_1
//        for(int index = 1;index < 13; index++)
//            BUF[index] -= 48;
#endif //FORMAT_FORCHAR


#ifdef SEND_NONE_SIMU_1
        if( !ifRecoginitionSuccess_FLAG  )
        {
           if( SendBuf_COUNT< 3000)
                sprintf(BUF, "%s", "N1000000");
        }
#endif


    //写入串口
    wr_num=write(fd, BUF, sizeof(BUF));
    cout << "BUF:" << BUF << endl;
    cout << "wr_num:" << wr_num << endl;
    cout << "ifRecoginitionSuccess_FLAG:" << ifRecoginitionSuccess_FLAG << "\n\n";


#ifdef SLEEP_MODE_1
        Sleep_us(SLEEPTIME);
#endif //SLEEP_MODE_1

        if(wr_num > 0)
              printf("Write success!\n");
        else
              printf("Write fail!\n");

        //NOTE : RUNTIME 计算时间
        endTime = clock();//计时
        cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    }
    //回存旧的序列埠设定值
    tcsetattr(fd, TCSANOW, &oldstate);
    return 0;
}



#ifdef PARMODE_CRC_1
/** CRC8校验函数
 *
 *  @param:  char *buf   需要检验的字符串
 *  @param:  uint16_t len 是否进行奇偶校验,'Y'表示需要奇偶校验,'N'表示不需要奇偶校验
 *
 *  @return: bool  初始化是否成功
 *  @brief:  CRC8校验 ---MAXIM x8+x5+x4+x1  多项式 POLY（Hex）:31(110001)  初始值 INIT（Hex）：00  结果异或值 XOROUT（Hex）：
 *  @note:   在使用其他本类提供的函数前,请先调用本函数进行串口的初始化
 *　　　　　   函数提供了一些常用的串口参数设置
 *           本串口类析构时会自动关闭串口,无需额外执行关闭串口
 */

uint8_t Checksum_CRC8(char *buf,uint16_t len)
{
    uint8_t check = 0;

    while(len--)
    {
        check = CRC8Tab[check^(*buf++)];
    }

    return (check)&0x00ff;
}

#endif //PARMODE_CRC_1

#ifdef SLEEP_MODE_1
void Sleep_us(unsigned int secs)
{
    struct timeval tval;
    tval.tv_usec=(secs)%1000000;
    select(0,NULL,NULL,NULL,&tval);
}
#endif

