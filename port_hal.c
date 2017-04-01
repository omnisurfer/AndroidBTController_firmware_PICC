/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "port_hal.h"
#include "processor_hal.h"

/**
 * Write Port
 * @param portName
 * @param data
 * @return
 */
char WritePort(PortName portName, char data)
{   
    //which port to write to
    switch(portName)
    {
        case PORT_A:
            PORTA = data;
            break;

        case PORT_B:
            PORTB = data;
            break;

        case PORT_C:
            PORTC = data;
            break;

        default:
            break;
    }
    return 0;    
}

char ReadPort(PortName portName)
{
    char data = 0;
    //which port to write to
    switch(portName)
    {
        case PORT_A:
            data = PORTA;
            break;

        case PORT_B:
            data = PORTB;
            break;

        case PORT_C:
            data = PORTC;
            break;

        default:
            break;
    }
    return data;
}

bool WritePin(PortName portName, PortPin pinName, bool state)
{
    bool outOfBound = false;
    
    switch(portName)
    {
        case PORT_A:
            /*Code using bit shift. Maybe faster? - 20150726*/
            /*
            if(state)
                PORTA &= (0x01 << pinName);
            else
                PORTA |= ~(0x01 << pinName);
            */
            switch(pinName)
            {
                case PIN_0:
                    PORTAbits.RA0 = state;
                    break;

                case PIN_1:
                    PORTAbits.RA1 = state;
                    break;

                case PIN_2:
                    PORTAbits.RA2 = state;
                    break;

                case PIN_3:
                    PORTAbits.RA3 = state;
                    break;

                case PIN_4:
                    PORTAbits.RA4 = state;
                    break;

                case PIN_5:
                    PORTAbits.RA5 = state;
                    break;

                default:
                    outOfBound = true;
                    break;
            }
            break;

        case PORT_B:
            switch(pinName)
            {
                case PIN_4:
                    PORTBbits.RB4 = state;
                    break;

                case PIN_5:
                    PORTBbits.RB5 = state;
                    break;

                case PIN_6:
                    PORTBbits.RB6 = state;
                    break;

                case PIN_7:
                    PORTBbits.RB7 = state;
                    break;

                default:
                    outOfBound = true;
                    break;
            }
            break;

        case PORT_C:
            switch(pinName)
            {
                case PIN_0:
                    PORTCbits.RC0 = state;
                    break;

                case PIN_1:
                    PORTCbits.RC1 = state;
                    break;

                case PIN_2:
                    PORTCbits.RC2 = state;
                    break;

                case PIN_3:
                    PORTCbits.RC3 = state;
                    break;

                case PIN_4:
                    PORTCbits.RC4 = state;
                    break;

                case PIN_5:
                    PORTCbits.RC5 = state;
                    break;

                case PIN_6:
                    PORTCbits.RC6 = state;
                    break;

                case PIN_7:
                    PORTCbits.RC7 = state;
                    break;

                default:
                    outOfBound = true;
                    break;
            }
            break;
            
        default:
            outOfBound = true;
            break;
    }

    return outOfBound;
}

bool ReadPin(PortName portName, PortPin pinName)
{
    bool result = false;

    switch(portName)
    {
        case PORT_A:
            switch(pinName)
            {
                case PIN_0:
                    result = PORTAbits.RA0;
                    break;

                case PIN_1:
                    result = PORTAbits.RA1;
                    break;

                case PIN_2:
                    result = PORTAbits.RA2;
                    break;

                case PIN_3:
                    result = PORTAbits.RA3;
                    break;

                case PIN_4:
                    result = PORTAbits.RA4;
                    break;

                case PIN_5:
                    result = PORTAbits.RA5;
                    break;

                default:                    
                    break;
            }
            break;

        case PORT_B:
            switch(pinName)
            {
                case PIN_4:
                    result = PORTBbits.RB4;
                    break;

                case PIN_5:
                    result = PORTBbits.RB5;
                    break;

                case PIN_6:
                    result = PORTBbits.RB6;
                    break;

                case PIN_7:
                    result = PORTBbits.RB7;
                    break;

                default:                    
                    break;
            }
            break;

        case PORT_C:
            switch(pinName)
            {
                case PIN_0:
                    result = PORTCbits.RC0;
                    break;

                case PIN_1:
                    result = PORTCbits.RC1;
                    break;

                case PIN_2:
                    result = PORTCbits.RC2;
                    break;

                case PIN_3:
                    result = PORTCbits.RC3;
                    break;

                case PIN_4:
                    result = PORTCbits.RC4;
                    break;

                case PIN_5:
                    result = PORTCbits.RC5;
                    break;

                case PIN_6:
                    result = PORTCbits.RC6;
                    break;

                case PIN_7:
                    result = PORTCbits.RC7;
                    break;

                default:                    
                    break;
            }
            break;

        default:            
            break;
    }

    return result;
}
