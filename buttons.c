/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "port_hal.h"

/******************************************************************************/
/* Animation Function Variables                                               */
/******************************************************************************/

/*debounce algorithm taken from:
 http://www.embedded.com/electronics-blogs/break-points/4024981/My-favorite-software-debouncers
 */
bool debouncedPortPin(PortName portName, PortPin pinName, char* state)
{    
    *state = (*state <<1)|!ReadPin(portName, pinName)|0xe0;
    if(*state==0xf0)
        return true;
    return false;
}