#include "NBBC95.h"
#include <string.h>

const char* AT          =   "AT";
const char* AT_CMEE		=	"AT+CMEE";   //上报设备错误。启用结果码，使用数字型取值，参数为1
const char* AT_CGMI		=	"AT+CGMI";			//查询设备制造商信息
const char* AT_CGMM		=	"AT+CGMM";			//查询设备ID
const char* AT_CGMR		=	"AT+CGMR";			//查询设备固件版本
const char* AT_NBAND	=	"AT+NBAND?";		//查询模块是否支持band
const char* AT_NCONFIG	=   "AT+NCONFIG?";	//查询用户配置
const char* AT_CGSN	    =	"AT+CGSN";		//查询IMEI,参数为1
const char* AT_CIMI		=	"AT+CIMI";			//查询IMSI
const char* AT_CGATT1	=	"AT+CGATT";	//附着(1)GPRS网络,参数为1
const char* AT_CGATT0	=	"AT+CGATT";	//分离(0)GPRS网络，参数为0
const char* AT_CGATT	=	"AT+CGATT?";		//查询附着状态, 需等待几秒
const char* AT_CSQ		=	"AT+CSQ";			//查询信号强度
const char* AT_COPS		=	"AT+COPS?";		//查询注册模式和运营商
const char* AT_CEREG	=	"AT+CEREG?";		//查询注册状态,返回1表示已注册本地网络
const char* AT_NUESTATS	=   "AT+NUESTATS";	//获取最新的操作统计


const NBOperaFun bc95fun = {
    .Openbc95           =  openbc95,
    .Initbc95           =  initbc95,
    .CreateUDPServer    =  createUDPServer_bc95,
    .SendToUdp          =  sendToUdp_bc95,
    .RecFromUdp         =  recFromUdp_bc95,
    .BC95Main           =  bc95Main
};

#define NB_CMD_SEND_BUF_MAX_LEN 512
#define NB_CMD_RECE_BUF_MAX_LEN 512

struct CmdBufSend{
    char buf[NB_CMD_SEND_BUF_MAX_LEN];
    uint16_t len;
}NBCmdBufSend;
//NBCmdBufSend CmdbufSend;

struct CmdBufRec{
    char buf[NB_CMD_RECE_BUF_MAX_LEN];
    uint16_t len;
}NBCmdBufRec;




extern NBOperaFun bc95_OperaFun;
static bc95_state nb_state = {PROCESS_NONE, 0};
static ATcmd atcmd;

void InitATcmd(atcmdInfo cmdinfo, const char* cmd, char* param, cmd_type property) 
{
    cmdinfo->NBcmd = cmd;
    cmdinfo->NBcmdParameter = param;
    cmdinfo->property = property;
    cmdinfo->max_timeout = 2000;
    cmdinfo->expectReply = "";
    cmdinfo->cmd_try = 5;
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


uint8_t openbc95(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->Openbc95 == NULL)
        return 0;
    bc95->funcPtr = (void*)&bc95fun;
    bc95->funcPtr->Openbc95(bc95);
    return 1;
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

const char* getModuleInfo_bc95(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->getModuleInfo == NULL)
        return 0;
    return bc95->funcPtr->getModuleInfo(bc95);
    
}


const char* getRegisterInfo_bc95(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->getRegisterInfo == NULL)
        return 0;
    return bc95->funcPtr->getRegisterInfo(bc95);
}

const char* NetSign_bc95(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->getMISIInfo == NULL)
        return 0;
    return bc95->funcPtr->getMISIInfo(bc95);
}


uint8_t isNetSign_bc95(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->isNetSign == NULL)
        return 0;
    return bc95->funcPtr->isNetSign(bc95);
}

uint8_t createUDPServer_bc95(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->CreateUDPServer == NULL)
        return 0;
    return bc95->funcPtr->CreateUDPServer(bc95);
}

uint8_t sendToUdp_bc95(NBModule bc95, int len, char* buf)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->SendToUdp == NULL)
        return 0;
    return bc95->funcPtr->SendToUdp(bc95, len, buf);
}

uint8_t recFromUdp_bc95(NBModule bc95)
{
    return 0;
}

uint8_t closeUdp_bc95(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->CloseUdp == NULL)
        return 0;
    return bc95->funcPtr->CloseUdp(bc95);
}

uint8_t bc95Main(NBModule bc95)
{
    if (bc95 == NULL)
        return 0;
    if (bc95->funcPtr->BC95Main == NULL)
        return 0;
    return bc95->funcPtr->BC95Main(bc95);
}

uint8_t NBbc95SendCMD_Usart(bc95object bc95, atcmdInfo cmdinfo) 
{
    bc95->SPfunTable->serialPortSend((uint8_t*)NBCmdBufSend.buf, NBCmdBufSend.len);
    return 0;
}







