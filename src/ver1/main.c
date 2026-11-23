/**
 * @file main.c
 * @brief Entry point for macropad firmware.
 *
 * Initializes the Raspberry Pi Pico SDK and all firmware
 * subsystems, then executes the main application loop.
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include "tusb.h"
#include "usb_hid.h"
#include "keymap.h"
#include "buttons.h"

int main(void)
{
    stdio_init_all();

    buttons_init();
    usb_hid_init();

    ButtonEventData event;
    
    while (true) 
    {
        usb_hid_task();
        if (buttons_scan(&event))
        {
            uint8_t keycode = get_keycode(event.button);

            if (event.event == BUTTON_PRESSED)
            {
            usb_hid_keypress(keycode);
            }
            else
            {
            usb_hid_keyrelease();
            }
        }

        sleep_ms(6);
    }
}
