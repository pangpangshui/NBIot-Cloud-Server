#ifndef __DMA_FUN_H__
#define __DMA_FUN_H__
#ifdef __cpluscplus
extern C {
#endif

#include "stm32f1xx_hal.h"
    
    
#define SEND_BUF_MAX_SIZE   256
#define RECE_BUF_MAX_SIZE   128
    
    
#define HAL_USART_RX_FULL       0X01
#define HAL_USART_RX_TIMEOUT    0X02
    
typedef struct DMA_Rece_Config {
    uint16_t recBuf[RECE_BUF_MAX_SIZE]; //缓冲区大小
    uint16_t rxHead;                    //有效数据头部
    uint16_t rxEnd;                     //最后一次数据末尾
    uint8_t  rxTimeoutTick;             //超时时间,ms
    uint32_t rxTimeoutCount;            //超时计数开始数值
    
    uint8_t  sendBuf[2][SEND_BUF_MAX_SIZE];//发送缓冲区
    uint8_t  txIdx[2];
    uint8_t  txSel;
    uint8_t  txTimeoutTick;
    volatile uint32_t txTimeoutCount;
    volatile uint8_t  txTimeoutCountValid;  //txTimeoutCount是否有效
    uint8_t  txDMApending;              //
}dmaRec_cfg;


typedef void (*sendData_Callback)(uint8_t *buf, uint16_t len);


//初始化dmaRec_cfg结构，返回rx Buffer
extern uint8_t* usartDMA_Init(sendData_Callback, USART_TypeDef*);

//从接收缓冲区里面读取指定长度的数据，并释放占用空间
extern uint16_t usartDMA_Read(uint8_t *buf, uint16_t len);

//将要发送的数据拷贝到指定缓冲区里
extern uint16_t usartDMA_Write(uint8_t *buf, uint16_t len);

//计算缓冲区数据个数
extern uint16_t usartDMA_Avail(void);

//找到当前DMA接收缓冲区正在操作的位置
static uint16_t findTail(void);

//轮询接收缓冲区数据长度
extern uint8_t usartDMA_Poll_RecAvail(void);

#ifdef __cpluscplus
}
#endif

#endif

