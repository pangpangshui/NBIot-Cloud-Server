#include "uartTimerPoll.h"
//#include "NBBC95.h"

bc95_TimerCallback TimerOutCb;

uint32_t TickStart = 0;
uint32_t TickDelta = 0;
uint8_t  TickOpenFlag = 0;


void TimerSet(bc95_TimerCallback timerCb)
{
    TimerOutCb = timerCb;
}
        
void TimerStart(uint32_t ms) 
{
    TickStart = ms;
    TickDelta = HAL_GetTick(); //获取当前滴答值
    TickOpenFlag = 1;
}

void TimerPoll(void)
{
    uint32_t tick;
    if (TickOpenFlag) {
        tick = HAL_GetTick();
        uint32_t delay = tick > TickStart? tick - TickStart: tick + UINT32_MAX - TickStart;
        if (TickDelta > delay) {
            TickDelta -= delay;
            TickStart = tick;
        }
        else {
            TickDelta = 0;
            TickOpenFlag = 0;
            if (TimerOutCb) {
                TimerOutCb(); 
            }
        }
    }
}
        
void TimerStop(void)
{
    TickOpenFlag = 0;
}






