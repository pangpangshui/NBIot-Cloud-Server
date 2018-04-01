#ifndef NBBC95_CFG_H
#define NBBC95_CFG_H

#include "NBBC95.h"


extern int NB_MsgreportCallback(msg_type, int, char*);

serialfun Serial_fun = {
    .serialPortOpen = HAL_DMA_UsartInit,
    .serialPortSend = HAL_USART_Write,
    .serialPortClose = HAL_USART_Close
};


bc95Module HWAtrrs_object = {
    .baundrate = 9600,
    .SPfunTable = &Serial_fun
};

NBbc95 bc95_cfg = {
    .funcPtr = NULL,
    .object = (void*)&HWAtrrs_object,
    .recMsg_Callback = NB_MsgreportCallback
};


#endif