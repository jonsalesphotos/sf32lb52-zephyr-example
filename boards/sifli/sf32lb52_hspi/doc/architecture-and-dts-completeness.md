# SF32LB52-HSPI(黄山派)Zephyr 工程架构与 DTS 完整性研究报告

> 生成日期:2026-07-02
> 工作区:`E:\1\sf32lb52-zephyr-example`
> 参考:`E:\1\OpenSiFli\SiFli-SDK`(板级 `customer/boards/sf32lb52-lchspi-ulp*`)、`E:\1\OpenSiFli\xiaozhi-sf32`、本目录既有硬件文档
> 配套 HTML 版:[architecture-and-dts-completeness.html](./architecture-and-dts-completeness.html)

---

## 0. 快速结论(TL;DR)

1. **工程架构**:这是一个标准的 Zephyr `west` workspace,以 `application/` 为 manifest 仓库,拉取 OpenSiFli 的 **zephyr-downstream** fork 和 **hal_sifli** 模块。黄山派板级定义 `sf32lb52_hspi` 放在应用仓库内(out-of-tree board),继承自 zephyr fork 内的 `sf32lb52_devkit_lcd`。
2. **DTS 器件覆盖度**:板上**所有主要器件都已经出现在 DTS 中**——屏幕、触摸、三颗传感器、充电 IC、三路板级稳压器 + 两路片内 LDO、按键、RGB 灯、振动马达、音频功放使能全部有节点;其中屏幕/电源/音频/存储/蓝牙/控制台等 **13 类已启用(okay)**,触摸/传感器/充电/RGB/马达 **7 个节点为 disabled 占位**(等待 bring-up,策略合理)。
3. **缺口状态(2026-07-02 已补全,见 §2.6)**:电池电量测量(GPADC 内部通道 7)、TF 卡设备节点(含 PA_27 卡检测)、PA_44 VBUS 检测已全部补入 DTS 并通过两轮构建验证;PA_01 经屏幕板网表核实为 NC(无需建模)。剩余:USB 与 SDIO 需要 SoC 级(zephyr fork)支持,AW32001 尚无驱动(占位绑定已添加)。
4. **与 SDK 的差异中,多数是本工程"更正确"**:PA_26 在 SDK 里被标成 LED1,实为 VCC_3V3 载荷开关使能,本工程已按网表建模为 regulator;PA_44 在 SDK 里配置为 charger INT,网表核实为 VBUS_DET 分压。**PA_01 矛盾已定论**:核心板网 `PA_01_LCD_BL_PWM` 经 22P FPC pin 2 映射到屏幕板 FPC pin 21(映射关系 `屏侧 = 23 − 核心板侧`,14 个信号逐一验证吻合),而屏幕板 V1.1 网表中该脚不属于任何网络(**NC 悬空**),屏幕板本身是纯无源转接板(电源 IC 在屏排线模组内部)。SDK 上电拉高 PA_01(`LCD_VADD_EN`)在本屏幕版本上是无操作,DTS 不建模是正确的。

---

## 1. 工程整体架构

### 1.1 west workspace 布局

