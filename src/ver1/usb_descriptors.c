/**
 * @file usb_descriptors.c
 * @brief USB descriptors implementation.
 *
 * Defines the USB device descriptors for the HID device by:
 * - Identify Pico as a USB HID device to the host computer.
 * - Tell computer what USB Interfaces device provides
 * - Define format of keyboard data sent
 * - Provide human readable strings for device identification
 * - Provide TinyUSB with descriptors needed to respond to host requests
 */

#include "tusb.h"
#include <string.h>
#define ITF_NUM_HID 0
#define EPNUM_HID 0x81
#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)

// 1. HID Report Descriptor
uint8_t const desc_hid_report[] = 
{
    TUD_HID_REPORT_DESC_KEYBOARD()
};

// 2. Configuration Descriptor
uint8_t const desc_configuration[] = 
{
    TUD_CONFIG_DESCRIPTOR(
        1,
        1,
        0,
        CONFIG_TOTAL_LEN,
        0,
        100
    ),

    TUD_HID_DESCRIPTOR(
        ITF_NUM_HID,
        0,
        HID_ITF_PROTOCOL_KEYBOARD,
        sizeof(desc_hid_report),
        EPNUM_HID,
        8,
        10
    )
};

// 3. Device Descriptor
tusb_desc_device_t const desc_device = 
{
    .bLength = sizeof(tusb_desc_device_t),
    .bDescriptorType = TUSB_DESC_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = 0x00,
    .bDeviceSubClass = 0x00,
    .bDeviceProtocol = 0x00,
    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor = 0x2E8A,
    .idProduct = 0x000B,
    .bcdDevice = 0x0100,
    .iManufacturer = 0x01,
    .iProduct = 0x02,
    .iSerialNumber = 0x03,
    .bNumConfigurations = 0x01
};

// 4. Callbacks
uint8_t const * tud_descriptor_device_cb(void)
{
    return (uint8_t const *) &desc_device;
}

uint8_t const * tud_descriptor_configuration_cb(uint8_t index)
{
    (void) index;
    return desc_configuration;
}

uint8_t const * tud_hid_descriptor_report_cb(uint8_t instance)
{
    (void) instance;
    return desc_hid_report;
}

// String Descriptors
static uint16_t _desc_str[32];

char const *string_desc_arr[] = {
    "Raspberry Pi",
    "Macropad",
    "000001"
};

uint16_t const * tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
    (void) langid;

    if (index == 0)
    {
        _desc_str[1] = 0x0409;
        _desc_str[0] = (TUSB_DESC_STRING << 8) | 4;
    }
    else
    {
        if ((index - 1) >= sizeof(string_desc_arr) / sizeof(string_desc_arr[0])) // # strings in array
        {
            return NULL;
        }
        const char *str = string_desc_arr[index - 1];

        uint8_t chr_count = strlen(str); // num characters
        for (uint8_t i = 0; i < chr_count; i++)
        {
            _desc_str[1 + i] = str[i];
        }
        _desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * chr_count + 2);

    } return _desc_str;
}