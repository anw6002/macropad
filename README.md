# Custom Hot-Swappable Macropad for League of Legends

**Table of Contents**

[Overview](#overview) · [Hardware Design: Version 1](#hardware-design-version-1) · [Version 1 PCB Specifications](#ver-1-pcb-specifications) · [Hardware Components](#hardware-components) · [GPIO Mapping](#gpio-mapping) · [Button Module Specifications](#button-module-specifications)  

[Hardware Design: Version 2 (In Progress)](#hardware-design-version-2-in-progress)


## Overview

This project implements a custom USB macropad using the Raspberry Pi Pico.
The macropad is designed for League of Legends, providing dedicated QWER ability
keys, DF keys, and rotary encoder for volume controls. The firmware is written in C using the
Raspberry Pi Pico SDK, and the final hardware is designed in KiCad and
manufactured as a custom PCB.

There is a planned joystick expansion for character movement using League's new WASD support.
Up to 20 additional keys will be included in the expansion. 

### Technologies
- C
- CAD (3D Printed Case)
- Raspberry Pi Pico SDK
- TinyUSB
- KiCad
- Altium
- Git
- VS Code

## Hardware Design: Version 1

The PCB is designed in KiCad for a Raspberry Pi Pico-based USB HID macropad (also compatible with the Raspberry Pi Pico 2). The board is intended to support six mechanical keyboard switches, with hot-swap sockets for easier switch replacement. The PCB will connect each key to a dedicated GPIO pin, with the switches sharing a common ground. The PCB design will accommodate a rotary encoder with push button for volume-control functionality.

### Ver. 1 PCB Specifications

- **EDA software:** KiCad 10
- **Microcontroller:** Raspberry Pi Pico
- **Input switches:** 6 mechanical keyboard switches
- **Switch mounting:** Kailh CPG151101S11 hot-swap sockets
- **PCB layout:** Custom-designed PCB with a 4-key top row and 2 additional keys on the right side
- **Enclosure:** Custom 3D-printed case (planned)
- **Connectivity:** USB through the Pico's onboard connector
- **Firmware:** C using the Raspberry Pi Pico SDK and TinyUSB

### Hardware Components

| Component | Purpose | 
|---|---|
| Raspberry Pi Pico | Microcontroller and USB HID interface |
| Kailh CPG151101S11 hot-swap sockets | Allow switches to be replaced without desoldering |
| MX Mechanical keyboard switches | Physical key inputs |
| Custom PCB | Mounts switches and microcontroller connections |
| Header pins / sockets | Connects the Pico to the PCB |
| 3D-printed enclosure | Houses and protects the assembled macropad |
| Rotary encoder | volume control knob |


### GPIO Mapping

| Key | Pico GPIO | Physical Pin |
|---|---:|---:|
| Q | GP01 | 02 |
| W | GP05 | 07 |
| E | GP09 | 12 |
| R | GP15 | 20 |
| D | GP13 | 17 |
| F | GP14 | 19 |

The switches use a shared ground connection, with GPIO internal pull-ups intended to be enabled in firmware.

## Button Module Specifications

### Purpose

The button module provides an interface for initializing and scanning the macropad's pushbuttons. It abstracts the GPIO hardware and \
reports button press and release events.

### Functional Requirements
- Initialize all configured GPIO pins as digital inputs.
- Enable the Raspberry Pi Pico's internal pull-up resistors.
- Scan all buttons periodically.
- Detect button press events.
- Detect button release events.
- Generate exactly one press event for each physical press.
- Generate exactly one release event for each physical release.

### Assumptions
- Buttons are active-low.
- One side of every switch is connected to a GPIO pin.
- The opposite side is connected to ground.
- Internal pull-up resistors are enabled.

### Button Debouncing
This Macropad utilizes MX Mechanical Keyboard switches that connect the GPIO pin to GND when pressed. \
\
When pressing a mechanical keyboard switch, metal contacts in the switch can briefly bounce, causing a short duration in which the microcontroller
reads a rapid fluctuation between HIGH (1) and LOW (0) for the pin. Debouncing is implemented to make sure a single button press does not register as multiple
events. \
\
Software debouncing filters out these transient fluctuations by accepting a state change only after the button state has remained stable for a set amount of time, preventing
a single physical press from being registered as multiple events. For this repository's implementation, the debounce timer is set to 10 ms.

## Hardware Design: Version 2 (In Progress)

V2 is a substantial redesign of the original macropad, introducing a keyboard matrix architecture and joystick integration for expanded input functionality.

The updated hardware is being designed in Altium Designer, with a redesigned PCB and schematic.

### Key Improvements

Keyboard Matrix: Transitioning from individual GPIO connections for each switch to a row-column scanning architecture, reducing GPIO requirements and supporting an expanded number of keys.

Anti-Ghosting Diodes: Incorporating diodes into the keyboard matrix to prevent unintended key detection when multiple switches are pressed simultaneously.

Joystick Integration: Adding an analog joystick for WASD character movement, supporting League of Legends' WASD control scheme.

Expanded Input Support: Designing the hardware to accommodate additional mechanical keyboard switches and joystick inputs.


