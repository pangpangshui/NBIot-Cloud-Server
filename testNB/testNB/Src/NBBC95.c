#include "NBBC95.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const char* AT          =   "AT";
const char* AT_CMEE		=	"AT+CMEE";      //上报设备错误。启用结果码，使用数字型取值，参数为1
const char* AT_CGMI		=	"AT+CGMI";		//查询设备制造商信息
const char* AT_CGMM		=	"AT+CGMM";		//查询设备ID
const char* AT_CGMR		=	"AT+CGMR";		//查询设备固件版本
const char* AT_NBAND	=	"AT+NBAND";		//查询模块是否支持band
const char* AT_NCONFIG	=   "AT+NCONFIG";	//查询用户配置
const char* AT_CGSN	    =	"AT+CGSN";		//查询IMEI,参数为1
const char* AT_CIMI		=	"AT+CIMI";		//查询IMSI
const char* AT_CGATT1	=	"AT+CGATT";	    //附着(1)GPRS网络,参数为1
const char* AT_CGATT0	=	"AT+CGATT";	    //分离(0)GPRS网络，参数为0
const char* AT_CGATT	=	"AT+CGATT";		//查询附着状态, 需等待几秒
const char* AT_CSQ		=	"AT+CSQ";		//查询信号强度
const char* AT_COPS		=	"AT+COPS";		//查询注册模式和运营商
const char* AT_CEREG	=	"AT+CEREG";		//查询注册状态,返回1表示已注册本地网络
const char* AT_NUESTATS	=   "AT+NUESTATS";	//获取最新的操作统计
const char* AT_NSORF    =   "AT+NSORF";     //读取UDP发送回来的数据，返回实际返回的数据长度
const char* AT_CFUN     =   "AT+CFUN";      //功能限制 等于1时开启所有传输和接收的射频功能
const char* AT_CSCON    =   "AT+CSCON";     //Query the signal connection status, 1 means Connected 0 means idle
const char* AT_NSMI     =   "AT+NSMI";      //设置或获取通知当上行数据发送到CDP服务器时
const char* AT_NNMI     =   "AT+NNMI";      //当终端收到来自CDP服务器的下行数据时设置或接收通知
const char* AT_NSOCL    =   "AT+NSOCL";     //关闭socket
const char* AT_NSOCR    =   "AT+NSOCR";     //创建socket, 第二个参数是设置协议, UDP对应的是17
const char* AT_NSOST    =   "AT+NSOST";     //发送一个固定长度的UDP数据报到服务器
const char* AT_NCDP     =   "AT+NCDP";      //set and query the server IP address and port for the CDP 
const char* AT_NMGS     =   "AT+NMGS";      //通过CDP服务器从中断向网络发送消息
const char* AT_NMGR     =   "AT+NMGR";      //从CDP服务器接收消息
//NB模块操作
typedef enum {
    ACTION_NONE,        //0
    ACTION_SYNC,//AT
    ACTION_CMEE,
    ACTION_CFUN,
    ACTION_CIMI,
    ACTION_CGSN,
    ACTION_CEREG,
    ACTION_CSCON,
    ACTION_CGATT,
    ACTION_CGATT_QUERY,
    ACTION_NSMI,
    ACTION_NNMI,
    ACTION_CGMI,
    ACTION_CGMM,
    ACTION_CGMR,
    ACTION_NBAND,
    //ACTION_NCONFIG,
    //ACTION_CSQ,
    //ACTION_NUESTATS,
    ACTION_UDP_CLOSE,   //20
    ACTION_UDP_CREATE,  //19
    
    ACTION_UDP_SEND,    //21
    ACTION_UDP_RESET,   //22
    ACTION_END
}NBAction;

const uint8_t bc95InitProcess[] = 
    { ACTION_NONE, ACTION_SYNC, ACTION_CMEE, ACTION_CFUN, //ACTION_CGMI, ACTION_CGMR, 
      /*ACTION_NBAND, ACTION_NCONFIG,*/ACTION_CIMI, ACTION_CGSN, ACTION_CEREG, ACTION_CSCON, 
      ACTION_CGATT, ACTION_CGATT_QUERY, ACTION_NSMI, ACTION_NNMI, ACTION_END};

const uint8_t bc95GetInfoProcess[] = 
    { ACTION_NONE, ACTION_CGMI, ACTION_CGMM, ACTION_CGMR, ACTION_NBAND, ACTION_END};
  
const uint8_t bc95UDPCreateProcess[] = 
    { ACTION_NONE, ACTION_UDP_CREATE, ACTION_UDP_CLOSE, ACTION_UDP_CREATE, ACTION_END };
    
const uint8_t bc95UDPCloseProcess[] = 
    { ACTION_NONE, ACTION_UDP_CLOSE, ACTION_END };
    
const uint8_t bc95UDPSendProcess[] = 
    { ACTION_NONE, ACTION_UDP_SEND, ACTION_END };
    
//const uint8_t bc95CoapProcess[] = 
//    { ACTION_NONE, }

const NBOperaFun bc95fun = {
    .Openbc95           =  openbc95,
    .Initbc95           =  initbc95,
    .getModuleInfo      =  getModuleInfo_bc95,
    .getRegisterInfo    =  getRegisterInfo_bc95,
    .getMISIInfo        =  getMISIInfo_bc95,
    .isNetSign          =  isNetSign_bc95,
    .CreateUDPServer    =  createUDPServer_bc95,
    .SendToUdp          =  sendToUdp_bc95,
    //.RecFromUdp         =  recFromUdp_bc95,
    .CloseUdp           =  closeUdp_bc95,
    .CoapServer         =  coapServer_bc95,
    .CoapSentIndication =  coapSentIndication_bc95,
    .CoapReceIndication =  coapReceIndication_bc95,
    .CoapSentMsg        =  coapSentMsg_bc95,
    .BC95Main           =  bc95Main
};

