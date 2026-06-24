.. zephyr:board:: sf32lb52_hspi

Overview
********

SF32LB52-HSPI (Huangshan Pi) is an LCKFB development board based on the
SF32LB52x series chip SoC. This out-of-tree board definition currently starts
from the SiFli SF32LB52-DevKit-LCD because both boards use an SF32LB52 module.
Board-specific pin mappings should be checked against the Huangshan Pi hardware
schematic before enabling production peripherals.

More information about the board can be found at the
`SF32LB52-HSPI website`_ and the `SiFli official board guide`_.

Hardware
********

SF32LB52-HSPI provides the following hardware components:

- SF32LB52-MOD-1-N16R8 module based on SF32LB525UC6

  - 8MB OPI-PSRAM @ 144MHz (from SF32LB525UC6)
  - 128Mb QSPI-NOR @ 72MHz, STR mode
  - 48MHz crystal
  - 32.768KHz crystal
  - Onboard antenna (default) or IPEX antenna, selectable via 0 ohm resistor
  - RF matching network and other R/L/C components

- Dedicated screen interface

  - 1.85 inch 390 x 450 AMOLED display, ZC-A1D85W-010, with CO5300AF-01 display
    IC and BV6802W display power IC.
  - SPI/DSPI/QSPI, supports DDR mode QSPI, led out through 22-pin FPC and 40-pin
    header.
  - 8-bit MCU/8080, led out through 22pin FPC and 40pin header.
  - FT6146-M00 touch controller with I2C interface.

- Audio

  - Analog MIC input.
  - Analog audio output, onboard Class-D audio PA.

- USB

  - Type C interface, connected to CH340N USB to serial chip, enabling program
    download and software debug, can also supply power.
  - Type C interface, supports USB-2.0 FS, can also supply power.

- SD card

  - Supports TF cards using SPI interface, onboard Micro SD card slot.

- Board peripherals

  - SK6812MINI-HS RGB LED.
  - LSM6DS3TR-C six-axis sensor, MMC5603NJ geomagnetic sensor, and
    LTR-303ALS-01 ambient light sensor.
  - AW32001 linear charger (I2C2, address 0x49) and related power path
    components.

Hardware Reference Artifacts
============================

The local board documentation directory includes downloaded open hardware
artifacts and a consolidated pin/resource reference page:

- :download:`Board hardware reference <board-hardware-reference.html>`
  (30P/22P connectors, 68-pin module map, board resources, and the
  netlist x SDK x DTS cross-validation summary)
- :download:`Huangshan Pi reference notes <SF32LB52-黄山派-资料.md>`
  (synced from the SiFli SDK; section 6 is the full per-pin
  netlist x SDK x Zephyr-DTS cross-check)
- :download:`On-board sensors and device reference <sensors.html>`
  (per-device pinout, I2C address, Zephyr compatible / bring-up notes; links the
  datasheets under ``doc/datasheets/``)
- :download:`Core board schematic PDF <PDF_立创·黄山派SF32LB52开发板/SCH_黄山派核心板_SCH_V1.2_2026-06-24.pdf>`
- :download:`LCD board schematic PDF <PDF_立创·黄山派SF32LB52开发板/SCH_黄山派LCD屏幕板_SCH_V1.1_2026-06-24.pdf>`
- :download:`Core board netlist <Netlist_黄山派核心板_SCH_V1.2_2026-06-24.tel>`
- :download:`LCD board netlist <Netlist_黄山派LCD屏幕板_SCH_V1.1_2026-06-24.tel>`
- :download:`BOM spreadsheet <BOM_立创·黄山派SF32LB52开发板.xlsx>`
- :download:`SF32LB52x chip datasheet <../../common/doc/DS5201-SF32LB52x-芯片技术规格书 V2p5p3.pdf>`
- :download:`SF32LB52x user manual <../../common/doc/UM5201-SF32LB52x-用户手册 V0p8p8.pdf>`
- :download:`SF32LB52x product brief <../../common/doc/PB5201-SF32LB52x-产品简介.pdf>`
- :download:`SF32LB52-MOD-1 module datasheet <../../common/doc/DS5203-SF32LB52-MOD-1技术规格书 V0p3.pdf>`
- :download:`Original EasyEDA Pro project archive <ProPrj_立创·黄山派SF32LB52开发板_copy_2026-06-24.epro2>`
- :download:`Updated EasyEDA Pro project <ProPrj_立创·黄山派SF32LB52开发板V1.2(202504250924).epro>`
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

.. _SF32LB52-HSPI website:
   https://wiki.lckfb.com/zh-hans/hspi-sf32lb52/hardware/board.html

.. _SiFli official board guide:
   https://wiki.sifli.com/board/sf32lb52x/SF32LB52-%E9%BB%84%E5%B1%B1%E6%B4%BE.html

.. _sftool website:
   https://github.com/OpenSiFli/sftool
