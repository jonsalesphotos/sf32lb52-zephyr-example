# SF32LB52 黄山派 电源树

> 根据原理图 `SCH_黄山派核心板_SCH_V1.2_2026-06-24` 和网表梳理，2026-06-28。

---

## 1. 电源树总图

```
                       USB_VBUS_5V
                            │
                   LP5305AQVF (U17)
                   OVP/OCP 保护芯片
                            │
                         VBUS_5V ───LED1 电源指示灯 (R6 4.7kΩ → GND, 插 USB 即亮)
                            │
   VBAT_S ─────────────────┤
   (电池)                  │
                            ▼
          ┌─────────────────────────────────┐
          │     AW32001ECSR (U3)            │
          │     线性充电芯片                  │
          │     I2C2: SCL=PA_10, SDA=PA_11  │
          │     CHG_INT: U3.B2 → Q1/R5      │
          │     VBUS_DET: PA_44             │
          │     VBUS → VSYS_S               │
          │     VBAT → VSYS_S               │
          └─────────────────────────────────┘
                            │
                         VSYS_S (VSYS)
                            │
       ┌────────────────────┼────────────────────┐
       │                    │                    │
       ▼                    ▼                    ▼
   NS4150B             SF32LB52             LP5240HVF
   功放 (PA_42)         主控 U1              (U2, PA_38)
   Class-D PA             │                    │
                          └─ LDO3_3V3 / VDD33_VOUT2
                             模组 pin 17, 板级网名 VDD33_VOUT
                              ├─ R51 0Ω → LED3 WS2812B VDD
                              └─ R36 5.1Ω → 振动马达供电
                                               │
                                               ▼
                                            VSYS_1
                                               │
          ┌──────────────────┬─────────────────┤
          │                  │                 │
          ▼                  ▼                 ▼
      屏幕 FPC        ETA5055V330DS2F    ETA5055V330DS2F
      (VSYS_1 直供)   (U4, PA_26)        (U15, PA_30)
      CO5300 OLED          │                 │
                           ▼                 ▼
                       VCC_3V3_S          GS_3V3
                     (TP/SD/SPI)       (传感器总线)
```

---

## 2. 电源域详细说明

### 2.1 VBUS_5V — USB 5V 总线

| 属性 | 值 |
|------|-----|
| 来源 | USB_VBUS_5V → LP5305AQVF (U17) |
| 保护 | 过压/过流保护 (OVP/OCP) |
| 负载 | LED1 电源指示灯 (R6 4.7kΩ → GND，**不可控**)、AW32001 充电输入 |

### 2.2 VSYS — 系统主电源

| 属性 | 值 |
|------|-----|
| 来源 | AW32001ECSR (U3) 输出，VBUS_5V 或 VBAT_S 二选一 |
| 电压 | 电池电压或 USB 5V 经充电路径 |
| 负载 | SF32LB52 主控、NS4150B 功放、LP5240HVF (VSYS_1 生成) |

### 2.3 VSYS_1 — 外设电源总线

| 属性 | 值 |
|------|-----|
| 来源 | VSYS → LP5240HVF (U2)，PA_38 高有效使能 |
| DTS 节点 | `vsys_en` = `regulator-vsys` |
| 上电顺序 | **第 1 步**，最先上电 |
| 负载 | 屏幕 FPC (直供)、U4 (VCC_3V3)、U15 (GS_3V3) |

### 2.4 VCC_3V3_S — 3.3V 数字外设电源

| 属性 | 值 |
|------|-----|
| 来源 | VSYS_1 → ETA5055V330DS2F (U4)，PA_26 高有效使能 |
| DTS 节点 | `vcc_3v3` = `regulator-vcc3v3` |
| 上电顺序 | **第 2 步** |
| 负载 | 触摸 I2C1 上拉、SPI1 / TF 卡 VDD、LCD FPC 接口 3.3V 参考 |
| 关键依赖 | **必须上电** 才有 TP 通信和 SD 卡供电 |

### 2.5 GS_3V3 — 传感器 3.3V 电源

| 属性 | 值 |
|------|-----|
| 来源 | VSYS_1 → ETA5055V330DS2F (U15)，PA_30 高有效使能 |
| DTS 节点 | `gs_3v3` = `regulator-gs3v3` |
| DTS 策略 | `regulator-boot-off` — **默认关闭**，应用层按需 `regulator_enable()` |
| 上电顺序 | **第 3 步**（最后），但需应用显式开启 |
| 负载 | I2C3 传感器总线: LSM6DS3TR-C (U13)、MMC5603NJ (U14)、LTR-303ALS-01 (U16) |
| 延时要求 | GS_3V3 上电后 ~500 µs 才能访问传感器 I2C |

### 2.6 VDD33_VOUT — 模组内部 LDO3 3.3V 输出