#define NB_CMD_SEND_BUF_MAX_LEN 512
#define NB_CMD_RECE_BUF_MAX_LEN 512

#define NB_SP_RECE_EVENT    0x0001      //收到串口数据事件
#define NB_TIMEOUT_EVENT    0x0002      //超时时间
#define NB_UDP_RECE_EVENT   0x0004      //UDP接收事件
#define NB_COAP_RECE_EVENT  0x0008      //caop接收事件
#define NB_REG_STA_EVENT    0x0010      //网络附着事件


#define BAND_850MHZ_ID      5
#define BAND_850MHZ_STR     "850"

#define BAND_900MHZ_ID      8
#define BAND_900MHZ_STR     "900"

#define BAND_800MHZ_ID      20
#define BAND_800MHZ_STR     "800"

#define BAND_700MHZ_ID      28
#define BAND_700MHZ_STR     "700"

#define LOCAL_UDP_SET       "DGRAM,17,5783,1"
#define REMOTE_SERVER_IP    "193.112.57.70"
#define REMOTE_SERVER_PORT  "18777"

#define REMOTE_COAP_INFO    "193.112.57.70,5683"


struct CmdBufSend{
    char buf[NB_CMD_SEND_BUF_MAX_LEN];
    uint16_t len;
}NBCmdBufSend;
//NBCmdBufSend CmdbufSend;

struct CmdBufRec{
    char buf[NB_CMD_RECE_BUF_MAX_LEN];
    uint16_t len;
}NBCmdBufRec;

typedef struct {
    uint8_t     socketID;
    uint16_t    ReceDataLen;
}NB_UDPRece;

typedef struct {
    uint8_t connectionStatus;
    uint8_t registerStatus;
    char* ManuFacID;
    char* ModuleInfo;
    char* RecentInfo;
    uint8_t IMSI[16];
    uint8_t IMEI[16];
    char    UDP_ID[2];//创建的UDP socket ID
    NB_UDPRece UDP_Len; //UDP接收到的数据长度
    
}NBStatus;

NBStatus bc95_status;

extern NBOperaFun bc95_OperaFun;

//NB操作状态
static bc95_state nb_state = {PROCESS_NONE, 0};

static ATcmd atcmd;

//事件标志，可多个事件同时发生
static uint16_t bc95_event_reg = 0;


static void ResetState(void)
{
    nb_state.state = PROCESS_NONE;
    nb_state.sub_state = 0;
}

static void ResetReceBuf(void)
{
    memset(&NBCmdBufRec, 0, sizeof(struct CmdBufRec));
}

//将字符串转整型，base为进制数
uint32_t NB_Strtoul(const char* pStr, int base)
{
    return strtoul(pStr, 0, base);
}

//根据异步消息，调整指令的响应
uint8_t addr_adjust(char *buf, char *pStart, uint16_t* pLen)
{
    uint8_t isAsyn = 0;
    char *pEnd = NULL;
    uint8_t msgLen = 0;
    if ((pStart - buf) >= 2) {
        pStart -= 2;
    }
    if (pEnd = strstr(pStart, "\r\n")) {
        if (pEnd == pStart) 
            pEnd = strstr(pStart + 2, "\r\n");
        if (!pEnd) {
            *pLen = (uint8_t)(pStart - buf);
            return !!(*pLen); //?????
        }
        pEnd += 2;
        msgLen = (uint8_t)(pEnd - pStart);
        
        if (*pLen >= msgLen) {
            *pLen -= msgLen;
            if (*pLen == 0)
                isAsyn = 1;
            else {
                if (pStart == buf)
                    buf += msgLen;
            }
        }
    }
    return isAsyn;
}


//处理bc95异步返回
uint8_t bc95_AsynNotification(char* buf, uint16_t* len)
{
    uint8_t isAsyn = 0;
    char *position_addr_start = NULL;
    //position_addr_start记录在buf中出现+CEREG字符串的首个位置
    ///*Use AT+CEREG? to query current EPS Network Registration Status*/
    if (position_addr_start = strstr(buf, "+CEREG")) {
        //从position_addr_start中找出首个出现:字符的位置
        char *pColon = strchr(position_addr_start, ':');
        if (pColon) {
            pColon++;//移到下一个字符
            bc95_status.registerStatus = (*pColon - 0x30);//0x30是数字0的ascii码,字符转数字
        }
        isAsyn = addr_adjust(buf, position_addr_start, len);
        bc95_SetEvent(NB_REG_STA_EVENT);//已注册?
    }
    
    //AT+CSCON Signalling Connection Status 
    else if (position_addr_start = strstr(buf,"+CSCON")) {
        char *pColon = strchr(position_addr_start, ':');
        if (pColon) {
            pColon++;//移到下一个字符
            bc95_status.connectionStatus = (*pColon - 0x30);//0x30是数字0的ascii码,字符转数字
        }
        isAsyn = addr_adjust(buf, position_addr_start, len);
    }
    
    //AT+NSONMI  Create a Socket 
    if (position_addr_start = strstr(buf,"+NSONMI")) {
        char *pColon = strchr(position_addr_start, ':');
        if (pColon) {
            pColon++;//移到下一个字符
            bc95_status.UDP_Len.socketID = NB_Strtoul(pColon, 10);//将pColon转10进制数字
        }
        char *pCmd = strchr(pColon, ',');
        if (pCmd) {
            pColon++;//移到下一个字符
            bc95_status.UDP_Len.ReceDataLen = NB_Strtoul(pCmd, 10);
        }
        isAsyn = addr_adjust(buf, position_addr_start, len);
        bc95_SetEvent(NB_UDP_RECE_EVENT);
    }
    //AT+NNMI  Receive a message from the CDP server
    else if (position_addr_start = strstr(buf,"+NNMI")) {
        
        isAsyn = addr_adjust(buf, position_addr_start, len);
        bc95_SetEvent(NB_COAP_RECE_EVENT);
    }
    return isAsyn;
}


