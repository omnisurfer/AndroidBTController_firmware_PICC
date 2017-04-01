/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "processor_hal.h"
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "timing.h"
#include "port_hal.h"
#include "buttons.h"

#include "uart.h"

/******************************************************************************/
/* User Global Variable Declaration
 * Not fond of global but makes things easier for now
/******************************************************************************/
/* <Initialize variables in user.h and insert code for user algorithms.> */


/******************************************************************************/
/* Main Program
 * Four clock edges per instruction. At 8MHz FOSC, one instruction takes
 * 500ns to execute (2MIPS). At 20MHz FOSC, 200ns (5MIPS)
/******************************************************************************/

/*
 * TODO:
 * 
 */

//Dev Reference
//http://microchip.wikidot.com/

int test = 0;

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    InitializeUART();
             
    struct SYSTEM_TIMERS timerTicks =
    {        
        {0},
        {0},
        {0},
        {0},        

        {0},
        {0},
        {0},
        {0}        
    };

    char debugTrigger = 0;

    //read the switch every ms
    bool buttonOK = false;
    
    //turn on bluetooth module
    WritePin(PORT_C, PIN_4, true);

    //main execution loop
    //
    while(1)
    {                                                            
        //
        TimerDaemon(&timerTicks);

        //16uS
        /*
        if(timerTicks.baseClock_msCounter == 50)
            buttonOK = debouncedPortPin(PORT_A, PIN_3, &mainButtonState);
                
        if(buttonOK)
        {                                                                        
            
        }
        */

        //
        //send out a test UART transmission - only when no transmission is occuring
        //This will be implemented better but wanted an easy way to test the UART without bogging
        //the rest of the micro down.
        //        
        if((&timerTicks)->baseClock_1000msTick == debugTrigger)
        {
            //GUI-LEFT modifier brings up "Alt" like function
            //Tab is 2B
            //using USB HID Keyboard Reports
            //https://learn.adafruit.com/introducing-bluefruit-ez-key-diy-bluetooth-hid-keyboard/sending-keys-via-serial

            char temp[] = {0xFD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

            int i = 0;

            if(test == 0)
            {
                temp[1] = 0x04;
                temp[3] = 0x2B;
                test++;
            }

            else if (test == 1)
            {
                temp[1] = 0x04;
                temp[3] = 0x90;
                test++;
            }

            else if(test == 2)
            {
                temp[1] = 0x00;
                temp[3] = 0x00;
                test = 0;
            }

            do
            {
                if(TXSTAbits.TRMT == 1)
                {
                    UARTTransmit(temp[i]);
                    i++;
                }
            }while(i < 9);

            debugTrigger = !debugTrigger;
        }

        if((&timerTicks)->baseClock_1000msTick == true)        
            WritePin(PORT_C, PIN_7, true);
        else
            WritePin(PORT_C, PIN_7, false);
    }
}

