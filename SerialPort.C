#include <SerialPort.h>

    /** 打开串口
     *  @param:    portNo 串口编号,默认值为1,即COM1,注意,尽量不要大于9
     *  @return
     */
    SerialPort::SerialPort(int portNo) {

        const char* DeviceName[4] = {"", "/dev/ttyUSB0", "/dev/ttyUSB1", "/dev/ttyUSB2"};

         /* WARNING :  终端设备默认会设置为控制终端，因此open(O_NOCTTY不作为控制终端)
         * Terminals'll default to be set as Control Terminals
         */
         /*打开串口*/
        fd=open(DeviceName[portNo], O_RDWR|O_NONBLOCK|O_NOCTTY|O_NDELAY);

        if (fd == -1)
        {
            perror("Can't Open Serial Port\n");
        }
        else
            printf("Open Serial Port %s Successful\n", DeviceName[portNo]);

        /*改为阻塞模式*/
        if (fcntl(fd, F_SETFL, 0) < 0)
            printf("fcntl failed!\n");
        else
            printf("fcntl=%d\n", fcntl(fd, F_SETFL, 0));

        /*测试是否为终端设备*/
        if (isatty(STDIN_FILENO) == 0)
            printf("standard input is not a terminal device\n");
        else
            printf("isatty success!\n");

    }

    /** 关闭串口 **/
    SerialPort::~SerialPort(void)
    {
        if (!close(fd))
            printf("Close Serial Port Successful\n");
    }

    /** 初始化串口函数
     * @Default
     *  @param:  int baud   波特率,默认为115200
     * @Default
     *  @param:  char parity 是否进行奇偶校验,'Y'表示需要奇偶校验,'N'表示不需要奇偶校验
     * @Default
     *  @param:  int databits 数据位的个数,默认值为8个数据位
     *
     *  @return: bool  初始化是否成功
     *  @note:   在使用其他本类提供的函数前,请先调用本函数进行串口的初始化
     *　　　　　   函数提供了一些常用的串口参数设置
     *           本串口类析构时会自动关闭串口,无需额外执行关闭串口
     */
    bool SerialPort::initPort(int baud )
    {
        struct termios newstate, option;
        /*保存测试现有串口参数设置，在这里如果串口号等出错，会有相关的出错信息*/
        if (tcgetattr(fd, &option) != 0)
        {
            perror("SetupSerial");
            printf("tcgetattr( fd,&option) -> %d\n",tcgetattr(fd, &option));
            return 0;
        }
        /*串口设置*/

        //本地连线, 取消控制功能 | 开始接收
        newstate.c_cflag |= CLOCAL | CREAD;
        //设置字符大小
        newstate.c_cflag &= ~CSIZE;
        //设置停止位1
        newstate.c_cflag &= ~CSTOPB;
        //设置数据位8位
        newstate.c_cflag |= CS8;
        //设置无奇偶校验位，N
        newstate.c_cflag &= ~PARENB;

        /*阻塞模式的设置*/
        newstate.c_cc[VTIME]=0.01;
        newstate.c_cc[VMIN]=0;

        /*设置发送波特率*/
        cfsetospeed(&newstate, baud);

        /*激活新配置*/
        if ((tcsetattr(fd, TCSANOW, &newstate)) != 0)
        {
            perror("Com Set Error\n");
            return 0;
        }
        printf("Com Set done!\n");
        return 1;
    }


/** 向串口写数据
 *
 *  将缓冲区中的数据写入到串口
 *  @param:  unsigned char * buf_temp 指向需要写入串口的数据缓冲区
 *  ()@param:  unsigned int length 需要写入的数据长度
 *  @return: bool  操作是否成功
 */
    bool SerialPort::WriteData(char *buf)
    {
        if (write(fd, buf, sizeof(buf) == -1))
        {
            printf("write failed\n");
            return 0;
        }
        return 1;
    }


/** 串口读取
*  @param:  int fd
*
*  @return: string  返回收到的字符串
*  @note:   在使用其他本类提供的函数前,请先调用本函数进行串口的初始化
*           逐字节读取并存到字符串
*           等待0.01s后结束读取,将所得字符串返回
*/
string ReceiveData()
{
    char rece_buf_temp[RECEBUFFERSIZE];
    string rece_buf = "";
    int rece_COUNT=0;
    int rece_First_COUNT=0;

    do{
        memset(rece_buf_temp, 0, RECEBUFFERSIZE); //清空缓存
        int rece_buf_temp_int[RECEBUFFERSIZE];
        read(fd, rece_buf_temp_int, RECEBUFFERSIZE); //接收数据
        if(0 >= Read && !rece_buf.empty())
        {//如果这一次沒有收到数据，且未成功收到
            rece_COUNT++;
            if(rece_COUNT>10)break;
        }
        else if(0 < Read)
        {//如果有收到数据
            //成功收到数据,计数归0
            rece_COUNT=0;
            //将读到的数据存入rece_buf
            rece_buf.append((char*)rece_buf_temp, Read);
        }
        else
        {//首次读取成功,记录第一次成功读取
            rece_First_COUNT++;
        }
    }while(rece_First_COUNT + rece_COUNT < 100);//设定串口读取次数
     //cout << "rece_buf= " << rece_buf << endl;
    return rece_buf;
}


