.. zephyr:board:: sf32lb52_hspi

Overview
********

HSPI-SF32LB52 (Huangshan Pi) is an LCKFB development board based on the
SF32LB52x series chip SoC. This out-of-tree board definition currently starts
from the SiFli SF32LB52-DevKit-LCD because both boards use an SF32LB52 module.
Board-specific pin mappings should be checked against the Huangshan Pi hardware
schematic before enabling production peripherals.

More information about the board can be found at the
`HSPI-SF32LB52 website`_.

Hardware
********

HSPI-SF32LB52 provides the following hardware components:

- SF32LB52-MOD-1-N16R8 module based on SF32LB525UC6

  - 8MB OPI-PSRAM @ 144MHz (from SF32LB525UC6)
  - 128Mb QSPI-NOR @ 72MHz, STR mode
  - 48MHz crystal
  - 32.768KHz crystal
  - Onboard antenna (default) or IPEX antenna, selectable via 0 ohm resistor
  - RF matching network and other R/L/C components

- Dedicated screen interface

  - SPI/DSPI/QSPI, supports DDR mode QSPI, led out through 22-pin FPC and 40-pin
    header
  - 8-bit MCU/8080, led out through 22pin FPC and 40pin header.
  - Supports touch screens with I2C interface.

- Audio

  - Analog MIC input.
  - Analog audio output, onboard Class-D audio PA.

- USB

  - Type C interface, connected to USB to serial chip, enabling program
    download and software debug, can also supply power.
  - Type C interface, supports USB-2.0 FS, can also supply power.

- SD card

  - Supports TF cards using SPI interface, onboard Micro SD card slot.

Supported Features
==================

.. zephyr:board-supported-hw::

Programming and Debugging
*************************

.. zephyr:board-supported-runners::

Refer to `sftool website`_ for more information.

References
**********

.. target-notes::

.. _HSPI-SF32LB52 website:
   https://wiki.lckfb.com/zh-hans/hspi-sf32lb52/hardware/board.html

.. _sftool website:
   https://github.com/OpenSiFli/sftool