| 属性 | 值 |
|------|-----|
| 来源 | SF32LB52 内部 PMUC `LDO3_3V3` / 模组管脚 `VDD33_VOUT2` |
| 板级网名 | `VDD33_VOUT` |
| DTS 节点 | `ldo3_3v3`，regulator-name = `vdd33-vout` |
| 负载 | `R51` 0Ω → `LED3` WS2812B VDD；`R36` 5.1Ω → 振动马达供电路径 |
| 控制信号 | WS2812B data = `PA_32`；Vibrator PWM = `PA_20_VIB_PWM` |
| 电流限制 | 模组资料标称外部 3.3V 输出最大 150 mA；马达和彩灯总负载需按这个预算核算 |
| 注意 | 这是芯片内部 LDO 输出，不是外部 3.3V 输入，也不是系统主供电；系统主供电仍是 `VSYS` / 电池路径 |

---

## 3. 上电时序

```
                    ┌─ regulator-always-on: 自动由驱动拉高
                    │
PA_38 (VSYS_1) ─────┤
                    │  t_settle
                    ▼
PA_26 (VCC_3V3) ────┤
                    │  t_settle
                    ▼
PA_30 (GS_3V3) ─────┤  ← regulator-boot-off: 初始 LOW，需应用层 regulator_enable()
                    │
                    │  ~500 µs (应用层延时)
                    ▼
传感器 I2C / 充电 I2C 可用
```

> SDK `bsp_power.c` 实现此顺序。所有使能 GPIO 均为高有效，默认复位后为低（关闭）。
> `vsys_en` 和 `vcc_3v3` 由 `regulator-always-on` 自动拉高；`gs_3v3` 使用 `regulator-boot-off` 默认保持关闭，在传感器 bring-up 时由应用层开启。

---

## 4. LED 清单

| PCB 标号 | 型号 | 连接 | 可控 | DTS |
|---------|------|------|------|-----|
| LED1 | Red 0603 | VBUS_5V → R6 (4.7kΩ) → LED1 → GND | ❌ 插 USB 即亮 | 无 |
| LED3 | WS2812B-2020 | PA_32 (1-Wire data)，VDD = `VDD33_VOUT` 经 R51 | ✅ | `led_strip` (disabled) |

> **注意**: PA_26 **没有** 连接任何 LED。之前 DTS 中 `led0` 在 PA_26 是错误的（源自对 SDK `CONFIG_BSP_LED1_ACTIVE_HIGH` 的误解——SDK 将 VCC_3V3 使能脚称为 "LED1"，但实际硬件上 LED1 是 VBUS_5V 电源指示灯）。

### 4.1 振动马达

| 项目 | 连接 |
|------|------|
| 供电 | `VDD33_VOUT` 经 R36 5.1Ω 到马达/保护二极管网络 |
| 控制 | `PA_20_VIB_PWM`，DTS 中按 `GPTIM2 CH1` 建模 |
| DTS | `pwm-vibrator` / `vibrator` 节点已建，但默认 `disabled`，避免启动时误振动 |

---

## 5. DTS regulator 对应关系

| DTS 节点 | GPIO | 芯片 | 输出电压 | 供电对象 | 策略 |
|----------|------|------|---------|---------|------|
| `vsys_en` | PA_38 | LP5240HVF (U2) | VSYS_1 | 屏幕、U4、U15 | `regulator-always-on` — 系统主电源，永不关闭 |
| `vcc_3v3` | PA_26 | ETA5055V330DS2F (U4) | VCC_3V3_S (3.3V) | TP I2C, SPI1, SD 卡 | `regulator-always-on` — 基础外设电源，运行时常开 |
| `gs_3v3` | PA_30 | ETA5055V330DS2F (U15) | GS_3V3 (3.3V) | I2C3 传感器总线 | `regulator-boot-off` — 默认关闭，应用层按需开启 |
| `ldo3_3v3` | PMUC 内部控制 | SF32LB52 内部 LDO3 | `VDD33_VOUT` (3.3V) | LED3 WS2812B、振动马达供电 | `regulator-boot-on` — 模组内部 LDO |

所有 regulator 均设置 `regulator-boot-on`，需要 `CONFIG_REGULATOR=y` 才能自动使能。

### 5.1 Regulator 策略说明

Zephyr 的 `regulator-fixed` 驱动通过引用计数管理 GPIO 使能：

| DTS 属性 | 初始 refcnt | 初始 GPIO | 能关闭? | 本板用途 |
|----------|------------|----------|---------|---------|
| `regulator-always-on` | 1 | HIGH | ❌ `disable()` NOOP | 系统级电源 (vsys_en, vcc_3v3) |
| `regulator-boot-on` | 1 | HIGH | ✅ refcnt→0 时 | 模组内部 LDO (ldo3_3v3) |
| `regulator-boot-off` | 0 (强制) | LOW | ✅ 应用使能 | 传感器总线 (gs_3v3) |

- **vsys_en / vcc_3v3**: 系统基础电源，`regulator-always-on`。断开 vsys_en=MCU 掉电，断开 vcc_3v3=TP/SPI/SD 失效。
- **gs_3v3**: 传感器专用电源，`regulator-boot-off`。默认关闭节省功耗，应用层通过 `regulator_enable(DT_NODELABEL(gs_3v3))` 按需开启，使用完毕 `regulator_disable()` 关闭。传感器驱动 (lsm6dsl/mmc56x3/ltr329) 的 Zephyr binding 未内置 `vin-supply` 支持，因此 regulator 联动需在应用层显式管理。