```
E:\1\sf32lb52-zephyr-example\           ← west workspace 根(非 git 仓库)
├── .west\config                         ← manifest = application/west.yml
├── application\                         ← ★ manifest 仓库(应用 + 板级,git 仓库)
│   ├── west.yml                         ← 声明依赖:zephyr-downstream、lvgl 等
│   ├── app\                             ← 主应用(blink + sensor 模板,源自 Nordic
│   │                                       example-application 脚手架)
│   ├── samples\
│   │   ├── uart_shell\                  ← Shell 样例(另带 usb.overlay / bt.overlay)
│   │   └── smf_thermostat\              ← 状态机框架(SMF)恒温器演示
│   ├── drivers\
│   │   ├── blink\gpio_led.c             ← 自定义驱动示例("blink" 类)
│   │   └── sensor\example_sensor\       ← 自定义传感器驱动示例
│   ├── dts\bindings\                    ← 上述自定义驱动的 DT 绑定
│   ├── lib\custom\                      ← 自定义库示例
│   └── boards\
│       ├── sifli\sf32lb52_hspi\         ← ★ 黄山派板级(DTS/pinctrl/文档/网表)
│       └── vendor\custom_plank\         ← 脚手架自带的模板示例板
├── zephyr\                              ← OpenSiFli/zephyr-downstream(Zephyr fork)
│   ├── soc\sifli\sf32\sf32lb52x\        ← SoC 启动/内存/Kconfig
│   ├── dts\arm\sifli\sf32lb52x.dtsi     ← SoC 设备树(外设全景见 §1.3)
│   ├── dts\bindings\...\sifli,*.yaml    ← SiFli 绑定
│   ├── boards\sifli\sf32lb52_devkit_lcd\ ← 官方 DevKit-LCD 板(HSPI 的蓝本)
│   └── drivers\...                      ← 20+ 类 SiFli 驱动(见 §1.3)
├── modules\
│   ├── hal\sifli\                       ← hal_sifli:BF0 HAL/LL、cmsis 寄存器头、
│   │                                       ipc_queue(双核 IPC)、LCPU 初始化
│   ├── hal\cmsis_6\                     ← ARM CMSIS 6
│   ├── fs\{fatfs, littlefs}             ← 文件系统(TF 卡/Flash 会用到)
│   └── lib\{gui\lvgl, cmsis-dsp, cmsis-nn, nanopb, zcbor}
└── bootloader\mcuboot\                  ← 可选 bootloader/OTA(west 模块)
```

### 1.2 依赖关系(west.yml)

- `application/west.yml` 只有两个直接 project:**lvgl**(锁定 commit)和 **zephyr**(OpenSiFli 的 `zephyr-downstream`,`main` 分支)。
- 其余模块(cmsis_6、**hal_sifli**、cmsis-dsp/nn、fatfs、littlefs、mcuboot、nanopb、zcbor)通过 zephyr 的 manifest **name-allowlist** 导入——这是精简过的白名单,只保留 SF32LB52x 需要的模块。
- 板级 `sf32lb52_hspi` 在 **application 仓库**里(out-of-tree),SoC 支持在 **zephyr fork** 里,寄存器级代码在 **hal_sifli** 里。三层职责清晰:改板上外设 → 动 application;改外设驱动 → 动 zephyr fork;改寄存器/HAL → 动 hal_sifli。

### 1.3 Zephyr fork 中的 SiFli 支持全景

SoC 设备树 `zephyr/dts/arm/sifli/sf32lb52x.dtsi` 声明的外设,与对应驱动(全部位于 `zephyr/drivers/`):

| 子系统 | DTS 节点 | 驱动 | 说明 |
|---|---|---|---|
| 时钟 | `hxt48` `lxt32` `hrc48` `rcc_clk`(dll1/dll2) `pmuc_clk` | `clock_control_sf32lb_*.c` | HSPI 配置:系统 240 MHz(DLL1)、MPI1 288 MHz(DLL2) |
| 复位 | `rcc_rst` | `reset_sf32lb.c` | |
| 引脚复用 | `pinctrl`(PA 0-44 + SA 0-12) | `pinctrl_sf32lb52x.c` | 宏形如 `PA33_I2C1_SDA` |
| GPIO | `gpioa_00_31` / `gpioa_32_44` | `gpio_sf32lb.c` | Zephyr 端口上限 32 pin,故拆两组 |
| 串口 | `usart1/2/3` | `uart_sf32lb.c` | HSPI 仅启用 usart1 |
| I2C | `i2c1~i2c4` | `i2c_sf32lb.c` | HSPI 启用 1/2/3 |
| SPI | `spi1/spi2` | `spi_sf32lb.c` | HSPI 启用 spi1(TF 卡总线) |
| DMA | `dmac`(8 通道) | `dma_sf32lb.c` | |
| 存储 | `mpi1`(OPI PSRAM)/`mpi2`(QSPI NOR) | `memc_sf32lb_mpi_opi_psram.c` / `flash_sf32lb_mpi_qspi_nor.c` | |
| 显示 | `lcdc` + `mipi-dbi` 子节点 | `mipi_dbi_sf32lb.c` + `display_co5300_qspi.c` | CO5300 QSPI 面板驱动在 fork 内 |
| 触摸 | —(板级 i2c 子节点) | `input_ft6146.c` | 绑定 `focaltech,ft6146` 已有 |
| 音频 | `audcodec` | `sf32lb_codec.c` | 含 DAC(喇叭)/ADC(麦克风)两路 DMA |
| 蓝牙 | `mailbox` | `hci_sf32lb.c` | HCI over 双核邮箱,控制器跑在 LCPU;依赖 hal_sifli 的 `ipc_queue` 与 LCPU 固件安装(`lcpu_install.c`) |
| ADC | `gpadc` | `adc_sf32lb.c` | **HSPI 板级未启用 → 电池测压缺口** |
| 定时/PWM | `atim`(+pwm)、`gptim2`(+pwm) | `pwm_sf32lb_atim.c` / `pwm_sf32lb_gpt.c` | **无 gptim1/btim/lptim 节点** |
| RTC | `rtc`(+备份寄存器) | `rtc_sf32lb.c` | |
| 看门狗 | `wdt` | `wdt_sf32lb.c` | |
| 安全 | `crc` `crypto`(AES) `trng` `efuse` | `crc_sf32lb.c` `crypto_sf32lb.c` `entropy_sf32lb.c` `otp_sifli_efuse.c` | efuse 含 UID/ADC 出厂校准 |
| 温度 | `tsen` | `sf32lb_tsen.c` | 片内温度传感器 |
| 电源 | `pmuc` regulators(`ldo1_1v8` `ldo2_3v3` `ldo3_3v3`) | `regulator_sf32lb_ldo.c` | |
| 其他 | `hwinfo` | `hwinfo_sifli_sf32lb52x.c` | |

