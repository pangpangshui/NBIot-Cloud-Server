#include "NBBC95_cfg.h"
#include "stm32f1xx_hal.h"
#include "uartTimerPoll.h"


bc95_TimerFun UartTimerFun = {
    .bc95_TimerInitFun = TimerSet,
    .bc95_TimerStartFun = TimerStart,
    .bc95_TimerStopFun = TimerStop
};


serialfun Serial_fun = {
    .serialPortOpen = HAL_DMA_UsartInit,
    .serialPortSend = HAL_USART_Write,
    .serialPortClose = HAL_USART_Close
};


bc95Module HWAtrrs_object = {
    .baundrate = 9600,
    .SPfunTable = &Serial_fun,
    .timerFun = &UartTimerFun
};

NBbc95 bc95_cfg = {
    .funcPtr = NULL,
    .object = (void*)&HWAtrrs_object,
    .recMsg_Callback = NB_MsgreportCallback
};