---

## 6. 关键提醒

1. **LED1 不可控**: 是 VBUS_5V 电源指示灯，插 USB 即亮，无 GPIO 控制。
2. **PA_26 ≠ LED**: PA_26 控制 VCC_3V3_S 轨，关闭它会断开触摸屏 I2C 和 SD 卡供电。
3. **电源顺序严格**: 必须 PA_38 → PA_26 → PA_30，不可颠倒。
4. **GS_3V3 延时**: 上电后至少等待 500 µs 才能访问 I2C3 传感器。
5. **VDD33_VOUT 是内部 LDO3 输出**: 给 WS2812B 和振动马达供电；PA_32 / PA_20 只是控制信号。
6. **WS2812B (LED3)**: 1-Wire NZR 协议，当前 DTS 已建节点但 disabled。
7. **振动马达**: DTS 已按 PWM 输出建占位节点但 disabled，启用前需确认占空比、启动电流和 150 mA 输出预算。

---

## 7. KEY1 / PWRKEY 与 AW32001 充电芯片联动

> 电路溯源: 网表 `Netlist_黄山派核心板_SCH_V1.2_2026-06-24.tel`
> 芯片手册: `AW32001E_datasheet_Awinic.md`

### 7.1 电路分析

KEY1 (SW1) 不仅是普通按键，还通过 MOSFET Q1 与 AW32001 充电芯片的 INT 引脚
硬件联动，构成一个**一石三鸟**的设计：

```
VBAT ── SW1.1
         │                    ┌─────────────────────┐
    SW1 (按下)                │     AW32001ECSR      │
         │                    │                      │
         SW1.2 ── R34 ──┬────┤ U1.14  PA_34 (MCU)   │
                        │    │                      │
                        ├────┤ R35 (15kΩ) ── GND    │
                        │    │                      │
                        └────┤ Q1.1  N-MOSFET Gate  │
                             │   │                  │
                             │   Q1.2 ── GND        │
                             │   Q1.3 ──────────────┤ U3.B2  INT
                             │                      │   │
                             │                      │   R5 (100kΩ)
                             │                      │   │
                             │                      │   VDD
                             └─────────────────────┘
```

| 网表网络 | 连接节点 | 说明 |
|---------|---------|------|
| `PA_34_KEY1` | CN3.26, D15.2, **R34.2**, SW1.2, TP8.1 | 按键侧 |
| `PA_34_PWRKEY` | **Q1.1**, **R34.1**, R35.2, U1.14 | MCU + MOSFET Gate |
| `CHG_INT` | Q1.3, R5.1, U3.B2 | AW32001 INT 脚 |
| `PA_44_VBUSDET` | R14.1, R15.2, U1.2 | MCU 读取 VBUS 分压检测，不是 AW32001 INT |

### 7.2 AW32001 INT 引脚功能

根据 AW32001ECSR datasheet (Pin B2):

| 功能 | 方向 | 说明 |
|------|------|------|
| **Charge status interrupt** | AW32001 → Host | 充电状态/故障中断通知 |
| **Shipping mode control** | Host → AW32001 | 拉低 INT 可进入/退出船运模式 |
| **Wake from shipping** | Host → AW32001 | 船运模式下拉低 INT 可唤醒 |

INT 是**双向开漏**引脚：
- 常态: CHG_INT 由 R5 拉到 U3 VDD；AW32001 可输出低脉冲，但该网未直接接到 MCU GPIO，软件不能通过 PA_44 读取它
- Host 拉低: Q1 导通 → CHG_INT=LOW → AW32001 检测外部拉低 → 切换 shipping mode

### 7.3 按键行为与时长

```
短按 (< 数百 ms):
  CHG_INT 短暂拉低
  → AW32001 去抖忽略
  → MCU 检测 KEY1 → 触发 INPUT_KEY_1 事件
  → 普通按键行为

长按 (数秒):
  CHG_INT 持续拉低
  → AW32001 判定为 shipping mode 切换命令
  → 断开内部 BATFET（电池→系统 MOSFET）
  → VSYS 断电 → MCU 掉电 → 等效硬关机

船运模式下短按:
  CHG_INT 拉低
  → AW32001 唤醒
  → 重新接通 BATFET → VSYS 上电
  → MCU 冷启动
```

### 7.4 关键约束

| 约束 | 说明 |
|------|------|
| **MCU 不能长时间拉高 PA_34** | 会导致 CHG_INT 持续 LOW → AW32001 误判为 shipping mode 命令 → 系统断电 |
| **长按 = 硬件掉电** | 非 Zephyr 软件控制，是 AW32001 硬件行为，软件无法拦截 |
| **PA_44 不是 AW32001 INT** | 通过分压电阻 R14/R15 读取 VBUS_DET，只能作为 USB/VBUS 插入检测 |
| **PA_34 不能配成推挽输出** | 必须保持输入态，否则可能持续驱动 Q1 |

