# SF32LB52-HSPI pin 与板载器件对应表

来源：[`board-hardware-reference.html`](./board-hardware-reference.html)。

本文把 HTML 硬件参考页整理成 Markdown 速查表，重点列出：

- 每个 GPIO/网络连接到哪个板载器件、屏幕、传感器或接口。
- 每个器件反向对应哪些 pin。
- 30P 排针和 22P 屏幕 FPC 的完整脚位。
- 当前 Zephyr DTS 中已经按网表修正的项目和仍未建模的缺口。

## 快速结论

- 屏幕 QSPI 使用 `PA_00` 到 `PA_08`。`PA_01` 名义为背光 PWM,但屏幕板 V1.1 网表证实其屏侧引脚(FPC 镜像映射后为屏侧 pin 21)悬空 NC,实际无功能。
- 触摸屏 `FT6146-M00` 使用 `PA_33` SDA、`PA_37` SCL、`PA_41` INT、`PA_09` RST。
- 板上传感器 `LSM6DS3TR-C`、`MMC5603NJ`、`LTR-303ALS-01` 共享传感器 I2C：`PA_39` SDA、`PA_40` SCL，并有 `PA_31` INT1、`PA_30` 传感器电源控制。
- TF 卡占用 SPI1：`PA_24` DO、`PA_25` DI、`PA_28` CLK、`PA_29` CS，另有 `PA_27` DET。
- 充电 IC 以 BOM/SDK 为准为 `AW32001ECSR`，使用 `PA_11` SDA、`PA_10` SCL；AW32001 INT 为 `CHG_INT`，经 Q1 与 `PA_34` 硬件联动，不直接接 MCU GPIO；当前 DTS 已把 `i2c2` pinctrl 配到这两个脚，charger 子节点仍为 `disabled`。
- `LDO3_3V3` / `VDD33_VOUT2` 在核心板网名为 `VDD33_VOUT`，给板载 WS2812B 彩灯和振动马达供电；彩灯数据脚是 `PA_32`，马达 PWM 是 `PA_20_VIB_PWM`。

## Pin -> 器件/功能

