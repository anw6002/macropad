#ifndef USB_HID_H
#define USB_HID_H

#include <stdint.h>

void usb_hid_init(void);
void usb_hid_task(void);
void usb_hid_keypress(uint8_t key);
void usb_hid_keyrelease(void);

#endif // USB_HID_H