//处理串口返回的数据, 重要, 是uart(bc95串口)接收下行数据的接口
static void bc95_SerialReceCallBack(char* buf, uint16_t len)
{
    if (len == 0)
        return;
    //printf("len:%d", len);
    if (!bc95_AsynNotification(buf, &len))
    {
        if (len == 0)
            return;
        //printf("<-::%s", buf);
        if ((NBCmdBufRec.len + len) < NB_CMD_RECE_BUF_MAX_LEN) {
            memcpy(NBCmdBufRec.buf + NBCmdBufRec.len, buf, len);
            NBCmdBufRec.len += len;
        }
        bc95_SetEvent(NB_SP_RECE_EVENT);
    }
}

static void bc95_SetEvent(int eventID)
{
    bc95_event_reg |= eventID;
}

static void bc95_TimerOutCallback(void)
{
    bc95_SetEvent(NB_TIMEOUT_EVENT);
}

void InitATcmd(atcmdInfo cmdinfo, const char* cmd, char* param, cmd_type property) 
{
    if (cmdinfo == NULL)
        return;

    cmdinfo->NBcmd = cmd;
    cmdinfo->NBcmdParameter = param;
    cmdinfo->property = property;
    cmdinfo->cmd_action = ACTION_OK_NEXT_ERROR_TRY;
    cmdinfo->max_timeout = 2000;
    cmdinfo->expectReply = "";
    cmdinfo->cmd_try = 10;
    cmdinfo->havetried = 0;
    cmdinfo->repeatPeri = 200;
}


uint16_t formatATcmd(atcmdInfo cmdinfo) 
{
    uint16_t cmdlen = 0;
    if (cmdinfo == NULL)
        return cmdlen;
    memset(NBCmdBufSend.buf, 0, NB_CMD_SEND_BUF_MAX_LEN);
    NBCmdBufSend.len = 0;
    if (cmdinfo->property == CMD_TEST)
        cmdlen = snprintf(NBCmdBufSend.buf, NB_CMD_SEND_BUF_MAX_LEN, "%s=?\r\n", cmdinfo->NBcmd);
    else if (cmdinfo->property == CMD_READ)
        cmdlen = snprintf(NBCmdBufSend.buf, NB_CMD_SEND_BUF_MAX_LEN, "%s?\r\n", cmdinfo->NBcmd);
    else if (cmdinfo->property == CMD_SET)
        cmdlen = snprintf(NBCmdBufSend.buf, NB_CMD_SEND_BUF_MAX_LEN, "%s=%s\r\n", cmdinfo->NBcmd, cmdinfo->NBcmdParameter);
    else if (cmdinfo->property == CMD_EXCUTE)
        cmdlen = snprintf(NBCmdBufSend.buf, NB_CMD_SEND_BUF_MAX_LEN, "%s\r\n", cmdinfo->NBcmd);
    NBCmdBufSend.len = cmdlen;
    return cmdlen;  
}


unsigned char openNBModule(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->Openbc95 == NULL)
        return 0;
    bc95->funcPtr = (void*)&bc95fun;
    bc95->funcPtr->Openbc95(bc95);
    return 1;
}

uint8_t openbc95(NBModule bc95)
{
    bc95object bc95Obj = (bc95object)bc95->object;
//    if (nb_state.state != PROCESS_NONE)
//        return 0;
    bc95_event_reg = 0;
    ResetState();
    ResetReceBuf();
    bc95Obj->SPfunTable->serialPortOpen(bc95_SerialReceCallBack, bc95Obj->baundrate);
    bc95Obj->timerFun->bc95_TimerInitFun(bc95_TimerOutCallback);
    return 1;
}


unsigned char initNBModule(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->Initbc95 == NULL) 
        return 0;
    return bc95->funcPtr->Initbc95(bc95);
}

uint8_t initbc95(NBModule bc95)
{
//    uint8_t cmdlen = 0;
//    atcmdInfo cmdinfo;
//    bc95object bc95_handle = (bc95object)bc95->object;
//    InitATcmd(cmdinfo, "AT", "", CMD_EXCUTE);
//    cmdlen = formatATcmd(cmdinfo);
//    NBbc95SendCMD(bc95_handle, cmdinfo);
//    return 1;
    
    bc95object bc95Obj = (bc95object)bc95->object;
    if (nb_state.state != PROCESS_NONE)
        return 0;
    InitATcmd(&atcmd, AT, NULL, CMD_EXCUTE);
    nb_state.state = PROCESS_INIT;
    nb_state.sub_state = 1;
    atcmd.max_timeout = 2000;
    NBbc95SendCMD_Usart(bc95Obj, &atcmd);
    return 1;   
}