| Pin/网络 | 信号/功能 | 连接的器件或资源 | 引出位置 | Zephyr/DTS 备注 |
|---|---|---|---|---|
| `PA_00` | LCD reset | AMOLED 屏幕 QSPI reset | 22P FPC pin 12, 模组 pin 47 | `display reset` 已用 |
| `PA_01` | LCD BL_PWM | 名义背光 PWM;屏幕板 V1.1 网表证实屏侧 NC 悬空 | 22P FPC pin 2, 模组 pin 46 | 已定论不建模(见 co5300 节点注释) |
| `PA_02` | LCD QSPI TE | AMOLED 屏幕 tearing effect | 22P FPC pin 11, 模组 pin 45 | LCDC QSPI |
| `PA_03` | LCD QSPI CS | AMOLED 屏幕 QSPI CS | 22P FPC pin 15, 模组 pin 44 | LCDC QSPI |
| `PA_04` | LCD QSPI CLK | AMOLED 屏幕 QSPI CLK | 22P FPC pin 13, 模组 pin 43 | LCDC QSPI |
| `PA_05` | LCD QSPI D0 | AMOLED 屏幕 QSPI D0 | 22P FPC pin 14, 模组 pin 42 | LCDC QSPI |
| `PA_06` | LCD QSPI D1 | AMOLED 屏幕 QSPI D1 | 22P FPC pin 16, 模组 pin 41 | LCDC QSPI |
| `PA_07` | LCD QSPI D2 | AMOLED 屏幕 QSPI D2 | 22P FPC pin 3, 模组 pin 40 | LCDC QSPI |
| `PA_08` | LCD QSPI D3 | AMOLED 屏幕 QSPI D3 | 22P FPC pin 4, 模组 pin 39 | LCDC QSPI |
| `PA_09` | TP_RSTN | 触摸屏 reset | 22P FPC pin 21, 模组 pin 38 | `ft6146 reset-gpios` 已建, 节点 disabled |
| `PA_10` | Charger I2C SCL | `AW32001ECSR` 充电 IC | 30P pin 30, 模组 pin 32 | I2C2 SCL 已配, charger 节点 disabled |
| `PA_11` | Charger I2C SDA | `AW32001ECSR` 充电 IC | 30P pin 29, 模组 pin 31 | I2C2 SDA 已配, charger 节点 disabled |
| `PA_12` | MPI2 CS | 模组内部 QSPI NOR Flash CS | 模组 pin 68 | N16R8 默认连接内部 NOR |
| `PA_13` | MPI2 D1 | 模组内部 QSPI NOR Flash D1 | 模组 pin 67 | N16R8 默认连接内部 NOR |
| `PA_14` | MPI2 D2 | 模组内部 QSPI NOR Flash D2 | 模组 pin 66 | N16R8 默认连接内部 NOR |
| `PA_15` | MPI2 D0 | 模组内部 QSPI NOR Flash D0 | 模组 pin 63 | N16R8 默认连接内部 NOR |
| `PA_16` | MPI2 CLK | 模组内部 QSPI NOR Flash CLK | 模组 pin 64 | N16R8 默认连接内部 NOR |
| `PA_17` | MPI2 D3 | 模组内部 QSPI NOR Flash D3 | 模组 pin 65 | N16R8 默认连接内部 NOR |
| `PA_18` | UART RXD | `CH340N` USB 转串口调试/下载 RX | 30P pin 27, 模组 pin 30 | USART1 RX |
| `PA_19` | UART TXD | `CH340N` USB 转串口调试/下载 TX | 30P pin 25, 模组 pin 29 | USART1 TX |
| `PA_20` | VIB PWM | 振动马达控制，马达供电来自 `VDD33_VOUT` | 30P pin 24, 模组 pin 28 | `pwm-vibrator` 已建，占位 disabled；pinctrl = `PA20_GPTIM2_CH1` |
| `PA_21` | — | 未出现在核心板网表(SoC 有该脚,模组未引出/板上未使用) | — | 无需建模 |
| `PA_22` | XTAL32K XI | 32.768 kHz 低速晶振输入 | 模组 pin 6 | 已配 LXT32 |
| `PA_23` | XTAL32K XO | 32.768 kHz 低速晶振输出 | 模组 pin 5 | 已配 LXT32 |
| `PA_24` | SPI1 DO | Micro SD/TF 卡 DO | 30P pin 20, 模组 pin 18 | SPI1 pinctrl |
| `PA_25` | SPI1 DI | Micro SD/TF 卡 DI | 30P pin 22, 模组 pin 19 | SPI1 pinctrl, 偏置应上拉 |
| `PA_26` | VSYS_1 to VCC33 switch | 电源路径/3.3 V 切换控制 | 模组 pin 20 | DTS `vcc_3v3` regulator，高有效 |
| `PA_27` | SD_DET | Micro SD/TF 卡插入检测 | 30P pin 23, 模组 pin 21 | 已配置:`sdhc0` 节点 `cd-gpios`(上拉,低有效) |
| `PA_28` | SPI1 CLK | Micro SD/TF 卡 CLK | 30P pin 21, 模组 pin 22 | SPI1 pinctrl |
| `PA_29` | SPI1 CS | Micro SD/TF 卡 CS | 30P pin 19, 模组 pin 23 | SPI1 pinctrl |
| `PA_30` | Sensor power control | 板上传感器电源控制/电源切换 | 30P pin 18, 模组 pin 24 | DTS `gs_3v3` regulator 已配 |
| `PA_31` | Sensor INT1 | `LSM6DS3TR-C` INT1 | 模组 pin 25, 未引出到 30P | `lsm6dsl irq-gpios` 已建, 节点 disabled |
| `PA_32` | RGB LED data | 板载 `WS2812B-2020` RGB LED，VDD 来自 `VDD33_VOUT` | 30P pin 17, 模组 pin 16 | DTS `led_strip` 已建, 节点 disabled |
| `PA_33` | TP I2C SDA | 触摸屏 `FT6146-M00` I2C SDA | 22P FPC pin 19, 模组 pin 15 | I2C1 SDA 已配 |
| `PA_34` | KEY1/PWRKEY | `SW1` HOME/开关机/长按复位 | 30P pin 26, 模组 pin 14 | KEY1 已配 |
| `PA_35` | USB DP | USB 2.0 FS Type-C DP | 30P pin 15, 模组 pin 13 | 未配置 |
| `PA_36` | USB DM | USB 2.0 FS Type-C DM | 30P pin 13, 模组 pin 12 | 未配置 |
| `PA_37` | TP I2C SCL | 触摸屏 `FT6146-M00` I2C SCL | 22P FPC pin 20, 模组 pin 11 | I2C1 SCL 已配 |
| `PA_38` | VSYS to VSYS_1 switch | 电源路径切换控制 | 模组 pin 10 | DTS `vsys_en` regulator 已配 |
| `PA_39` | Sensor I2C SDA | `LSM6DS3TR-C`、`MMC5603NJ`、`LTR-303ALS-01` 传感器 I2C SDA | 30P pin 14, 模组 pin 9 | I2C3 SDA 已配 |
| `PA_40` | Sensor I2C SCL | `LSM6DS3TR-C`、`MMC5603NJ`、`LTR-303ALS-01` 传感器 I2C SCL | 30P pin 16, 模组 pin 8 | I2C3 SCL 已配 |
| `PA_41` | TP INT | 触摸屏 `FT6146-M00` 中断 | 22P FPC pin 18, 模组 pin 7 | `ft6146 int-gpios` 已建, 节点 disabled |
| `PA_42` | Audio_PA_EN | 板载 Class-D 音频功放使能脚 | 模组 pin 4 | `audcodec pa-power-gpios` 已配 |
| `PA_43` | KEY2 | `SW2` 功能按键 | 30P pin 28, 模组 pin 3 | `key2` 已配 |
| `PA_44` | VBUS_DET | 充电器插入检测/电源路径检测 | 模组 pin 2 | 已配置:`zephyr,user` 的 `vbus-det-gpios`;不是 AW32001 INT |
| `MIC_BIAS` | MIC 偏置 | 板载 MEMS MIC | 模组 pin 36 | 模拟音频网络 |
| `MIC_ADC_IN` | MIC ADC 输入 | 板载 MEMS MIC | 模组 pin 37 | 模拟音频网络 |
| `AU_DAC1P_OUT` | DAC 正端输出 | 模拟音频输出/功放输入 | 模组 pin 33 | 模拟音频网络 |
| `AU_DAC1N_OUT` | DAC 负端输出 | 模拟音频输出/功放输入 | 模组 pin 34 | 模拟音频网络 |
| `VDD33_VOUT2` | 3.3 V 输出 | 模组内部 `LDO3_3V3` 输出；板级网名 `VDD33_VOUT` | 模组 pin 17 | DTS `ldo3_3v3` / `vdd33-vout` 已建；供 WS2812B 和振动马达 |
| `VBAT` | 电池/屏幕电源 | 电池、电源路径、屏幕/背光电源输入 | 30P pin 6, 22P FPC pin 1, 模组 pin 27 | 30P pin 5/6 为功耗测试短接点 |
| `VBATS` | 电池电压检测 | 模组电池电压检测输入 | 模组 pin 61 | 电源检测 |
| `USB_VBUS_5V` | USB 5 V | Type-C VBUS | 30P pin 1/2 | 可作 5 V 输入/输出, 取决于 USB 插入状态 |
| `VSYS`/`VSYS_S` | 系统电源 | VSYS 电源输入/功耗测试短接点 | 30P pin 8/7 | 常规工作需短接 |
| `VCC_3V3`/`VCC_3V3_S` | 3.3 V 电源 | 核心板 3.3 V/功耗测试短接点 | 30P pin 12/11, 22P FPC pin 17 | 常规工作需短接 |

