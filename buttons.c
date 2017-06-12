/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "port_hal.h"
#include "buttons.h"

/******************************************************************************/
/* Animation Function Variables                                               */
/******************************************************************************/

/*debounce algorithm taken from:
 http://www.embedded.com/electronics-blogs/break-points/4024981/My-favorite-software-debouncers
 */
bool portEdgeDetection(PortName portName, PortPin pinName, char* state) {    
    *state = (*state << 1) | !ReadPin(portName, pinName) | 0xe0;
    if (*state == 0xf0)
        return true;
    else
        return false;
}

void debounceButton(struct DEBOUNCED_BUTTON* button) {
    //pin is being interpreted as being asserted when low
    //look for stable positive edge to indicate button has been released
    if (button->pressed) {
        button->debounceState = (button->debounceState << 1) | ReadPin(button->portName, button->portPin) & 0x0f;
        if (button->debounceState == 0x0f) {
            button->pressed = false;
        }

    } //look for negative edge to indicate button has been pressed
    else if (!button->pressed) {
        button->debounceState = (button->debounceState << 1) | ReadPin(button->portName, button->portPin) | 0xf0;
        if (button->debounceState == 0xf0) {
            button->pressed = true;
        }
    }    
}