int SignNBModule(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->isNetSign == NULL)
        return 0;
    return bc95->funcPtr->isNetSign(bc95);
}


int isNetSign_bc95(NBModule bc95)
{
    bc95object bc95Obj = (bc95object)bc95->object;
    if (nb_state.state != PROCESS_NONE)
        return 0;
    InitATcmd(&atcmd, AT_CSQ, NULL, CMD_EXCUTE);
    atcmd.cmd_try = 1;
    nb_state.state = PROCESS_SIGN;
    nb_state.sub_state = 1;
    atcmd.max_timeout = 2000;
    NBbc95SendCMD_Usart(bc95Obj, &atcmd);
    return 1;   
}

extern int getModuleInfoNBModule(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->getModuleInfo == NULL)
        return 0;
    return bc95->funcPtr->getModuleInfo(bc95);
}

int getModuleInfo_bc95(NBModule bc95)
{
    bc95object bc95Obj = (bc95object)bc95->object;
    if (nb_state.state != PROCESS_NONE)
        return 0;
    InitATcmd(&atcmd, AT_CGMI, NULL, CMD_EXCUTE);
    atcmd.cmd_try = 1;
    nb_state.state = PROCESS_MODULE_INFO;
    nb_state.sub_state = 1;
    atcmd.max_timeout = 1000;
    NBbc95SendCMD_Usart(bc95Obj, &atcmd);
    return 1;   
}


const char* getRegisterInfo_bc95(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->getRegisterInfo == NULL)
        return 0;
    return bc95->funcPtr->getRegisterInfo(bc95);
}

const char* getMISIInfo_bc95(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->getMISIInfo == NULL)
        return 0;
    return bc95->funcPtr->getMISIInfo(bc95);
}


uint8_t createUDPServer_bc95(NBModule bc95)
{
    bc95object bc95Obj = (bc95object)bc95->object;
    if (nb_state.state != PROCESS_NONE)
        return 0;
    InitATcmd(&atcmd, AT_NSOCR, LOCAL_UDP_SET, CMD_SET);
    atcmd.cmd_try = 1;
    //atcmd.max_timeout = 2000;
    atcmd.cmd_action = ACTION_OK_EXIT_ERROR_NEXT;
    nb_state.state = PROCESS_UDP_CREATE;
    nb_state.sub_state = 1;
    NBbc95SendCMD_Usart(bc95Obj, &atcmd);
    return 1;
}


uint8_t createUDPServerNBModule(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->CreateUDPServer == NULL)
        return 0;
    return bc95->funcPtr->CreateUDPServer(bc95);
}

uint8_t sendToUdp_bc95(NBModule bc95, int len, char* msg)
{
    bc95object bc95Obj = (bc95object)bc95->object;
    if (nb_state.state != PROCESS_NONE)
        return 0;
    if (bc95_status.UDP_ID[0] < '0' || bc95_status.UDP_ID[0] > '6')
        return 0;
    uint16_t maxLen = (NB_CMD_SEND_BUF_MAX_LEN - 40) >> 1;
    uint16_t strLen = 0;
    char buf[NB_CMD_SEND_BUF_MAX_LEN - 40];
    memset(buf, 0, NB_CMD_SEND_BUF_MAX_LEN - 40);
    if (len > maxLen)
        strLen = maxLen;
    else 
        strLen = len;
    uint16_t msgLen = snprintf(buf, NB_CMD_SEND_BUF_MAX_LEN - 40,
                               "%s,%s,%s,%d,", bc95_status.UDP_ID,
                               REMOTE_SERVER_IP, REMOTE_SERVER_PORT, strLen);
    for (uint16_t i = 0; i < strLen; i++)
        //sprintf(&buf[msgLen + (i << 1)], "%02X", (uint8_t)msg[i]);
        sprintf(&buf[msgLen + (i << 1)], "%02X", (unsigned char)msg[i]);
    InitATcmd(&atcmd, AT_NSOST, buf, CMD_SET);
    atcmd.max_timeout = 5000;
    nb_state.state = PROCESS_UDP_SEND;
    nb_state.sub_state = 1;
    NBbc95SendCMD_Usart(bc95Obj, &atcmd);
    return 1;
}

uint8_t sendToUdpNBModule(NBModule bc95, int len, char* buf)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->SendToUdp == NULL)
        return 0;
    return bc95->funcPtr->SendToUdp(bc95, len, buf);
}

uint8_t closeUdp_bc95(NBModule bc95)
{
    bc95object bc95Obj = (bc95object)bc95->object;
    if (nb_state.state != PROCESS_NONE)
        return 0;
    if (bc95_status.UDP_ID[0] < '0' || bc95_status.UDP_ID[0] > '6')
        return 0;
    InitATcmd(&atcmd, AT_NSOCL, bc95_status.UDP_ID, CMD_SET);
    nb_state.state = PROCESS_UDP_CLOSE;
    nb_state.sub_state = 1;
    NBbc95SendCMD_Usart(bc95Obj, &atcmd);
    return 1;
}

uint8_t closeUdpNBModule(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->CloseUdp == NULL)
        return 0;
    return bc95->funcPtr->CloseUdp(bc95);
}


