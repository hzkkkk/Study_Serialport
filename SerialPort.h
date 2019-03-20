#ifndef SERIALPORT_H
#define SERIALPORT_H

/**              头文件            **/
#include <iostream>
#include <stdio.h>
/*****配置所需头文件******/
#include <fcntl.h>      /*文件控制定义*/
#include <termios.h>    /*PPSIX终端控制定义*/
/*****Write所需头文件******/
#include <unistd.h>     /*Unix标准函数定义*/

/**              宏定义            **/
using namespace std;


/**              函数声明            **/
//延时函数，防止发送过快
void Sleep_us(unsigned int secs);


class SerialPort {

private:
    //串口标志量
    int fd;

public:
    SerialPort(int portNo = 1);
    bool initPort(int baud = B115200);
    bool WriteData(char *buf);
    string ReceiveData(int fd);

public:
    ~SerialPort();

};



#endif // SERIALPORT_H