## 器件/资源 -> Pin

| 器件/资源 | 对应 pin/网络 | 连接器位置 | 备注 |
|---|---|---|---|
| 1.85 inch AMOLED `ZC-A1D85W-010` | `PA_00` RST, `PA_01` BL_PWM, `PA_02` TE, `PA_03` CS, `PA_04` CLK, `PA_05` D0, `PA_06` D1, `PA_07` D2, `PA_08` D3 | 22P FPC pin 12/2/11/15/13/14/16/3/4 | 屏幕驱动 IC 为 `CO5300AF-01`, 屏幕电源 IC 为 `BV6802W` |
| 触摸屏 `FT6146-M00` | `PA_33` SDA, `PA_37` SCL, `PA_41` INT, `PA_09` RST | 22P FPC pin 19/20/18/21 | DTS pinctrl 和 GPIO 已建, 节点 disabled |
| 六轴传感器 `LSM6DS3TR-C` | `PA_39` SDA, `PA_40` SCL, `PA_31` INT1, `PA_30` power control | 30P pin 14/16/18, `PA_31` 仅模组 pin 25 | 与地磁、光照传感器共享 I2C |
| 地磁传感器 `MMC5603NJ` | `PA_39` SDA, `PA_40` SCL, `PA_30` power control | 30P pin 14/16/18 | 与其他板上传感器共享 I2C |
| 光照传感器 `LTR-303ALS-01` | `PA_39` SDA, `PA_40` SCL, `PA_30` power control | 30P pin 14/16/18 | 与其他板上传感器共享 I2C |
| 传感器上电链路 | `PA_38` VSYS 切换, `PA_26` VCC3V3 切换, `PA_30` sensor power control | 模组 pin 10/20/24, `PA_30` 还在 30P pin 18 | HTML 备注建议按 `PA_38 -> PA_26 -> PA_30` 顺序上电并延时 500 us |
| Micro SD/TF 卡座 | `PA_24` DO, `PA_25` DI, `PA_28` CLK, `PA_29` CS, `PA_27` DET | 30P pin 20/22/21/19/23 | 使用外扩 SPI1 时会与板载 TF 卡冲突 |
| `CH340N` USB 转串口 | `PA_19` TXD, `PA_18` RXD | 30P pin 25/27 | 用于下载和 Zephyr console/shell |
| USB 2.0 FS Type-C | `PA_35` DP, `PA_36` DM | 30P pin 15/13 | 启用 USB 设备后不能复用为普通 GPIO |
| `SW1` KEY1/PWRKEY | `PA_34` | 30P pin 26 | 开关机、HOME、长按复位相关 |
| `SW2` KEY2 | `PA_43` | 30P pin 28 | DTS 已配到 `gpioa_32_44` offset 11 |
| `AW32001ECSR` 充电 IC | `PA_11` SDA, `PA_10` SCL;`CHG_INT` 经 Q1/PA34 硬件联动 | 30P pin 29/30 | DTS i2c2 已建;无直接 AW32001 `int-gpios`, charger 节点 disabled |
| `WS2812B-2020` RGB LED | `PA_32` data；VDD = `VDD33_VOUT` 经 R51 | 30P pin 17 | DTS `worldsemi,ws2812-gpio` 节点已建, disabled |
| 振动马达 | `PA_20` PWM；供电 = `VDD33_VOUT` 经 R36 | 30P pin 24 | DTS `pwm-vibrator` 已建, disabled；不用马达时可作 GPIO/PWM |
| 板载 MEMS MIC | `MIC_BIAS`, `MIC_ADC_IN` | 模组 pin 36/37 | 模拟音频网络 |
| 模拟音频输出/功放 | `AU_DAC1P_OUT`, `AU_DAC1N_OUT`, `PA_42` Audio_PA_EN | 模组 pin 33/34/4 | DTS `pa-power-gpios` 已配到 PA42 |
| 电源管理网络 | `PA_44` VBUS_DET, `PA_38` VSYS switch, `PA_26` VCC33 switch, `VDD33_VOUT2`, `VBAT`, `VBATS` | 多为模组内部或 30P 电源脚 | `VDD33_VOUT2` 为 SF32LB52 内部 LDO3 输出；其余涉及 `LP5240HVF`、`ETA5055V330DS2F` 等电源网络 |
| 模组内部 QSPI NOR Flash | `PA_12` CS, `PA_13` D1, `PA_14` D2, `PA_15` D0, `PA_16` CLK, `PA_17` D3 | 模组 pin 68/67/66/63/64/65 | N16R8 模组默认连接内部 NOR, 不能当普通外部 GPIO |
| 32.768 kHz 低速晶振 | `PA_22` XI, `PA_23` XO | 模组 pin 6/5 | 当前 pinctrl 配为 LXT32, 不建议复用 |