uint8_t recFromUdp_bc95(NBModule bc95)
{
    bc95object bc95Obj = (bc95object)bc95->object;
    if (nb_state.state != PROCESS_NONE)
        return 0;
    uint16_t maxLen = (NB_CMD_RECE_BUF_MAX_LEN - 40) >> 1;
    uint16_t readLen = maxLen;
    
    if (bc95_status.UDP_Len.ReceDataLen < maxLen)
        readLen = bc95_status.UDP_Len.ReceDataLen;
    
    char buf[10];
    maxLen = snprintf(buf, 10, "%d,%d", bc95_status.UDP_Len.socketID, readLen);
    buf[maxLen] = 0;
    InitATcmd(&atcmd, AT_NSORF, buf, CMD_SET);
    
    nb_state.state = PROCESS_UDP_RECE;
    nb_state.sub_state = 1;
    NBbc95SendCMD_Usart(bc95Obj, &atcmd);
    return 1;
}


uint8_t coapServer_bc95(NBModule bc95, unsigned char isSet, char* coap)
{
    bc95object bc95Obj = (bc95object)bc95->object;
    char* buf = NULL;
    if (nb_state.state != PROCESS_NONE)
        return 0;
    if (isSet) {
        if (coap == NULL)
            buf = REMOTE_COAP_INFO;
        else 
            buf = coap;
        InitATcmd(&atcmd, AT_NCDP, buf, CMD_SET);
    }
    else
        InitATcmd(&atcmd, AT_NCDP, "?", CMD_READ);
    
    nb_state.state = PROCESS_COAP;
    nb_state.sub_state = 1;
    NBbc95SendCMD_Usart(bc95Obj, &atcmd);
    return 1;
}


uint8_t coapServerNBModule(NBModule bc95, unsigned char isSet, char* coap)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->CoapServer == NULL)
        return 0;
    return bc95->funcPtr->CoapServer(bc95, isSet, coap);
}

//code = 1 ->响应信息;  code = 0 ->不做任何反应
uint8_t coapSentIndication_bc95(NBModule bc95, int code)
{
    return 1;
}


uint8_t coapSentIndicationNBModule(NBModule bc95, int code)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->CoapSentIndication == NULL)
        return 0;
    return bc95->funcPtr->CoapSentIndication(bc95, code);
}

//code = 1 ->直接接收;  code = 0 ->表示缓存
uint8_t coapReceIndication_bc95(NBModule bc95, int code)
{
    return 1;
}


uint8_t coapReceIndicationNBModule(NBModule bc95, int code)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->CoapReceIndication == NULL)
        return 0;
    return bc95->funcPtr->CoapReceIndication(bc95, code);
}

uint8_t coapSentMsg_bc95(NBModule bc95, int len, char* msg)
{
    bc95object bc95Obj = (bc95object)bc95->object;
    if (nb_state.state != PROCESS_NONE)
        return 0;
    
    //判断Socket ID是否正确
    uint16_t maxLen = (NB_CMD_SEND_BUF_MAX_LEN - 40) >> 1;
    uint16_t strLen = 0;
    
    char buf[NB_CMD_SEND_BUF_MAX_LEN - 40];
    memset(buf, 0, NB_CMD_SEND_BUF_MAX_LEN - 40);
    if (len > maxLen)
        strLen = maxLen;
    else
        strLen = len;
    uint16_t msgLen = snprintf(buf, NB_CMD_SEND_BUF_MAX_LEN - 40, "%d,", strLen);
    for (uint16_t i = 0; i < strLen; i++)
        sprintf(&buf[msgLen + (i << 1)], "%02X", (unsigned char)msg[i]);
    
    InitATcmd(&atcmd, AT_NMGS, buf,CMD_SET);
    atcmd.max_timeout = 6000;
    
    nb_state.state = PROCESS_COAP_SEND;
    nb_state.sub_state = 1;
    NBbc95SendCMD_Usart(bc95Obj, &atcmd);
    return 1;
}


uint8_t coapSentMsgNBModule(NBModule bc95, int len, char* msg)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->CoapSentMsg == NULL)
        return 0;
    return bc95->funcPtr->CoapSentMsg(bc95, len, msg);
}

uint8_t recFromCoap_bc95(NBModule bc95)
{
    bc95object bc95Obj = (bc95object)bc95->object;
    if (nb_state.state != PROCESS_NONE)
        return 0;

    //主动查询方式
    InitATcmd(&atcmd, AT_NMGR, NULL, CMD_EXCUTE);
    
    nb_state.state = PROCESS_COAP_RECE;
    nb_state.sub_state = 1;
    NBbc95SendCMD_Usart(bc95Obj, &atcmd);
    return 1;
}


static int8_t cmdIsPass(char *buf)
{
    int8_t result = -1;
    if (atcmd.expectReply == NULL) {
        if (strstr(buf, "OK")) 
            result = 1;
        else if (strstr(buf, "ERROR"))
            result = 0;
    }
    else {
        if (strstr(buf, "OK")) {
            if (strstr(buf, atcmd.expectReply))
                result = 1;
            else 
                result = 0;
        }
        else if (strstr(buf, "ERROR"))
            result = 0;
    }
    return result;
}

static void NBStopTimer(bc95object bc95Obj)
{
    if (atcmd.max_timeout)
        bc95Obj->timerFun->bc95_TimerStopFun();
}

uint16_t NBHexStrToNum(char *str)
{
    uint16_t i = 0;
    uint16_t len = strlen(str);
    uint8_t temp1, temp2;
    for(i = 0; i < len; i++) {
        if (str[i] > '0' && str[i] < '9')
            temp1 = str[i] - '0';
        else if (str[i] > 'a' && str[i] < 'f')
            temp1 = str[i] - 'a' + 10;
        else if (str[i] > 'A' && str[i] < 'F')
            temp1 = str[i] - 'A' + 10;
        else 
            temp1 = 0;
        if (i % 2 == 0)
            temp2 = temp1;
        else 
        {
            temp2 <<= 4;
            temp2 += temp1;
            str[i >> i] = temp2;
        }
    }
    str[i >> 1] = 0;
    return (i >> 1);
}

