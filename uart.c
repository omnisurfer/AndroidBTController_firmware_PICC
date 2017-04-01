/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "processor_hal.h"

/******************************************************************************/
/* UART Routines                                                         */
/******************************************************************************/

//see http://www.mcuexamples.com/PIC-Serial-Communication.php
void InitializeUART(void)
{    
    //Set pins
    TRISBbits.TRISB5 = 1;   //RB5 to RX input
    TRISBbits.TRISB7 = 0;   //RB7 to TX output
    
    //Baud rate for FOSC @ 8MHz
    SPBRG = 0xCF;           //9600bps
    SPBRGH = 0x00;
    
    //Transmit register
    TXSTAbits.TXEN = 1;     //TX enabled
    TXSTAbits.SYNC = 0;     //ASYNC
    TXSTAbits.BRGH = 1;     //High speed

    //Receiver register
    RCSTAbits.SPEN = 1;     //Serial port enabled
    RCSTAbits.CREN = 1;     //RX enabled
    
    //Baud rate control
    BAUDCTLbits.BRG16 = 1;  //16-bit buad rate generator is used
    
    //UART RX Interrupt Disabled
    PIE1bits.RCIE = 0;
}

void UARTTransmit(int b)
{    
    TXREG = b;              //load data 
}