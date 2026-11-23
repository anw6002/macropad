/**
 * @file buttons.h
 * @brief Public interface for the macropad button driver.
 *
 * Defines the available buttons, button events, and functions used
 * to initialize and scan the macropad's button inputs.
 */

#ifndef BUTTONS_H
#define BUTTONS_H
#include <stdbool.h>

#define BUTTON_COUNT 6

typedef enum
{
    BUTTON_Q,
    BUTTON_W,
    BUTTON_E,
    BUTTON_R,
    BUTTON_D,
    BUTTON_F,
} Button;

typedef enum
{
    BUTTON_PRESSED,
    BUTTON_RELEASED
} ButtonEvent;

typedef struct
{
    Button button;
    ButtonEvent event;
} ButtonEventData;


void buttons_init(void);
bool buttons_scan(ButtonEventData *event);

#endif  // BUTTONS_H