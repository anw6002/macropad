/**
 * @file buttons.c
 * @brief Button driver for the macropad.
 *
 * Handles GPIO initialization, button scanning,
 * debouncing, and state changes.
 */

#include "buttons.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define DEBOUNCE_MS 10

static bool previous_state[BUTTON_COUNT];
static bool stable_state[BUTTON_COUNT];
static absolute_time_t last_change[BUTTON_COUNT];
static const unsigned int BUTTON_PINS[BUTTON_COUNT] =
{
    1,
    5,
    9,
    15,
    13,
    14,
};

/**
 * @brief Initialize all button GPIOs.
 *
 * Configures each button pin as an input and enables
 * the internal pull-up resistor.
 */
void buttons_init(void)
{
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        gpio_init(BUTTON_PINS[i]);
        gpio_set_dir(BUTTON_PINS[i], GPIO_IN);
        gpio_pull_up(BUTTON_PINS[i]);

        previous_state[i] = false;
        stable_state[i] = false;
        last_change[i] = get_absolute_time();
    }
}

/**
 * @brief Scan all buttons for debounced state changes.
 *
 * Reads each button and generates an event only when the
 * new state has remained stable for the debounce period.
 *
 * @param event Pointer to the event structure to populate.
 * @return true if a debounced button event was detected,
 *         false otherwise.
 */
bool buttons_scan(ButtonEventData *event)
{
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        // Read current state of pin pressed (active-low)
        bool current_state = (gpio_get(BUTTON_PINS[i]) == 0);
        
        // If state changed, record new state and reset debounce timer
        if (current_state != previous_state[i])
        {
            previous_state[i] = current_state;
            last_change[i] = get_absolute_time();
        }

        // Accept the new state only if it has remained unchanged
        // for the required debounce period.
        if (current_state != stable_state[i] &&
            absolute_time_diff_us(last_change[i], get_absolute_time())
                >= DEBOUNCE_MS * 1000)
        {
            stable_state[i] = current_state;

            event->button = (Button)i;

            if (current_state)
            {
                event->event = BUTTON_PRESSED;
            }
            else
            {
                event->event = BUTTON_RELEASED;
            }

            return true;
        }
    }

    return false; // No debounced button event detected
}