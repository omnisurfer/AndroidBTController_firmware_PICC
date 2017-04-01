/* 
 * File:   timing.h
 * Author: Daniel
 *
 * Created on February 9, 2014, 3:17 PM
 */

#ifndef TIMING_H
#define	TIMING_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* TIMING_H */

/******************************************************************************/
/* Timing #define Macros                                                */
/******************************************************************************/

//#define A                 1
//#define B                 2
//#define C                 3

/******************************************************************************/
/* Timing Function Structs & Unions                                           */
/******************************************************************************/
typedef struct {
    char hiByte, lowByte;

}byte_count;

typedef union timer1_count
{
    byte_count bytes;
    unsigned int word;
};

//each rawTick is ~205uS when using TIMER0 interrupt with 1:4 Prescale, ~5 rawTicks = 1 ms
struct SYSTEM_TIMERS
{
    char rawClockCounter,
    baseClock_msCounter,
    baseClock_100msCounter,
    baseClock_1000msCounter;

    bool rawClockTick,
    baseClock_msTick,
    baseClock_100msTick,
    baseClock_1000msTick;
} timerTicksX;

/******************************************************************************/
/* Timing Function Variables                                                  */
/******************************************************************************/

volatile bool rawTick;

/******************************************************************************/
/* Timing Function Prototypes                                                 */
/******************************************************************************/

void TimerDaemon(struct SYSTEM_TIMERS* timerTicks); /* provides timer functionality*/