void NBSendMsg(NBModule bc95, char **buf, unsigned char isOK)
{
    if (bc95 == NULL)
        return;
    if (isOK == 0) {
        bc95->recMsg_Callback((msg_type)nb_state.state, 1, "F");
        return;
    }
    if (nb_state.state == PROCESS_INIT) {
        switch (bc95InitProcess[nb_state.sub_state]) {
            case ACTION_SYNC:
                break;
            case ACTION_CMEE:
                break;
            case ACTION_CFUN:
                break;
//            case ACTION_CGMI:
//            {
//                memcpy(bc95_status.ManuFacID, buf[0], 8);
//                bc95->recMsg_Callback((msg_type)TYPES_CGMI, strlen(buf[0]), buf[0]);
//            }
//            break;
//            case ACTION_CGMM:
//            {
//                memcpy(bc95_status.ModuleInfo, buf[0], 8);
//                bc95->recMsg_Callback((msg_type)TYPES_CGMM, strlen(buf[0]), buf[0]);
//            }
//            break;
//            case ACTION_CGMR:
//                break;
//            case ACTION_NBAND:
//                break;
//            case ACTION_NCONFIG:
//                break;
            case ACTION_CIMI:
            {
                memcpy(bc95_status.IMSI, buf[0], 15);
                bc95_status.IMSI[15] = 0;
                bc95->recMsg_Callback((msg_type)TYPES_CIMI, strlen(buf[0]), buf[0]);
            }
            break;
            case ACTION_CGSN:
            {
                char* pColon = strchr(buf[0], ':');
                if (pColon) {
                    pColon++;
                    memcpy(bc95_status.IMEI, pColon, 15);
                    bc95_status.IMEI[15] = 0;
                    bc95->recMsg_Callback((msg_type)TYPES_CGSN, 15, (char*)bc95_status.IMEI);
                }
                break;
            }
            case ACTION_CEREG:
                break;
            case ACTION_CSCON:
                break;
            case ACTION_CGATT:
                break;
            case ACTION_CGATT_QUERY:
                break;
            //case action_
            case ACTION_END:
                bc95->recMsg_Callback((msg_type)PROCESS_INIT, 1, "S");
                break;
        }
    }
    else if (nb_state.state == PROCESS_MODULE_INFO) {
        switch (bc95InitProcess[nb_state.sub_state]) {
            case ACTION_CGMI:
                bc95->recMsg_Callback((msg_type)TYPES_CGMI, strlen(buf[0]), buf[0]);
                break;
            case ACTION_CGMM:
                bc95->recMsg_Callback((msg_type)TYPES_CGMM, strlen(buf[0]), buf[0]);
                break;
            case ACTION_CGMR:
            {
                char* pCmd = strchr(buf[0], ',');
                if (pCmd) {
                    pCmd++;
                    bc95->recMsg_Callback((msg_type)TYPES_CGMR, strlen(pCmd), pCmd);
                }
                break;
            }
            case ACTION_NBAND:
            {
                char* pColon = strchr(buf[0], ':');
                char* pFreq = NULL;
                if (pColon) {
                    pColon++;
                    uint8_t hz_id = NB_Strtoul(pColon, 10);
                    if (hz_id == BAND_700MHZ_ID)
                        pFreq = BAND_700MHZ_STR;
                    else if (hz_id == BAND_800MHZ_ID)
                        pFreq = BAND_800MHZ_STR;
                    else if (hz_id == BAND_850MHZ_ID)
                        pFreq = BAND_850MHZ_STR;
                    else if (hz_id == BAND_900MHZ_ID)
                        pFreq = BAND_900MHZ_STR;
                    bc95->recMsg_Callback((msg_type)TYPES_NBAND, strlen(pFreq), pFreq);
                }
                break;
            }
            case ACTION_END:
                bc95->recMsg_Callback((msg_type)PROCESS_MODULE_INFO, 1, "S");
                break;
        }
    }
    else if (nb_state.state == PROCESS_REGISTER) {
        if (nb_state.sub_state == 1) {
            char* pColon = strchr(buf[0], ':');
            pColon++;
            uint8_t lqi = NB_Strtoul(pColon, 10);
            int8_t rssi = -113 + (lqi << 1);
            uint8_t len = snprintf(buf[0], 10, "%d", rssi);
            *(buf[0] + len) = 0;
            bc95->recMsg_Callback((msg_type)PROCESS_REGISTER, len, buf[0]);
        }
    }
    else if (nb_state.state == PROCESS_UDP_CREATE) {
        switch(bc95UDPCreateProcess[nb_state.sub_state]) {
            case ACTION_UDP_CREATE:
            {
                memcpy(bc95_status.UDP_ID, buf[0], 2);
                if (nb_state.sub_state == 1) {
                    bc95->recMsg_Callback((msg_type)PROCESS_UDP_CREATE, 1, "S");
                }
            }
            break;
            case ACTION_UDP_CLOSE:
                break;
            case ACTION_END:
                bc95->recMsg_Callback((msg_type)PROCESS_UDP_CREATE, 1, "S");
                break;
        }
    }
    else if (nb_state.state == PROCESS_UDP_CLOSE) {
        switch(bc95UDPCreateProcess[nb_state.sub_state]) {
            case PROCESS_UDP_CLOSE:
            {
                bc95_status.UDP_ID[0] = 0;
                bc95_status.UDP_ID[1] = 0;
            }
            break;
            case ACTION_END:
                bc95->recMsg_Callback((msg_type)PROCESS_UDP_CLOSE, 1, "S");
                break;
        }
    }
    else if (nb_state.state == PROCESS_UDP_SEND) {
        switch(bc95UDPCreateProcess[nb_state.sub_state]) {
            case PROCESS_UDP_SEND:
                bc95->recMsg_Callback((msg_type)PROCESS_UDP_SEND, 1, "S");
                break;
        }
    }
    else if (nb_state.state == PROCESS_UDP_RECE) {
        if (nb_state.sub_state == 1) {
            char *param[6];
            uint16_t index = 0;
            char *tempBuf = buf[0];
            while ((param[index] == strtok(tempBuf, ",")) != NULL) {
                index++;
                tempBuf = NULL;
                if (index >= 6)
                    break;
                if (index != 6) {
                    bc95->recMsg_Callback((msg_type)PROCESS_UDP_RECE, 1, "F");
                    return;
                }
                tempBuf = param[4];
                index = NBHexStrToNum(tempBuf);
                bc95->recMsg_Callback((msg_type)PROCESS_UDP_RECE, index, tempBuf);
            }
        }
    }
    else if (nb_state.state == PROCESS_COAP) {
        if (nb_state.sub_state == 1) {
            char* tempBuf = NULL;
            if (strstr(buf[0], "OK"))
                tempBuf = "S";
            else {
                tempBuf = strchr(buf[1], ':');
                if (tempBuf)
                    tempBuf++;
            }
            bc95->recMsg_Callback((msg_type)PROCESS_COAP, strlen(tempBuf),tempBuf);
        }
        else if (nb_state.state == PROCESS_COAP_SEND) {
            if (nb_state.sub_state == 1)
                bc95->recMsg_Callback((msg_type)PROCESS_COAP_SEND, 1, "S");
        }
        else if (nb_state.state == PROCESS_COAP_RECE) {
            if (nb_state.sub_state == 1) {
                uint16_t index = 0;
                char* tempBuf = NULL;
                tempBuf = strchr(buf[0], ',');
                if (tempBuf) {
                    tempBuf++;
                    index = NBHexStrToNum(tempBuf);
                    bc95->recMsg_Callback((msg_type)PROCESS_COAP_RECE, index, tempBuf);
                }
            }
        }
    }
}

