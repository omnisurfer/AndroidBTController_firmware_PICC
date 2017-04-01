/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "timing.h"

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12
//extern volatile bool rawTick;

void interrupt isr(void)
{    
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

    //Only PC is saved during interrupt (see page 213, Section 14.4).
    //Need to use W_TEMP and STATUS_TEMP to save context

#if 1
    /* Determine which flag generated the interrupt */
    if(INTCONbits.T0IE == 1 && INTCONbits.T0IF == 1)
    {
        //PORTCbits.RC7 = !PORTCbits.RC7;
        rawTick = true;
        INTCONbits.T0IF = 0;
    }

    else if(PIE1bits.TMR1IE == 1 && PIR1bits.TMR1IF == 1)
    {                        
        PIR1bits.TMR1IF = 0;
    }

    else if (PIR1bits.RCIF == 1)
    {
        //does nothing for now
    }

    else
    {        
        //do nothing
    }

#endif

}
#endif


