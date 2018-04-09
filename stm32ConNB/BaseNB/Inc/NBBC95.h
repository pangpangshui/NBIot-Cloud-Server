#ifndef __NBBC95_H__
#define __NBBC95_H__


#include <stdint.h>
#include "stm32f1xx_hal.h"
//#include "usart.h"


typedef enum {
    CMD_TEST,   //测试命令
    CMD_READ,   //读取命令
    CMD_SET,    //设置命令
    CMD_EXCUTE  //执行命令
}cmd_type;

typedef enum {
    ACTION_OK_EXIT_ERROR_NEXT,  //若成功执行后退出，若错误将继续执行下一条指令
    ACTION_OK_NEXT_ERROR_TRY    //若成功执行后继续执行下一跳指令，出错后进行尝试。
}cmdAction;                     //若达到最大尝试次数后，仍没有成功，将退出

typedef struct {
    const char*     NBcmd;      //AT指令
    char*           NBcmdParameter;   //AT指令参数
    cmd_type        property;      //指令属性
    char*           expectReply;      //期望得到的回复
    unsigned char   cmd_try;  //出错尝试次数
    unsigned char   havetried;//已经重复发送的次数
    cmdAction       cmd_action;//AT指令行为
    uint8_t         repeatPeri;     //重复发送的时间间隔
    uint16_t        max_timeout;   //最大超时时间
}ATcmd;

typedef ATcmd* atcmdInfo;


typedef enum {
    MSG_NONE,
    MSG_INIT,
    MSG_IMSI,
    MSG_IMEI,
    MSG_SIGN,
    MSG_DEVID,
    MSG_MANUINFO,
    MSG_MODULEINFO,
    MSG_MREVER,
    MSG_BAND,
    MSG_REGISTER,
    MSG_UDP_CREATE,
    MSG_UDP_SEND,
    MSG_UDP_RECE,
    MSG_UDP_CLOSE,
    MSG_COAP
}msg_type;



typedef enum {
    PROCESS_NONE,
    PROCESS_INIT = MSG_INIT,
    PROCESS_MODULE_INFO = MSG_MODULEINFO,
    PROCESS_REGISTER = MSG_REGISTER,
//    PROCESS_IMSI = MSG_IMSI,
//    PROCESS_IMEI = MSG_IMEI,
    PROCESS_SIGN = MSG_SIGN,
    PROCESS_UDP_CREATE = MSG_UDP_CREATE,
    PROCESS_UDP_SEND = MSG_UDP_SEND,
    PROCESS_UDP_RECE = MSG_UDP_RECE,
    PROCESS_UDP_CLOSE = MSG_UDP_CLOSE,
    PROCESS_COAP = MSG_COAP
}NB_Process;


typedef enum {
    TYPES_CIMI      =   MSG_IMSI,
    TYPES_CGSN      =   MSG_IMEI,
    TYPES_CGMI      =   MSG_MANUINFO,
    TYPES_CGMM      =   MSG_MODULEINFO,
    TYPES_CGMR      =   MSG_MREVER,
    TYPES_NBAND     =   MSG_BAND,
    TYPES_UDP_CREATE=   MSG_UDP_CREATE,
    TYPES_UDP_CLOSE =   MSG_UDP_CLOSE,
    TYPES_UDP_SEND  =   MSG_UDP_SEND,
    TYPES_UDP_RECE  =   MSG_UDP_RECE
}reportMsgType;

typedef struct BC95State {
    NB_Process  state;
    int         sub_state;
}bc95_state;

typedef int (*NBReceMsg)(msg_type, int, char*);


typedef struct NBbc95 *NBModule;

typedef uint8_t (*NB_OpenModule)(NBModule);
typedef uint8_t (*NB_initbc95)(NBModule);
typedef const char* (*NB_ModuleInfo)(NBModule);
typedef const char* (*NB_RegisterInfo)(NBModule);
typedef const char* (*NB_MISIInfo)(NBModule);
typedef int (*NB_NetSign)(NBModule);
typedef uint8_t (*NB_CreateUdpServer)(NBModule);
typedef uint8_t (*NB_SendToUdp)(NBModule, int , char*);
//typedef uint8_t (*NB_RecFromUdp)(NBModule);
typedef uint8_t (*NB_CloseUdp)(NBModule);
typedef uint8_t (*NB_BC95Main)(NBModule);

