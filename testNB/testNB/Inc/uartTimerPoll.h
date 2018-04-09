#ifndef __UARTTIMERPOLL_H__
#define __UARTTIMERPOLL_H__

#ifdef __cpluscplus
    extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "NBBC95.h"

void TimerSet(bc95_TimerCallback timerCb);
        
void TimerStart(uint32_t ms);

void TimerPoll(void);
        
void TimerStop(void);


        
#ifdef __cpluscplus
    }
#endif
#endif
    