**SoC 级尚未支持(silicon 有、dtsi 里没有)**:USB(USBD)、SDIO(SD1)、GPTIM1、BTIM、LPTIM、I2S、AUDPRC、EPIC(2D 加速)、ezip 等。这解释了 §2.4 中部分板级缺口的根因。

### 1.4 hal_sifli 模块(`modules/hal/sifli`)

- `cmsis/sf32lb52x/`:寄存器定义(`register.h`,如 `GPTIM1_BASE 0x50090000`)、启动文件、**LCPU 固件安装与初始化**(`lcpu_install.c`、`bf0_lcpu_init.c`)。
- `hal/`:SiFli BF0 HAL(与 SiFli-SDK 同源,`bf0_hal_*.h` 覆盖 ADC/AES/AUDCODEC/LCDC/…)。Zephyr 驱动多为「薄封装 + HAL」的结构。
- `ll/`:低层驱动;`ipc_queue/`:HCPU↔LCPU 邮箱队列,蓝牙 HCI 的运输层。

### 1.5 双核与蓝牙架构

SF32LB52x 为 **HCPU(Cortex-M33,跑 Zephyr)+ LCPU(蓝牙控制器)** 双核。Zephyr 侧不实现控制器,而是:`bt` 子系统 → `hci_sf32lb.c` → `ipc_queue`/`mailbox` → LCPU 固件(由 hal_sifli 安装到共享 RAM)。板级 DTS 里 `zephyr,bt-hci = &mailbox` 即此链路。

### 1.6 存储与启动映射

| 区域 | 地址 | 大小 | 用途 |
|---|---|---|---|
| `ptable` 分区 | flash 0x0 | 64 KB | SiFli 引导 ROM 的分区表 |
| `code` 分区 | flash 0x10000 | 16320 KB | Zephyr 应用(`zephyr,code-partition`,XIP) |
| MPI2 NOR | 0x12000000(映射) | 16 MB(PY25Q128HA) | 模组内 QSPI NOR,四线,DMA |
| MPI1 PSRAM | 0x60000000 | 8 MB(片内 OPI) | `zephyr,memory-region` "PSRAM",由 `ldo1_1v8` 供电 |
| SRAM | ram012 | 512 KB | `sf32lb52x-ram012.dtsi` |

烧录:`west flash`(runner = **sftool**,`--chip=SF32LB52`,经 CH340N 串口下载)。

### 1.7 构建入口速查

```bash
# 工作区根目录下
west build -b sf32lb52_hspi application/samples/uart_shell
west flash            # sftool 串口下载
# 主应用(blink+sensor 模板,面向 custom_plank 概念板,学习脚手架用)
west build -b sf32lb52_hspi application/app
```