typedef struct {
    NB_OpenModule       Openbc95;
    NB_initbc95         Initbc95;
    NB_ModuleInfo       getModuleInfo;
    NB_RegisterInfo     getRegisterInfo;
    NB_MISIInfo         getMISIInfo;
    NB_NetSign          isNetSign;
    NB_CreateUdpServer  CreateUDPServer;
    NB_SendToUdp        SendToUdp;
    //NB_RecFromUdp       RecFromUdp;
    NB_CloseUdp         CloseUdp;
    NB_BC95Main         BC95Main;
}NBOperaFun;


//BC95功能结构数据
typedef struct NBbc95{
    NBOperaFun  *funcPtr;
    void        *object;//BC95 uart对象指针
    NBReceMsg   recMsg_Callback;
}NBbc95;

//串口接收回调
typedef void (*BC95_SP_ReceiveCallback)(char*, uint16_t);


typedef void (*SerialPortOpen)(BC95_SP_ReceiveCallback, uint32_t);
typedef void (*SerialPortSend)(uint8_t*, uint16_t);
typedef void (*SerialPortClose)(void);
//串口操作结构体，用作初始化BC95对象结构的serialfun
typedef struct {
    SerialPortOpen  serialPortOpen;
    SerialPortSend  serialPortSend;
    SerialPortClose serialPortClose;
}serialfun;


typedef void (*bc95_TimerCallback)(void);
typedef void (*bc95_TimerInit)(bc95_TimerCallback);
typedef void (*bc95_TimerStart)(uint32_t);
typedef void (*bc95_TimerStop)(void);


typedef struct {
    bc95_TimerInit      bc95_TimerInitFun;
    bc95_TimerStart     bc95_TimerStartFun;
    bc95_TimerStop      bc95_TimerStopFun;
}bc95_TimerFun;

//BC95对象结构，用作初始化NBbc95中的BC95 uart对象指针
typedef struct {
    uint16_t    baundrate;
    serialfun   *SPfunTable;
    bc95_TimerFun *timerFun;
}bc95Module;

typedef bc95Module *bc95object;



extern uint8_t openbc95(NBModule bc95);
extern uint8_t initbc95(NBModule bc95);
extern const char* getModuleInfo_bc95(NBModule bc95);
extern const char* getRegisterInfo_bc95(NBModule bc95);
extern const char* getMISIInfo_bc95(NBModule bc95);
extern int isNetSign_bc95(NBModule bc95);
extern uint8_t createUDPServer_bc95(NBModule bc95);
extern uint8_t sendToUdp_bc95(NBModule bc95, int len, char* buf);
uint8_t recFromUdp_bc95(NBModule bc95);
extern uint8_t closeUdp_bc95(NBModule bc95);
extern uint8_t bc95Main(NBModule bc95);
void InitATcmd(atcmdInfo cmdinfo, const char* cmd, char* param, cmd_type property);
uint16_t formatATcmd(atcmdInfo cmdinfo);
void NBbc95SendCMD_Usart(bc95object bc95, atcmdInfo cmdinfo);



extern unsigned char openNBModule(NBModule bc95);
extern unsigned char initNBModule(NBModule bc95);
extern int SignNBModule(NBModule bc95);
extern uint8_t NBModuleMain(NBModule bc95);



static void ResetState(void);
static void ResetReceBuf(void);
static void bc95_SerialReceCallBack(char* buf, uint16_t len);
static void bc95_SetEvent(int eventID);
static void bc95_TimerOutCallback(void);
uint32_t NB_Strtoul(const char* pStr, int base);
uint8_t addr_adjust(char *buf, char *pStart, uint16_t* pLen);
uint8_t bc95_AsynNotification(char* buf, uint16_t* len);
static int8_t cmdIsPass(char *buf);
static void NBStopTimer(bc95object bc95Obj);

void NBSendMsg(NBModule bc95, char **buf, unsigned char isOK);
uint16_t NBHexStrToNum(char *str);
unsigned char bc95ResultHandle(NBModule bc95, unsigned char isOK);
static unsigned char GotoNextCmd(void);

#endif