## 30P 排针 CN3

| CN3 脚号 | 网络/管脚 | 功能 | 板上占用/连接 |
|---|---|---|---|
| 1 | `USB_VBUS_5V` | USB Type-C VBUS | 插 USB 时可作 5 V 输出, 未插 USB 时可作 5 V 输入 |
| 2 | `USB_VBUS_5V` | USB Type-C VBUS | 同 pin 1 |
| 3 | `GND` | 接地 | 电源地 |
| 4 | `GND` | 接地 | 电源地 |
| 5 | `VBAT_S` | VBAT 电源输出 | 与 pin 6 短接, 用于功耗测试 |
| 6 | `VBAT` | VBAT 电源输入 | 连接充电 IC VBAT 和模组 VBATS |
| 7 | `VSYS_S` | VSYS 电源输出 | 与 pin 8 短接, 用于功耗测试 |
| 8 | `VSYS` | VSYS 电源输入 | 连接模组 VSYS 和其他 VSYS 输入 |
| 9 | `GND` | 接地 | 电源地 |
| 10 | `GND` | 接地 | 电源地 |
| 11 | `VCC_3V3_S` | 3.3 V 电源输出 | 与 pin 12 短接, 用于功耗测试 |
| 12 | `VCC_3V3` | 3.3 V 电源输入 | 核心板主 3.3 V |
| 13 | `PA_36_USB_DM` | USB DM | USB 2.0 FS DM |
| 14 | `PA_39_I2C3_SDA` | Default I2C SDA | 板上传感器 I2C SDA |
| 15 | `PA_35_USB_DP` | USB DP | USB 2.0 FS DP |
| 16 | `PA_40_I2C3_SCL` | Default I2C SCL | 板上传感器 I2C SCL |
| 17 | `PA_32` | RGB LED data/GPIO | 板载 `WS2812B-2020` RGB LED 数据，VDD 来自 `VDD33_VOUT` |
| 18 | `PA_30` | Sensor power control | 板上传感器电源控制 |
| 19 | `PA_29_SPI1_CS` | SPI1 CS/GPIO | 板载 TF 卡 SPI1 CS |
| 20 | `PA_24_SPI1_DO` | SPI1 DO/GPIO | 板载 TF 卡 SPI1 DO |
| 21 | `PA_28_SPI1_CLK` | SPI1 CLK/GPIO | 板载 TF 卡 SPI1 CLK |
| 22 | `PA_25_SPI1_DI` | SPI1 DI/GPIO | 板载 TF 卡 SPI1 DI |
| 23 | `PA_27_SD_DET` | SD_DET/GPIO | 板载 TF 卡插入检测 |
| 24 | `PA_20_VIB_PWM` | VIB PWM/GPIO | 振动马达 PWM，马达供电来自 `VDD33_VOUT` |
| 25 | `PA_19_UART_TXD` | Debug UART TXD | 调试/下载 UART TX, 连接 USB 转串口 |
| 26 | `PA_34_KEY1` | KEY1 | SW1/PWRKEY/HOME |
| 27 | `PA_18_UART_RXD` | Debug UART RXD | 调试/下载 UART RX, 连接 USB 转串口 |
| 28 | `PA_43_KEY2` | KEY2 | SW2 功能按键 |
| 29 | `PA_11_I2C2_SDA` | Charger I2C SDA | `AW32001ECSR` 充电 IC I2C SDA |
| 30 | `PA_10_I2C2_SCL` | Charger I2C SCL | `AW32001ECSR` 充电 IC I2C SCL |