---

## 2. HSPI 板 DTS 完整性审计(对照 OpenSiFli SDK)

### 2.1 审计方法

以三份材料交叉对照:

1. **本工程 DTS**:`sf32lb52_hspi.dts` + `sf32lb52_hspi-pinctrl.dtsi`;
2. **SiFli-SDK 成熟板级**:`customer/boards/sf32lb52-lchspi-ulp{,_base}/`(`bsp_pinmux.c`、`bsp_power.c`、`bsp_lcd_tp.c`、`board.conf`、`Kconfig.board`)——这是官方对黄山派的完整定义;
3. **既有硬件核对文档**:本目录 `board-hardware-reference-pin-map.md`、`SF32LB52-黄山派-资料.md`(网表级核对)。

### 2.2 器件级完整性总表

图例:✅ 已建模且启用 | 🟡 已建模、`disabled` 占位(策略性,待 bring-up) | ❌ 未建模(缺口)

#### A. 显示与触摸

| 器件 | 硬件连接 | SDK(lchspi-ulp)参考 | Zephyr DTS 现状 | 状态 |
|---|---|---|---|---|
| AMOLED 屏 CO5300AF-01(390×450 QSPI) | PA_02~08 QSPI 七线,RST PA_00 | `LCD_USING_TFT_CO5300`,`BSP_PIN_LCD` QADSPI 分支引脚一致 | `&lcdc`/`mipi_dbi`/`co5300` **okay**,`zephyr,display` 指向,pinctrl 与 SDK 完全一致 | ✅ |
| 屏幕背光/电源使能 PA_01 | 22P FPC pin 2 → 屏幕板 FPC pin 21(**网表 NC**) | `LCD_BACKLIGHT_CONTROL_PIN=1`(pwmt1 CH4);`bsp_lcd_tp.c` 以 `LCD_VADD_EN=PA1` 上电拉高 | 屏幕板 V1.1 网表核实该脚悬空,SDK 行为系无操作;结论已写入 co5300 节点注释,不建模 | ✅ 已定论(无需建模) |
| FT6146-M00 触摸 | I2C1:SDA PA_33 / SCL PA_37;INT PA_41;RST PA_09 | `BSP_PIN_Touch()` 同引脚;`TOUCH_IRQ_PIN=41` | `&i2c1` okay + `ft6146@38`(INT/RST 齐全)**disabled**;fork 内驱动+绑定齐备 | 🟡 可直接 bring-up |

#### B. 传感器(I2C3,GS_3V3 供电)

| 器件 | 硬件连接 | SDK 参考 | Zephyr DTS 现状 | 状态 |
|---|---|---|---|---|
| LSM6DS3TR-C 六轴 IMU | I2C3 @0x6a,INT1 PA_31 | 驱动 `sensor/LSM6DSL/`,示例经 `i2c3`(PA_39/40)+ PA_38/PA_30 上电 | `lsm6dsl@6a`(`st,lsm6dsl`,irq PA_31)**disabled** | 🟡 |
| MMC5603NJ 磁力计 | I2C3 @0x30 | 驱动 `sensor/MMC56x3/` | `mmc56x3@30`(`memsic,mmc56x3`)**disabled** | 🟡 |
| LTR-303ALS-01 光感 | I2C3 @0x29 | 驱动 `sensor/LTR303/` | `ltr303@29` 借用 `liteon,ltr329`(寄存器近似、未验证)**disabled** | 🟡 需先验证驱动兼容 |
| 传感器总线本身 | PA_39 SDA / PA_40 SCL | SDK 默认 board.conf **未启用 I2C3**,传感器示例工程单独打开 | `&i2c3` **okay**,pinctrl 正确 | ✅ 比 SDK 默认更完整 |

> 注意:三颗传感器读数前必须 `regulator_enable(gs_3v3)`(PA_30)并等待 ≥500 µs;上游传感器驱动无 `vin-supply` 逻辑,需应用层管理——DTS 注释已写明,与 SDK `bsp_power.c` 的 PA_38→PA_26→PA_30 顺序一致。

