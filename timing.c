/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "processor_hal.h"
#include "timing.h"

/******************************************************************************/
/* Timing Routines                                                         */
/******************************************************************************/

void TimerDaemon(struct SYSTEM_TIMERS* timerTicks)
{
    //disable interrupts!
    INTCONbits.GIE = 0;
        
    //each rawTick is ~1mS when using TIMER0 interrupt with 1:4 Prescale, ~1 rawTicks = 1 ms
    if(rawTick == true)
    {
        rawTick = false;

        //timerTicks->rawClockCounter++;
                
        //if(timerTicks->rawClockCounter == 5)
        //{
            //timerTicks->rawClockCounter = 0;
            
            timerTicks->baseClock_msCounter++;
            timerTicks->baseClock_msTick = !timerTicks->baseClock_msTick;

            if(timerTicks->baseClock_msCounter == 100)
            {
                timerTicks->baseClock_100msCounter++;
                timerTicks->baseClock_100msTick = !timerTicks->baseClock_100msTick;
                timerTicks->baseClock_msCounter = 0;

                if(timerTicks->baseClock_100msCounter == 10)
                {                    
                    timerTicks->baseClock_1000msCounter++;
                    timerTicks->baseClock_1000msTick = !timerTicks->baseClock_1000msTick;
                    timerTicks->baseClock_100msCounter = 0;

                    if(timerTicks->baseClock_1000msCounter == 10)
                        timerTicks->baseClock_1000msCounter = 0;
                }
            //}
        }
    }
    //re-enable interrutps    
    INTCONbits.GIE = 1;
}
