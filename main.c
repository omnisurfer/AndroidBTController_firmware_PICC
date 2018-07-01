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

void AltTabControl(struct DEBOUNCED_BUTTON* buttonPrev, char *rawHIDArray, int rawHIDArraySize);
void WindowsKeyControl(struct DEBOUNCED_BUTTON* buttonStop, char *rawHIDArrayPointer, int rawHIDArraySize);
void EscKeyControl(struct DEBOUNCED_BUTTON* buttonPlay, char *rawHIDArrayPointer, int rawHIDArraySize);
void BackspaceKeyControl(struct DEBOUNCED_BUTTON* buttonNext, char *rawHIDArrayPointer, int rawHIDArraySize);

void DPADControl(struct DEBOUNCED_BUTTON* buttonLeft, struct DEBOUNCED_BUTTON* buttonRight, struct DEBOUNCED_BUTTON* buttonUp, struct DEBOUNCED_BUTTON* buttonDown, struct DEBOUNCED_BUTTON* buttonCenter, char *rawHIDArrayPointer, int rawHIDArraySize);

int AddKeyToHIDArray(char key, char *rawHIDArrayPointer, int rawHIDArraySize);
int ReleaseKeyFromHIDArray(char key, char *rawHIDArrayPointer, int rawHIDArraySize);
int SendHIDKeyCodes(char *rawHIDArrayPointer, int rawHIDArraySize);
int AddModifierToHIDArray(char modifier, char *rawHIDArrayPointer);