#### C. 电源(稳压器/LDO)

| 器件 | 硬件连接 | SDK 参考 | Zephyr DTS 现状 | 状态 |
|---|---|---|---|---|
| LP5240HVF(U2)VSYS_1 开关 | EN = PA_38 | `bsp_power.c` 深睡唤醒拉高 PA38 | `vsys_en` regulator-fixed,`regulator-boot-on` | ✅ |
| ETA5055V330(U4)VCC_3V3 开关 | EN = PA_26 | SDK 误标 `LED1_PIN=26`(见 §2.5) | `vcc_3v3` regulator-fixed,`regulator-always-on` | ✅ 已按网表纠错 |
| ETA5055V330(U15)GS_3V3 传感器电源 | EN = PA_30 | `bsp_pinmux.c` "Sensor Power" | `gs_3v3` regulator-fixed,`regulator-boot-off`(应用层管理) | ✅ |
| 片内 LDO1 1.8 V | PSRAM 供电 | — | `&ldo1_1v8` okay + boot-on,`mpi1` 的 `power-supply` | ✅ |
| 片内 LDO3 3.3 V(VDD33_VOUT) | 供 WS2812B、马达 | — | `&ldo3_3v3` okay + boot-on,更名 `vdd33-vout` | ✅ |
| 片内 LDO2 3.3 V | 本板未用 | — | 保持 disabled | ✅ 合理 |
| AW32001ECSR(U3)线性充电 | I2C2:SCL PA_10 / SDA PA_11,@0x49 | `CHARGE_USING_AW32001`,`bsp_power.c` 深睡唤醒时直操 I2C2 关 CEB/看门狗 | `&i2c2` okay + `charger@49` **disabled**;占位绑定已加入 `application/dts/bindings/charger/awinic,aw32001.yaml`,仍无驱动 | 🟡 缺驱动 |
| 电池电量测量(GPADC) | VBAT 内部通道 7(无外部引脚) | `BSP_USING_ADC` + `battery_table.c` 放电曲线(41808→4.1808 V 等) | `&gpadc` okay + `channel@7`(eFuse 出厂校准,驱动自动换算电池 mV),`zephyr,user` 提供 `io-channels` "vbat" | ✅ 已补全 |
| VBUS 检测 PA_44 | VBUS_5V 分压 → PA_44 | `BSP_CHARGER_INT_PIN=44`(当充电检测用) | `zephyr,user` 的 `vbus-det-gpios`(按网表以 VBUS_DET 建模,而非充电 INT) | ✅ 已补全 |

#### D. 人机交互 / 杂项外设

| 器件 | 硬件连接 | SDK 参考 | Zephyr DTS 现状 | 状态 |
|---|---|---|---|---|
| KEY1(电源/HOME) | PA_34,高有效;硬件副作用:长按经 Q1 拉低 CHG_INT → 关机 | `KEY1_PIN=34` | `key1` gpio-keys + `INPUT_KEY_1`,注释警告副作用 | ✅ |
| KEY2(功能键) | PA_43,高有效 | `KEY2_PIN=43` | `key2` gpio-keys + `INPUT_KEY_2` | ✅ |
| WS2812B-2020 RGB 灯 | 数据 PA_32,VDD=VDD33_VOUT | `RGBLED_CONTROL_PIN=32`(SDK 驱动按 SK6812) | `led_strip`(`worldsemi,ws2812-gpio`)**disabled**,时序占位待实测 | 🟡 |
| 振动马达 | PA_20 = GPTIM2_CH1,供电 VDD33_VOUT | 立创资料 VIB PWM | `pwm_vibrator`(pwm-leds)+ `gptim2_pwm` 均 **disabled**,pinctrl 已备 | 🟡 |
| 红色电源 LED1 | VBUS_5V 硬连,不可控 | — | 注释说明,无节点 | ✅ 正确(不该建模) |
| 音频 codec + 功放 | 片内 AUDCODEC;PA 使能 PA_42(U6 NS4150B) | `PA_USING_AW8155`,`AW8155_GPIO_PIN=42` | `&audcodec` okay,TX/RX 双 DMA(含麦克风 ADC 路径),`pa-power-gpios`=PA_42 | ✅ |
| TF 卡(SPI 模式) | SPI1:PA_24/25/28/29;卡检测 PA_27 | `bsp_pinmux.c` SPI1 + PA_27 card detect | `&spi1` okay + `cs-gpios`(PA_29 改 GPIO 片选,SD 协议需跨传输保持 CS)+ `sdhc0`(`zephyr,sdhc-spi-slot`,`cd-gpios`=PA_27 上拉低有效)+ `sdmmc` 磁盘节点(disk-name "SD") | ✅ 已补全 |
| USB(Type-C,PA_35/36) | USB2.0 FS + CH340N 下载口 | SDK 有 USBD 栈(默认引脚置 GPIO 下拉) | **SoC dtsi 无 usbd 节点**;`uart_shell/usb.overlay` 引用的 `zephyr_udc0` 在本板不存在(继承自上游样例,不可用) | ❌ SoC 级缺口 |

