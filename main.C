
/*********************************************************************
 *
 *  Copyright (c) 2019, WildWolfTeam_hzk
 *  All rights reserved.
 *
 *  @Project  : Serial Communication DEBUG
 *  @FileName : main.C
 *  @Abstract : SerialPort(int portNo = 1);
 *              bool initPort(int baud = B115200);
 *              bool WriteData(char *buf);
 *
 *  @Log      : Bundle up the codes to a class
 *
 *  @Vertion  : 2.2
 *  @Author   : HZK
 *  @Date     : 2018.01.13
 *
 *  @Legacy   : 2.1
 *  @Author   : HZK
 *  @Date     : 2019.01.09
 *
 *  @Legacy   : 2.0
 *  @Author   : HZK
 *  @Date     : 2018.12.12
 *
 *********************************************************************/


#include <SerialPort.h>

char *g_buf = new char[8];
int main()
{
    SerialPort Port(1);
    Port.initPort();


    for(int i = 0;i < 100; i++)
    {
        sprintf(g_buf, "%s%d%s%d", "S", 320 + i, ",", 240 - i);
        std::cout << g_buf << std::endl;
        Port.WriteData(g_buf);
    }
    return 0;

}