//AT指令出错处理
unsigned char bc95ResultHandle(NBModule bc95, unsigned char isOK)
{
    unsigned char isNext = 0;
    bc95object bc95Obj = (bc95object)bc95->object;
    if (isOK) {
        if (atcmd.cmd_action == ACTION_OK_NEXT_ERROR_TRY)
            isNext = 1;
        else 
            ResetState();
    }
    else {
        if (atcmd.cmd_action == ACTION_OK_NEXT_ERROR_TRY) {
            atcmd.havetried++;
            if (atcmd.havetried < atcmd.cmd_try) {
                bc95Obj->SPfunTable->serialPortSend((uint8_t*)NBCmdBufSend.buf, NBCmdBufSend.len);
                if (atcmd.max_timeout)
                    bc95Obj->timerFun->bc95_TimerStartFun(atcmd.max_timeout);
            }
            else {
                NBSendMsg(bc95, NULL, 0);
                ResetState();
            }
        }
        else if (atcmd.cmd_action == ACTION_OK_EXIT_ERROR_NEXT)
            isNext = 1;
    }
    return isNext;
}

//产生下一条AT指令
static unsigned char GotoNextCmd(void)
{
    if (nb_state.state == PROCESS_INIT) {
        nb_state.sub_state++;
        if (bc95InitProcess[nb_state.sub_state] == ACTION_END)
            return 0;
        switch (bc95InitProcess[nb_state.sub_state]) {
            case ACTION_CMEE:
                InitATcmd(&atcmd, AT_CMEE, "1", CMD_SET);
                break;
            case ACTION_CFUN:
                InitATcmd(&atcmd, AT_CFUN, "1", CMD_SET);
                atcmd.max_timeout = 10000;
                break;
            case ACTION_CIMI:
                InitATcmd(&atcmd, AT_CIMI, NULL, CMD_EXCUTE);
                break;
            case ACTION_CGSN:
                InitATcmd(&atcmd, AT_CGSN, "1", CMD_SET);
                break;
            case ACTION_CEREG:
                InitATcmd(&atcmd, AT_CEREG, "1", CMD_SET);
                break;
            case ACTION_CSCON:
                InitATcmd(&atcmd, AT_CSCON, "1", CMD_SET);
                break;
            case ACTION_CGATT:
                InitATcmd(&atcmd, AT_CGATT, "1", CMD_SET);
                atcmd.max_timeout = 2000;
                atcmd.repeatPeri = 1;//true
                break;
            case ACTION_CGATT_QUERY:
                InitATcmd(&atcmd, AT_CGATT, NULL, CMD_READ);
                atcmd.max_timeout = 2000;
                atcmd.repeatPeri = 1;
                atcmd.cmd_try = 100;
                atcmd.expectReply = "CGATT:1";
                break;
            //coap 
            case ACTION_NSMI:
                InitATcmd(&atcmd, AT_NSMI, "1", CMD_SET);
                break;
            //coap 被动异步通知, 接受下行数据
            case ACTION_NNMI:
                InitATcmd(&atcmd, AT_NNMI, "2", CMD_SET);
                break;
        }
    }
    else if (nb_state.state == PROCESS_MODULE_INFO) {
        nb_state.sub_state++;
        if (bc95InitProcess[nb_state.sub_state] == ACTION_END)
            return 0;
        switch (bc95InitProcess[nb_state.sub_state]) {
            case ACTION_CGMM:
                InitATcmd(&atcmd, AT_CGMM, NULL, CMD_EXCUTE);
                break;
            case ACTION_CGMR:
                InitATcmd(&atcmd, AT_CGMR, NULL, CMD_EXCUTE);
                break;
            case ACTION_NBAND:
                InitATcmd(&atcmd, AT_NBAND, NULL, CMD_READ);
                break;
        }
    }
    else if (nb_state.state == PROCESS_UDP_CREATE) {
        nb_state.sub_state++;
        if (bc95UDPCreateProcess[nb_state.sub_state] == ACTION_END)
            return 0;
        switch (bc95UDPCreateProcess[nb_state.sub_state]) {
            case ACTION_UDP_CLOSE:
                InitATcmd(&atcmd, AT_NSOCL, "0", CMD_SET);
                break;
            case ACTION_UDP_CREATE:
                InitATcmd(&atcmd, AT_NSOCR, LOCAL_UDP_SET, CMD_SET);
                break;
        }
    }
    else if (nb_state.state == PROCESS_UDP_CLOSE) {
        nb_state.sub_state++;
        return 0;
    }
    else if (nb_state.state == PROCESS_UDP_SEND) {
        nb_state.sub_state++;
        return 0;
    }
    else if (nb_state.state == PROCESS_UDP_RECE) {
        nb_state.sub_state++;
        return 0;
    }
    else if (nb_state.state == PROCESS_COAP) {
        nb_state.sub_state++;
        return 0;
    }
    else if (nb_state.state == PROCESS_COAP_SEND) {
        nb_state.sub_state++;
        return 0;
    }
    else if (nb_state.state == PROCESS_COAP_RECE) {
        nb_state.sub_state++;
        return 0;
    }
    return 1;
}