#### E. 系统级(全部就绪)

`usart1`(1 Mbps 控制台)、`mailbox`(BT HCI)、`mpi1` PSRAM、`mpi2` NOR + 分区、`dmac`、`wdt`、`rtc`、`crc`、`crypto`、`trng`、`tsen`、`efuse`、`hxt48`/`lxt32`(PA_22/23)/`dll1` 240 MHz/`dll2` 288 MHz —— 均 ✅,与 DevKit-LCD 蓝本一致且经黄山派网表核对修正。

### 2.3 引脚级对照结论(Zephyr pinctrl vs SDK bsp_pinmux)

- **PSRAM(MPI1)**:Zephyr `mpi1_default`(SA01-04→DIO0-3、SA08-11→DIO4-7、SA07 CLK、SA05 CS、SA12 DQSDM、SA00/SA06 模拟)与 SDK `board_pinmux_psram_func1_2_4(1)`(APS 64P XCELLA,即 8 MB OPI)**逐脚一致**。SDK 是按芯片 PID 运行时选表,Zephyr 是静态声明——对 525UC6 固定为该映射,正确。
- **NOR(MPI2)**:SDK 显式配置 PA_12~17;Zephyr **不配置**(无 pinctrl-0),依赖引导 ROM 在 XIP 启动前已配好。与 DevKit 蓝本一致,可用但属于"隐式契约",文档中应知晓。
- **UART1/I2C1/I2C2/I2C3/SPI1/LCDC/LXT32**:两边逐脚一致(PA_18/19、PA_33/37、PA_10/11、PA_39/40、PA_24/25/28/29、PA_02~08、PA_22/23)。
- **SDK 有而 Zephyr 无**:仅剩 PA_35/36(USB,受限于 SoC 级无 usbd 节点)。原差异项已于 2026-07-02 处理:PA_01 网表证实 NC 不需建模、PA_27 已作 `cd-gpios`、PA_44 已入 `zephyr,user`。另注意 PA_29 有意从 `SPI1_CS` 复用改为 GPIO 片选(`cs-gpios`),与 SDK 硬件 CS 方案不同,原因见 §2.6。
- **SDK board.conf 有而两边都没引脚的**:`BSP_USING_I2C4`(基板无 I2C4 pinmux,疑为遗留配置,不构成缺口)。

### 2.4 缺口清单与处理结果(2026-07-02 更新)

