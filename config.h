#ifndef CONFIG_H
#define CONFIG_H

#define BUF buf

/*!**/
//TODO: Serious
#define BANDRATE_2   //1: 波特率115200     // 2: 波特率1500000
#define DEVICE_NAME "/dev/ttyUSB0"

//TODO: SendMode
#define TX_MODE_1      //1:"S"     2:"SE"     3:0x
#define PARMODE_CRC_0  //0:无CRC校验位         //1:CRC校验位
//TODO: ReceiveMode
#define RX_MODE_1

//Settings
#define PARMODE_0    //0:无校验位    //1:奇校验位  //2:偶校验位
#define READWAITTIME 1 //读取等待时间
#define SENDLOOP_1    //循环次数    //0:1        //1:20000
#define SEND_SIMU_1     //发送变换的测试数据   //0:OFF      //1:ON
#define SEND_NONE_SIMU_0   //测试NONE情况  //0:OFF      //1:ON  ///@brief : 需要改N1000000字符串
#define SLEEP_MODE_0   //是否睡眠  //0:OFF      //1:ON
    #ifdef SLEEP_MODE_1
        #define SLEEPTIME 800   //999999:1s但1000000不行
    #endif


#define DEBUG_FORMAT_FORCHAR_1  //acsii转真实值 －４８




//TX_MODE_1
#ifdef TX_MODE_1
    #ifdef PARMODE_CRC_1
        #define DATABIT_TEMP 14
        #define BUF_TEMP buf_temp
        #define DATABIT 17
    #endif

    #ifdef PARMODE_CRC_0
        #define DATABIT 11
    #endif
#endif  //TX_MODE_1

#ifdef TX_MODE_2
    #ifdef PARMODE_CRC_0
        #define DATABIT 10
    #endif
#endif //TX_MODE_2


#ifdef TX_MODE_3
    #ifdef PARMODE_CRC_0
        #define DATABIT 8
    #endif
#endif  //TX_MODE_3


#ifdef TX_MODE_4
#endif //TX_MODE_4


#ifdef PARMODE_CRC_1
const unsigned char CRC8Tab[]=
{
    0,94,188,226,97,63,221,131,194,156,126,32,163,253,31,65,
    157,195,33,127,252,162,64,30, 95,1,227,189,62,96,130,220,
    35,125,159,193,66,28,254,160,225,191,93,3,128,222,60,98,
    190,224,2,92,223,129,99,61,124,34,192,158,29,67,161,255,
    70,24,250,164,39,121,155,197,132,218,56,102,229,187,89,7,
    219,133,103,57,186,228,6,88,25,71,165,251,120,38,196,154,
    101,59,217,135,4,90,184,230,167,249,27,69,198,152,122,36,
    248,166,68,26,153,199,37,123,58,100,134,216,91,5,231,185,
    140,210,48,110,237,179,81,15,78,16,242,172,47,113,147,205,
    17,79,173,243,112,46,204,146,211,141,111,49,178,236,14,80,
    175,241,19,77,206,144,114,44,109,51,209,143,12,82,176,238,
    50,108,142,208,83,13,239,177,240,174,76,18,145,207,45,115,
    202,148,118,40,171,245,23,73,8,86,180,234,105,55,213,139,
    87,9,235,181,54,104,138,212,149,203, 41,119,244,170,72,22,
    233,183,85,11,136,214,52,106,43,117,151,201,74,20,246,168,
    116,42,200,150,21,75,169,247,182,232,10,84,215,137,107,53
};
#endif


//Bandrate setting
#ifdef BANDRATE_1
    #define BANDRATE B115200
#endif
#ifdef BANDRATE_2
    #define BANDRATE B1500000
#endif

//SendMode setting
#ifdef SENDLOOP_0
    #define LOOP 1
#endif
#ifdef SENDLOOP_1
    #define LOOP 200000
#endif


#endif // CONFIG_H

