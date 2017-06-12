/* 
 * File:   buttons.h
 * Author: Daniel
 *
 * Created on August 10, 2014, 4:33 PM
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

/******************************************************************************/
/* Button Function Prototypes                                                 */
/******************************************************************************/

bool portEdgeDetection(PortName portName, PortPin pinName, char* state);

void debounceButton(struct DEBOUNCED_BUTTON* button);

struct DEBOUNCED_BUTTON
{
    char debounceState;
    bool pressed;
    PortName portName;
    PortPin portPin;
};