| # | 缺口 | 处理结果 |
|---|---|---|
| 1 | PA_01 屏幕背光/VADD 使能 | ✅ **已定论,无需建模**:屏幕板 V1.1 网表证实该脚在屏侧 NC 悬空(映射到屏侧 FPC pin 21);结论已写入 co5300 节点注释 |
| 2 | 电池电量:gpadc 未启用 | ✅ **已补全**:`&gpadc` okay + `channel@7`(内部 VBAT,eFuse 校准)+ `zephyr,user` `io-channels` "vbat";pinctrl 使用合法的空状态(所有外部 ADC 引脚均被占用);电量换算曲线可移植 SDK `battery_table.c` |
| 3 | TF 卡无设备节点 | ✅ **已补全**:`sdhc0`(`zephyr,sdhc-spi-slot`,24 MHz)+ `sdmmc` 磁盘(disk-name "SD")+ `cd-gpios`=PA_27;PA_29 改为 GPIO 片选(`cs-gpios`) |
| 4 | PA_44 VBUS 检测未建模 | ✅ **已补全**:`zephyr,user` `vbus-det-gpios`,按网表以 VBUS_DET 建模 |
| 5 | AW32001 无驱动/绑定 | 🟡 **绑定已补**(`application/dts/bindings/charger/awinic,aw32001.yaml`,含 SDK 寄存器参考);驱动仍缺,节点保持 disabled |
| 6 | 传感器/触摸/RGB/马达 7 节点 disabled | 🟡 维持现状(策略性,非缺失):bring-up 时先 `gs_3v3` 上电时序 → I2C3 扫 0x6a/0x30/0x29 → 逐个 `status="okay"`;LTR303 需先验证 ltr329 驱动寄存器兼容性 |
| 7 | USB / SDIO SoC 级无节点 | ❌ 仍开放:需在 zephyr fork 的 `sf32lb52x.dtsi` 补 usbd/sdhci 节点并写驱动(HAL 中 `bf0_hal_pcd/hcd/sdhci` 已有底层),列入路线图 |

### 2.5 SDK 与网表的矛盾点备忘(阅读 SDK 时防坑)

| 引脚 | SDK 的说法 | 网表/本工程核实 | 结论 |
|---|---|---|---|
| PA_26 | `BSP_LED1_PIN=26`(LED) | ETA5055V330(U4)EN,VCC_3V3 载荷开关;真 LED1 是 VBUS 硬连红灯 | 信网表:本工程建模为 `vcc_3v3` regulator ✅ |
| PA_44 | `BSP_CHARGER_INT_PIN=44` | VBUS_5V 分压检测;AW32001 INT 走 CHG_INT 网络,经 Q1 与 PA_34 联动,不直连 MCU | 信网表:按 VBUS_DET 建模 |
| PA_01 | `LCD_VADD_EN` / 背光 PWM,上电拉高 | 屏幕板 V1.1 网表:PA_01 映射至屏侧 FPC pin 21,**NC 悬空**;屏幕板为纯无源转接板(仅电容/上拉电阻,BV6802W 在屏排线模组内部) | **已定论**:SDK 拉高 PA_01 在本屏版本上是无操作;DTS 不建模 ✅ |
| PA_34 | 仅"Key1 - Power key" | 网表:PA_34 同时驱动 Q1 栅极 → 拉低 CHG_INT;长按触发 AW32001 shipping mode(硬关机) | 固件禁止长时间驱高 PA_34,DTS 注释已警告 |
| 功放型号 | `PA_USING_AW8155` | BOM/网表:U6 = NS4150B(使能脚同为 PA_42,高有效) | 行为等价,型号以 BOM 为准 |
| RGB 灯型号 | SiFli wiki:SK6812MINI-HS | 立创 BOM:WS2812B-2020 | 协议兼容,时序 bring-up 实测 |
| 充电 IC 型号 | SiFli wiki:SY6103 | BOM/SDK 配置/网表:AW32001ECSR | 以 AW32001 为准(@0x49) |

### 2.6 DTS 补全记录(2026-07-02)

针对 §2.4 缺口 #2/#3/#4/#5 的补全已落地,修改文件:

| 文件 | 修改内容 |
|---|---|
| `sf32lb52_hspi.dts` | ① 新增 `zephyr,user`(`vbus-det-gpios`=PA_44、`io-channels`=\<&gpadc 7\> "vbat");② 启用 `&gpadc` + `channel@7`(内部 VBAT);③ `&spi1` 加 `cs-gpios`(PA_29)并挂 `sdhc0`/`sdmmc` TF 卡节点(`cd-gpios`=PA_27);④ aliases 补 `led-strip`;⑤ co5300 注释补 PA_01 网表 NC 结论;⑥ 头部补 `adc.h` include |
| `sf32lb52_hspi-pinctrl.dtsi` | ① `spi1_default` 移除 `PA29_SPI1_CS`(改由 `cs-gpios` GPIO 片选——SD 协议要求跨多次传输保持 CS,`sdhc_spi` 依赖 `SPI_HOLD_ON_CS`,GPIO 片选由 spi_context 统一处理);② 新增空的 `gpadc_default` 状态(绑定强制要求 pinctrl,而 PA_28~34=CH0~6 全部另作他用,仅内部 VBAT 通道可用) |
| `application/dts/bindings/charger/awinic,aw32001.yaml` | 新增 AW32001 占位绑定(含 SDK 寄存器级参考注释),使 `charger@49` 节点通过绑定校验 |

