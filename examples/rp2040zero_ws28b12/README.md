# rp2040zero_ws28b12

This example shows the usage of the builtin WS28B12 RGB led of the [RP2040-Zero](https://www.waveshare.com/wiki/RP2040-Zero). It uses the [FReeRTOS](https://www.freertos.org) kernel.

A separate RTOS task initializes the PIO controller and cycles through the colors.

For accessing the LED the PIO controller of the RP2040 is used.
