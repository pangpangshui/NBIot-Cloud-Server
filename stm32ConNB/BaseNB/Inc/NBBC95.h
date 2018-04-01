#ifndef __NBBC95_H__
#define __NBBC95_H__


#include <stdint.h>
#include "usart.h"



typedef enum {
    CMD_TEST,   //测试命令
    CMD_READ,   //读取命令
    CMD_SET,    //设置命令
    CMD_EXCUTE  //执行命令
}cmd_type;


typedef struct{
    const char* NBcmd;      //AT指令
    char* NBcmdParameter;   //AT指令参数
    cmd_type property;      //指令属性
    char* expectReply;      //期望得到的回复
    unsigned char cmd_try;  //出错尝试次数
    unsigned char havetried;//已经重复发送的次数
    uint8_t repeatPeri;     //重复发送的时间间隔
    uint16_t max_timeout;   //最大超时时间
}ATcmd,*atcmdInfo;




typedef enum {
    MSG_IMSI,
    MSG_IMEI,
    MSG_SIGN,
    MSG_DEVID,
    MSG_MANUINFO,
    MSG_REGESTA,
    MSG_UDP,
    MSG_COAP
}msg_type;

typedef int (*NBReceMsg)(msg_type, int, char*);


typedef struct NBbc95 *NBModule;

typedef int (*NB_OpenModule)(NBModule);
typedef int (*NB_initbc95)(NBModule);
typedef int (*NB_initUdpServer)(NBModule);
typedef int (*NB_SendToUdp)(NBModule);
typedef int (*NB_RecFromUdp)(NBModule);
typedef int (*NB_BC95Main)(NBModule);

typedef struct {
    NB_OpenModule       Openbc95;
    NB_initbc95         Initbc95;
    NB_initUdpServer    InitUDPServer;
    NB_SendToUdp        SendToUdp;
    NB_RecFromUdp       RecFromUdp;
    NB_BC95Main         BC95Main;
}NBOperaFun;


//BC95功能结构数据
typedef struct NBbc95{
    NBOperaFun  *funcPtr;
    void        *object;//BC95 uart对象指针
    NBReceMsg   recMsg_Callback;
}NBbc95;

//串口接收回调
typedef void (*bc95_SP_receive_callback)(char*, uint16_t);


typedef void (*SerialPortOpen)(bc95_SP_receive_callback, uint32_t);
typedef void (*SerialPortSend)(uint8_t*, uint16_t);
typedef void (*SerialPortClose)(void);
//串口操作结构体，用作初始化BC95对象结构的serialfun
typedef struct {
    SerialPortOpen  serialPortOpen;
    SerialPortSend  serialPortSend;
    SerialPortClose serialPortClose;
}serialfun;


//BC95对象结构，用作初始化NBbc95中的BC95 uart对象指针
typedef struct {
    uint16_t    baundrate;
    serialfun   *SPfunTable;
}bc95Module;

typedef bc95Module *bc95object;



extern uint8_t openbc95(NBModule bc95);
extern uint8_t initbc95(NBModule bc95);
extern uint8_t initUDPServer_bc95(NBModule bc95);
extern uint8_t sendToUdp_bc95(NBModule bc95);
extern uint8_t recFromUdp_bc95(NBModule bc95);
extern uint8_t bc95Main(NBModule bc95);
void InitATcmd(atcmdInfo cmdinfo, const char* cmd, char* param, cmd_type property);
uint16_t formatATcmd(atcmdInfo cmdinfo);
uint8_t NBbc95SendCMD(bc95object bc95, atcmdInfo cmdinfo);




#endif