**构建验证**(板卡 `sf32lb52_hspi/sf32lb525uc6`,样例 `samples/uart_shell`):

1. 默认配置:构建成功(FLASH 65 848 B / RAM 12 904 B);
2. 驱动全开(`CONFIG_ADC/SPI/SDHC/REGULATOR/DISK_ACCESS/DISK_DRIVER_SDMMC=y`):构建成功(FLASH 84 576 B),确认 `CONFIG_ADC_SF32LB(含 eFuse 校准)`、`CONFIG_DISK_DRIVER_SDMMC`、`CONFIG_REGULATOR_FIXED`、sdhc-spi-slot 全部实例化,空 pinctrl 状态代码生成无告警。

> 注:构建目录必须放在本地真实磁盘(如仓库内)。另:workspace 曾整体从 `E:\sf32lb52-zephyr-example` 移动到 `E:\1\...`,`samples/uart_shell/build/` 旧缓存内是失效的绝对路径,重建时请删除或换目录。

---

## 3. 学习路径建议(从零上手本工程)

1. **跑通闭环**:`west build -b sf32lb52_hspi application/samples/uart_shell` → `west flash` → 1 Mbps 串口进 shell,玩 `device list`、`kernel threads`、`bt` 命令(验证 LCPU 蓝牙链路)。
2. **读板级 DTS**(配合本目录 [dts-reference.md](./dts-reference.md) 逐行解析):`sf32lb52_hspi.dts` → `sf32lb52x.dtsi` → 各绑定 yaml,理解 chosen/regulator/pinctrl 三大块。
3. **第一个 bring-up 实验(推荐传感器)**:应用里 `regulator_enable(gs_3v3)` + 延时,overlay 把 `lsm6dsl` 置 okay,用 `sensor` shell 命令读数——完整体验"电源时序 + DTS overlay + 驱动绑定"链路。
4. **显示/触摸**:显示已 okay,可直接跑 lvgl(模块已拉取);触摸把 `ft6146` 置 okay 验证 input 子系统。(PA_01 已证实 NC,屏幕排障时无需再查该脚。)
5. **功能启用练手**:DTS 侧缺口已补全,应用层直接启用即可——TF 卡(`CONFIG_DISK_DRIVER_SDMMC` + fatfs 挂载 "SD")、电池电压(`CONFIG_ADC`,读 `zephyr,user` 的 "vbat" 通道)、VBUS 检测(GPIO 读 `vbus-det-gpios`)。进阶题目:AW32001 充电驱动(参考占位绑定注释与 SDK 寄存器操作)、SoC 级 USB/SDIO 支持。
6. **架构深潜**:`hci_sf32lb.c` + `ipc_queue`(双核)、`memc_sf32lb_mpi_opi_psram.c`(存储)、`bsp_power.c`(SDK 低功耗流程,Zephyr 侧 PM 尚未对齐——进阶方向)。

## 4. 相关文档索引

| 文档 | 内容 |
|---|---|
| [board-hardware-reference-pin-map.md](./board-hardware-reference-pin-map.md) | 逐 pin ↔ 器件对照、30P/22P 排针表 |
| [board-hardware-reference.html](./board-hardware-reference.html) | 硬件参考页(网表 × SDK × DTS 交叉验证) |
| [dts-reference.md](./dts-reference.md) | 板级 DTS 逐行解析 |
| [power-tree.md](./power-tree.md) | 电源树与 KEY1 关机行为 |
| [psram-registration.md](./psram-registration.md) | PSRAM 注册机制研究 |
| [SF32LB52-黄山派-资料.md](./SF32LB52-黄山派-资料.md) | SDK 侧板级资料汇编(源自 OpenSiFli) |
| [sensors.html](./sensors.html) | 板载传感器/器件参考(含 datasheet 链接) |