uint8_t NBModuleMain(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->BC95Main == NULL)
        return 0;
    return bc95->funcPtr->BC95Main(bc95);
}


uint8_t bc95Main(NBModule bc95)
{
    bc95object bc95Obj = (bc95object)bc95->object;
    unsigned char isNext = 0;
    if (bc95_event_reg & NB_SP_RECE_EVENT) {
        char *tempBuf = NBCmdBufRec.buf;
        char *param[15];
        uint8_t index = 0;
        int8_t isPass;
        
        //判断命令是否执行成功
        isPass = cmdIsPass(NBCmdBufRec.buf);
        
        if ((isPass >= 0) && (isPass <= 1)) {
            //命令执行完毕，停止定时器
            if (atcmd.repeatPeri == 0 || isPass == 1) 
                NBStopTimer(bc95Obj);
            //用\r\n将接收到的命令分割并存入param数组
            while ((param[index] = strtok(tempBuf, "\r\n")) != NULL) {
                index++;
                tempBuf = NULL;
                //一次性不超过15条返回的命令
                if (index >= 15)
                    break;
            }
            if (index == 0)
                return 0;
        }
        
        //如果命令执行成功
        if (isPass == 1) {
            NBSendMsg(bc95, param, 1);
            isNext = bc95ResultHandle(bc95, 1);
            ResetReceBuf();
        }
        else if (isPass == 0) {
            if (atcmd.repeatPeri == 0) 
                isNext = bc95ResultHandle(bc95, 0);
            ResetReceBuf();
        }
        else {
            //指令未执行完
        }
        bc95_event_reg ^= NB_SP_RECE_EVENT;
    }
    if (bc95_event_reg & NB_TIMEOUT_EVENT) {
        ResetReceBuf();
        isNext = bc95ResultHandle(bc95, 0);
        bc95_event_reg ^= NB_TIMEOUT_EVENT;
    }
    if (bc95_event_reg & NB_UDP_RECE_EVENT) {
        if (recFromUdp_bc95(bc95) == 1)
            bc95_event_reg ^= NB_UDP_RECE_EVENT;
    }
    if (bc95_event_reg & NB_COAP_RECE_EVENT) {
        if (recFromUdp_bc95(bc95) == 1) //需要修改
            bc95_event_reg ^= NB_COAP_RECE_EVENT;
    }
    if (bc95_event_reg & NB_REG_STA_EVENT) {
        bc95->recMsg_Callback((msg_type)PROCESS_REGISTER, 1, 
                              (char*)&bc95_status.registerStatus);
        bc95_event_reg ^= NB_REG_STA_EVENT;
    }
    if (isNext) {
        if (GotoNextCmd())
            NBbc95SendCMD_Usart(bc95Obj, &atcmd);
        else {
            NBSendMsg(bc95, NULL, 1);
            ResetState();
        }
    }
    return 1;
}

void NBbc95SendCMD_Usart(bc95object bc95, atcmdInfo cmdinfo) 
{
    int cmdLen = 0;
    if (bc95 == NULL || cmdinfo == NULL)
        return;
    cmdLen = formatATcmd(cmdinfo);
    bc95->SPfunTable->serialPortSend((uint8_t*)NBCmdBufSend.buf, cmdLen);
    if (cmdinfo->max_timeout)
        bc95->timerFun->bc95_TimerStartFun(atcmd.max_timeout);
}












