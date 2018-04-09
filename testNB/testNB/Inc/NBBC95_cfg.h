#ifndef __NBBC95_CFG_H__
#define __NBBC95_CFG_H__

//切不可乱包含头文件，容易造成相互包含找不到函数定义或者变量定义
//#include "NBBC95.h"
#include "usart.h"



extern NBbc95 bc95_cfg;
extern int NB_MsgreportCallback(msg_type, int, char*);



#endif

