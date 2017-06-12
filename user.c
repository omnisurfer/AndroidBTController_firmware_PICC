/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

void InitApp(void)
{
    /*DIGITAL IOs*/
    TRISA = 0xFF, TRISB = 0x50, TRISC = 0x0B;    
    WPUA = 0x17, WPUB = 0x50;
    PORTA = 0x00, PORTB = 0x00, PORTC = 0x00;

    /*ANALOG IOs*/
    //No analog inputs
    ANSEL = 0x00;
    ANSELH = 0x00;

    /*INTERRUPTS*/
#if 0
    //Disable all peripheral 1 interrupts

    PIE1bits.ADIE = 0;
    PIE1bits.CCP1IE = 0;
    PIE1bits.RCIE = 0;
    PIE1bits.SSPIE = 0;
    PIE1bits.T1IE = 0;
    PIE1bits.T2IE = 0;
    PIE1bits.TMR1IE = 0;
    PIE1bits.TMR2IE = 0;
    PIE1bits.TXIE = 0;

    PIE2bits.C1IE = 0;
    PIE2bits.C2IE = 0;
    PIE2bits.EEIE = 0;
    PIE2bits.OSFIE = 0;

    INTCONbits.GIE = 0;
    INTCONbits.INTE = 0;
    INTCONbits.INTF = 0;
    INTCONbits.PEIE = 0;
    INTCONbits.RABIE = 0;
    INTCONbits.RABIF = 0;
    INTCONbits.T0IE = 0;
    INTCONbits.T0IF = 0;
   
    //Clear interrupt flags
    PIR1bits.ADIF = 0;
    PIR1bits.CCP1IF = 0;
    PIR1bits.RCIF = 0;
    PIR1bits.SSPIF = 0;
    PIR1bits.T1IF = 0;
    PIR1bits.T2IF = 0;
    PIR1bits.TMR1IF = 0;
    PIR1bits.TMR2IF = 0;
    PIR1bits.TXIF = 0;

    PIR2bits.C1IF = 0;
    PIR2bits.C2IF = 0;
    PIR2bits.EEIF = 0;
    PIR2bits.OSFIF = 0;

    INTCONbits.INTF = 0;
    INTCONbits.RABIF = 0;
    INTCONbits.T0IF = 0;
#endif
    
    //Global Interrupts Enabled
    INTCONbits.GIE = 1;
    
    //Peripheral Interrupts Enabled
    INTCONbits.PEIE = 1;
    
    /*TIMER1*/
#if 0
    //Initialize TIMER1 Clock Source: FOSC/4 = 2MHz
    T1CONbits.TMR1CS = 0;

    //1:8 Prescale, 2MHz/8 = 4uS per tick
    T1CONbits.T1CKPS = 0x00;

    //Timer 1 Interrupt Flag Clear
    PIR1bits.TMR1IF = 0;

    //Timer 1 Register Clear
    TMR1H = 0x00;
    TMR1L = 0x00;

    //Timer 1 ON
    T1CONbits.TMR1ON = 1;
    
    //Timer 1 Interrupt ON
    PIE1bits.TMR1IE = 1;
#endif

    /*TIMER0*/

    //Timer 0 Clock Source: Fosc/4
    OPTION_REGbits.T0CS = 0;

    
    //Timer 0 PSA with 1:4 prescale
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0x01;

    //Timer 0 Interrupt ON
    INTCONbits.T0IE = 1;
    
    //turn on global pull-ups
    OPTION_REGbits.nRABPU = 0;


}

