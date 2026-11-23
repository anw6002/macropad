/**
 * @file keymap.h
 * @brief Maps macropad buttons to keyboard keycodes.
 *
 * Defines the interface used to convert logical macropad buttons
 * into USB HID keyboard keycodes.
 */

#ifndef KEYMAP_H
#define KEYMAP_H

#include "buttons.h"
#include <stdint.h>

uint8_t get_keycode(Button button);

#endif // KEYMAP_H