void main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    InitializeUART();

    struct SYSTEM_TIMERS timerTicks = {
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

    /*
     * Note, PICKit3 programmer will interfere with pins RA0 and RA1 when plugged in.
     * RA0 (Up DPAD, A)
     * RA1 (Center DPAD)
     * RA2 (Left DPAD, C)
     * RA3 (Down DPAD, unmarked)
     * RA4 (Right, B)
     * 
     * RB4 (SW_PLAY)
     * RB6 (SW_STOP)
     * 
     * RC0 (SW_NEXT)
     * RC1 (SW_PREV)
     */

/*USB HID Keycodes:
     // Bits in usbHidKeyboardInput.modifiers
final byte MODIFIER_NONE          =byte((0));
final byte MODIFIER_CONTROL_LEFT  =byte((1<<0));
final byte MODIFIER_SHIFT_LEFT    =byte((1<<1));
final byte MODIFIER_ALT_LEFT      =byte((1<<2));
final byte MODIFIER_GUI_LEFT      =byte((1<<3));
final byte MODIFIER_CONTROL_RIGHT =byte((1<<4));
final byte MODIFIER_SHIFT_RIGHT   =byte((1<<5));
final byte MODIFIER_ALT_RIGHT     =byte((1<<6));
final byte MODIFIER_GUI_RIGHT     =byte((1<<7));
 
// Values for usbHidKeyboardInput.keyCodes
// Only the key codes for common keys are defined here. See Hut1_12.pdf for a full list.
final byte KEY_NONE               =byte(0x00);
final byte KEY_A                  =byte(0x04);
final byte KEY_B                  =byte(0x05);
final byte KEY_C                  =byte(0x06);
final byte KEY_D                  =byte(0x07);
final byte KEY_E                  =byte(0x08);
final byte KEY_F                  =byte(0x09);
final byte KEY_G                  =byte(0x0A);
final byte KEY_H                  =byte(0x0B);
final byte KEY_I                  =byte(0x0C);
final byte KEY_J                  =byte(0x0D);
final byte KEY_K                  =byte(0x0E);
final byte KEY_L                  =byte(0x0F);
final byte KEY_M                  =byte(0x10);
final byte KEY_N                  =byte(0x11);
final byte KEY_O                  =byte(0x12);
final byte KEY_P                  =byte(0x13);
final byte KEY_Q                  =byte(0x14);
final byte KEY_R                  =byte(0x15);
final byte KEY_S                  =byte(0x16);
final byte KEY_T                  =byte(0x17);
final byte KEY_U                  =byte(0x18);
final byte KEY_V                  =byte(0x19);
final byte KEY_W                  =byte(0x1A);
final byte KEY_X                  =byte(0x1B);
final byte KEY_Y                  =byte(0x1C);
final byte KEY_Z                  =byte(0x1D);
final byte KEY_1                  =byte(0x1E);
final byte KEY_2                  =byte(0x1F);
final byte KEY_3                  =byte(0x20);
final byte KEY_4                  =byte(0x21);
final byte KEY_5                  =byte(0x22);
final byte KEY_6                  =byte(0x23);
final byte KEY_7                  =byte(0x24);
final byte KEY_8                  =byte(0x25);
final byte KEY_9                  =byte(0x26);
final byte KEY_0                  =byte(0x27);
final byte KEY_RETURN             =byte(0x28);
final byte KEY_ESCAPE             =byte(0x29);
final byte KEY_BACKSPACE          =byte(0x2A);
final byte KEY_TAB                =byte(0x2B);
final byte KEY_SPACE              =byte(0x2C);
final byte KEY_MINUS              =byte(0x2D);
final byte KEY_EQUAL              =byte(0x2E);
final byte KEY_BRACKET_LEFT       =byte(0x2F);
final byte KEY_BRACKET_RIGHT      =byte(0x30);
final byte KEY_BACKSLASH          =byte(0x31);
final byte KEY_EUROPE_1           =byte(0x32);
final byte KEY_SEMICOLON          =byte(0x33);
final byte KEY_APOSTROPHE         =byte(0x34);
final byte KEY_GRAVE              =byte(0x35);
final byte KEY_COMMA              =byte(0x36);
final byte KEY_PERIOD             =byte(0x37);
final byte KEY_SLASH              =byte(0x38);
final byte KEY_CAPS_LOCK          =byte(0x39);
final byte KEY_F1                 =byte(0x3A);
final byte KEY_F2                 =byte(0x3B);
final byte KEY_F3                 =byte(0x3C);
final byte KEY_F4                 =byte(0x3D);
final byte KEY_F5                 =byte(0x3E);
final byte KEY_F6                 =byte(0x3F);
final byte KEY_F7                 =byte(0x40);
final byte KEY_F8                 =byte(0x41);
final byte KEY_F9                 =byte(0x42);
final byte KEY_F10                =byte(0x43);
final byte KEY_F11                =byte(0x44);
final byte KEY_F12                =byte(0x45);
final byte KEY_PRINT_SCREEN       =byte(0x46);
final byte KEY_SCROLL_LOCK        =byte(0x47);
final byte KEY_PAUSE              =byte(0x48);
final byte KEY_INSERT             =byte(0x49);
final byte KEY_HOME               =byte(0x4A);
final byte KEY_PAGE_UP            =byte(0x4B);
final byte KEY_DELETE             =byte(0x4C);
final byte KEY_END                =byte(0x4D);
final byte KEY_PAGE_DOWN          =byte(0x4E);
final byte KEY_ARROW_RIGHT        =byte(0x4F);
final byte KEY_ARROW_LEFT         =byte(0x50);
final byte KEY_ARROW_DOWN         =byte(0x51);
final byte KEY_ARROW_UP           =byte(0x52);
final byte KEY_NUM_LOCK           =byte(0x53);
final byte KEY_KEYPAD_DIVIDE      =byte(0x54);
final byte KEY_KEYPAD_MULTIPLY    =byte(0x55);
final byte KEY_KEYPAD_SUBTRACT    =byte(0x56);
final byte KEY_KEYPAD_ADD         =byte(0x57);
final byte KEY_KEYPAD_ENTER       =byte(0x58);
final byte KEY_KEYPAD_1           =byte(0x59);
final byte KEY_KEYPAD_2           =byte(0x5A);
final byte KEY_KEYPAD_3           =byte(0x5B);
final byte KEY_KEYPAD_4           =byte(0x5C);
final byte KEY_KEYPAD_5           =byte(0x5D);
final byte KEY_KEYPAD_6           =byte(0x5E);
final byte KEY_KEYPAD_7           =byte(0x5F);
final byte KEY_KEYPAD_8           =byte(0x60);
final byte KEY_KEYPAD_9           =byte(0x61);
final byte KEY_KEYPAD_0           =byte(0x62);
final byte KEY_KEYPAD_DECIMAL     =byte(0x63);
final byte KEY_EUROPE_2           =byte(0x64);
final byte KEY_APPLICATION        =byte(0x65);
final byte KEY_POWER              =byte(0x66);
final byte KEY_KEYPAD_EQUAL       =byte(0x67);
final byte KEY_F13                =byte(0x68);
final byte KEY_F14                =byte(0x69);
final byte KEY_F15                =byte(0x6A);
final byte KEY_CONTROL_LEFT       =byte(0xE0);
final byte KEY_SHIFT_LEFT         =byte(0xE1);
final byte KEY_ALT_LEFT           =byte(0xE2);
final byte KEY_GUI_LEFT           =byte(0xE3);
final byte KEY_CONTROL_RIGHT      =byte(0xE4);
final byte KEY_SHIFT_RIGHT        =byte(0xE5);
final byte KEY_ALT_RIGHT          =byte(0xE6);
final byte KEY_GUI_RIGHT          =byte(0xE7);
     */
    struct DEBOUNCED_BUTTON buttonPrevious, buttonNext, buttonPlay, buttonStop;

    buttonPrevious.debounceState = 0x00;
    buttonPrevious.portName = PORT_C;
    buttonPrevious.portPin = PIN_1;
    buttonPrevious.pressed = false;

    buttonNext.debounceState = 0x00;
    buttonNext.portName = PORT_C;
    buttonNext.portPin = PIN_0;
    buttonNext.pressed = false;

    buttonPlay.debounceState = 0x00;
    buttonPlay.portName = PORT_B;
    buttonPlay.portPin = PIN_4;
    buttonPlay.pressed = false;

    buttonStop.debounceState = 0x00;
    buttonStop.portName = PORT_B;
    buttonStop.portPin = PIN_5;
    buttonStop.pressed = false;

    struct DEBOUNCED_BUTTON buttonDPADLeft, buttonDPADRight, buttonDPADUp, buttonDPADDown, buttonDPADCenter;

    buttonDPADLeft.debounceState = 0x00;
    buttonDPADLeft.portName = PORT_A;
    buttonDPADLeft.portPin = PIN_2;
    buttonDPADLeft.pressed = false;

    buttonDPADRight.debounceState = 0x00;
    buttonDPADRight.portName = PORT_A;
    buttonDPADRight.portPin = PIN_4;
    buttonDPADRight.pressed = false;

    buttonDPADUp.debounceState = 0x00;
    buttonDPADUp.portName = PORT_A;
    buttonDPADUp.portPin = PIN_0;
    buttonDPADUp.pressed = false;

    buttonDPADDown.debounceState = 0x00;
    buttonDPADDown.portName = PORT_A;
    buttonDPADDown.portPin = PIN_3;
    buttonDPADDown.pressed = false;

    buttonDPADCenter.debounceState = 0x00;
    buttonDPADCenter.portName = PORT_A;
    buttonDPADCenter.portPin = PIN_1;
    buttonDPADCenter.pressed = false;

    //turn on bluetooth module
    WritePin(PORT_C, PIN_4, true);

    //Raw HID array
    char rawHIDArray[] = {0xFD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    char *rawHIDArrayPointer = rawHIDArray;
    int rawHIDArraySize = sizeof (rawHIDArray) / sizeof (rawHIDArray[0]);

    //main execution loop
    //
    while (1) {
        //
        TimerDaemon(&timerTicks);

        if ((&timerTicks)->baseClock_msTick == true) {
            debounceButton(&buttonPrevious);
            debounceButton(&buttonNext);
            debounceButton(&buttonPlay);
            debounceButton(&buttonStop);
            debounceButton(&buttonDPADLeft);
            debounceButton(&buttonDPADRight);
            debounceButton(&buttonDPADUp);
            debounceButton(&buttonDPADDown);
            debounceButton(&buttonDPADCenter);
        }

        AltTabControl(&buttonPrevious, rawHIDArrayPointer, rawHIDArraySize);

        WindowsKeyControl(&buttonStop, rawHIDArrayPointer, rawHIDArraySize);
        
        EscKeyControl(&buttonPlay, rawHIDArrayPointer, rawHIDArraySize);
        
        BackspaceKeyControl(&buttonNext, rawHIDArrayPointer, rawHIDArraySize);

        DPADControl(&buttonDPADLeft, &buttonDPADRight, &buttonDPADUp, &buttonDPADDown, &buttonDPADCenter, rawHIDArrayPointer, rawHIDArraySize);

        //SendHIDKeyCodes(rawHIDArrayPointer, rawHIDArraySize);

        /* heartbeat LED
        if ((&timerTicks)->baseClock_1000msTick == true)
            WritePin(PORT_C, PIN_7, true);
        else
            WritePin(PORT_C, PIN_7, false);
         */
    }
}

void AltTabControl(struct DEBOUNCED_BUTTON* button, char *rawHIDArrayPointer, int rawHIDArraySize) {
    static int altTabState = 0;

    switch (altTabState) {

            //wait for button to be pressed
        case 0:
            if (button->pressed) {

                WritePin(PORT_C, PIN_7, true);
                altTabState++;
            }
            break;

            //send initial alt tab command
        case 1:
            rawHIDArrayPointer[1] = 0x04;
            rawHIDArrayPointer[3] = 0x2B;

            for (int i = 0; i < rawHIDArraySize;) {
                if (TXSTAbits.TRMT == 1) {
                    UARTTransmit(rawHIDArrayPointer[i]);
                    i++;
                }
            }

            altTabState++;
            break;

            //release the tab
        case 2:
            rawHIDArrayPointer[1] = 0x04;
            rawHIDArrayPointer[3] = 0x00;

            for (int i = 0; i < rawHIDArraySize;) {
                if (TXSTAbits.TRMT == 1) {
                    UARTTransmit(rawHIDArrayPointer[i]);
                    i++;
                }
            }

            altTabState++;
            break;

            //wait for button to be released
        case 3:
            if (!button->pressed) {
                WritePin(PORT_C, PIN_7, false);

                rawHIDArrayPointer[1] = 0x00;
                //rawHIDArrayPointer[3] = 0x00;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                altTabState = 0;
            }
            break;

        default:
            altTabState = 0;
            break;
    }
}

void WindowsKeyControl(struct DEBOUNCED_BUTTON* button, char *rawHIDArrayPointer, int rawHIDArraySize) {
    static int buttonStopState = 0;

    switch (buttonStopState) {
        case 0:
            if (button->pressed) {
                rawHIDArrayPointer[1] = 0x08;
                //rawHIDArrayPointer[3] = 0xE7;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonStopState++;
            }
            break;

        case 1:
            if (!button->pressed) {
                rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0xe7;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonStopState = 0;
            }
            break;
        default:
            buttonStopState = 0;
            break;
    }
}

void EscKeyControl(struct DEBOUNCED_BUTTON* button, char *rawHIDArrayPointer, int rawHIDArraySize) {
    static int buttonPlayState = 0;

    switch (buttonPlayState) {
        case 0:
            if (button->pressed) {
                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x29;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonPlayState++;
            }
            break;

        case 1:
            if (!button->pressed) {
                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x00;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonPlayState = 0;
            }
            break;
        default:
            buttonPlayState = 0;
            break;
    }
}

void BackspaceKeyControl(struct DEBOUNCED_BUTTON* button, char *rawHIDArrayPointer, int rawHIDArraySize) {
    static int buttonNextState = 0;

    switch (buttonNextState) {
        case 0:
            if (button->pressed) {
                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x2a;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonNextState++;
            }
            break;

        case 1:
            if (!button->pressed) {
                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x00;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonNextState = 0;
            }
            break;
        default:
            buttonNextState = 0;
            break;
    }
}

void DPADControl(struct DEBOUNCED_BUTTON* buttonLeft, struct DEBOUNCED_BUTTON* buttonRight, struct DEBOUNCED_BUTTON* buttonUp, struct DEBOUNCED_BUTTON* buttonDown, struct DEBOUNCED_BUTTON* buttonCenter, char *rawHIDArrayPointer, int rawHIDArraySize) {
    static int buttonLeftState = 0, buttonRightState = 0, buttonUpState = 0, buttonDownState = 0, buttonCenterState;

    switch (buttonLeftState) {
        case 0:
            if (buttonLeft->pressed) {
                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x50;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonLeftState++;
            }
            break;

        case 1:
            if (!buttonLeft->pressed) {
                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x00;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonLeftState = 0;
            }
            break;
        default:
            buttonLeftState = 0;
            break;
    }

    switch (buttonRightState) {
        case 0:
            if (buttonRight->pressed) {

                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x4f;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                //*/                                                
                //AddKeyToHIDArray(0x4f, rawHIDArrayPointer, rawHIDArraySize);

                buttonRightState++;
            }
            break;

        case 1:
            if (!buttonRight->pressed) {

                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x00;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }

                buttonRightState = 0;
            }
            break;
        default:
            buttonRightState = 0;
            break;
    }

    switch (buttonUpState) {
        case 0:
            if (buttonUp->pressed) {
                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x52;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonUpState++;
            }
            break;

        case 1:
            if (!buttonUp->pressed) {
                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x00;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonUpState = 0;
            }
            break;
        default:
            buttonUpState = 0;
            break;
    }

    switch (buttonDownState) {
        case 0:
            if (buttonDown->pressed) {
                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x51;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonDownState++;
            }
            break;

        case 1:
            if (!buttonDown->pressed) {
                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x00;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonDownState = 0;
            }
            break;
        default:
            buttonDownState = 0;
            break;
    }

    switch (buttonCenterState) {
        case 0:
            if (buttonCenter->pressed) {
                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x28;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonCenterState++;
            }
            break;

        case 1:
            if (!buttonDown->pressed) {
                //rawHIDArrayPointer[1] = 0x00;
                rawHIDArrayPointer[3] = 0x00;

                for (int i = 0; i < rawHIDArraySize;) {
                    if (TXSTAbits.TRMT == 1) {
                        UARTTransmit(rawHIDArrayPointer[i]);
                        i++;
                    }
                }
                buttonCenterState = 0;
            }
            break;
        default:
            buttonCenterState = 0;
            break;
    }
}

int AddKeyToHIDArray(char key, char *rawHIDArrayPointer, int rawHIDArraySize) {
    static int emptyKeyCodeIndex = 0 + 3;

    if (emptyKeyCodeIndex < rawHIDArraySize) {
        rawHIDArrayPointer[emptyKeyCodeIndex] = key;
        emptyKeyCodeIndex++;
        return 0;
    }
    return -1;
}

int AddModifierToHIDArray(char modifier, char *rawHIDArrayPointer) {
    rawHIDArrayPointer[1] = modifier;
    return -1;
}

int ReleaseKeyFromHIDArray(char key, char *rawHIDArrayPointer, int rawHIDArraySize) {
    return -1;
}

int SendHIDKeyCodes(char *rawHIDArrayPointer, int rawHIDArraySize) {
    if (rawHIDArrayPointer[1] == 0x00 && rawHIDArrayPointer[3] == 0x00)
        return -1;

    for (int i = 0; i < rawHIDArraySize;) {
        if (TXSTAbits.TRMT == 1) {
            UARTTransmit(rawHIDArrayPointer[i]);
            i++;
        }
    }
    return 1;
}

