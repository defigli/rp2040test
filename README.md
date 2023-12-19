# RP2040 Test

## Table of Contents

- [Introduction](#introduction)
- [Cloning the repository](#cloning-the-repository)
- [Creating the makefiles](#creating-the-makefiles)
- [Building the examples](#building-the-examples)
- [Flashing the binary to the hardware](#flashing-the-binary-to-the-hardware)
- [Flashing the binary to the hardware (RP2040-Zero)](#flashing-the-binary-to-the-hardware-rp2040-zero)
- [Troubleshooting](#troubleshooting)

## Introduction

This project includes various examples of how to use the RP2040's features and peripherals. The code is written in C and uses the PICO SDK for development and the FreeRTOS micro kernel.

List of the examples:
- rp2040zero_ws28b12: use of the WS28B12 RGB pixel of the RP2040 Zero

Feel free to explore the code and try out the different examples!

## Cloning the repository

This repository includes the submodules to the [Raspberry Pi Pico SDK](https://www.raspberrypi.com/documentation/pico-sdk/) and the [FReeRTOS](https://www.freertos.org) kernel. Clone this repository together with the submodules with

```console
git clone --recurse-submodules
```

## Creating the makefiles

To create the makefiles in the folder `build`:

```console
cmake -S . -B build
```

If the folder does not exists it will be created.

## Building the examples

```console
cmake --build build
```

## Flashing the binary to the hardware

1. Ensure that the board is not connected to the computer
1. Press and hold the 'BOOT' button
1. Connect the board with the computer(while holding the button)
1. Release the 'BOOT' button
1. A mass storage device should appear on the computer
1. Copy the binary(with the .uf2 extension) on the mass storage device
1. After copying the controller should reboot.

## Flashing the binary to the hardware(RP2040-Zero)

The RP2040-Zero board has a separate RESET button.

1. Connect the board with the computer
1. Press and hold the 'RESET' button
1. Press and hold the 'BOOT' button
1. Release the 'RESET' button
1. Release the 'BOOT' button
1. A mass storage device should appear on the computer
1. Copy the binary(with the .uf2 extension) on the mass storage device
1. After copying the controller should reboot.

## Troubleshooting

### The board does not appear as mass storage device

Cheap USB charging cables, often referred to as "charge-only" cables, may not include data pins. These cables are designed solely for charging purposes and do not support data transfer between devices.

If you're experiencing issues when trying to transfer data using a cheap USB charging cable, it's likely because the cable does not have the necessary data pins. In such cases, it's recommended to use a high-quality USB cable that supports both charging and data transfer.
