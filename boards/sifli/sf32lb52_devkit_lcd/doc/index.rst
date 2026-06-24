.. zephyr:board:: sf32lb52_devkit_lcd

Overview
********

SF32LB52-DevKit-LCD is a development board based on the SF32LB52x series chip
SoC. It is mainly used for developing various applications based on
SPI/DSPI/QSPI or MCU/8080 interface display screens.

This directory collects the consolidated hardware reference material for the
board. The canonical Zephyr board definition (device tree, Kconfig, defconfig)
lives in ``zephyr/boards/sifli/sf32lb52_devkit_lcd/`` and is treated as the
authoritative source for pin assignments in the reference page below.

More information about the board can be found at the
`SF32LB52-DevKit-LCD website`_ and the `Zephyr board documentation`_.

Hardware
********

SF32LB52-DevKit-LCD provides the following hardware components:

- SF32LB52-MOD-1-N16R8 module based on SF32LB525UC6

  - 8MB OPI-PSRAM @ 144MHz (from SF32LB525UC6)
  - 128Mb QSPI-NOR (PY25Q128HA) @ 72MHz, STR mode
  - 48MHz crystal
  - 32.768KHz crystal
  - Onboard antenna (default) or IPEX antenna, selectable via 0 ohm resistor
  - RF matching network and other R/L/C components

- Dedicated screen interface

  - SPI/DSPI/QSPI, supports DDR mode QSPI, led out through 22-pin FPC (J0102)
    and 40-pin Raspberry-Pi-style header (J0117).
  - 8-bit MCU/8080, led out through the 22-pin FPC and 40-pin header.
  - Supports touch screens with I2C interface (SDA ``PA_33`` / SCL ``PA_30``).
  - LCD backlight driven by an onboard AW9962 boost (``LEDA``/``LEDK``,
    PWM control on ``PA_01``).

- Audio

  - Analog MIC input (WMM7037 MEMS microphone).
  - Analog audio output, onboard NS4150B Class-D audio PA (enable ``PA_10``).

- USB

  - Type C interface, connected to CH343P USB to serial chip, enabling program
    download and software debug, can also supply power.
  - Type C interface, supports USB-2.0 FS (``PA_35``/``PA_36``), can also
    supply power.

- SD card

  - Supports TF cards using SPI interface (SPI1 ``PA_24/25/28/29``), onboard
    Micro SD card slot.

- Board peripherals

  - SK6812MINI-HS RGB LED (data ``PA_32``).
  - User LED on ``PA_26`` (shared with TF-card detect), ETA9640P linear charger
    and related power path components.

Hardware Reference Artifacts
============================

The local board documentation directory includes the organized open hardware
artifacts and a consolidated pin/resource reference page. Pin assignments on the
reference page were derived directly from the V1.2.0 schematic netlist and
cross-checked against the Zephyr device tree.

- :download:`Pin and board resource reference <pin-resources.html>`
- :download:`Board schematic PDF <SF32LB52-DevKit-LCD_V1.2.0/SF32LB52-DevKit-LCD-1-SCH_V1.2.0.pdf>`
- :download:`Board schematic netlist (PADS export) <SF32LB52-DevKit-LCD_V1.2.0/SF32LB52-DevKit-LCD-1-SCH_V1.2.0.txt>`
- :download:`Board BOM spreadsheet <SF32LB52-DevKit-LCD_V1.2.0/SF32LB52-DevKit-LCD-1-BOM-V1.2.0.xlsx>`
- :download:`Board PCB PDF <SF32LB52-DevKit-LCD_V1.2.0/SF32LB52-DevKit-LCD_PCB_V1.2.0.pdf>`
- :download:`Board placement drawing <SF32LB52-DevKit-LCD_V1.2.0/SF32LB52-DevKit-LCD_PLACEMENT_V1.2.0.pdf>`

The generic SF32LB52x chip / SF32LB52-MOD-1 module specifications are shared by
all SiFli boards in this tree and are kept under ``boards/sifli/common/doc``:

- :download:`SF32LB52x chip datasheet <../../common/doc/DS5201-SF32LB52x-芯片技术规格书 V2p5p3.pdf>`
- :download:`SF32LB52x user manual <../../common/doc/UM5201-SF32LB52x-用户手册 V0p8p8.pdf>`
- :download:`SF32LB52x product brief <../../common/doc/PB5201-SF32LB52x-产品简介.pdf>`
- :download:`SF32LB52-MOD-1 module datasheet <../../common/doc/DS5203-SF32LB52-MOD-1技术规格书 V0p3.pdf>`
- :download:`Module schematic PDF <../../common/doc/SF32LB52-MOD-1-V1.0.0/SF32LB52-MOD-1_SCH_V1.0.0.pdf>`
- :download:`Module PCB PDF <../../common/doc/SF32LB52-MOD-1-V1.0.0/SF32LB52-MOD-1_PCB_V1.0.0.pdf>`

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

.. _SF32LB52-DevKit-LCD website:
   https://wiki.sifli.com/board/sf32lb52x/SF32LB52-DevKit-LCD.html

.. _Zephyr board documentation:
   https://docs.zephyrproject.org/latest/boards/sifli/sf32lb52_devkit_lcd/doc/index.html

.. _sftool website:
   https://github.com/OpenSiFli/sftool
