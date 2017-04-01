/* 
 * File:   uart.h
 * Author: Daniel
 *
 * Created on February 24, 2014, 8:28 PM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

/******************************************************************************/
/* UART #define Macros                                                   */
/******************************************************************************/

//#define A                 1
//#define B                 2
//#define C                 3

/******************************************************************************/
/* UART Function Variables                                               */
/******************************************************************************/

/******************************************************************************/
/* UART Function Prototypes                                              */
/******************************************************************************/
void InitializeUART(void);  /* provides uart initialization*/

void UARTTransmit(int b);   /* provides uartTransmit functionality*/