## 22P QSPI 屏幕 FPC

| FPC 脚号 | 网络/管脚 | 功能 | 板上占用/连接 |
|---|---|---|---|
| 1 | `VBAT` | VBAT 电源输出 | 屏幕/背光电源输入 |
| 2 | `PA_01_LCD_BL_PWM` | BL PWM | LCD 背光 PWM |
| 3 | `PA_07_LCD_QSPI_D2` | QSPI D2 | LCD QSPI D2 |
| 4 | `PA_08_LCD_QSPI_D3` | QSPI D3 | LCD QSPI D3 |
| 5 | `NC` | NC | 未用 |
| 6 | `NC` | NC | 未用 |
| 7 | `NC` | NC | 未用 |
| 8 | `NC` | NC | 未用 |
| 9 | `NC` | NC | 未用 |
| 10 | `NC` | NC | 未用 |
| 11 | `PA_02_LCD_QSPI_TE` | QSPI TE | LCD QSPI TE |
| 12 | `PA_00_LCD_QSPI_RSTB` | LCD Reset | LCD reset |
| 13 | `PA_04_LCD_QSPI_CLK` | QSPI CLK | LCD QSPI CLK |
| 14 | `PA_05_LCD_QSPI_D0` | QSPI D0 | LCD QSPI D0 |
| 15 | `PA_03_LCD_QSPI_CS` | QSPI CS | LCD QSPI CS |
| 16 | `PA_06_LCD_QSPI_D1` | QSPI D1 | LCD QSPI D1 |
| 17 | `VDD_3V3` | 3.3 V 电源输出 | 屏幕/触摸 3.3 V |
| 18 | `PA_41_TP_INT` | 触摸屏 INT | 触摸屏中断 |
| 19 | `PA_33_TP_I2C1_SDA` | 触摸屏 I2C SDA | 触摸 I2C SDA |
| 20 | `PA_37_TP_I2C1_SCL` | 触摸屏 I2C SCL | 触摸 I2C SCL |
| 21 | `PA_09_TP_RSTN` | 触摸屏 Reset | 触摸 reset |
| 22 | `GND` | 接地 | FPC shield/固定脚也接 GND |

