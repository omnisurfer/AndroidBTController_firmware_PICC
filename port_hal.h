/* 
 * File:   port_hal.h
 * Author: Daniel
 *
 * Created on July 13, 2014, 4:45 PM
 */

#ifndef PORT_HAL_H
#define	PORT_HAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* PORT_HAL_H */

//Copied from PIC c code
typedef enum
{
    PORT_A,
    PORT_B,
    PORT_C,

} PortName;

typedef enum
{
    PIN_0,
    PIN_1,
    PIN_2,
    PIN_3,

    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7
} PortPin;

char WritePort(PortName portName, char data);

char ReadPort(PortName portName);

bool WritePin(PortName portName, PortPin pinName, bool state);

bool ReadPin(PortName portName, PortPin pinName);

//future functions
//char SetPortMode();
//char SetPinMode();





