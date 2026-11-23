/**
 * @file keymap.c
 * @brief Maps button events to keyboard actions.
 *
 * Defines the behavior associated with each physical button.
 */

 #include "keymap.h"
 #include "tusb.h"

 uint8_t get_keycode(Button button)
{
    switch (button)
    {
        case BUTTON_Q:
            return HID_KEY_Q;

        case BUTTON_W:
            return HID_KEY_W;

        case BUTTON_E:
            return HID_KEY_E;

        case BUTTON_R:
            return HID_KEY_R;

        case BUTTON_D:
            return HID_KEY_D;

        case BUTTON_F:
            return HID_KEY_F;

        default:
            return 0;
    }
}