# SF32LB52-HSPI Board Devicetree 逐行解析

> 板级 DTS: `application/boards/sifli/sf32lb52_hspi/sf32lb52_hspi.dts`
> PinCtrl: `application/boards/sifli/sf32lb52_hspi/sf32lb52_hspi-pinctrl.dtsi`
> SoC DTSI: `zephyr/dts/arm/sifli/sf32lb52x.dtsi`
> 基于原理图/网表核对，2026-06-28。

---

## 目录

1. [文件头与 include](#1-文件头与-include)
2. [根节点与 chosen](#2-根节点与-chosen)
3. [输入设备: buttons](#3-输入设备-buttons)
4. [LED 清单（注释）](#4-led-清单注释)
5. [aliases](#5-aliases)
6. [内存区域: PSRAM](#6-内存区域-psram)
7. [电源树: regulators](#7-电源树-regulators)
8. [WS2812B LED Strip 与振动马达](#8-ws2812b-led-strip-与振动马达)
9. [CPU 与时钟系统](#9-cpu-与时钟系统)
10. [GPIO 控制器](#10-gpio-控制器)
11. [DMA](#11-dma)
12. [内部 LDO](#12-内部-ldo)
13. [MPI 存储控制器](#13-mpi-存储控制器)
14. [PinCtrl (引脚复用)](#14-pinctrl-引脚复用)
15. [UART 控制台](#15-uart-控制台)
16. [音频 Codec](#16-音频-codec)
17. [看门狗 & RTC](#17-看门狗--rtc)
18. [I2C 总线](#18-i2c-总线)
19. [SPI](#19-spi)
20. [加密与安全](#20-加密与安全)
21. [显示: LCDC + CO5300 OLED](#21-显示-lcdc--co5300-oled)
22. [附录: 驱动与绑定映射表](#22-附录-驱动与绑定映射表)

---

## 1. 文件头与 include

```dts
/dts-v1/;

#include <sifli/sf32lb52x.dtsi>             // ← SoC 级定义: CPU, 总线, 所有外设基址
#include <sifli/sf32lb52x-ram012.dtsi>       // ← 多核共享内存区域
#include <zephyr/dt-bindings/dma/sf32lb52x-dma.h>
#include <zephyr/dt-bindings/gpio/gpio.h>     // ← GPIO_ACTIVE_HIGH/LOW 宏
#include <zephyr/dt-bindings/i2c/i2c.h>      // ← I2C_BITRATE_FAST 等宏
#include <zephyr/dt-bindings/input/input-event-codes.h>  // ← INPUT_KEY_1/2
#include <zephyr/dt-bindings/led/led.h>      // ← LED_COLOR_ID_* 宏
#include <zephyr/dt-bindings/pwm/pwm.h>      // ← PWM_MSEC / PWM_POLARITY_* 宏

#include "sf32lb52_hspi-pinctrl.dtsi"        // ← 本板引脚复用配置
```

| include | 提供的节点 |
|---------|-----------|
| `sf32lb52x.dtsi` | `cpu0`, `rcc_clk`, `gpioa_*`, `mpi1/2`, `usart1`, `i2c1/2/3`, `spi1`, `lcdc`, `audcodec`, `wdt`, `rtc`, `crc`, `crypto`, `trng`, `mailbox`, `efuse`, `tsen` 等 |
| `sf32lb52x-ram012.dtsi` | `ram012` (511KB 片上 SRAM), `sram0_shared`, `sram1_shared` |
| `sf32lb52_hspi-pinctrl.dtsi` | 所有 `*_default` pinmux 配置 |

---

## 2. 根节点与 chosen

```dts
/ {
    model = "LCKFB SF32LB52-HSPI (Huangshan Pi)";
    compatible = "sifli,sf32lb52-hspi";
```

`chosen` 节点告知 Zephyr 内核哪些硬件承担什么角色：

```dts
    chosen {
        zephyr,flash = &py25q128ha;          // 16MB QSPI NOR Flash (Puya)
        zephyr,flash-controller = &mpi2;      // Flash 通过 MPI2 控制器访问
        zephyr,code-partition = &code;        // 固件存放分区 (0x10000~)
        zephyr,console = &usart1;             // printf / printk 输出
        zephyr,shell-uart = &usart1;          // Shell 交互 (同一 UART)
        zephyr,crc = &crc;                    // 硬件 CRC 引擎
        zephyr,entropy = &trng;               // 真随机数发生器
        zephyr,bt-hci = &mailbox;             // BLE HCI 通过 mailbox 通信
        zephyr,display = &co5300;             // 默认显示器
    };
```

| 属性 | 指向 | 说明 |
|------|------|------|
| `zephyr,flash` | `py25q128ha` | 16MB NOR Flash，存放固件和文件系统 |
| `zephyr,flash-controller` | `mpi2` | QSPI 控制器，CPU 通过 AHB 直接映射访问 Flash |
| `zephyr,code-partition` | `code` | 固件分区，起始 0x10000 (64KB 留给 ptable) |
| `zephyr,console` | `usart1` | PA_18(RX)/PA_19(TX)，1Mbps |
| `zephyr,bt-hci` | `mailbox` | 双核间 BLE 通信 |

---

## 3. 输入设备: buttons

```dts
    buttons {
        compatible = "gpio-keys";
```

### key1 (PA_34) — ⚠️ 带硬件联动

```dts
        key1: key1 {
            label = "KEY1";
            gpios = <&gpioa_32_44 2 GPIO_ACTIVE_HIGH>;
            zephyr,code = <INPUT_KEY_1>;
        };
```

| 属性 | 值 | 说明 |
|------|----|------|
| GPIO | `gpioa_32_44` offset=2 | PA_34 |
| 极性 | `GPIO_ACTIVE_HIGH` | 按下=高电平 |
| 按键码 | `INPUT_KEY_1` | Linux input 子系统 keycode |

> **⚠️ 硬件联动**: PA_34 同时驱动 Q1 MOSFET → 按下 KEY1 会拉低 AW32001 充电芯片的
> INT 引脚。长按（数秒）会触发 AW32001 的 shipping mode（断开电池，系统掉电）。
> **不要在固件中长时间拉高 PA_34。** 详见 [power-tree.md §7](power-tree.md#7-key1--pwrkey-与-aw32001-充电芯片联动)。

### key2 (PA_43)

```dts
        key2: key2 {
            label = "KEY2";
            gpios = <&gpioa_32_44 11 GPIO_ACTIVE_HIGH>;
            zephyr,code = <INPUT_KEY_2>;
        };
```

| 属性 | 值 | 说明 |
|------|----|------|
| GPIO | `gpioa_32_44` offset=11 | PA_43 (网表 `PA_43_KEY2` → SW2) |
| 极性 | `GPIO_ACTIVE_HIGH` | 按下=高电平 |

> **历史修正**: KEY2 曾误配到 PA_11（实际是充电 I2C2 SDA），已按网表修正为 PA_43。

**C 代码获取按键**:

```c
#include <zephyr/input/input.h>
// 轮询方式
const struct device *dev = DEVICE_DT_GET(DT_NODELABEL(buttons));
```

---

## 4. LED 清单（注释）

```dts
    /*
     * LED inventory (schematic / netlist verified):
     * - LED1: Red 0603 power indicator, hard-wired between VBUS_5V (via R6
     *   4.7kΩ) and GND. Always on when USB is plugged — NOT GPIO-controllable.
     * - LED3 (WS2812B-2020): RGB smart LED on PA_32, 1-Wire protocol. Modeled
     *   as led_strip below (currently disabled). LED3 VDD is VDD33_VOUT from
     *   SF32LB52 LDO3_3V3 via R51.
     *
     * There is NO GPIO-controlled LED on PA_26. PA_26 drives the VCC_3V3
     * load-switch enable (ETA5055V330DS2F U4) — see regulator-vcc3v3 below.
     */
```

**总结**:

| PCB 标号 | 型号 | 连接 | 可控? | DTS 节点 |
|---------|------|------|-------|---------|
| LED1 | Red 0603 | VBUS_5V → R6(4.7kΩ) → LED1 → GND | ❌ 插 USB 即亮 | 无 |
| LED3 | WS2812B-2020 | PA_32, 1-Wire NZR; VDD=`VDD33_VOUT` 经 R51 | ✅ | `led_strip` (disabled) |
| ~~LED0~~ | 不存在 | 不存在 | — | **已删除** |

---

## 5. aliases

```dts
    aliases {
        codec0 = &audcodec;       // 音频 codec
        sw0 = &key1;              // 按键 1 (PA_34)
        sw1 = &key2;              // 按键 2 (PA_43)
        rtc = &rtc;               // RTC 外设
        watchdog0 = &wdt;         // 看门狗
    };
```

| alias | 目标 | 应用层用法 |
|-------|------|-----------|
| `codec0` | `audcodec` | `DT_ALIAS(codec0)` → 音频驱动获取设备 |
| `sw0/sw1` | `key1/key2` | `DT_ALIAS(sw0)` → 按键驱动 |
| `rtc` | `rtc` | `DT_ALIAS(rtc)` → RTC 子系统 |
| `watchdog0` | `wdt` | `DT_ALIAS(watchdog0)` → 看门狗子系统 |

> **已删除**: 之前有 `led0 = &led0`，因 PA_26 上无 LED 而已移除。

---

## 6. 内存区域: PSRAM

```dts
    psram: psram@60000000 {
        compatible = "zephyr,memory-region";
        reg = <0x60000000 DT_SIZE_M(8)>;          // 8MB, 地址 0x60000000
        zephyr,memory-region = "PSRAM";           // 链接器区域名
        zephyr,memory-attr = <(DT_MEM_ARM(ATTR_MPU_RAM))>;  // MPU: 普通 RAM
    };
```

| 属性 | 值 | 作用 |
|------|----|------|
| `compatible` | `zephyr,memory-region` | 告诉链接器生成 MEMORY 区域和输出段 |
| `reg` | `0x60000000`, 8MB | 物理地址和大小 |
| `zephyr,memory-region` | `"PSRAM"` | 链接器脚本中的区域名: `PSRAM (rw) : ORIGIN = 0x60000000, LENGTH = 0x800000` |
| `zephyr,memory-attr` | `ATTR_MPU_RAM` | MPU 配置属性（可读写，可缓存） |

**两层注册机制**:
1. **硬件层**: `&mpi1` 节点 (`sifli,sf32lb-mpi-opi-psram`) → `memc_sf32lb_mpi_opi_psram_init()` 初始化 MPI 控制器
2. **链接器层**: `psram@60000000` → `LINKER_DT_REGIONS()` / `LINKER_DT_SECTIONS()` 生成链接器脚本

详见 [psram-registration.md](psram-registration.md)。

---

## 7. 电源树: regulators

### 7.1 电源树 ASCII 图

```
USB_VBUS_5V ── LP5305AQVF (U17, OVP/OCP) ── VBUS_5V
                                               │
VBAT_S ────────────────────────────────────────┤
                                               ▼
               AW32001ECSR (U3, charger, I2C2 PA_10/PA_11)
               ├─ CHG_INT = U3.B2/Q1.3/R5.1, pulled low via Q1 by PA_34
               ├─ PA_44 = VBUS_DET divider, not AW32001 INT
               ▼
             VSYS_S (VSYS)
               │
  ┌────────────┼────────────────────┐
  ▼            ▼                    ▼
NS4150B     SF32LB52             LP5240HVF
(PA_42)     主控                 (U2, PA_38)
功放          │                    │
              └─ LDO3_3V3 / VDD33_VOUT2
                 模组 pin 17, 板级网名 VDD33_VOUT
                  ├─ R51 0Ω → LED3 WS2812B VDD
                  └─ R36 5.1Ω → 振动马达供电
                                   ▼
                                 VSYS_1
                                   │
  ┌────────────────┬───────────────┤
  ▼                ▼               ▼
屏幕 FPC       ETA5055V330DS2F  ETA5055V330DS2F
(VSYS_1直供)   (U4, PA_26)      (U15, PA_30)
                   │                │
                   ▼                ▼
               VCC_3V3_S         GS_3V3
             (TP/SPI/SD卡)     (传感器总线)
```

### 7.2 regulator-fixed 绑定机制

**绑定文件**: `zephyr/dts/bindings/regulator/regulator-fixed.yaml`
**驱动文件**: `zephyr/drivers/regulator/regulator_fixed.c`

`regulator-fixed` 是一个**用 GPIO 控制使能脚的固定电压稳压器**。它不调节电压——只负责拉高/拉低一个 GPIO。

驱动实现极其简单：

```c
// 使能 = GPIO 拉高
static int regulator_fixed_enable(const struct device *dev) {
    return gpio_pin_set_dt(&cfg->enable, 1);   // ← 就这一行
}

// 禁能 = GPIO 拉低
static int regulator_fixed_disable(const struct device *dev) {
    return gpio_pin_set_dt(&cfg->enable, 0);   // ← 就这一行
}
```

初始化时的行为取决于 flags 标志位。

### 7.3 regulator-boot-on 的工作原理

完整链路：DTS 属性 → 宏展开 → 标志位 → 驱动初始化 → refcnt

```
DTS: regulator-boot-on;
  │
  ▼ header 宏 (regulator.h:249)
flags |= REGULATOR_BOOT_ON       // = BIT(1) = 0x02
  │
  ▼ 同时定义
REGULATOR_INIT_ENABLED = REGULATOR_ALWAYS_ON | REGULATOR_BOOT_ON  // = 0x03
  │
  ▼ regulator_fixed_init()
should_enable = (flags & REGULATOR_INIT_ENABLED) != 0   // = true
gpio_pin_configure_dt(&enable, GPIO_OUTPUT_ACTIVE)      // 拉高 GPIO
  │
  ▼ regulator_common_init(dev, true)
data->refcnt = 1                                         // 引用计数 = 1
```

**三种标志位对比**:

| DTS 属性 | 标志位 | GPIO 初始 | refcnt 初始 | `disable()` 能关吗? | 本板用途 |
|----------|--------|----------|------------|-------------------|---------|
| `regulator-boot-on` | `BOOT_ON` | HIGH | 1 | ✅ 可以 | 模组内部 LDO (ldo3_3v3) |
| `regulator-boot-off` | `BOOT_OFF` | HIGH→LOW | 1→0 | ✅ 可以 (初始关) | 传感器总线 (gs_3v3) |
| `regulator-always-on` | `ALWAYS_ON` | HIGH | 1 | ❌ `disable()` NOOP | 系统电源 (vsys_en, vcc_3v3) |
| (无) | 0 | LOW | 0 | ✅ 可以 (初始关) | — |

**引用计数机制** (`regulator_common.c`):

```
enable:   refcnt++ ; if refcnt==1 → gpio HIGH
disable:  refcnt-- ; if refcnt==0 → gpio LOW
```

多消费者共享一个 regulator 时不会互相干扰。

### 7.4 vsys_en — VSYS_1 使能

```dts
    vsys_en: regulator-vsys {
        compatible = "regulator-fixed";
        regulator-name = "vsys-en";
        enable-gpios = <&gpioa_32_44 6 GPIO_ACTIVE_HIGH>;
        regulator-always-on;
    };
```

| 属性 | 值 | 说明 |
|------|----|------|
| GPIO | `gpioa_32_44` offset=6 | PA_38 → LP5240HVF (U2) EN |
| 策略 | `regulator-always-on` | 系统主电源，断开=MCU 掉电，永不关闭 |
| 负载 | 屏幕 FPC, U4(VCC_3V3), U15(GS_3V3) | VSYS_1 是整个外设电源总线的源头 |
| 上电顺序 | **第 1 步** | 最先上电 |

### 7.5 vcc_3v3 — VCC_3V3_S 轨

```dts
    vcc_3v3: regulator-vcc3v3 {
        compatible = "regulator-fixed";
        regulator-name = "vcc-3v3";
        enable-gpios = <&gpioa_00_31 26 GPIO_ACTIVE_HIGH>;
        regulator-always-on;
    };
```

| 属性 | 值 | 说明 |
|------|----|------|
| GPIO | `gpioa_00_31` offset=26 | PA_26 → ETA5055V330DS2F (U4) EN |
| 策略 | `regulator-always-on` | 基础外设电源 (TP/SPI/SD)，运行时常开 |
| 负载 | I2C1 上拉电阻, SPI1 VDD, SD 卡 VDD | TP 和 SPI/SD 通信全靠它 |
| 上电顺序 | **第 2 步** | |

> **⚠️ 这不是 LED!** PA_26 控制的是 VCC_3V3_S 电源轨的负载开关 U4。
> 关闭它会导致触摸屏和 SD 卡通信失效。

### 7.6 gs_3v3 — 传感器电源

```dts
    gs_3v3: regulator-gs3v3 {
        compatible = "regulator-fixed";
        regulator-name = "gs-3v3";
        enable-gpios = <&gpioa_00_31 30 GPIO_ACTIVE_HIGH>;
        regulator-boot-off;
    };
```

| 属性 | 值 | 说明 |
|------|----|------|
| GPIO | `gpioa_00_31` offset=30 | PA_30 → ETA5055V330DS2F (U15) EN |
| 策略 | `regulator-boot-off` | **默认关闭**，应用层通过 `regulator_enable()` 按需开启 |
| 负载 | LSM6DS3TR-C (U13), MMC5603NJ (U14), LTR-303ALS-01 (U16) | **三个传感器共享** |
| 上电顺序 | **第 3 步**（最后） | 应用层开启后等 ~500µs 才能用 I2C |

> **设计原因**: Zephyr 传感器驱动 (lsm6dsl/mmc56x3/ltr329) 的 binding 未内置 `vin-supply`，
> 无法自动联动 regulator。因此使用 `regulator-boot-off` + 应用层显式管理。
> 当所有传感器都禁用/未初始化时，该 rail 保持关闭以节省功耗。

### 7.7 C 代码控制示例

```c
#include <zephyr/drivers/regulator.h>

// 获取设备
const struct device *gs3v3 = DEVICE_DT_GET(DT_NODELABEL(gs_3v3));
const struct device *vcc33 = DEVICE_DT_GET(DT_NODELABEL(vcc_3v3));

// vsys_en 和 vcc_3v3 设置了 regulator-always-on，无需手动管理

// 传感器 bring-up: 按需开启 gs_3v3
if (!device_is_ready(gs3v3)) {
    LOG_ERR("gs_3v3 regulator not ready");
}
regulator_enable(gs3v3);     // refcnt 0→1 → PA_30 HIGH → GS_3V3 上电
k_sleep(K_USEC(500));        // 等 500µs 稳定

// ... 初始化传感器 (lsm6dsl_init, mmc56x3_init, ltr303_init) ...

// 传感器关闭/低功耗模式
regulator_disable(gs3v3);    // refcnt 1→0 → PA_30 LOW → GS_3V3 断电
```

> **引用计数**: 多个模块可独立调用 `regulator_enable/disable`，驱动内部 refcnt
> 保证只在 0↔1 时真正操作 GPIO。例如 sensor A enable → refcnt=1 (GPIO HIGH)，
> sensor B enable → refcnt=2，sensor A disable → refcnt=1，sensor B disable →
> refcnt=0 (GPIO LOW)。

---

## 8. WS2812B LED Strip 与振动马达

### 8.1 WS2812B LED Strip

```dts
    led_strip: led-strip {
        compatible = "worldsemi,ws2812-gpio";
        gpios = <&gpioa_32_44 0 GPIO_ACTIVE_HIGH>;   // PA_32
        chain-length = <1>;                           // 只有一个 LED
        color-mapping = <LED_COLOR_ID_GREEN
                         LED_COLOR_ID_RED
                         LED_COLOR_ID_BLUE>;          // GRB 顺序
        reset-delay = <280>;                          // 复位脉冲 (ns)
        status = "disabled";                          // 暂未启用
    };
```

| 属性 | 值 | 说明 |
|------|----|------|
| GPIO | `gpioa_32_44` offset=0 | PA_32, 1-Wire NZR 协议 |
| `chain-length` | 1 | 单颗 WS2812B-2020 |
| `reset-delay` | 280 ns | 复位脉冲宽度，需实测调优 |
| `color-mapping` | GRB | WS2812B 的典型色彩顺序 |
| 供电 | `VDD33_VOUT` | 来自 SF32LB52 内部 `LDO3_3V3`，经 R51 到 LED3 VDD |

> `worldsemi,ws2812-gpio` 绑定不声明 `power-supply` 属性，所以 DTS 里用注释记录 LED3 供电关系，避免引入 binding 校验错误。

### 8.2 振动马达 PWM 占位节点

```dts
    pwm_vibrator: pwm-vibrator {
        compatible = "pwm-leds";
        status = "disabled";

        vibrator: vibrator {
            label = "VIBRATOR";
            pwms = <&gptim2_pwm 0 PWM_MSEC(5) PWM_POLARITY_NORMAL>;
        };
    };

&gptim2 {
    gptim2_pwm: pwm {
        pinctrl-0 = <&vib_pwm_default>;
        pinctrl-names = "default";
        status = "disabled";
    };
};
```

| 项 | 值 | 说明 |
|----|----|------|
| 控制脚 | `PA_20_VIB_PWM` | pinctrl 使用 `PA20_GPTIM2_CH1` |
| 供电 | `VDD33_VOUT` 经 R36 | 来自 SF32LB52 内部 `LDO3_3V3` |
| DTS 状态 | `disabled` | 避免启动时误振动；bring-up 时再同时启用 `pwm-vibrator`、`&gptim2`、`&gptim2_pwm` |

---

## 9. CPU 与时钟系统

### 9.1 CPU

```dts
&cpu0 {
    clock-frequency = <DT_FREQ_M(240)>;   // 240 MHz Cortex-M33
};
```

### 9.2 外部晶振

```dts
&hxt48 { status = "okay"; };   // 外部 48MHz 晶振
&lxt32 { status = "okay"; };   // 外部 32.768kHz 晶振 (RTC 时钟源)
```

### 9.3 时钟控制器 (RCC)

```dts
&rcc_clk {
    status = "okay";
    sifli,hdiv  = <1>;                    // HCLK 不分频
    sifli,pdiv1 = <1>;                    // PCLK1 不分频
    sifli,pdiv2 = <6>;                    // PCLK2 ÷6
    sifli,sys-clk-src = "dll1";          // 系统时钟源 = DLL1
    sifli,mpi1-clk-src = "dll2";         // PSRAM 时钟源 = DLL2

    dll1 {
        status = "okay";
        clock-frequency = <DT_FREQ_M(240)>;   // 240 MHz → 系统时钟
    };
    dll2 {
        status = "okay";
        clock-frequency = <DT_FREQ_M(288)>;   // 288 MHz → PSRAM OPI 时钟
    };
};
```

| 参数 | 值 | 说明 |
|------|----|------|
| `dll1` | 240 MHz | 系统主时钟源 |
| `dll2` | 288 MHz | MPI1 (PSRAM) 时钟源，OPI 频率 = 144 MHz |
| `hdiv` | 1 | HCLK = 240 MHz |
| `pdiv1` | 1 | PCLK1 = 240 MHz |
| `pdiv2` | 6 | PCLK2 = 40 MHz |

---

## 10. GPIO 控制器

```dts
&gpioa_00_31 { status = "okay"; };   // PA_00 ~ PA_31
&gpioa_32_44 { status = "okay"; };   // PA_32 ~ PA_44
```

SF32LB52 有两个 GPIO 块，合起来共 45 个 IO。在 DTS 中使用时注意 offset：

| DTS phandle | offset 范围 | 物理引脚 | 示例 |
|------------|------------|---------|------|
| `&gpioa_00_31` | 0~31 | PA_00 ~ PA_31 | `<&gpioa_00_31 26 ...>` = PA_26 |
| `&gpioa_32_44` | 0~12 | PA_32 ~ PA_44 | `<&gpioa_32_44 10 ...>` = PA_42 |

---

## 11. DMA

```dts
&dmac { status = "okay"; };
```

使能 DMA 控制器。当前使用者：
- `&mpi2` → Flash 读写的 DMA 通道
- `&audcodec` → 音频播放/录音的 DMA 通道

---

## 12. 内部 LDO

```dts
&ldo1_1v8 {
    regulator-boot-on;         // 启动时自动使能
    status = "okay";
};
```

| 属性 | 说明 |
|------|------|
| 用途 | 提供 1.8V 给 PSRAM (`&mpi1` 的 `power-supply`) |
| `regulator-boot-on` | 驱动初始化时自动打开，`memc_sf32lb_mpi_opi_psram_init()` 会先调 `regulator_enable()` |

```dts
&ldo3_3v3 {
    regulator-name = "vdd33-vout";
    regulator-boot-on;
    status = "okay";
};
```

| LDO | DTS 节点 | 板级/芯片用途 |
|-----|----------|----------------|
| `LDO1_1V8` | `ldo1_1v8` | PSRAM / MPI1 1.8 V 供电 |
| `LDO2_3V3` / `VDD33_VOUT1` | `ldo2_3v3` | Flash 启动相关；HAL 里有关机前关闭 LDO2 的注释，说明它由 ROM/早期启动代码打开以保证 Flash 可读，板级 DTS 不在运行期接管 |
| `LDO3_3V3` / `VDD33_VOUT2` | `ldo3_3v3` | 核心板网名 `VDD33_VOUT`，给 LED3 WS2812B 和振动马达供电 |

> `VDD33_VOUT` 是芯片内部 LDO 输出，不是外部 3.3 V 输入；马达和彩灯总负载需要按模组 150 mA 输出能力核算。

---

## 13. MPI 存储控制器

### 13.1 MPI1 — 内部 OPI PSRAM

```dts
&mpi1 {
    compatible = "sifli,sf32lb-mpi-opi-psram";
    reg = <0x50041000 0x1000>,        // MPI1 控制寄存器
          <0x60000000 DT_SIZE_M(8)>;  // PSRAM 内存映射窗口 (8MB)
    reg-names = "ctrl", "psram";
    pinctrl-0 = <&mpi1_default>;
    pinctrl-names = "default";
    power-supply = <&ldo1_1v8>;       // 1.8V LDO
    status = "okay";
};
```

| 寄存器 | 地址 | 说明 |
|--------|------|------|
| `ctrl` | `0x50041000` | MPI 控制器寄存器（命令/时序/校准） |
| `psram` | `0x60000000` | PSRAM AHB 映射窗口，CPU 直接读写 |

> **SiP 合封**: PSRAM die 与 MCU 封装在同一模组内，OPI 信号走内部 bond wire。
> 详见 [psram-registration.md](psram-registration.md)。

### 13.2 MPI2 — 外部 QSPI NOR Flash

```dts
&mpi2 {
    compatible = "sifli,sf32lb-mpi-qspi-nor";
    dmas = <&dmac 0 SF32LB52X_DMA_REQ_MPI2 SF32LB_DMA_PL_MEDIUM>;
    sifli,psclr = <0>;    // prescaler = 0 (不分频)
    sifli,lines = <4>;    // 4 线 QSPI 模式
    status = "okay";

    py25q128ha: flash@0 {
        compatible = "puya,py25q128ha", "jedec,qspi-nor";
        reg = <0x0>;
        size = <DT_SIZE_M(128)>;                    // 16 MB
        quad-enable-requirements = "S2B1v1";        // 四线使能方式

        partitions {
            compatible = "fixed-partitions";
            #address-cells = <1>;
            #size-cells = <1>;

            ptable: partition@0 {
                label = "ptable";
                reg = <0x0 DT_SIZE_K(64)>;          // 0~64KB: 分区表
            };

            code: partition@10000 {
                label = "code";
                reg = <0x10000 DT_SIZE_K(16320)>;   // 64KB~16MB: 固件代码
            };
        };
    };
};
```

| 分区 | 偏移 | 大小 | 用途 |
|------|------|------|------|
| `ptable` | 0x00000 | 64 KB | SiFli 分区表 |
| `code` | 0x10000 | 16320 KB | Zephyr 固件 |

---

## 14. PinCtrl (引脚复用)

```dts
&pinctrl { status = "okay"; };
```

所有引脚复用配置在 `sf32lb52_hspi-pinctrl.dtsi` 中定义：

| 配置名 | 引脚 | 外设 |
|--------|------|------|
| `usart1_default` | PA_18(RXD), PA_19(TXD) | 调试控制台 / Shell |
| `i2c1_default` | PA_33(SDA), PA_37(SCL) | 触摸屏 I2C (FT6146) |
| `i2c2_default` | PA_11(SDA), PA_10(SCL) | 充电芯片 I2C (AW32001) |
| `i2c3_default` | PA_39(SDA), PA_40(SCL) | 传感器 I2C (IMU+磁力计+光照) |
| `spi1_default` | PA_24(DIO), PA_25(DI), PA_28(CLK), PA_29(CS) | TF 卡 SPI |
| `vib_pwm_default` | PA_20 | GPTIM2 CH1, 振动马达 PWM |
| `lcdc_qspi_default` | PA_02~PA_08 | CO5300 OLED QSPI |
| `mpi1_default` | SA01~SA12 | 内部 OPI PSRAM |

> **注意**: SA00 和 SA06 是 PSRAM 的电源引脚，配为 `SA00_ANALOG`/`SA06_ANALOG`（不作为数字 IO 使用）。

---

## 15. UART 控制台

```dts
&usart1 {
    status = "okay";
    current-speed = <1000000>;            // 1 Mbps
    pinctrl-0 = <&usart1_default>;
    pinctrl-names = "default";
};
```

| 属性 | 值 | 说明 |
|------|----|------|
| 引脚 | PA_18(RX), PA_19(TX) | |
| 波特率 | 1,000,000 | 高速调试输出 |
| 角色 | `zephyr,console` + `zephyr,shell-uart` | |

---

## 16. 音频 Codec

```dts
&audcodec {
    dmas = <&dmac 1 SF32LB52X_DMA_REQ_AUDAC_CH0 SF32LB_DMA_PL_HIGH>,   // TX: 播放
           <&dmac 4 SF32LB52X_DMA_REQ_AUDADC_CH0 SF32LB_DMA_PL_HIGH>;  // RX: 录音
    dma-names = "tx", "rx";
    pa-power-gpios = <&gpioa_32_44 10 GPIO_ACTIVE_HIGH>;   // PA_42 → NS4150B (U6)
    status = "okay";
};
```

| 属性 | 值 | 说明 |
|------|----|------|
| DMAC TX | channel 1 | 音频 DAC 播放 |
| DMAC RX | channel 4 | 音频 ADC 录音 |
| PA GPIO | PA_42 | Class-D 功放 NS4150B 使能脚 |

---

## 17. 看门狗 & RTC

```dts
&wdt { status = "okay"; };
&rtc { status = "okay"; };
```

---

## 18. I2C 总线

### 18.1 I2C1 — 触摸屏

```dts
&i2c1 {
    status = "okay";
    pinctrl-0 = <&i2c1_default>;
    pinctrl-names = "default";
    clock-frequency = <I2C_BITRATE_FAST>;    // 400 kHz

    ft6146: ft6146@38 {
        compatible = "focaltech,ft6146";
        reg = <0x38>;
        int-gpios = <&gpioa_32_44 9 GPIO_ACTIVE_LOW>;    // PA_41 INT
        reset-gpios = <&gpioa_00_31 9 GPIO_ACTIVE_LOW>;  // PA_09 RST
        status = "disabled";    // ← 暂未 bring-up
    };
};
```

### 18.2 I2C3 — 传感器总线

```dts
&i2c3 {
    status = "okay";
    pinctrl-0 = <&i2c3_default>;             // PA_39(SDA), PA_40(SCL)
    pinctrl-names = "default";
    clock-frequency = <I2C_BITRATE_FAST>;

    lsm6dsl: lsm6dsl@6a {                    // LSM6DS3TR-C IMU (U13)
        compatible = "st,lsm6dsl";
        reg = <0x6a>;                        // SA0=0 → 0x6A
        irq-gpios = <&gpioa_00_31 31 GPIO_ACTIVE_HIGH>;  // PA_31 INT1
        status = "disabled";
    };

    mmc56x3: mmc56x3@30 {                    // MMC5603NJ 磁力计 (U14)
        compatible = "memsic,mmc56x3";
        reg = <0x30>;                        // 固定地址
        status = "disabled";
    };

    ltr303: ltr303@29 {                      // LTR-303ALS-01 光照 (U16)
        compatible = "liteon,ltr329";        // 兼容驱动，待验证
        reg = <0x29>;
        status = "disabled";
    };
};
```

| 芯片 | I2C 地址 | 供电 | 状态 |
|------|---------|------|------|
| LSM6DS3TR-C (U13) | 0x6A | GS_3V3 | disabled |
| MMC5603NJ (U14) | 0x30 | GS_3V3 | disabled |
| LTR-303ALS-01 (U16) | 0x29 | GS_3V3 | disabled |

> **电源依赖**: 三个传感器都挂在 GS_3V3 轨上 (PA_30 控制)。上电顺序: PA_38 → PA_26 → PA_30，PA_30 上电后需等 ~500µs 才能访问 I2C。

### 18.3 I2C2 — 充电芯片

```dts
&i2c2 {
    status = "okay";
    pinctrl-0 = <&i2c2_default>;             // PA_11(SDA), PA_10(SCL)
    pinctrl-names = "default";
    clock-frequency = <I2C_BITRATE_FAST>;

    charger: charger@49 {
        compatible = "awinic,aw32001";       // 尚无上游驱动
        reg = <0x49>;                        // AW32001ECSR (U3)
        // No int-gpios: CHG_INT is not directly connected to an MCU GPIO.
        // PA_44 is VBUS_DET via R14/R15, not AW32001 INT.
        status = "disabled";
    };
};
```

---

## 19. SPI

```dts
&spi1 {
    status = "okay";
    pinctrl-0 = <&spi1_default>;
    pinctrl-names = "default";
};
```

| 引脚 | 功能 |
|------|------|
| PA_24 | DIO (MOSI/MISO 合并) |
| PA_25 | DI (MISO, 带 pull-up) |
| PA_28 | CLK |
| PA_29 | CS |

当前未挂载子设备（TF 卡驱动待添加）。

---

## 20. 加密与安全

```dts
&crc      { status = "okay"; };    // 硬件 CRC
&crypto   { status = "okay"; };    // 硬件加密引擎
temp_sensor: &tsen { status = "okay"; };  // 片内温度传感器
&trng     { status = "okay"; };    // 真随机数发生器
&mailbox  { status = "okay"; };    // 双核 mailbox (BLE HCI)
&efuse    { status = "okay"; };    // eFuse (芯片唯一 ID 等)
```

---

## 21. 显示: LCDC + CO5300 OLED

```dts
&lcdc {
    status = "okay";

    mipi_dbi: mipi-dbi {
        status = "okay";
        #address-cells = <1>;
        #size-cells = <0>;
        pinctrl-0 = <&lcdc_qspi_default>;    // PA_02~PA_08, QSPI 模式
        pinctrl-names = "default";

        co5300: display@0 {
            compatible = "chipone,co5300-qspi";
            reg = <0>;
            reset-gpios = <&gpioa_00_31 0 GPIO_ACTIVE_LOW>;  // PA_00 RSTB
            width = <390>;                                     // 390×450 AMOLED
            height = <450>;
            mipi-max-frequency = <50000000>;                   // 50 MHz QSPI
            mipi-mode = "MIPI_DBI_MODE_QSPI";
        };
    };
};
```

| 属性 | 值 | 说明 |
|------|----|------|
| IC | CO5300 | Chipone OLED 驱动 IC |
| 接口 | MIPI DBI QSPI | PA_02(TE) PA_03(CS) PA_04(CLK) PA_05~08(D0~D3) |
| 分辨率 | 390×450 | AMOLED |
| 复位 | PA_00, 低有效 | |
| 供电 | VSYS_1 直供 | 屏幕自带电源 IC 从 VCC_3V3 生成 AVDD |
| AVDD | **无主控 GPIO** | 屏幕内部自举，不占用 PA_37（PA_37 是触摸 I2C1 SCL） |

---

## 22. 附录: 驱动与绑定映射表

| DTS compatible | 驱动文件 | 初始化阶段 |
|---------------|---------|-----------|
| `regulator-fixed` | `zephyr/drivers/regulator/regulator_fixed.c` | PRE_KERNEL |
| `gpio-keys` | `zephyr/drivers/input/input_gpio_keys.c` | POST_KERNEL |
| `worldsemi,ws2812-gpio` | `zephyr/drivers/led_strip/ws2812.c` | POST_KERNEL |
| `pwm-leds` | `zephyr/drivers/led/led_pwm.c` | POST_KERNEL |
| `sifli,sf32lb-gpt-pwm` | `zephyr/drivers/pwm/pwm_sf32lb_gpt.c` | POST_KERNEL |
| `sifli,sf32lb-rcc-clk` | `zephyr/drivers/clock_control/clock_control_sf32lb.c` | PRE_KERNEL |
| `sifli,sf32lb-mpi-opi-psram` | `zephyr/drivers/memc/memc_sf32lb_mpi_opi_psram.c` | POST_KERNEL |
| `sifli,sf32lb-mpi-qspi-nor` | `modules/hal/sifli/...` | POST_KERNEL |
| `puya,py25q128ha` / `jedec,qspi-nor` | `zephyr/drivers/flash/spi_nor.c` | POST_KERNEL |
| `sifli,sf32lb-usart` | `zephyr/drivers/serial/uart_sf32lb.c` | PRE_KERNEL |
| `sifli,sf32lb-lcdc` | `zephyr/drivers/display/display_sf32lb_lcdc.c` | POST_KERNEL |
| `chipone,co5300-qspi` | `zephyr/drivers/display/display_co5300.c` | POST_KERNEL |
| `st,lsm6dsl` | `zephyr/drivers/sensor/st/lsm6dsl.c` | POST_KERNEL |
| `memsic,mmc56x3` | `zephyr/drivers/sensor/mmc56x3/` | POST_KERNEL |
| `zephyr,memory-region` | **无驱动** (链接器处理) | 链接时 |

| 初始化阶段 | 含义 |
|-----------|------|
| `PRE_KERNEL` | 内核启动前，最早初始化 |
| `POST_KERNEL` | 内核启动后，调度器已运行 |
| 链接时 | 链接器脚本生成，无运行时代码 |