## DTS 当前状态与剩余缺口

| 项目 | 当前工程配置 | 硬件资料对应 | 状态/建议 |
|---|---|---|---|
| KEY2 | `&gpioa_32_44 11`, 即 `PA_43` | `PA_43_KEY2`, 30P pin 28, `SW2` | 已按网表修正 |
| 触摸 I2C SCL | `PA37_I2C1_SCL` | `PA_37_TP_I2C1_SCL`, 22P FPC pin 20 | 已按网表修正 |
| LCD AVDD enable | 无独立 AVDD GPIO | `PA_37` 是触摸 SCL, AMOLED AVDD 由屏幕板电源 IC 产生 | 当前 DTS 未占用 PA37 作 AVDD, 与网表一致 |
| LED0 / VCC_3V3 EN | `vcc_3v3` regulator = `PA_26` active high | SDK `LED1_ACTIVE_HIGH`, 实际是 VCC_3V3 rail enable | 已修正为 regulator；不要当普通 LED 使用 |
| Audio PA power | `pa-power-gpios = PA_42` | `PA_42` -> U6(NS4150B), SDK `AW8155_GPIO_PIN=42` | 已按网表修正 |
| Touch reset/interrupt | `ft6146@38` 已建, status disabled | `PA_09` Reset, `PA_41` INT, `PA_33`/`PA_37` I2C | GPIO 已建, 驱动 bring-up 前保持 disabled |
| Charger | `i2c2` okay, `charger@49` disabled | `PA_10/PA_11` I2C2, U3 AW32001ECSR;`CHG_INT` 不直连 MCU GPIO | pinctrl 已建, 无 upstream driver 时保持 disabled |
| RGB LED | `led-strip` 已建, status disabled | `PA_32` -> LED3 WS2812B-2020；VDD = `VDD33_VOUT` | `worldsemi,ws2812-gpio` 使用 `gpios` 属性, 时序需实测 |
| VDD33_VOUT / LDO3 | `ldo3_3v3` 已建, `regulator-name = "vdd33-vout"` | `VDD33_VOUT2` / `VDD33_VOUT` 给 WS2812B 和振动马达供电 | 内部 LDO3 输出，不是外部输入；负载总电流按 150 mA 预算 |
| 振动马达 | `pwm-vibrator` 已建, status disabled；`PA20_GPTIM2_CH1` pinctrl 已建 | `PA_20_VIB_PWM` 控制马达，供电来自 `VDD33_VOUT` 经 R36 | 启用前确认 PWM 频率、占空比和启动电流 |
| Backlight | 不建模(已定论) | `PA_01_LCD_BL_PWM`, 22P FPC pin 2 → 屏侧 pin 21 | 屏幕板 V1.1 网表证实屏侧 NC 悬空,SDK 拉高该脚系无操作 |
| SD 卡 / SD_DET | 已配置(2026-07-02) | `PA_24/25/28/29` SPI1 + `PA_27` | `sdhc0`(`zephyr,sdhc-spi-slot`)+ `sdmmc` 磁盘 + `cd-gpios`;PA_29 改 GPIO 片选(`cs-gpios`) |
| 电池电压 / VBUS | 已配置(2026-07-02) | GPADC 内部通道 7 / `PA_44` | `&gpadc` + `channel@7`(eFuse 校准);`zephyr,user`(`io-channels` "vbat"、`vbus-det-gpios`) |
| USB | 未配置 | `PA_35` `PA_36` | SoC 级无 usbd 节点,待 zephyr fork 支持 |

## 传感器补充说明

HTML 中确认的板上传感器型号为：

- `LSM6DS3TR-C`：六轴 IMU。
- `MMC5603NJ`：地磁传感器。
- `LTR-303ALS-01`：环境光传感器。

三者共享 `PA_39`/`PA_40` 传感器 I2C。当前 DTS 已按网表建立 `lsm6dsl@6a`、`mmc56x3@30`、`ltr303@29` 占位节点并默认 disabled；`PA_31` 已由核心板网表确认连接到 U13 `LSM6DS3TR-C` INT1。
