**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

- **AW32001E Single Cell Li-ion Battery Charger with Power Path Management and Full USB Compliance** 

- **Features General Description** ⚫ Charge Voltage Regulation Accuracy: The AW32001E is a highly-integrated Li-Ion/Li±0.5% ( 0°C to 50°C ) Polymer battery linear charger with system power path management. The charge process of 

- ⚫ Charge Current Accuracy: ±5% AW32001E includes: Pre-Charge, Fast Charge and 

- ⚫ Maximum 28V Input Voltage Rating with OverConstant Voltage Regulation. The charge Voltage Protection parameters and operating modes are 

- ⚫ Minimum -5V Input Voltage Protection programmable through I[2] C interface. The charge ⚫ Complete Charge Process with Pre-Charge, Fast process runs automatically and recharging occurs Charge and Constant Voltage Regulation when the battery voltage drops below VBAT_REG- 

- ⚫ Programmable Charge Parameters Through I[2] C VRCH after the charge done status. Compatible Interface The AW32001E is targeted at space limited 

- ⚫ Programmable Charge Termination and portable applications. The chip can take input 

- Autonomous Recharge power from either an AC adaptor or a USB port to 

- ⚫ Wide Range of Fast Charge Current: supply the system load and charge the battery. 2mA~500mA Meanwhile, the chip provides system short circuit 

- ⚫ Strong and Robust Protection: VIN OVP, Battery protection function by limiting the current from the OVP, OCP, Reverse Leakage Protection, Short input to the system and the battery to the system. Protection, Thermal Protection, PCB Over These features are effective to protect the battery Temperature Protection or chip from damage. The parameters of input 

- ⚫ BATFET Control to Support Shipping Mode current limit, the discharge current limit and safety timer can be programmed by the I[2] C interface. 

- ⚫ System Reset Function Additionally, input over voltage protection, input 

- ⚫ Fully Integrated Power Path Management under voltage lockout and input headroom voltage 

- ⚫ Ultra-low Battery Leakage Current to Support are integrated for good input source detection. Shipping Mode 

- ⚫ WLCSP 1.68mm×1.68mm×0.63mm-9B, 0.5mm AW32001E separates the charging route from the Pitch Package system power supply to fulfill the power management function. The system power supply is 

- ⚫ 7-bit slave address (A7~A1) is 1001001 at first priority with no dependency on battery 

- binary(0x49H) existence. Once a bad power-limited adapter 

- ⚫ IEC62368-1 Approved-File No.BE-37454 appears at the input, AW32001E would reduce the charging current firstly. If the system load is still too 

- **Applications** heavy for input source, AW32001E will reduce the input-system current to prevent the input source from being pulled down. Under this circumstance, if 

- ⚫ Smart Handheld Devices 

AW32001E separates the charging route from the system power supply to fulfill the power management function. The system power supply is at first priority with no dependency on battery existence. Once a bad power-limited adapter appears at the input, AW32001E would reduce the charging current firstly. If the system load is still too heavy for input source, AW32001E will reduce the input-system current to prevent the input source from being pulled down. Under this circumstance, if the system voltage drops 30mV below the battery voltage, the battery to system supply route will be fully turned on to power the system load, which is supplement mode. 

- ⚫ Wearable Devices 

- ⚫ Smart Watches 

- ⚫ Fitness Accessories 

www.awinic.com                              1             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Typical Application Circuit** 

**==> picture [457 x 527] intentionally omitted <==**

**----- Start of picture text -----**<br>
USB  IN SYS SLoadystem<br>Port CIN1 CSYS<br>4.750V m F 4.7 m F<br>TVS<br>VDD BAT<br>CVDD CBAT<br>1 m F 4.7 m F<br>AW32001E VDD<br>VDD VIO RT1<br>BATTERY<br>10kΩ 10kΩ 10kΩ<br>INT NTC<br>Host RT2 RNTC<br>SCL<br>SDA GND<br>Figure 1  Typical Application Circuit of AW32001E<br>All trademarks are the property of their respective owners.<br>awinic Confidential<br>**----- End of picture text -----**<br>


www.awinic.com                              2             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Pin Configuration and Top Mark** 

**==> picture [473 x 589] intentionally omitted <==**

**----- Start of picture text -----**<br>
AW32001ECSR PIN Configuration AW32001ECSR Marking<br>(Top View) (Top View)<br>1 2 3 1 2 3<br>A IN SYS BAT A<br>B NTC INT VDD B<br>C SDA SCL GND C<br>3GP4 - AW32001ECSR Marking<br>XXXX - Production Tracing Code<br>YYYY YYYY - Die Location<br>Figure 2  Pin Configuration and Top Mark<br>Pin Definition<br>Pin No.  Pin Name  Description<br>A1  IN  Input power pin. Bypass with a 4.7μF capacitor to GND.<br>A2  SYS  System power supply pin. Bypass with a 4.7μF capacitor to GND.<br>A3  BAT  Battery pin. Bypass with a 4.7μF capacitor to GND.<br>Temperature sense input. Connect a negative temperature<br>coefficient thermistor. Program the hot and cold temperature window<br>with resistor dividers from VDD to GND, and NTC is the middle node.<br>B1  NTC  Pull NTC to VDD if NTC function is not used. If NTC function is<br>unused, it is suggested to disable the NTC function and tie the NTC<br>port to VDD for decreasing leakage current of battery, because<br>PCB_OTP is default.<br>Interrupt output. The INT pin can send charge status and fault<br>interrupt to the host. This pin is also used to disconnect the system<br>B2  INT<br>from battery, and awake the chip from shipping mode. If INT is<br>unused, it is suggested to tie INT to VDD by resistor.<br>Internal power supply pin. Bypass with a 1μF capacitor to GND. No<br>B3  VDD<br>external load is allowed.<br>C1  SDA  I [2] C Interface serial date.<br>C2  SCL  I [2] C Interface clock.<br>C3  GND  Ground.<br>awinic Confidential<br>YYYY YYYY<br>3GP4<br>XXXX<br>**----- End of picture text -----**<br>


## **Pin Definition** 

www.awinic.com 3             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

**==> picture [284 x 38] intentionally omitted <==**

Sep. 2023 V1.4 

## **Ordering Information** 

**Moisture Part Environmental Delivery Temperature Package Marking Sensitivity Number Information Form Level** 3000 units/ AW32001ECSR -40°C ～ 85°C 1.68mm×1.68mm-9B WLCSP 3GP4 MSL1 ROHS+HF Tape and Reel 

www.awinic.com 4             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Absolute Maximum Ratings[(NOTE1)]** 

|**PARAMETERS**|**PARAMETERS**|**PARAMETERS**|**MIN**|**MAX**|**MAX**|**UNIT**|
|---|---|---|---|---|---|---|
|Input voltage range VIN(with respect to GND)|IN||-5|28||V|
|NTC voltage range VNTC(with respect to GND)|NTC||-0.3|VVDD+0.3||V|
|Other pins voltage range (with respect to GND)<br>|SYS, BAT(NOTE 2), INT,<br>VDD, SCL, SDA<br>||-0.3<br>l|6<br>||V|
|Operating free-air temperature range<br>|||-40<br>|85<br>||°C|
|Operating junction temperature TJ<br>|||-40<br>|150<br>||°C|
|Storage temperature TSTG<br>|||-65<br>|150<br>||°C|
|Lead temperature (Soldering 10 seconds)<br>||||260<br>||°C|
|_NOTE1_:_Conditions out of those ranges listed in "absolute maximum ratings" may cause permanent damages_<br>_to the device. In spite of the limits above, functional operation conditions of the device should within the ranges_<br>_listed in "recommended operating conditions". Exposure to absolute-maximum-rated conditions for prolonged_<br>_periods may affect device reliability._<br>_NOTE2_: BAT pin can handle 8.9V transients for less than 10us<br>**ESD Rating and Latch Up**<br>nfiden|||||||
|**PARAMETERS**<br>||**VALUE**<br>|||**UNIT**||
|HBM (Human Body Model)(NOTE 3)<br>||±2<br>|||kV||
|CDM(NOTE 4)<br>||±1.5<br>|||kV||
|Latch-Up(NOTE 5)<br>c||+IT：200<br>-IT：-200<br>|||mA||
|_NOTE3_:_The human body model is a 100pF capacitor discharged through a 1.5kΩ resistor into each pin. Test_<br>_method: ESDA/JEDEC JS-001-2017_<br>_NOTE4: Test method: ESDA/JEDEC JS-002-2018_<br>_NOTE5: Test method: JESD78E_<br>awini|||||||
|www.awinic.com5             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved|||||||



_NOTE1_ : _Conditions out of those ranges listed in "absolute maximum ratings" may cause permanent damages to the device. In spite of the limits above, functional operation conditions of the device should within the ranges listed in "recommended operating conditions". Exposure to absolute-maximum-rated conditions for prolonged_ 

_NOTE3_ : _The human body model is a 100pF capacitor discharged through a 1.5kΩ resistor into each pin. Test method: ESDA/JEDEC JS-001-2017_ 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Recommended Operating Conditions** 

|**PARAMETERS**|**MIN**|**NORM**|**MAX**|**UNIT**|
|---|---|---|---|---|
|Supply voltage range VIN|4||5.5|V|
|Supply current IIN|||550|mA|
|Discharge current IBAT<br>|||3.2<br>|A<br>|
|Charge current ICHG<br>|2<br>||512<br>|mA<br>|
|Battery regulated voltage VBAT_REG<br>|3.6<br>||4.545<br>|V<br>|
|Operating junction temperature TJ<br>|-40<br>||125<br>|°C<br>|
|**Thermal Information**<br>|||nt||
|**PARAMETERS**<br>|||**VALUE**<br>|**UNIT**<br>|
|Junction-to-ambient thermal resistance θJA<br>|||122<br>|°C/W<br>|
|awinic Co||nfi|||



www.awinic.com 6             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Electrical Characteristics** 

VIN=5V, VBAT=3.5V, TJ=25°C for typical values (unless otherwise noted). 

|**PARAMETER**|**PARAMETER**|**TEST CONDITIONS**|**MIN**|**TYP**|**MAX**|**UNIT**|
|---|---|---|---|---|---|---|
|**INPUT SOURCE AND BATTERY PROTECTION**|||||||
|VIN_UVLO|UVLO threshold voltage, entry<br>UVLO<br>|VINfalling<br>|3.5<br>|3.6<br>|3.7<br>|V|
||Hysteresis for UVLO<br>|VINrising<br>||300<br>||mV|
|TDGL_UVLO|Exit Deglitch time for VIN_UVLO<br>|Exits UVLO<br>||30<br>||ms|
|VIN_OVP|VIN OVP threshold voltage<br>|VINrising<br>|5.85<br>|6<br>|6.15<br>|V|
||VIN OVP hysteresis<br>|VINfalling from above VIN_OVP<br>||350<br>||mV|
|TDGL_OVP|Exit deglitch time for VIN_OVP<br>|Exits VINOVP<br>||30<br>||ms|
|VBAT|BAT input voltage<br>||||4.6<br>|V|
|VBAT_UVLO|UVLO threshold voltage for<br>BAT voltage, VBATfalling,<br>entry UVLO<br>|REG01H[2:0]=000<br>|2.33<br>|2.43<br>|2.53<br>|V|
|||REG01H[2:0]=100<br>fi|2.64<br>|2.76<br>|2.88<br>|V|
|||REG01H[2:0]=111<br>|2.93<br>|3.03<br>|3.13<br>|V|
||Hysteresis voltage<br>|VBAT_UVLO=2.76V<br>||190<br>||mV|
|VHDRM|Input vs. battery voltage<br>headroom threshold<br>|VINrising<br>|80<br>|130<br>|170<br>|mV|
||Input vs. battery voltage<br>headroom threshold<br>hysteresis<br>|VINfalling<br>||60<br>||mV|
|**CHARGE PROCESS**<br>|||||||
|VBAT_PRE|Pre-charge to fast charge<br>threshold<br>ni|REG04H[1]=1, VBATrising<br>|2.9<br>|3.0<br>|3.1<br>|V|
|||REG04H[1]=0, VBATrising<br>|2.7<br>|2.8<br>|2.9<br>|V|
||Fast charge to pre-charge<br>threshold<br>i|VBATfalling<br>||200<br>||mV|
|VBAT_REG|Battery charge voltage<br>regulation voltage<br>aw|REG04H[7:2]=000000,<br>VBAT_REG=3.6V<br>|3.585<br>|3.600<br>|3.615<br>|V|
|||REG04H[7:2]=101000,<br>VBAT_REG=4.2V<br>|4.180<br>|4.200<br>|4.220<br>|V|
|||REG04H[7:2]=110100,<br>VBAT_REG=4.38V<br>|4.360<br>|4.380<br>|4.400<br>|V|
|||REG04H[7:2]=111110,<br>VBAT_REG=4.53V<br>|4.507<br>|4.530<br>|4.553<br>|V|
|VRECH|Recharge threshold voltage|REG04H[0]=0, VBAT_REG=4.2V,<br>below VBAT_REG|60|100|140|mV|
|||REG04H[0]=1, VBAT_REG=4.2V,<br>below VBAT_REG|160|200|240|mV|
||Deglitch time for VRCH|VBATfalling below VRECHafter<br>charge termination||130||ms|
|VBAT_OVP|Battery OVP threshold<br>voltage|VBATthreshold over VBAT_REGto<br>turn off charger duringcharging||130||mV|
||VBAT_OVPhysteresis|||50||mV|



www.awinic.com 7             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Electrical Characteristics** _**(Continued)**_ 

VIN=5V, VBAT=3.5V, TJ=25°C for typical values (unless otherwise noted). 

|**PARAMETER**|**PARAMETER**|**TEST CONDITIONS**|**MIN**|**TYP**|**MAX**|**UNIT**|
|---|---|---|---|---|---|---|
|**POWER PATH MANAGEMENT**|||||||
|VSYS_REG|Regulated system output<br>voltage<br>|VIN=5.0V, REG07H[3:0]=0000,<br>RSYS=100Ω, ICHG=0A,<br>VSYS_REG=4.2V<br>|4.11<br>|4.20<br>|4.29<br>|V|
|||VIN=5.0V, REG07H[3:0]=1000,<br>RSYS=100Ω, ICHG=0A,<br>VSYS_REG=4.6V<br>|4.51<br>|4.60<br>|4.69<br>|V|
|||VIN=5.3V, REG07H[3:0]=1111,<br>RSYS=100Ω, ICHG=0A,<br>VSYS_REG=4.6V<br>|4.85<br>t|4.95<br>|5.05<br>|V|
|IIN_LIM|Input current limit<br>|REG00H[3:0]=0000, IIN_LIM=50mA<br>|30<br>|45<br>|60<br>|mA|
|||REG00H[3:0]=0011, IIN_LIM=140mA<br>|112<br>|125<br>|140<br>|mA|
|||REG00H[3:0]=1001, IIN_LIM=320mA<br>|275<br>|296<br>|320<br>|mA|
|||REG00H[3:0]=1111, IIN_LIM=500mA<br>i|440<br>|460<br>|500<br>|mA|
|VIN_DPM|Dynamic input power<br>management clamp<br>voltage<br>|REG00H[7:4]=0000, VIN_DPM=3.88V<br>f|3.68<br>|3.88<br>|4.18<br>|V|
|||REG00H[7:4]=1000, VIN_DPM=4.52V<br>|4.32<br>|4.52<br>|4.82<br>|V|
|||REG00H[7:4]=1111, VIN_DPM=5.08V<br>|4.88<br>|5.08<br>|5.35<br>|V|
|RON_Q1|IN to SYS switches on<br>resistance<br>|VIN_DPM=3.88V, VIN=4.5V,<br>ISYS=100mA<br>||300<br>|350<br>|mΩ|
|RON_Q2|BAT to SYS switch on<br>resistance<br>|VIN<2V, VBAT=3.5V, ISYS=100mA<br>||103<br>|115<br>|mΩ|
|IIN_Q|Input quiescent current<br>(not include the current<br>from external NTC<br>resistor)<br>|VIN=5V, EN_HIZ=0, CEB=0,<br>**(charge enable)**,ICHG=0,ISYS=0<br>||1.7<br>|3.2<br>|mA|
|||VIN=5V, EN_HIZ=0, CEB=1,<br>**(charge disabled)**,ICHG=0,ISYS=0<br>||1.5<br>|3.0<br>|mA|
|IBAT_Q|Battery quiescent current<br>(not include the current<br>from external NTC<br>resistor)<br>awin|VIN=5V, CEB=0, charge done,<br>ICHG=0,ISYS=0<br>||58<br>|80<br>|μA|
|||VIN=0, CEB=1, VBAT=4.35V,<br>DIS_PCB_OTP=1,ISYS=0<br>||21<br>|32<br>|μA|
|||VIN=0, CEB=1, VBAT=4.35V,<br>DIS_PCB_OTP=0,ISYS=0<br>||27<br>|38<br>|μA|
|||VIN=0, CEB=1, VBAT=4.35V,<br>DIS_PCB_OTP=0, ISYS=0, enable<br>watchdog<br>||28<br>|38<br>|μA|
|||VBAT=4.5V, VIN=VSYS=0,<br>FET_DIS=1,shippingmode<br>|||1<br>|μA|
|ISYS-BAT_LKG|SYS reverse to BAT<br>switch leakage|VSYS=4.60V, VIN=5V, VBAT=0,<br>CEB=1, EN_HIZ=1, charge<br>disabled|||1|μA|
|IDSCHG|BAT FET discharge<br>current limit|REG03H[7:4]=0001, IDSCHG=400mA|300|440|500|mA|
|||REG03H[7:4]=1001,IDSCHG=2000mA||2000||mA|
|VFWD|Ideal diode forward<br>voltage in supplement<br>mode|50mA discharge current||30||mV|



www.awinic.com 8             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Electrical Characteristics** _**(Continued)**_ 

VIN=5V, VBAT=3.5V, TJ=25°C for typical values (unless otherwise noted) 

|**PARAMETER**|**PARAMETER**|**TEST CONDITIONS**|**MIN**|**TYP**|**MAX**|**UNIT**|
|---|---|---|---|---|---|---|
|**CHARGE CURRENT**|||||||
|ICHG|Output charge regulation current<br>programmable range<br>|VBAT_PRE<VBAT<VBAT_REG，<br>REG0BH[7]=1, ICHG=2mA<br>|1.5<br>|2<br>|2.5<br>|mA|
|||VBAT_PRE<VBAT<VBAT_REG，<br>REG0BH[7]=0, ICHG=8mA<br>|6.9<br>|8<br>|9<br>|mA|
|||VBAT_PRE<VBAT<VBAT_REG，<br>REG0BH[7]=0, ICHG=96mA<br>|89<br>|96<br>|103<br>|mA|
|||VBAT_PRE<VBAT<VBAT_REG，<br>REG0BH[7]=0, ICHG=264mA<br>|252<br>|264<br>|276<br>|mA|
|||VBAT_PRE<VBAT<VBAT_REG，<br>REG0BH[7]=0, ICHG=456mA<br>|434<br>|456<br>|478<br>|mA|
||Charge Current Regulation<br>Accuracy<br>|VBAT=3.8V, ICHG=2mA<br>|-25<br>||25<br>|%|
|||VBAT=3.8V, 4mA<ICHG≤12mA<br>|-20<br>||20<br>|%|
|||VBAT=3.8V,12mA<ICHG<264mA<br>fi|-7<br>||7<br>|%|
|||VBAT=3.8V, ICHG≥264mA<br>|-5<br>||5<br>|%|
|IPRE|Pre-charge current<br>programmable range,IPRE=ITERM<br>|VBAT<3.0V<br>|1<br>||31<br>|mA|
|ITERM|Termination charge current<br>threshold, programmable<br>c|REG03H[3:0]=0000,<br>ITERM=1mA<br>|0.8<br>|1<br>|1.2<br>|mA|
|||REG03H[3:0]=0001,<br>ITERM=3mA<br>|2.6<br>|3<br>|3.3<br>|mA|
|||REG03H[3:0]=0101,<br>ITERM=11mA<br>|9.5<br>|11<br>|13<br>|mA|
|||REG03H[3:0]=1111,<br>ITERM=31mA<br>|28<br>|31<br>|34<br>|mA|
|TTERM|Termination deglitch time<br>i|ICHG<ITERM, REG0CH[6]=0<br>||3.2<br>||s|
|IDBAT|Battery detection current before<br>charge done(sink current)<br>i|Begins after termination<br>detected and VBAT< VBAT_REG<br>||0.5<br>||mA|
|TDBAT|Battery detection time<br>|||262<br>||ms|
|**INT**|||||||
|VOL_INT|Low-level output saturation<br>voltage,INTpin<br>|IO=5mA, sink current<br>|||0.4<br>|V|
|ILKG_INT|High-level leakage current for<br>INT<br>|INT is in High-impedance<br>status,VINT=5V<br>|||1<br>|μA|
|TRST_DGL|INT pulled low time to reset VSYS|VINTlow(default setting)||16||s|
|**I2C BUS LOGIC LEVELS AND TIMING CHARACTERISITICS**|||||||
|VOL|Output low threshold level|IO=5mA, sink current|||0.4|V|
|VIL|Input low threshold level|Vpull_up=1.8V, SDA and SCL|||0.4|V|
|VIH|Input high threshold level|Vpull_up=1.8V, SDA and SCL|1.3|||V|



www.awinic.com 9             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

|**PARAMETER**|**PARAMETER**|**TEST CONDITIONS**|**MIN**|**TYP**|**MAX**|**UNIT**|
|---|---|---|---|---|---|---|
|IBIAS|Input bias current|Vpull_up=1.8V, SDA and SCL|||1|μA|
|**THERMAL PROTECTION**|||||||
|TJ_REG|Junction temperature regulation|Junction temperature rising||120||°C|
|TOTP|Overheating shutdown<br>protection temperature<br>|Junction temperature rising<br>||150<br>||°C|
||Thermal hysteresis for TOTP<br>|Junction temperature falling<br>||20<br>||°C|
|INTC|NTC pin output current<br>|CEB=0, NTC=3V<br>|-1<br>|0<br>|1<br>|μA|
|VCOLD|NTC cold temp rising threshold<br>|Percentage of VDD<br>|62<br>|64<br>|66<br>|%|
||Hysteresis voltage<br>|||60<br>||mV|
|VHOT|NTC hot temp falling threshold<br>|Percentage of VDD<br>|31<br>|33<br>|35<br>|%|
||Hysteresis voltage<br>|||70<br>||mV|
|VHOT_PCB|NTC hot temp falling threshold<br>for PCB OTP<br>|Percentage of VDD<br>i|31<br>|33<br>|35<br>|%|
||Hysteresis voltage<br>|f||70<br>||mV|
|**SHIPPING MODE EXIT TIME**<br>|||||||
|TEXIT_SHIPMODE|VBUS Plug in<br>|REG0BH[0]=0<br>|1.8<br>|2<br>|3.3<br>|s|
|||REG0BH[0]=1<br>|90<br>|100<br>|111<br>|ms|
||Put down INT PIN<br>|REG22H[3]=0<br>|1.8<br>|2<br>|3.3<br>|s|
|||REG22H[3]=1<br>|90<br>|100<br>|111<br>|ms|
|**CLOCK FREQUENCY AND WATCHDOG TIMER**<br>i|||||||
|FCLK|Clock frequency<br>|||250<br>||KHz|
|tWDT|Watchdog timer<br>i|REG05H[6:5]=11<br>||160<br>||s|
||aw||||||



www.awinic.com 10             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Electrical Characteristics** _**(Continued)**_ 

VIN=5V, VBAT=3.5V, TJ=25°C for typical values (unless otherwise noted) 

## **I[2] C INTERFACE TIMING** 

|**SYMBOL**|**DESCRIPTION**<br>|**DESCRIPTION**<br>|**DESCRIPTION**<br>|**DESCRIPTION**<br>|**DESCRIPTION**<br>|**DESCRIPTION**<br>|**DESCRIPTION**<br>|**DESCRIPTION**<br>|**DESCRIPTION**<br>|**DESCRIPTION**<br>|**DESCRIPTION**<br>|**DESCRIPTION**<br>|**DESCRIPTION**<br>|**DESCRIPTION**<br>|||||||||**MIN**<br>|**TYP**<br>|**TYP**<br>|**TYP**<br>|**TYP**<br>|**MAX**<br>|**UNIT**|
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|FSCL|Interface Clock Frequency<br>|||||||||||||||||||||||l||||400<br>|kHz|
|TDEGLITCH|Deglitch Time<br>||||||||||||||SCL<br>|||||||||83<br>|||||ns|
||||||||||||||||SDA<br>||||||||t|115<br>|||||ns|
|tHD:STA|(Repeat-Start) Start Condition Hold Time<br>||||||||||||||||||||||0.6<br>||||||μs|
|tLOW|Low Level Width of SCL<br>||||||||||||||||||||||1.3<br>||||||μs|
|tHIGH|High Level Width of SCL<br>||||||||||||||id||||||||0.6<br>||||||μs|
|tSU:STA|(Repeat-Start) Start Condition Setup Time<br>f||||||||||||||||||||||0.6<br>||||||μs|
|tHD:DAT|Data Hold Time<br>n||||||||||||||||||||||0<br>||||||μs|
|tSU:DAT|Data Setup Time<br>o||||||||||||||||||||||0.1<br>||||||μs|
|tR|Rising Time of SDA and SCL<br>|||||||||||||||||||||||||||0.3<br>|μs|
|tF|Falling Time of SDA and SCL<br>c|||||||||||||||||||||||||||0.3<br>|μs|
|tSU:STO|Stop Condition Setup Time<br>i||||||||||||||||||||||0.6<br>||||||μs|
|tBUF|Time Between Start and Stop Condition<br>in||||||||||||||||||||||1.3<br>||||||μs|
||SDA<br>SCL<br>|w||||||||||||||||||||||||||VIL<br>VIH<br>VIL<br>VIH<br>||
|||||||||||||||||||||||||||||||
|||||||||||||||||||||||||||||||
|||||||||||||||||||||||||||||||
||||||tBUF<br>|||||||||tHIGH<br>||||||||||||||||
||||||||||tLOW<br>tR<br>||||||||tF<br>|||||||||||||
|||||||||||||||||||||||||||||||
|||||||||||||||||||||||||||||||
|||||||||||||||||||||||||||||||
|||||||||||||||||||||||||||||||
|||||||||||||||||||||||||||||||
||||Stop|||tHD<br>Start|||:STA<br>tHD:DAT<br>tSU:DAT||||||||||tSU||Start<br>:STA||tSU:||STO<br>Stop|||||



**Figure 3  I[2] C Interface Timing** 

www.awinic.com 11             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Typical Characteristics** 

VIN=5V, TJ=25°C, IIN_LIM=500mA, ICHG=128mA, VIN_DPM=4.6V, unless other noted. 

**==> picture [484 x 622] intentionally omitted <==**

**----- Start of picture text -----**<br>
500 132.0<br>450 Temp=-40℃ ICHG=128mA<br>131.0<br>400 Temp=25℃<br>350 Temp=85℃ 130.0<br>300 129.0<br>250<br>128.0<br>200<br>150 127.0<br>100 126.0<br>50<br>125.0<br>0<br>(50) 124.0<br>0.0 0.5 1.0 1.5 2.0 2.5 3.0 3.5 4.0 4.5 5.0 -40 -20 0 20 40 60 80 100<br>VBAT(V) Temperature(℃)<br>Figure 4  ICHG vs. VBAT, VIN=5.0V Figure 5  ICHG vs. Temp, ILOAD=0<br>4.250 4.650<br>4.240 VBAT_REG=4.2V 4.640 VSYS_REG=4.6V<br>4.230 4.630<br>4.220 4.620<br>4.210 4.610<br>4.200 4.600<br>4.190 4.590<br>4.180 4.580<br>4.170 4.570<br>4.160 4.560<br>4.150 4.550<br>-40 -20 0 20 40 60 80 100 120 -40 -20 0 20 40 60 80 100 120<br>Temperature(℃) Temperature(℃)<br>Figure 6  VBAT_REG vs. Temp, IBAT=0 Figure 7  VSYS_REG vs. Temp, ISYS=0<br>4.560 470<br>VIN_DPM=4.52V 468 IIN_LIM=470mA<br>4.550<br>465<br>4.540<br>463<br>4.530 460<br>458<br>4.520<br>455<br>4.510<br>453<br>4.500 450<br>-40 -20 0 20 40 60 80 100 120 -40 -20 0 20 40 60 80 100 120<br>Temperature(℃) Temperature(℃)<br>Figure 8  VIN_DPM vs. Temp, ISYS=0 Figure 9  IIN_LIM vs. Temp,<br>awinic Confidential<br>mA) mA)<br>ICHG ( ICHG (<br>V) V)<br>BAT_REG ( SYS_REG (<br>V V<br>V) V)<br>VIN_DPM ( IIN_LIM (<br>**----- End of picture text -----**<br>


www.awinic.com 12             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Typical Characteristics** 

VIN=5V, TJ=25°C, IIN_LIM=500mA, ICHG=128mA, VIN_DPM=4.6V, unless other noted. 

**==> picture [480 x 616] intentionally omitted <==**

**----- Start of picture text -----**<br>
VIN VIN<br>VSYS  VSYS<br>VBAT<br>VBAT<br>IBAT<br>IBAT<br>ISYS=0A                                          ISYS=0A<br>Battery Charge Curve          Auto-Recharge Curve<br>VBAT VIN<br>VSYS  VSYS<br>IIN VBAT<br>ISYS  ISYS<br>VBAT=3.7V                                        VIN=5V/200mA, VBAT=3.7V<br>Input Current Limit-Based PPM  Input Voltage Regulation-Based PPM<br>VIN<br>VIN<br>VSYS  VSYS<br>IBAT VBAT<br>IBAT<br>ISYS<br>awinic Confidential<br>**----- End of picture text -----**<br>


VIN=5V, VBAT=3.7V, ICHG=456mA, ISYS=0A~1A           VBAT=3.7V, ISYS=0A **SYS Load Transient Power On/Off** 

www.awinic.com 13             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Typical Characteristics** _**(Continued)**_ 

VIN=5V, TJ=25°C, IIN_LIM=500mA, ICHG=128mA, VIN_DPM=4.6V, unless other noted. 

**==> picture [23 x 101] intentionally omitted <==**

**----- Start of picture text -----**<br>
VSYS<br>VBAT<br>VNTC<br>IBAT<br>**----- End of picture text -----**<br>


**==> picture [22 x 95] intentionally omitted <==**

**----- Start of picture text -----**<br>
VIN<br>VSYS<br>VBAT<br>IBAT<br>**----- End of picture text -----**<br>


**==> picture [409 x 549] intentionally omitted <==**

**----- Start of picture text -----**<br>
VBAT<br>VSYS<br>VNTC<br>VBAT<br>IBAT<br>IBAT<br>VBAT=3.7V, ISYS=0A                                 VBAT=3.7V, ISYS=0A, PCB_OTP disabled BAT=3.7V, ISYS=0A                                 VBAT=3.7V, ISYS=0A, PCB_OTP disabled =3.7V, ISYS=0A                                 VBAT=3.7V, ISYS=0A, PCB_OTP disabled SYS=0A                                 VBAT=3.7V, ISYS=0A, PCB_OTP disabled =0A                                 VBAT=3.7V, ISYS=0A, PCB_OTP disabled BAT=3.7V, ISYS=0A, PCB_OTP disabled =3.7V, ISYS=0A, PCB_OTP disabled SYS=0A, PCB_OTP disabled =0A, PCB_OTP disabled<br>Charge Enable/Disable  NTC Rising<br>VBAT<br>VSYS<br>VSYS<br>VBAT<br>VNTC VNTC<br>IBAT<br>IBAT<br>VBAT=3.7V, ISYS=0A, PCB_OTP disabled              VBAT=3.7V, ISYS=0A<br>NTC Falling  PCB_OTP @Charge mode<br>VIN<br>VNTC<br>VSYS<br>VBAT  VBAT<br>IBAT<br>VSYS<br>awinic Confidential<br>**----- End of picture text -----**<br>


VBAT=3.7V, ISYS=0A                                 VBAT=3.7V, ISYS=0A, PCB_OTP disabled BAT=3.7V, ISYS=0A                                 VBAT=3.7V, ISYS=0A, PCB_OTP disabled =3.7V, ISYS=0A                                 VBAT=3.7V, ISYS=0A, PCB_OTP disabled SYS=0A                                 VBAT=3.7V, ISYS=0A, PCB_OTP disabled =0A                                 VBAT=3.7V, ISYS=0A, PCB_OTP disabled BAT=3.7V, ISYS=0A, PCB_OTP disabled =3.7V, ISYS=0A, PCB_OTP disabled SYS=0A, PCB_OTP disabled =0A, PCB_OTP disabled **Charge Enable/Disable NTC Rising** 

VIN=0V, VBAT=3.7V                                 VBAT=3.7V, ISYS=0A **PCB_OTP @Discharge mode VIN OVP Operation IN OVP Operation  OVP Operation** 

**VIN OVP Operation IN OVP Operation  OVP Operation** 

www.awinic.com 14             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Functional Diagram** 

**==> picture [361 x 519] intentionally omitted <==**

**----- Start of picture text -----**<br>
Q1A Q1B<br>IN MID SYS SYS Q2A Q2B<br>>VBAT ON OFF<br><VBAT OFF ON<br>VSYS MODULATOR<br>Q2<br>MID Q2A<br>VDD VDD CHARGE<br>GEN BAT CONTROL Q2B<br>BAT<br>COMPARATOR<br>TOP DAC NTC  NTC<br>& DETECTOR<br>VREF<br>I2C<br>SCL<br>INTERFACE<br>CLOCK<br>SDA &<br>GEN<br>LOGIC<br>INT CONTROL GND<br>AW32001E<br>Figure 10  Functional Block Diagram<br>awinic Confidential<br>**----- End of picture text -----**<br>


www.awinic.com 15             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Detailed Functional Description** 

The AW32001E is a highly integrated linear battery charger with a complete power path management function (PPMF). The full-charge process of AW32001E not only includes pre-charge, constant-current fast charge (CC) and constant voltage (CV) regulation, but also charge termination, auto-recharge, etc. The PPMF can manage the input source to power the system load and charge the battery simultaneously. The system load has a higher priority than the charge current. When the input power is limited by input current or voltage, the charge current will decrease automatically. 

**==> picture [486 x 545] intentionally omitted <==**

**----- Start of picture text -----**<br>
current will decrease automatically.<br>Main Machine<br>AW32001E includes: START, Battery Discharge Mode(DISCHG), Battery Charge Mode(CHG), Only Power<br>System Mode(OPSM) and Shipping Mode(SHIP), Figure 11 is shown the main state machine conversion.<br>(1) Battery Discharge Mode: Only Battery to SYS Path is enabled.<br>(2) Battery Charge Mode: IN to SYS path and SYS to Battery path are enabled.<br>(3) Only Power System Mode: Only IN to SYS Path is enabled.<br>(4) Shipping Mode: All paths are disabled, AW32001E enters into low power consumption state.<br>POR<br>(INT=Low keeps 2s)<br>||(VIN plug in)||(FET_DIS=0)<br>START<br>Efuse_ok&&(HIZEN||<br>SHIP<br>(!HIZEN)&&efuse_ok VIN_UVLO)<br>&&(!VIN_UVLO)<br>VIN_UVLO||HIZEN<br>FET_DIS=1<br>OPSM DISCHG<br>CEB=1 VIN_UVLO||HIZEN<br>CEB=0<br>(!VIN_UVLO)<br>CHG &&(!HIZEN)<br>Figure 11  The main state machine conversion<br>The AW32001E integrates an input reverse-block FET (Q1A), a LDO FET (Q1B) between IN and SYS, and a<br>BATFET (Q2) between SYS and BAT. When VBUS plugs in and CEB=1, the device works in OPSM mode<br>that only IN and SYS path is enabled, the system is powered by VBUS. If CEB=0, the charge function is<br>enabled and Q2 turn on, the status switches to Battery Charge mode(CHG). When the system load demand<br>is over the input power capacity, the PPMF of AW32001E will reduce the charging current or use power from<br>the battery to satisfy the system load. The charge current is limited to maintain the system power supply with<br>higher priority all the time. Figure 12 shows the PPMF structure of the AW32001E, which is called Battery<br>Supplement Mode too. Once the VBUS is unplugged, the BATFET Q2 is turn on fully to supply the system,<br>and the charger enters into Battery Discharge Mode(DISCHG). Further, the device can turn off BATFET so<br>that the system voltage is zero to minimize the battery leakage current. When the host set FET_DIS=1, the<br>charger can turn off BATFET Q2 and entries Shipping Mode(SHIP).<br>awinic Confidential<br>**----- End of picture text -----**<br>


www.awinic.com 16             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

**==> picture [370 x 229] intentionally omitted <==**

**----- Start of picture text -----**<br>
USB port  System load<br>or adapter Q1A Q1B modules<br>Q2<br>CONTROL<br>LOGIC<br>Battery<br>**----- End of picture text -----**<br>


**==> picture [486 x 539] intentionally omitted <==**

**----- Start of picture text -----**<br>
Q2<br>CONTROL<br>LOGIC<br>Battery<br>Figure 12  Power Path management Structure<br>In Battery Charge Mode, the Q2 works as a fully featured linear charger with pre-charge, fast charge, constant<br>voltage charge, charge termination, auto-recharge, thermal protection, built-in timer control and NTC<br>monitoring. The charge current can be programmed via the I [2] C interface. When the chip’s temperature exceeds<br>the thermal regulation threshold (120°C default), the IC controls the charge current to reduce its temperature.<br>Power Supply<br>The AW32001E chooses the higher voltage of either BAT or IN to power VDD and the internal bias circuit,<br>showed as Figure 13. When BAT or IN voltage rises above its respective power on reset (POR) threshold, the<br>internal control circuit will wake up and the I [2] C interface will be ready for communication with all of registers<br>reset to default value. These registers can be controlled by the host.<br>IN BAT<br>VCLAMP 250ohm<br>VDD<br>awinic Confidential<br>**----- End of picture text -----**<br>


**Figure 13  The inner power supply sources selection circuit for VDD** 

www.awinic.com 17             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## _**VIN OVP, VIN UVLO and VIN GOOD**_ 

The AW32001E has an input UVLO and over-voltage protection (OVP) threshold. The Q1 is turned off immediately when the input voltage is out of its operating range. 

The input over-voltage protection is integrated to prevent the device and other components from damage of the high input voltage (Voltage from VIN to GND). If the voltage at VIN pin exceeds VIN_OVP threshold(6V typical) ， the chip will turn off Q1. When VIN drops lower than the input overvoltage exit threshold (5.65V typical) and continues to exceed TDGL_OVP(30ms typical), Q1 will be turned on again. DGL_OVP(30ms typical), Q1 will be turned on again. (30ms typical), Q1 will be turned on again. 

**==> picture [486 x 518] intentionally omitted <==**

**----- Start of picture text -----**<br>
continues to exceed TDGL_OVP(30ms typical), Q1 will be turned on again. DGL_OVP(30ms typical), Q1 will be turned on again. (30ms typical), Q1 will be turned on again.<br>When VIN falls below VUVLO, the Q1 is also turned off and the input to system loop controller is shut down. Once<br>VIN rises above VUVLO+300mV and continues to exceed TDGL_UVLO(30ms typical), the Q1 is turned on and<br>relative circuits start working.<br>OVP<br>protection<br>triggerd<br>6V<br>5.65V<br>3.9V<br>VBAT 130mV<br>TDGL_UVLO TDGL_OVP<br>VIN 30ms 30ms<br>VSYS<br>Figure 14  Input Power Detection Operation<br>Either VIN OVP or VIN UVLO had happened, the device send out a 256μs low-state interrupt pulse from INT<br>port, indicated a power fail status as REG08H[1]=0 and a fault status as REG09H[5]=1, which are read clear.<br>The VIN GOOD status not only means that VIN is between VIN_UVLO and VIN_OVP, but also .includes that the VIN<br>voltage increase is higher than VBAT+170mV(130mV typical), and higher than VSYS+75mV(50mV typical).<br>The all conditions have satisfied, and enter VIN GOOD. VIN voltage reduction meets VIN<VBAT+60mV or<br>VIN<VSYS, exiting VIN GOOD.<br>Only Power System Mode<br>The device meets VIN GOOD, EN_HIZ=0(REG01H[4]=0) and CEB=1(REG01H[3]=1), and firstly enter Only<br>Power System Mode(OPSM) which just turns on Q1A and Q1B, and supplies power the down-stream system<br>by VBUS. If the device is configured CEB=0(REG01H[3]=0), the main state machine switches to Charge Mode<br>from the Only Power System Mode.<br>awinic Confidential<br>**----- End of picture text -----**<br>


## **Charge Mode** 

When AW32001E operation in Charge Mode, the DPM, PPMF, Battery Supplement and other functions are available. These functions are useful in some application. 

www.awinic.com 18             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## _**Battery Regulation Voltage**_ 

The battery voltage of constant voltage regulation state is VBAT_REG. When VBAT_REG = 4.2V, the accuracy is ±0.5% in the range of 0°C to +50°C ambient temperature. 

## _**Input Current-and Input Voltage-Based Power Regulation**_ 

The AW32001E has an input current limit regulation to meet the input source’s (typically USB) maximum current limit specification. The function is realized by monitoring the input current continuously. If the rating of input source is lower than the preset input current limit, the input current limitation works to protect the input source from being overloaded. The total input current limit value can be set by the register IIN_LIM (REG00H[3:0]), and the function can prevent the input source from being over-loaded. Otherwise, when the load is over the input power capacity, the input voltage also can be regulated to VIN_DPMIN_DPM for the input voltage-based DPM regulation. VIN_DPM can be set via the register VIN_DPM (REG00H[7:4]), and IN_DPM can be set via the register VIN_DPM (REG00H[7:4]), and  can be set via the register VIN_DPM (REG00H[7:4]), and the VIN_DPM should be at least 250mV higher than VBAT_REG to ensure the stable operation of the regulator. The IN_DPM should be at least 250mV higher than VBAT_REG to ensure the stable operation of the regulator. The  should be at least 250mV higher than VBAT_REG to ensure the stable operation of the regulator. The BAT_REG to ensure the stable operation of the regulator. The  to ensure the stable operation of the regulator. The register DIS_VINLOOP=1 (REG07H[6]=1) can be set to disable the input voltage limit function. Either the input voltage or input current limit is reached, the total input power is limited by regulating the Q1B FET between IN and SYS. As a result, the system voltage drops. When the system voltage decrease to a **minimum value** of VSYS_REG - 135mV and VIN - 345mV, the charge current is reduced to prevent the system voltage from dropping further. _**Power Path Management Function (PPMF)**_ The AW32001E can decouple the system from the battery by employs a PPMF with the Q2, which allows the device to control Q2 between the system and the battery separately. The system has high priority to start up by regulating the integrated Q1B even the battery is in a deeply discharged or missing state. The function of Q1A, Q1B and Q2 can be controlled by the I[2] C as shown in table 1. Table 1: FET Control via I[2] C **FET On/Off HI-Z Mode and Charge Control Changed by Control Set EN_HIZ = 1 Set CEB = 1** Q1A and Q1B OFF x Q2(Charge Mode) x OFF Q2(Battery Discharge Mode) x x **NOTE: x=Don’t care.** For the system voltage control, when the input voltage is lower than VSYS_REG, the Q1A and Q1B are fully on with the input current limit. When the input voltage is higher than VSYS_REG, the system voltage is regulated to VSYS_REG. The VSYS_REG can be programmed through REG07H[3:0]. _**Battery Supplement Mode**_ When DPM occurs, the charge current is reduced to keep the input current or input voltage in regulation. If the charge current has already reduced to zero and the input source is still overloaded, the system voltage begins decreasing. If the system voltage drops to 30mV below the battery voltage, the AW32001E will enters battery supplement mode, and the ideal diode is enabled. If IDSCHG (supplement current) * RON_BATT is lower than 30mV, the Q2 is regulated to keep VBAT - VSYS at 30mV. If this regulation cannot maintain 30mV voltage drop due to heavy load from SYS, the Q2 will fully turn on to maintain the ideal forward voltage. When the system load decreases, the system voltage starts to increase. The ideal diode mode is disabled, when VSYS is higher than VBAT + 20mV. Figure 15 shows the DPM and battery supplement mode operation profile. 

Otherwise, when the load is over the input power capacity, the input voltage also can be regulated to VIN_DPMIN_DPM for the input voltage-based DPM regulation. VIN_DPM can be set via the register VIN_DPM (REG00H[7:4]), and IN_DPM can be set via the register VIN_DPM (REG00H[7:4]), and  can be set via the register VIN_DPM (REG00H[7:4]), and the VIN_DPM should be at least 250mV higher than VBAT_REG to ensure the stable operation of the regulator. The IN_DPM should be at least 250mV higher than VBAT_REG to ensure the stable operation of the regulator. The  should be at least 250mV higher than VBAT_REG to ensure the stable operation of the regulator. The BAT_REG to ensure the stable operation of the regulator. The  to ensure the stable operation of the regulator. The register DIS_VINLOOP=1 (REG07H[6]=1) can be set to disable the input voltage limit function. 

www.awinic.com 19             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

When VIN is not available, the AW32001E operates in discharge mode. During in discharge mode, the Q2 is fully on to reduce power loss. 

**==> picture [486 x 619] intentionally omitted <==**

**----- Start of picture text -----**<br>
VSYS IBAT VBAT VIN<br>IIN<br>Min{VIN-0.345,VSYS_REG-0.135}<br>VBUS VIN DPM loop works<br>VIN_DPM<br>IIN_LIM<br>VSYS_REG  345mV<br> 135mV IBUS_MAX<br>VBAT<br>PPMF happened<br>ICHG =20mV<br>Battery  =30mV<br>Supplement Mode<br>0 IBUS_MAX-ICHG IBUS_MAX IIN_LIM ISYS<br>Figure 15  DPM and Battery Supplement Operation Profile (Bad adaptor inserted)<br>NOTE:  IBUS_MAX is the maximum output current of the input source.<br>Battery Charge Profile<br>The AW32001E has three main charging processes: pre-charge, fast constant current charge(CC), and fast<br>constant voltage charge(CV):<br>VBAT ICHG<br>VBAT_REG<br>VBAT_REG-VRECH<br>ICC<br>ICHG VBAT<br>VBAT_PRE<br>ITERM<br>IPRE<br>Pre  Fast  Fast  Charge  Auto<br>Charge Charge(CC) Charge(CV) Termination recharge<br>awinic Confidential<br>**----- End of picture text -----**<br>


**Figure 16  Battery Charge Profile** 

www.awinic.com 20             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

- ⚫ Pre-charge: In the pre-charge process, the IC charges the deeply depleted battery safely with small current until the battery voltage rise to the pre-charge threshold (VBAT_PRE), and then the chip enters the fast-charge process. If the VBAT is not increasing to exceed than VBAT_PRE before the pre-charge timer expires (1 hour), the charge cycle stops, and a corresponding timeout fault signal is asserted. The register REG03H[3:0] can be set the current of pre-charge. 

|REG03H[3:0] can be set the current of pre-charge.||
|---|---|
|⚫<br>Fast constant current charge: When VBATexceeds VBAT_PRE, the AW32001E enters the|fast constant|
|charge process. The REG02H[5:0] can be set to change the fast-charge current .<br>⚫<br>Fast constant voltage charge: The charge mode changes from CC mode to CV mode when the VBATrises<br>to the battery-full voltage (VBAT_REG) set via REG04H[7:2]. At the same time, the charge current starts<br>decreasing in CV charge process.<br>Due to multiple loop regulations, such as dynamic power management (DPM) regulation (input voltage, input<br>current) or thermal regulation, the actual charge current may be less than the setting value.<br>When the charge current is smaller than termination current threshold ITERMfor 3.2s in CV process, the charge<br>cycle will be completed, and the charge status is updated to charge done. The register REG03[3:0] can set<br>the termination charge current threshold ITERM. The termination function can be disabled via EN_TERM=0<br>(REG05H[4]=0). Meanwhile, the register bit TERM_TMR (REG05H[0]) is able to control whether the charge<br>process continue or not when the termination conditions are met. The termination function is shown as table<br>2.<br>Table 2: Termination Function Selection Table<br>**EN_TERM**<br>**TERM_TMR**<br>**After Termination Condition is Met**<br>**Operation**<br>**Charge Status**<br>0<br>x<br>Keep CV Charge<br>Charge<br>1<br>0<br>Charge done<br>Charge done<br>1<br>1<br>Keep CV Charge<br>Charge<br>**Note: x=Don’t care.**<br>A new charge cycle starts when any of the following conditions are valid:<br>⚫<br>Auto-recharge kicks in.<br>⚫<br>Battery charging is enabled via the I2C.<br>⚫<br>The input power is recycled .<br>Under the following conditions:<br>⚫<br>No safety timer fault.<br>⚫<br>No thermistor fault at NTC.<br>awinic Confidential||
|⚫<br>BFET is not forced off.||
|⚫<br>No battery over-voltage event.||



## _**Automatic Recharge**_ 

After the charge process is completed and charge cycle is terminated, the system’s consumption or battery self-discharge may cause the battery voltage to decrease. When the battery voltage falls below the recharge threshold and VIN is still in the operating range, another new charging cycle will start automatically. The recharge threshold(below VBAT_REG) VRECH can be configured to 100mV or 200mV(default) via REG04H[0] 

www.awinic.com 21             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Battery Discharge Mode** 

In Battery discharge mode, The device has low quiescent current and low on-resistance of Q2 to help the battery working for a longer time. Once the discharge current exceeds the over discharge current threshold, the over discharge current protection works and ensures the IC work safely in different applications. 

## _**Battery Discharge Function**_ 

When the input source is absent and battery is connected to chip with the VBAT above VBAT_UVLO threshold, the Q2 is fully on. During discharge mode, the 90mΩ Q2 can minimizes conduction loss. _**Battery Disconnection Function**_ In some applications where the battery is not removable, it is essential to allow the system power to be reset in some applications or disconnect the battery from the system for shipping mode. The AW32001E provides both system reset function and shipping mode for different applications. The INT pin can be used to cut off the path from the battery to the system under certain condition to reset the system manually. The battery is disconnected from the system, when the logic of INT is set low for longer than tRST_DGL (which can be programmed by REG01H[7:6]). After a delay time of tRST_DUR (REG01H[5]), the Q2 is RST_DGL (which can be programmed by REG01H[7:6]). After a delay time of tRST_DUR (REG01H[5]), the Q2 is  (which can be programmed by REG01H[7:6]). After a delay time of tRST_DUR (REG01H[5]), the Q2 is RST_DUR (REG01H[5]), the Q2 is (REG01H[5]), the Q2 is turned on automatically, and the system is powered by the battery again. The tRST_DUR can be programmed by RST_DUR can be programmed by  can be programmed by REG01H[5]. During the off period, the INT pin is not limited to be high or low. Please notes that the tRST_DGLRST_DGL counter is triggered by the falling edge of INT. **INT tRST_DGL tRST_DUR VBAT VSYS Figure 17  System Reset Function Operation Timing Diagram Shipping Mode** The register bit FET_DIS (REG06H[5]) can be used to control the battery disconnection too. If the input source is absent, once setting FET_DIS=1, the AW32001E enters shipping mode after a delay time(default 1s). The delay time can be programmed by EN_SHIPPING_DGL(REG09H[7:6]). If the input source is present when FET_DIS is written to 1, chip will turn to shipping mode after 1s deglitch time with input voltage smaller than VIN_UVLO threshold. Plug in the input adapter or pull the INT pin down for 2s or 100ms to wake the AW32001E up from shipping mode. The waking time can be configured in EN_SHIPMD_0P1S (REG0BH[0]) and INT100MS (REG22H[3]). 

The INT pin can be used to cut off the path from the battery to the system under certain condition to reset the system manually. The battery is disconnected from the system, when the logic of INT is set low for longer than tRST_DGL (which can be programmed by REG01H[7:6]). After a delay time of tRST_DUR (REG01H[5]), the Q2 is RST_DGL (which can be programmed by REG01H[7:6]). After a delay time of tRST_DUR (REG01H[5]), the Q2 is  (which can be programmed by REG01H[7:6]). After a delay time of tRST_DUR (REG01H[5]), the Q2 is RST_DUR (REG01H[5]), the Q2 is (REG01H[5]), the Q2 is turned on automatically, and the system is powered by the battery again. The tRST_DUR can be programmed by RST_DUR can be programmed by  can be programmed by REG01H[5]. During the off period, the INT pin is not limited to be high or low. Please notes that the tRST_DGLRST_DGL 

If INT PIN is shorted to ground or left floating before entering Shipping Mode, DIS_SHIPINT (REG0CH[2]) must be written to 1 to avoid bad Shipping Mode operation. In this case, the only method of exiting shipping mode is plugging in the input adapter. 

Table 3: Shipping Mode Control 

www.awinic.com 22             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

**==> picture [452 x 635] intentionally omitted <==**

**----- Start of picture text -----**<br>
FET On/Off  Enter Shipping Mode  Exit Shipping Mode<br>Changed by Control  Set FET_DIS to 1  INT H to L for 2s  Vin Plug-In<br>Q1  x  x  On<br>Q2  Off(1s later)  On  On(2s later)<br>Note: x=Don’t care.<br>VBUS absent<br>Other mode<br>Set FET_DIS=0 Set FET_DIS=1<br>No  EN_SHIPPING_DGL<br>timer expiration?<br>Yes<br>Shipping mode<br>Figure 18  Enter Shipping Mode Timing Diagram(VBUS absent)<br>VBUS present<br>Other mode<br>No<br>Yes<br>Set FET_DIS=0 Set FET_DIS=1 2s timer expiration? Shipping mode<br>No<br>EN_SHIPPING_DGL  2s timer work<br>timer expiration?<br>Yes<br>Yes<br>VBUS shutdown VBUS<VUVLO？<br>No<br>awinic Confidential<br>**----- End of picture text -----**<br>


**Note: x=Don’t care.** 

**Figure 19  Enter Shipping Mode Timing Diagram(VBUS present)** 

www.awinic.com 23             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

**==> picture [120 x 228] intentionally omitted <==**

**----- Start of picture text -----**<br>
Shipping Mode<br>VBUS Plug in<br>or INT Pull Low<br>No  0.1s/2s timer<br>expiration?<br>Yes<br>Exit Shipping<br>Mode<br>**----- End of picture text -----**<br>


**==> picture [448 x 546] intentionally omitted <==**

**----- Start of picture text -----**<br>
VBUS Plug in<br>or INT Pull Low<br>No  0.1s/2s timer<br>expiration?<br>Yes<br>Exit Shipping<br>Mode<br>Figure 20  Exit Shipping Mode Timing Diagram<br>VIN<br>VIN_UVLO<br>VIN UVLO detect<br>VSYS<br>Exiting timer 0.1s/2s 30ms<br>Shipping Mode Discharge  Charge Mode<br>Mode<br>Figure 21  Recovery charging From Shipping Mode Operation Timing Diagram(VBUS Plug-In)<br>awinic Confidential<br>**----- End of picture text -----**<br>


www.awinic.com 24             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Protection Operation** 

The AW32001E has input OVP, UVLO, battery OVP and other functions to protect it’s normal operation. Additionally, NTC function is integrated to prevent battery from high temperature danger. The following table 4 is all fault functions summary table. 

Table 4: All fault functions summary table 

|Status|Operation Mode<br>|Brief Function Description<br>|Interrupt<br>|Action<br>|
|---|---|---|---|---|
|VIN GOOD|Charge, OPSM<br>|VINrises above VBAT+170mV and<br>VSYS+75mV，the device enters into VIN<br>Good, VINfalls down VBAT+60mV or<br>VSYS-50mV, exits VIN GOOD. Entry and<br>exit require 2ms to confirm.<br>|Yes<br>ial|Turn on Q1A<br>and Q1B.<br>|
|VIN UVLO|Charge, OPSM<br>|VINfalls down 3.6V, the device enters<br>VIN UVLO immediately. VINrises above<br>3.9V and keeps 30ms, the device exits.<br>n|Yes<br>|Turn off Q1A<br>and Q1B.<br>|
|VIN OVP|Charge, OPSM<br>|VINrises above 6V, the device enters<br>into VIN OVP immediately, VINfalls<br>down about 5.65V, exits VIN OVP. Exit<br>requires 2ms to confirm.<br>ide|Yes<br>|Quickly turn off<br>Q1B in 100ns.<br>|
|VBAT OVP|Charge<br>|After VBATrises above VBAT_REG+130mV<br>about 128us, the device enters into<br>VBAT OVP. Once VBATfalls down<br>VBAT_REG+50mV about 2ms, exits VBAT<br>OVP.<br>nf|Yes<br>|Turn off Q2.<br>|
|VBAT UVLO|Discharge, OPSM<br>|When VBATrises above<br>VBAT_UVLO+190mV about 31ms<br>(programmable 128us), the device exits<br>into VBAT UVLO. Once VBATfalls down<br>VBAT_UVLO(programmable), enters VBAT<br>UVLOimmediately.<br>Co|No<br>|Turn off Q2.<br>|
|OTP|Charge, OPSM,<br>Discharge<br>in|When the junction temperature exceeds<br>150℃, IC shuts down. When the junction<br>temperature falls below the thermal<br>recovery<br>temperature,<br>approximately<br>120℃, the device restarts by using the<br>soft-start sequence.<br>ic|Yes<br>|Turn off Q1B<br>and Q2.<br>|
|PCB OTP|Charge, OPSM,<br>Discharge<br>aw|PCB_OTP function is default settings.<br>VNTCfalls down VDD×33%, PCB OTP is<br>valid;<br>Once<br>VNTC<br>rises<br>up<br>VDD×33%+70mV for 31ms, the device<br>exits PCB OTP.<br>|Yes<br>|Turn off Q1B<br>and Q2.<br>|
|NTC HOT|Charge<br>|NTC HOT function is configured. VNTC<br>falls down VDD×33%, the device judges<br>battery hot, and reports NTC HOT; Once<br>VNTCrises up VDD×33%+70mV for<br>31ms, the device exits NTC HOT.<br>|Yes<br>|Turn off Q2.<br>|
|NTC COOL|Charge|NTC COOL function is configured. VNTC<br>rises up VDD×64%, the device judges<br>battery cold, and reports NTC COOL;<br>Once VNTCfalls down VDD×64%-60mV<br>for 31ms, the device exits NTC COOL.|Yes|Turn off Q2.|



www.awinic.com 25             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

|VSYS SCP|Charge, OPSM,<br>Discharge<br>|When the events including<br>ISYS>IOCP_INSYS(2A),<br>ISYS>IOCP_BATSYS(3.7A),<br>IIN_LIM<ISYS<IOCP_INSYSfor 60us, and<br>IDSCHG<ISYS<IOCP_BATSYSfor 60us happen<br>during VSYSlaunch and VSYS<0.7V, or<br>during working normally and VSYS<1.5V,<br>the device triggers VSYSshort protection<br>immediately and work in Hiccup Mode.<br>Turn off Q1 and Q2, and start up again<br>after 1ms later.<br>|No<br>l|Hiccup Mode.<br>Turn off Q1 and<br>Q2, and start up<br>again after 1ms<br>later<br>|
|---|---|---|---|---|
|VBAT ODCP|Discharge,<br>Supplement Mode<br>|Over-discharge current protection. Once<br>the IBATexceeds the programmable<br>discharge current limit IDSCHG(2A<br>default) for 60μs. The AW32001E enters<br>hiccup mode. In addition, if the<br>discharge current goes high and<br>reaches the internal fixed peak current<br>limit (about 3.7A), the Q2 turns off and<br>begins hiccup mode immediately.<br>ent|No<br>ia|Q2 turns off<br>|
|Watch Dog<br>fault|Charge, OPSM,<br>Discharge<br>|When the watchdog timer expires,, both<br>the Q1 and Q2 are turned off, and most<br>registers return to the default value, sent<br>a watch dog fault interrupt to system.<br>id|Yes<br>|Turn off Q1B<br>and Q2. Reset<br>CEB to 0.<br>|
|Safety time<br>fault|Pre Charge, Fast<br>Charge<br>|Pre-charge for more than 1 hour<br>(Configurable), or faster charge for more<br>than 5 hours (Configurable), entry to<br>safety time fault.<br>nf|Yes<br>|Turn off Q1B<br>and Q2. Reset<br>CEB to 0.<br>|
|**_Battery OVP(VBAT OVP)_**<br>The AW32001E has battery over-voltage protection (VBAT OVP) function (about 130mV higher than VBAT_REG).<br>When the battery OVP event occurs, AW32001E will stop the current charging cycle immediately and asserts<br>a fault.<br>**_Negative Temperature Coefficient (NTC) Temperature Sensor_**<br>The AW32001E is able to use NTC to sense the battery temperature. By monitoring the thermistor (usually<br>available in the battery pack), the battery is guaranteed to operate in safe environment.<br>The NTC function demands appropriately valued resistors connecting from VDD to NTC to ground. At the<br>same time, connect a thermistor from the NTC pin to ground. The NTC voltage is determined by the resistor<br>divider and thermistor, and the divide ratio depends on the temperature of thermistor. The upper and lower<br>bound of NTC voltage is pre-determined in AW32001E.<br>In the AW32001E, PCB_OTP function is default settings. The I2C can change the NTC and PCB_OTP<br>functions (see Table 5).<br>Table 5: NTC Function Selection Table<br>**I2C Control**<br>**Function**<br>**EN_NTC**<br>**DIS_PCB_OTP**<br>0<br>x<br>Disable<br>1<br>1<br>NTC(resistor-divided)<br>1<br>0<br>PCB_OTP<br>awinic Co|||||



www.awinic.com 26             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **NOTE: x=Don’t care** 

When PCB_OTP is selected and the NTC voltage is lower than the NTC hot threshold, both the Q2 and Q1 are turned off. The NTC_FAULT status is set (REG09H[1]) to 1 to show the PCB_OTP fault. The IC Operation resumes, when the NTC voltage returns to safe range. 

The NTC function works only in charge mode. Once the temperature is outside of the safe operating range, the IC stops charging state and report it on the status bits. When the temperature comes back to the safe range, the charge process resumes automatically. 

## _**Thermal Regulation and Thermal Shutdown**_ 

The internal junction temperature is monitored continuously to avoid overheating the chip and maximize power delivery. When the internal junction temperature reaches the preset limit TJ_REG (120°C default), the charge current starts reducing to prevent dangerous high power dissipation. The IC can work in diffident thermal requirements applications, because it has multiple thermal regulation thresholds from 60°C to 120°C. register REG07H bit [5:4] can set The junction temperature regulation threshold. 

The device has a built-in temperature sensor which monitors the internal junction temperature. When the junction temperature exceeds 150℃, the Q1 and Q2 will turn off. When the junction temperature falls below the thermal recovery temperature, approximately 120 ℃ , the device reworks. 

℃ , the device reworks. 

www.awinic.com 27             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## _**System Short-Circuit Protection(VSYS SCP)**_ 

**==> picture [426 x 573] intentionally omitted <==**

**----- Start of picture text -----**<br>
Power up (POR)<br>Chip works in  NO Chip works in  NO<br>Charge mode or<br>OPS mode? Discharge mode?<br>YES YES<br>IIN>IOCP_INSYS? YES ISYS>IOCP_BATSYS<br>?<br>NO NO<br>NO IIN>IIN_LIM?<br>ISYS>IDSCHG? NO<br>YES<br>YES<br>60μs delay<br>time<br>YES During VSYS<br>start-up?<br>NO<br>NO NO<br>VSYS<0.7V? VSYS<1.5V?<br>YES<br>Start<br>Hiccup<br>awinic Confidential<br>**----- End of picture text -----**<br>


**Figure 22  Short Circuit Hiccup Protection Flow Chart** 

The AW32001E has short-circuit protection (SCP) function in both the IN to SYS path and the BAT to SYS path. The IC monitor the system voltage continuously. If VSYS is lower than 1.5V, The SCP is active, and IDSCHG decreases to half of the original value. For the IN to SYS path, once IIN is over the 2A protection threshold IOCP_INSYS, both the Q1 and Q2 are turned off immediately, and the AW32001E enters hiccup mode. When the 

www.awinic.com 28             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

setting input current limit IIN_LIM is reached, IIN is regulated at IIN_LIM. After a 60μs delay, the hiccup mode starts, and the hiccup mode interval is 1ms. For the BAT to SYS path, once IBAT is over the 3.7A protection threshold IOCP_BATSYS, both the Q1 and Q2 are turned off immediately, and the AW32001E enters hiccup mode. When the battery discharge current limit threshold IDSCHG is reached, hiccup mode starts after a 60μs delay, and the hiccup mode interval is 1ms. 

Particularly, when system short-circuit occurs in both the input and battery, the both paths protection mechanism works together. The faster path dominates the hiccup operation. _**Over-Discharge Current Protection**_ In discharge mode and supplement mode, the AW32001E is designed to have an over-discharge current protection. Once the IBAT exceeds the programmable discharge current limit (2A default), the Q2 turns off after a 60μs delay. At the same time, the AW32001E enters hiccup mode as part of the over-current protection (OCP). The discharge current can be programmed to maximal 3.2A through the I[2] C. in addition, if the discharge current goes high and reaches the internal fixed peak current limit (about 3.7A), the Q2 turns off and begins hiccup mode immediately. **Safety timer** Because the abnormal battery conditions, the AW32001E designed a pre-charge and fast-charge safety timer to prevent an extra-long time charging cycle. The pre-charge safety timer is 1hour, and the fast-charge safety timer can be programmed through the I[2] C. Once the battery enters fast-charge mode, The fast charge safety timer starts. The safety timer can be disabled via the I[2] C. When charger works in VIN DPM or Temp regulation state, the charge current will decrease. In order to charge as full as possible, the register bit TMR2X_EN(REG06H[6]) could be set 1, which enable the timer slows down, the left safety time is double. If VIN DPM or Temp regulation state exit, or TMR2X_EN=0, the timer recovery normal. The following actions can restart the safety timer: ⚫ Write REG05H[3] from 0 to 1 (safety timer enable). ⚫ Write REG01H[3] from 1 to 0 (charge enable). ⚫ Write REG02H[7] from 0 to 1 (software reset). ⚫ A new charge cycle is kicked in. **Interrupt to host (INT)** The AW32001E can output a 256μs low-state INT pulse via INT to notify the system of the operation. All of the below events can trigger an INT output: ⚫ Charge completed ⚫ Good input source detected ⚫ Charging status change ⚫ UVLO or input over-voltage protection ⚫ Any fault in REG09H and REG08H (input fault, watchdog timer fault, safety timer fault, thermal fault, battery OVP fault, NTC fault) 

When a fault occurs, an INT pulse is send out and latches the fault state in REG09H. After the AW32001E exits the fault state, the fault bit is reset to 0 after the host reads faults registers. The NTC fault bit constantly reports the current thermistor conditions without latches. The INT signal can be masked when the corresponding control bit is set in REG06H[4:0]. When an INT condition is masked, this means that the INT pin signal (and register bit) will not trigger when the corresponding condition occurs. Masking INT pulses is useful when writing software code to avoid unnecessary interruptions due to these events. 

www.awinic.com 29             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Host Mode and Default Mode** 

The AW32001E is a host-controlled device. After the power-on reset, the AW32001E starts up in a default mode or watchdog timer expiration state. All registers are in their default settings. 

**==> picture [486 x 574] intentionally omitted <==**

**----- Start of picture text -----**<br>
In both charge and discharge mode ,  once the watchdog timer run out, both the Q1 and Q2 are turned off, and<br>most registers return to the default value (refer to the I [2] C Register Map section). The Q1 and Q2 are turn on<br>again automatically after tRST_DUR, which can be programmed by REG01H[5]. Also the watchdog timer can be<br>turned off in discharge mode by setting REG05H[7]=0. If the watchdog timer (REG05H[6:5]) is not disabled,<br>the host must reset the watchdog timer regularly by writing 1 to REG02H[6] before the watchdog timer expires<br>to keep the device in host mode. When the watchdog timer expires, the AW32001E goes back to default mode.<br>And any writing to the AW32001E will switch it to host mode. The watchdog timer limit can also be programmed<br>or disabled by the host control.<br>In charge mode and OPSM, the watchdog timer is valid by default. In discharge mode, the watchdog timer is<br>disable by default, and can be turned on by setting REG05H[7]=1. When the REG05H[6:5] is set to 00, the<br>watchdog timer is disabled under both charge mode and discharge mode regardless of the status of<br>REG05H[7]. Operation mode can be switched to default mode when one of the following conditions are valid:<br>⚫ Register REG02H[7] is reset.<br>⚫ Refresh input without battery.<br>⚫ Re-insert battery with no VIN.<br>POR or REG02H[7]  is reset<br>Watchdog timer expired<br>Reset registers<br>I2C interface enable<br>Host Mode<br>Y<br>I2C Write? Start watchdog timer<br>Host programs registers<br>N<br>Default Mode<br>Reset watchdog timer<br>Y<br>Reset registers  Reset REG02[6]?<br>N Y<br>I2C Write?<br>Y Watchdog Timer  N<br>Expired?<br>awinic Confidential<br>**----- End of picture text -----**<br>


In charge mode and OPSM, the watchdog timer is valid by default. In discharge mode, the watchdog timer is disable by default, and can be turned on by setting REG05H[7]=1. When the REG05H[6:5] is set to 00, the watchdog timer is disabled under both charge mode and discharge mode regardless of the status of REG05H[7]. Operation mode can be switched to default mode when one of the following conditions are valid: 

**Figure 23  Watchdog Timer Flow Chart** 

www.awinic.com 30             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **General I[2] C Operation** 

The device supports the I²C serial bus and data transmission protocol. It operates as a slave on the I²C bus. The maximum clock frequency specified by the I[2] C standard is 400kHz. Connect to the bus are made via the open-drain I/O pins SCL and SDA. The pull-up resistor can be selected in the range of 1k~10kΩ and the typical value is 4.7kΩ when I[2] C frequency is 400kHz. Different high level from 1.2V to 5V of this I[2] C interface is supported. 

**==> picture [337 x 499] intentionally omitted <==**

**----- Start of picture text -----**<br>
Table 6: Device Address<br>A6  A5  A4  A3  A2  A1<br>0  0  1  0  0  1<br>SDA<br>SCL<br>Data Line  Change<br>Stable of Data<br>Data Valid Allowed<br>Figure 24  Data Validation Diagram<br>SDA<br>SCL<br>S/Sr P<br>S: START condition P: STOP condition<br>Sr: START Repeated condition<br>awinic Confidential<br>**----- End of picture text -----**<br>


## _**Device Address**_ 

AW32001E 7-bit slave address (A7~A1) is 1001001 binary(0x49H). After the START condition, the I²C master sends the 7-bit chip address followed by an eighth (A0) read or write bit (R/W). R/W= 0 indicates a WRITE 

function and R/W = 1 indicates a READ function. 

||||Table 6: Device Address<br>|Table 6: Device Address<br>||||
|---|---|---|---|---|---|---|---|
|A7|A6<br>|A5<br>|A4<br>|A3<br>|A2<br>|A1<br>|A0|
|1|0<br>|0<br>|1<br>|0<br>|0<br>|1<br>|R/W|
|||||||||



## _**Data Validation**_ 

When SCL is high level, SDA level must be constant. SDA can be changed only when SCL is low level. 

## _**I[2] C Start/Stop**_ 

I[2] C start: SDA changes from high level to low level when SCL is high level. I[2] C stop: SDA changes from low level to high level when SCL is high level. 

## **Figure 25  Start and Stop Conditions** 

www.awinic.com 31             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## _**ACK (Acknowledgement)**_ 

ACK means the successful transfer of I[2] C bus data. After master sends 8bits data, SDA must be released; SDA is pulled to GND by slave device when slave acknowledges. 

When master reads, slave device sends 8bit data, releases the SDA and waits for ACK from master. If ACK is send and I[2] C stop is not send by master, slave device sends the next data. If ACK is not send by master, slave device stops to send data and waits for I[2] C stop. 

**==> picture [486 x 517] intentionally omitted <==**

**----- Start of picture text -----**<br>
Data Output<br>by Transmiter<br>Not Acknowledge （ NACK ）<br>Data Output<br>by Receiver<br>Acknowledge （ ACK ）<br>SCL From 1 2 8 9<br>Master<br>START  Clock Pulse for<br>condition Acknowledgement<br>Figure 26  Acknowledgement Diagram<br>Write Process<br>One data bit is transferred during each clock pulse. Data is sampled during the high state of the serial clock<br>(SCL). Consequently, throughout the clock’s high period, the data should remain stable. Any changes on the<br>SDA line during the high state of the SCL and in the middle of a transaction, aborts the current transaction.<br>New data should be sent during the low SCL state. This protocol allows a single data line to transfer both<br>command/control information and data using the synchronous serial clock.<br>Each data transaction is composed of a Start Condition, a number of byte transfers (set by the software) and<br>a Stop Condition to terminate the transaction. Every byte written to the SDA bus must be 8 bits long and is<br>transferred with the most significant bit first. After each byte, an Acknowledge signal must follow.<br>In a write process, the following steps should be followed:<br>a)  Master device generates START condition. The “START” signal is generated by lowering the SDA signal<br>while the SCL signal is high.<br>b)  Master device sends slave address (7-bit) and the data direction bit (r/w = 0).<br>c)  Slave device sends acknowledge signal if the slave address is correct.<br>d)  Master sends control register address (8-bit)<br>e)  Slave sends acknowledge signal<br>f)  Master sends data byte to be written to the addressed register<br>g)  Slave sends acknowledge signal<br>h)  If master will send further data bytes the control register address will be incremented by one after<br>acknowledge signal (repeat steps f and g)<br>i)  Master generates STOP condition to indicate write cycle end<br>awinic Confidential<br>**----- End of picture text -----**<br>


**==> picture [460 x 61] intentionally omitted <==**

**----- Start of picture text -----**<br>
SCL 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8<br>SDA A6 A5 A4 A3 A2 A1 A0 R/WAck A7 A6 A5 A4 A3 A2 A1 A0 Ack D7 D6 D5 D4 D3 D2 D1 D0<br>Ack<br>Start Device Address Register Address Write Data Stop<br>**----- End of picture text -----**<br>


www.awinic.com 32             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Figure 27  I[2] C Write Timing** 

## _**Read Process**_ 

In a read cycle, the following steps should be followed: 

- a) Master device generates START condition 

- b)  Master device sends slave address (7-bit) and the data direction bit (r/w = 0). 

**==> picture [486 x 618] intentionally omitted <==**

**----- Start of picture text -----**<br>
c)  Slave device sends acknowledge signal if the slave address is correct.<br>d)  Master sends control register address (8-bit)<br>e)  Slave sends acknowledge signal<br>f)  Master generates STOP condition followed with START condition or REPEAT START condition<br>g)  Master device sends slave address (7-bit) and the data direction bit (r/w = 1).<br>h)  Slave device sends acknowledge signal if the slave address is correct.<br>i)  Slave sends data byte from addressed register.<br>j)  If the master device sends acknowledge signal, the slave device will increase the control register<br>address by one, then send the next data from the new addressed register.<br>k)  If the master device generates STOP condition, the read cycle is ended.<br>SCL 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8<br>SDA A6 A5 A4 A3 A2 A1 A0 R/W Ack A7 A6 A5 A4 A3 A2 A1 A0 Ack<br>start Device Address Register Address<br>Using  …… 0 1 2 3 4 5 6 7 8 0 1 ... 6 7 8<br>Repeat start…… A6 A5 A4 A3 A2 A1 A0 R/W Ack D7 D6 …… D1 D0 Ack<br>RS<br>Device Address Read Data stop<br>Separated …… 0 1 2 3 4 5 6 7 8 0 1 ... 6 7 8<br>Read/write<br>transaction …… A6 A5 A4 A3 A2 A1 A0 R/W Ack D7 D6 …… D1 D0 Ack<br>P S<br>Device Address Read Data stop<br>Figure 28  I [2] C Read Timing<br>www.awinic.com                              33             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved<br>awinic Confidential<br>**----- End of picture text -----**<br>


j)  If the master device sends acknowledge signal, the slave device will increase the control register address by one, then send the next data from the new addressed register. 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Register List** 

## _**Register Map**_ 

## R/W = Read/Write, RC = Read Clear. 

|**ADDR**|0x00|0x01|0x01|0x01|0x01|0x02|0x02|0x03|0x03|0x03|0x04|
|---|---|---|---|---|---|---|---|---|---|---|---|
|**NAME**|Input Source Control|Power On Configuration||||Charge Current Control||Discharge Current Control|||Charge Voltage|
|**Default**|0x8F|0xAC||||0x0F||0x91|||0XA3|
|**Bit7**|VIN_DPM[3:0]<br>|tRST_DGL<br>||||REG_RST<br>||IDSCHG[3:0]<br>ial|||VBAT_REG[5:0]|
|**Bit6**||||||WD_TMR_RST<br>||||||
|**Bit5**||tRST_DUR<br>||||ICHG[5:0]<br>||||||
|**Bit4**||EN_HIZ<br>||||||||||
|**Bit3**|IIN_LIM[3:0]<br>|CEB<br>||||||ITERM[3:0]<br>nt||||
|**Bit2**||VBAT_UVLO[2:0]<br>||||||||||
|**Bit1**|||||||||||VBAT_PRE|
|**Bit0**|||||||||||VRECH|
|||||||||||||
|**ADDR**|0x05<br>|||||0x06<br>||0x07<br>|||0x08|
|**NAME**|Charger Termination/Timer Control<br>|||||Main Control<br>||System Voltage Control<br>|||System Status|
|**Default**|0x7A<br>|||||0xC0<br>||0x38<br>|||0x40|
|**Bit7**|EN_WD_DISCHG<br>|||||EN_NTC<br>||DIS_PCB_OTP<br>|||Watchdog_ Fault|
|**Bit6**|WATCHDOG[1:0]<br>|||||TMR2X_EN<br>||DIS_VINLOOP<br>|||Rev[1:0]|
|**Bit5**||||||FET_DIS<br>||TJ_REG[1:0]<br>||||
|**Bit4**|EN_TERM<br>|||PG_INT_CONTROL<br>|||||||CHG_STAT[1:0]|
|**Bit3**|EN_TIMER<br>|||EOC_INT_CONTROL<br>||||VSYS_REG[3:0]<br>||||
|**Bit2**|CHG_TMR[1:0]<br>|||CHG STATUS_INT_CONTROL<br>|||||||PPM_STAT|
|**Bit1**||||NTC_INT_CONTROL<br>|||||||PG_STAT|
|**Bit0**|TERM_TMR<br>|||BATOVP_INT_CONTROL<br>|||||||THERM_STAT|
|||||||||||||
|**ADDR**|0x09<br>||0x0A<br>||0x0B<br>|||0x0C<br>|||0x22|
|**NAME**|Fault<br>||Address<br>||Individual Charge<br>||Additional<br>|Function Control<br>|Additional Function Control<br>|||
|**Default**|0x00<br>||0x49<br>||0x43<br>|||0x10<br>|0x03<br>|||
|**Bit7**|EN_SHIPPING_DGL[1:0]<br>||CHIPID[7:0]<br>||EN_ICHG_DIVD<br>||EN0P55<br>||Reserve[3:0]<br>|||
|**Bit6**|||||Reserve<br>||ITERMDEG<br>|||||
|**Bit5**|VIN_FAULT<br>||||EN_IPRE_SET<br>||Reserve[1:0]<br>|||||
|**Bit4**|THEM_SD<br>||||IPRE[3:0]<br>|||||||
|**Bit3**|BAT_FAULT<br>||||||PRETO<br>||INT100MS<br>|||
|**Bit2**|STMR_FAULT<br>||||||EN100KINT<br>||Reserve[2:0]<br>|||
|**Bit1**|NTC_FAULT[1:0]||||||Reserve[0]|||||
|**Bit0**|||||EN_SHIPMD_0P1S||RSTDLAY|||||



www.awinic.com 34             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## _**Input Source Control Register**_ 

Address: 00H, Reset State: 1000 1111. 

|**BIT Name**<br>**W/R**<br>**BIT**<br>**SFTRST**<br>VIN_DPM<br>W/R<br>B7-B4<br>Y<br>IIN_LIM<br>W/R<br>B3-B0<br>Y<br>**_Power On Configuration Register_**<br>Address: 01H, Reset State1010 1100.<br>**BIT Name**<br>**W/R**<br>**BIT**<br>**SFTRST**<br>tRST_DGL<br>W/R<br>B7-B6<br>Y<br>tRST_DUR<br>W/R<br>B5<br>Y<br>EN_HIZ<br>W/R<br>B4<br>Y<br>CEB<br>W/R<br>B3<br>Y<br>VBAT_UVLO<br>W/R<br>B2-B0<br>Y<br>awinic C|**BIT Name**|**W/R**|**BIT**|**SFTRST**|**WTDRST**|**Function**|
|---|---|---|---|---|---|---|
||VIN_DPM<br>|W/R<br>|B7-B4<br>|Y<br>|N<br>|VIN_DPM voltage regulation setting:<br>BIN    VIN_DPM (V)<br>0000    3.88**1000** **4.52 (default)**<br>0001    3.96         1001    4.60<br>0010    4.04         1010    4.68<br>0011    4.12         1011    4.76<br>0100    4.20         1100    4.84<br>0101    4.28         1101    4.92<br>0110    4.36         1110    5.00<br>0111    4.44         1111    5.08<br>tial|
||IIN_LIM<br>|W/R<br>|B3-B0<br>|Y<br>|N<br>|Input current limit setting:<br>BIN    IIN_LIM (mA)<br>0000    50          1000    290<br>0001    80          1001    320<br>0010    110         1010    350<br>0011    140         1011    380<br>0100    170         1100    410<br>0101    200         1101    440<br>0110    230         1110    470<br>0111    260**1111    500(default)**<br>iden|
||||||on||
||**BIT Name**<br>|**W/R**<br>|**BIT**<br>|**SFTRST**<br>|**WTDRST**<br>|**Function**<br>|
||tRST_DGL<br>|W/R<br>|B7-B6<br>|Y<br>|Y<br>|Pull INT low time period to disconnect the battery:<br>BIN               time (s)<br>00: 8               01: 12<br>**10: 16(default)**11: 20<br>|
||tRST_DUR<br>|W/R<br>|B5<br>|Y<br>c|Y<br>|Q2 lasts off time before auto-on:<br>0: 2s;**1: 4s (default).**<br>|
||EN_HIZ<br>|W/R<br>|B4<br>|Y<br>|Y<br>|**0: disable (default);**1:enable.<br>|
||CEB<br>|W/R<br>|B3<br>|Y<br>|Y<br>|0: charge enable;**1: charge disable (default).**<br>|
||VBAT_UVLO<br>|W/R<br>|B2-B0<br>wi|Y<br>|Y<br>|Battery UVLO Threshold:<br>BIN     VBAT_UVLO (V)<br>000      2.43**100    2.76 (default)**<br>001      2.49         101    2.85 <br>010      2.58         110    2.94<br>011      2.67         111    3.03<br>|
||||||||



www.awinic.com 35             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## _**Charge Current Control Register**_ 

Address: 02H, Reset State:0000 1111 

|**BIT Name**<br>**W/R**<br>**BIT**<br>**REGRST**<br>REG_RST<br>W/R<br>B7<br>Y<br>WD_TMR_RST<br>W/R<br>B6<br>Y<br>ICHG<br>W/R<br>B5-B0<br>Y<br>**_Discharge Current Control Register_**<br>Address: 03H, Reset State1001 0001.<br>**BIT Name**<br>**W/R**<br>**BIT**<br>**REGRST**<br> <br>IDSCHG<br>W/R<br>B7-B4<br>Y<br>awinic C|**BIT Name**|**BIT Name**|**W/R**|**W/R**|**BIT**|**BIT**|**REGRST**|**REGRST**|**WTDRST**|**WTDRST**|**Function**|
|---|---|---|---|---|---|---|---|---|---|---|---|
||REG_RST||W/R||B7||Y||N||**0: keep current setting (default);**1: reset.|
||WD_TMR_RST||W/R||B6||Y||Y||**0: normal (default);**1: reset.|
||ICHG<br>||W/R<br>||B5-B0<br>in||Y<br>ic C||Y<br>onf||Fast charge current setting:<br>BIN     ICHG(mA)<br>000000   8            100000     264<br>000001   16           100001     272<br>000010   24           100010     280<br>000011   32           100011     288<br>000100   40           100100     296<br>000101   48           100101     304<br>000110   56           100110     312<br>000111   64           100111     320<br>001000   72           101000     328<br>001001   80           101001     336<br>001010   88           101010     344<br>001011   96           101011     352<br>001100   104          101100     360<br>001101   112          101101     368<br>001110   120          101110     376<br>**001111   128 (default)**101111     384<br>010000   136          110000     392<br>010001   144          110001     400<br>010010   152          110010     408<br>010011   160          110011     416<br>010100   168          110100     424<br>010101   176          110101     432<br>010110   184          110110     440<br>010111   192          110111     448<br>011000   200          111000     456<br>011001   208          setting REG0CH[7]=1 and<br>011010   216          REG00H[3:0]=1111, open<br>011011   224          111001     464<br>011100   232          111010     472<br>011101   240          111011     480<br>011110   248          111100     488<br>011111   256          111101     496<br>111110     504<br>111111     512<br>idential|
|||||||||||||
||**BIT Name**<br>|**W/R**<br>||**BIT**<br>||**REGRST**<br>||<br>|**WTDRST**<br>||**Function**<br>|
||IDSCHG|W/R||B7-B4||Y|||Y|BAT to SYS discharge current limit:<br>BIN  IDSCHG(mA)<br>0000   200         1000   1800<br>0001   400**1001   2000 (default)**<br>0010   600         1010   2200<br>0011   800         1011   2400<br>0100   1000        1100   2600<br>0101   1200        1101   2800<br>0110   1400        1110   3000<br>0111   1600        1111   3200||



www.awinic.com 36             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

**==> picture [284 x 38] intentionally omitted <==**

Sep. 2023 V1.4 

|ITERM<br>W/R<br>B3-B0<br>Y<br>**_Charge Voltage Register_**<br>Address: 04H, Reset State:1010 0011.<br>**BIT Name**<br>**W/R**<br>**BIT**<br>**REGRST**<br>VBAT_REG<br>W/R<br>B7-B2<br>Y<br>VBAT_PRE<br>W/R<br>B1<br>Y<br>VRECH<br>W/R<br>B0<br>Y<br>awinic|ITERM<br>|W/R<br>|B3-B0<br>|Y<br>|Y<br>|Termination current. current range:<br>BIN    ITERM(mA)<br>0000      1           1000     17 <br>**0001      3 (default)**1001     19<br>0010      5           1010     21<br>0011      7           1011     23<br>0100      9           1100     25<br>0101      11          1101     27<br>0110      13          1110     29<br>0111      15          1111     31<br>l|
|---|---|---|---|---|---|---|
|||||||ia|
||**BIT Name**<br>|**W/R**<br>|**BIT**<br>|**REGRST**<br>|**WTDRST**<br>|**Function**<br>|
||VBAT_REG<br>|W/R<br>a|B7-B2<br>wi|Y<br>nic|Y<br>Con|Battery regulation voltage:<br>BIN    VBAT_REG(V)<br>000000   3.600          100000    4.080<br>000001   3.615          100001    4.095<br>000010   3.630          100010    4.110<br>000011   3.645          100011    4.125<br>000100   3.660          100100    4.140<br>000101   3.675          100101    4.155<br>000110   3.690          100110    4.170<br>000111   3.705          100111    4.185<br>001000   3.720**101000    4.200(default)**<br>001001   3.735          101001    4.215<br>001010   3.750          101010    4.230<br>001011   3.765          101011    4.245<br>001100   3.780          101100    4.260<br>001101   3.795          101101    4.275<br>001110   3.810          101110    4.290<br>001111   3.825          101111    4.305<br>010000   3.840          110000    4.320<br>010001   3.855          110001    4.335<br>010010   3.870          110010    4.350<br>010011   3.885          110011    4.365<br>010100   3.900          110100    4.380<br>010101   3.915          110101    4.395<br>010110   3.930          110110    4.410<br>010111   3.945          110111    4.425<br>011000   3.960          111000    4.440<br>011001   3.975          111001    4.455<br>011010   3.990          111010    4.470<br>011011   4.005          111011    4.485<br>011100   4.020          111100    4.500<br>011101   4.035          111101    4.515<br>011110   4.050          111110    4.530<br>011111   4.065          111111    4.545<br>fiden|
||VBAT_PRE|W/R|B1|Y|Y|Pre-charge to Fast charge threshold:<br>0:2.8V;**1: 3.0V (default).**|
||VRECH|W/R|B0|Y|Y|Battery recharge threshold (below VBAT_REG):<br>0: 100mV;**1: 200mV (default).**|



www.awinic.com 37             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## _**Charger Termination/Timer Control Register**_ 

Address: 05H, Reset State:0111 1010. 

|**BIT Name**<br>**W/R**<br>**BIT**<br>**REGRST**<br>EN_WD_DISC<br>HG<br>W/R<br>B7<br>Y<br>WATCHDOG<br>W/R<br>B6-B5<br>Y<br>EN_TERM<br>W/R<br>B4<br>Y<br>EN_TIMER<br>W/R<br>B3<br>Y<br>CHG_TMR<br>W/R<br>B2-B1<br>Y<br>TERM_TMR<br>W/R<br>B0<br>Y<br>**_ain Control Register_**<br>ddress: 06H, Reset State:1100 0000.<br>|**W/R**|**BIT**|**REGRST**|**REGRST**|**WTDRST**|**WTDRST**|**Function**|**Function**|
|---|---|---|---|---|---|---|---|---|
||W/R|B7|Y||N||Watchdog control in discharge mode:<br>**0: disable (default);**1: enable.||
||W/R<br>|B6-B5<br>|Y<br>||N<br>||Watchdog setting:<br>00:  disable timer     01:  40s<br>10:  80s**11:  160s (default)**<br>If Bit[6:5]=00, then watchdog timer is disable no matter<br>Bit 7 is set or no.<br>l||
||W/R<br>|B4<br>|Y<br>||Y<br>||Termination Setting (control the termination is allowed or<br>not): 0: disable ;**1: enable (default).**<br>i||
||W/R<br>|B3<br>|Y<br>||Y<br>||Safety timer Setting:<br>0: disable;**1: enable (default).**<br>t||
||W/R<br>|B2-B1<br>|Y<br>||Y<br>||Fast charge timer:<br>00: 3hrs**01: 5hrs (default);**<br>10: 8hrs      11: 12hrs.<br>n||
||W/R<br>|B0<br>|Y<br>||Y<br>||Termination timer Setting (When TERM_TMR is enabled,<br>the device will not suspend the charge current after<br>charge termination):<br>**0: disable (default);**1: enable.<br>de||
||||||||fi||
|**BIT Name**|**W/R**<br>|**BIT**<br>|**REGRST**<br>||**WTDRST**<br>||**Function**<br>||
|EN_NTC|W/R<br>|B7<br>|Y<br>||Y<br>||0: disable ;**1: enable (default).**<br>||
|TMR2X_EN|W/R<br>|B6<br>|Y<br>||Y<br>||0: disable 2x extended safety timer during PPMF;<br>**1: enable 2x extended safety timer during PPMF**<br>**(default).**<br>||
|FET_DIS|W/R<br>|B5<br>|Y<br>||N<br>||**0: enable** **(default);**1: turn off.<br>||
|PG_INT_CON<br>TROL|W/R<br>|B4<br>|Y<br>|||Y<br>|**0: on (default);**1: off.<br>||
|EOC_INT_CO<br>NTROL|W/R<br>|B3<br>|Y<br>i|||Y<br>|**0: on (default);**1: off. (EOC: End of Charge)<br>||
|CHG<br>STATUS_INT<br>_CONTROL|W/R<br>|B2<br>|Y<br>|||Y<br>|**0: on (default);**1: off.<br>||
|NTC_INT_CO<br>NTROL|W/R<br>|B1<br>|Y<br>|||Y<br>|**0: on (default);**1: off.<br>||
|BATOVP_INT<br>_CONTROL|W/R<br>|B0<br>|Y<br>|||Y<br>|**0: on (default);**1: off.<br>||
|**_ystem Voltage Control Register_**<br>ddress: 07H, Reset State:0011 1000.<br>a|||||||||
|**BIT Name**|**W/R**|**BIT**||**REGRST**||**WTDRST**||**Function**|
|DIS_PCB_OTP|W/R|B7||Y||Y||PCB OTP Disable.<br>**0: enable PCB OTP (default);**1: disable PCB OTP.|
|DIS_VINLOOP|W/R|B6||Y||Y||VIN_DPM loop.<br>**0: enable VIN_DPM loop (default);**1: disable.|



www.awinic.com 38             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

**==> picture [284 x 38] intentionally omitted <==**

Sep. 2023 V1.4 

|TJ_REG<br>W/R<br>B5-B4<br>Y<br>VSYS_REG<br>W/R<br>B3-B0<br>Y<br>**_System Status Register_**<br>Address: 08H, Reset State:0100 0000.<br>|W/R|B5-B4|Y|Y|Y|Thermal regulation threshold:<br>BIN    Temperature(°C)<br>00        60           01      80<br>10       100**11      120 (default)**<br>System voltage regulation. Range:<br>BIN   VSYS_REG(V)<br>0000   4.20**1000   4.60 (default)**<br>0001   4.25       1001   4.65<br>0010   4.30       1010   4.70<br>0011   4.35       1011   4.75<br>0100   4.40       1100   4.80<br>0101   4.45       1101   4.85<br>0110   4.50       1110   4.90<br>0111   4.55       1111   4.95<br>ial|
|---|---|---|---|---|---|---|
||W/R<br>|B3-B0<br>|Y<br>||N<br>||
|||||||nt|
|**BIT Name**|**W/R**<br>|**BIT**<br>|**REG RST**<br>||**WTDRST**<br>|**Function**<br>|
|Watchdog_<br>Fault|R<br>|B7<br>|NA<br>||NA<br>|**0: normal (default);**1: watchdog timer expiration.<br>|
|Rev|R<br>|B6-B5<br>|NA<br>||NA<br>||
|CHG_STAT|R<br>|B4-B3<br>|NA<br>||NA<br>|**00: not charging (default);**01: pre charge;<br>10: charge;                11: charge done.<br>|
|PPM_STAT|R<br>|B2<br>|NA<br>||NA<br>|**0: no PPM (default);**1: IN PPM. <br>|
|PG_STAT|R<br>|B1<br>|NA<br>||NA<br>|0: Power fail; 1: Power good.<br>|
|THERM_STAT|R<br>|B0<br>|NA<br>||NA<br>|**0: no thermal regulation (default);** <br>1: in thermal regulation.<br>|
|**_Fault Register_**<br>Address: 09H, Reset State:0000 0000.<br>|||||||
|**BIT Name**|**W/R**<br>|**BIT**<br>|**REGRST**<br>|<br>|**WTDRST**<br>|**Function**<br>|
|EN_SHIPPING_<br>DGL|W/R<br>|B7-B6<br>i|Y<br>||N<br>|Enter shipping mode deglitch time:<br>BIN    deglitch time(s)<br>**00:     1 (default);**01:     2<br>10:     4              11:     8<br>|
|VIN_FAULT|R<br>|B5<br>|NA<br>||NA<br>|**0: normal (default);**1: input fault (OVP or bad source).<br>|
|THEM_SD|R<br>|B4<br>|NA<br>||NA<br>|**0: normal (default);**1: thermal shutdown.<br>|
|BAT_FAULT|R<br>|B3<br>|NA<br>||NA<br>|**0: normal (default);**1: battery OVP.<br>|
|STMR_FAULT|R<br>|B2<br>|NA<br>||NA<br>|**0: normal (default);**1: safety timer expiration.<br>|
|NTC_FAULT[1]|R<br>|B1<br>|NA<br>||NA<br>|**0: normal (default);**1: NTC hot.<br>|
|NTC_FAULT[0]|R<br>|B0<br>|NA<br>||NA<br>|**0: normal (default);**1: NTC cold.<br>|
|**Address Register**<br>Address: 0AH, Reset State:0100|||1001.||||
|**BIT Name**|**W/R**|**BIT**|**REGRST**||**WTDRST**|**Function**|
|CHIP ID|R|B7-B0|N||N|Chip ID used to be identified|



www.awinic.com 39             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## _**Individual Charge Register**_ 

Address: 0BH, Reset State:0100 0011. 

|**BIT Name**<br>EN_ICHG_DIVD<br>Reserve<br>EN_IPRE_SET<br>IPRE[3:0]<br>EN_SHIPMD_0<br>P1S|**BIT Name**<br>EN_ICHG_DIVD<br>Reserve<br>EN_IPRE_SET<br>IPRE[3:0]<br>EN_SHIPMD_0<br>P1S|**W/R**|**BIT**|**REGRST**|**WTDRST**|**Function**|
|---|---|---|---|---|---|---|
|||W/R<br>|B7<br>|Y<br>|Y<br>|1: reduce the current value of REG02[3:0] configuration<br>to 1/4;<br>**0: keep the current value of REG02[5:0]**<br>**configuration. (default).**<br>|
|||NA<br>|B6<br>|NA<br>|NA<br>|NA<br>|
|||W/R<br>|B5<br>|Y<br>|Y<br>|**0: IPRE is set by REG03[4:1] (default);**<br>1: IPRE is set by REG0B[4:1].<br>al|
|||W/R<br>|B4-B1<br>|Y<br>|Y<br>|1mA~31mA pre-charge current configuration:<br>2 mA/step,**3mA (default).**<br>BIN   IPRE(mA)<br>0000   1          1000   17<br>**0001   3(default)**1001   19<br>0010   5          1010   21<br>0011   7          1011   23<br>0100   9          1100   25<br>0101   11         1101   27<br>0110   13         1110   29<br>0111   15         1111   31<br>denti|
|||W/R<br>|B0<br>|Y<br>|Y<br>|VIN Plug: In deglitch time of shipping mode out：<br>0：2s;**1**：**100ms(default).**<br>|
|**_Additional Function Control Register_**<br>Address: 0CH, Reset State:0001 0000.<br>|||||o||
||**BIT Name**|**W/R**<br>|**BIT**<br>|**REGRST**<br>|**WTDRST**<br>|**Function**<br>|
||EN0P55|W/R<br>|B7<br>|Y<br>|Y<br>|Increase input current limit:<br>**0: The input current limit is set by REG00[3:0] (default);**<br>1: If REG00[3:0]=1111,this bit increase the input current<br>limit to 550mA, otherwise, it is useless.<br>|
||ITERMDEG|W/R<br>|B6<br>|Y<br>ic|Y<br>|Charge termination current deglitch time:<br>**0:3s (default);**1:1s.<br>|
||Reserve|NA<br>|B5~B4<br>|NA<br>|NA<br>|NA<br>|
||PRETO|W/R<br>|B3<br>i|Y<br>|Y<br>|**0: Pre-charge timeout is 1h (default);**<br>1: Pre-charge timeout is 2h.<br>|
||DIS_SHIPINT|W/R<br>|B2<br>|Y<br>|Y<br>|The function of disabling INT PIN during SHIPPING mode:<br>**0: Nominal INT PIN function(Default);**<br>1: Disable INT PIN function during SHIPPING mode.<br>|
||Reserve|NA<br>|B1<br>|NA<br>|NA<br>|NA<br>|
||RSTDLAY|W/R<br>|B0<br>|Y<br>|Y<br>|The delay time after VSYS is Reset:<br>**0: 0s (Default);**1: 2s.<br>|
|**_Additional Function Control Register1_**<br>Address: 22H, Reset State:0000 0011.|||||||
|**BIT Name**||**W/R**|**BIT**|**REGRST**|**WTDRST**|**Function**|
|Reserve||NA|B7~B4|NA|NA|NA|
|INT100MS||W/R|B3|Y|Y|INT 100ms exit shipping mode<br>**0: 2s (default);**<br>1:100ms.|
|Reserve||NA|B2~B0|NA|NA|NA|



|**BIT Name**<br>EN0P55<br>ITERMDEG<br>Reserve<br>PRETO<br>DIS_SHIPINT<br>Reserve<br>RSTDLAY|**W/R**<br>**BIT**<br>**REGRST**<br>W/R<br>B7<br>Y<br>W/R<br>B6<br>Y<br>NA<br>B5~B4<br>NA<br>W/R<br>B3<br>Y<br>W/R<br>B2<br>Y<br>NA<br>B1<br>NA<br>W/R<br>B0<br>Y<br>awinic|**WTDRST**<br>**Function**<br>Y<br>Increase input current limit:<br>**0: The input current limit is set by REG00[3:0] (default);**<br>1: If REG00[3:0]=1111,this bit increase the input current<br>limit to 550mA, otherwise, it is useless.<br>Y<br>Charge termination current deglitch time:<br>**0:3s (default);**1:1s.<br>NA<br>NA<br>Y<br>**0: Pre-charge timeout is 1h (default);**<br>1: Pre-charge timeout is 2h.<br>Y<br>The function of disabling INT PIN during SHIPPING mode:<br>**0: Nominal INT PIN function(Default);**<br>1: Disable INT PIN function during SHIPPING mode.<br>NA<br>NA<br>Y<br>The delay time after VSYS is Reset:<br>**0: 0s (Default);**1: 2s.<br>|
|---|---|---|



www.awinic.com 40             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Application Information** 

## **NTC FUNCTION** 

**==> picture [486 x 545] intentionally omitted <==**

**----- Start of picture text -----**<br>
NTC pin is connected to the thermistor paralleled with a resistor RF2 to ground. Another resistor RF1 is<br>connected to the VDD which is the chip’s internal power supply voltage. The high temperature limit and low<br>temperature limit can be varied by using different RF1 and RF2. Illustrated in Figure 29, the off chip resistors<br>must be connected as the blue part demonstrated. The resistance of RF1 and RF2 can be calculated by Equation<br>(1) and Equation (2):<br>(𝑉𝐶𝑂𝐿𝐷 −𝑉𝐻𝑂𝑇) × 𝑅𝑁𝑇𝐶𝐻 × 𝑅𝑁𝑇𝐶𝐿<br>𝑅𝐹2 = (𝑉𝐻𝑂𝑇 −𝑉𝐶𝑂𝐿𝐷 × 𝑉𝐻𝑂𝑇) × 𝑅𝑁𝑇𝐶𝐿 −(𝑉𝐶𝑂𝐿𝐷 −𝑉𝐶𝑂𝐿𝐷 × 𝑉𝐻𝑂𝑇) × 𝑅𝑁𝑇𝐶𝐻                                 (1)<br>𝑅𝐹1 =  [1 −𝑉][𝐶𝑂𝐿𝐷] × (𝑅𝐹2//𝑅𝑁𝑇𝐶𝐿)                                                                   (2)<br>𝑉𝐶𝑂𝐿𝐷<br>PAD_VDD<br>R1<br>RF1<br>NTC<br>PAD_NTC Detector<br>R2<br>RNTC RF2 R3<br>PAD_GND<br>Figure 29  NTC Function(resistor-divided mode)<br>Where RNTCH is the value of the NTC resistor at the high limit temperature, while the RNTCL is the value of the<br>NTC resistor at a low temperature limit.<br>External Capacitor<br>The external capacitor cannot be absent for the operation of AW32001E. Carefully selecting suitable capacitor<br>is important to guarantee the AW32001E working perfectly on the space limited board.<br>A 4.7μF ceramic capacitor with high level voltage endurance (at least 30V) between IN and GND is<br>recommended. This capacitor rejects input power supply ripple and enhance the stability of DPM loop.<br>A 1μF ceramic capacitor is required between the VDD and GND to maintain internal power supply voltage<br>higher than the POR threshold. Without this capacitor, the chip logic block may work abnormally when working<br>state changes.<br>awinic Confidential<br>**----- End of picture text -----**<br>


Connect a ceramic capacitor between SYS and GND with least capacitance of 4.7μF to guarantee the stability of the system power supply loop. Larger capacitor will further reduce the system output’s overshoot and undershoot. 

A least 4.7μF ceramic capacitor is also needed between BAT and GND for some application. 

Table 6: Recommended external capacitors 

www.awinic.com 41             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

|**Comments**|**Capacitor**|**Supplier**|**Description**|**ELA Size**|**Effective**<br>**Capacitance**|
|---|---|---|---|---|---|
|CIN|4.7μF|Any|Ceramic Capacitor;50V; X5R or X7R|0603|>2μF|
|CVDD|0.1μF|Any|Ceramic Capacitor;16V; X5R or X7R|0603|>50nF|
|CSYS|4.7μF|Any|Ceramic Capacitor;16V; X5R or X7R|0603|>3μF|
|CBAT|4.7μF<br>|Any<br>|Ceramic Capacitor;16V; X5R or X7R<br>|0603<br>|>3μF<br>|
||awinic Confiden|||tia||



www.awinic.com 42             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Tape and Reel Information** 

**==> picture [74 x 8] intentionally omitted <==**

**----- Start of picture text -----**<br>
TAPE DIMENSIONS<br>**----- End of picture text -----**<br>


**==> picture [482 x 520] intentionally omitted <==**

**----- Start of picture text -----**<br>
REEL DIMENSIONS TAPE DIMENSIONS<br>P1 P0 P2<br>K0<br>W<br>B0<br>D1<br>Cavity A0<br>A0 ： Dimension designed to accommodate the component width<br>B0 ： Dimension designed to accommodate the component length<br>K0 ： Dimension designed to accommodate the component thickness<br>W ： Overall width of the carrier tape<br>P0 ： Pitch between successive cavity centers and sprocket hole<br>P1 ： Pitch between successive cavity centers<br>D0 P2 ： Pitch between sprocket hole<br>D1 ： Reel Diameter<br>D0 ： Reel Width<br>QUADRANT ASSIGNMENTS FOR PIN 1 ORIENTATION IN TAPE<br>Pin 1 Sprocket Holes<br>Q1 Q2 Q1 Q2 Q1 Q2 Q1 Q2<br>Q3 Q4 Q3 Q4 Q3 Q4 Q3 Q4 User Direction of Feed<br>Pocket Quadrants<br>awinic Confidential<br>**----- End of picture text -----**<br>


www.awinic.com 43             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Package Description(POD)** 

**==> picture [350 x 603] intentionally omitted <==**

**----- Start of picture text -----**<br>
1.680<br>±0.020<br>PIN 1<br>CORNER<br>1.680<br>±0.020<br>Top View<br>0.040±0.005<br>0.350<br>0.667 ±0.012<br>MAX<br>0.240 BALL TYP<br>±0.020<br>Side View<br>1 2 3<br>9X( ∅ 0.310±0.020)<br>C<br>SYMM<br>1.000 B<br>TYP  ℄<br>0.500<br>TYP<br>A<br>0.500<br>TYP<br>1.000<br>TYP<br>SYMM<br>    ℄<br>Bottom View<br>Unit：mm<br>awinic Confidential<br>**----- End of picture text -----**<br>


www.awinic.com 44             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** 

Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Land Pattern Data** 

**==> picture [386 x 505] intentionally omitted <==**

**----- Start of picture text -----**<br>
1 2 3<br>9X( ∅ 0.260)<br>A<br>0.500<br>TYP<br>SYMM<br>B<br>    ℄<br>C<br>0.500<br>TYP<br>SYMM<br>    ℄<br>0.05 MIN<br>0.05 MAX<br>All AROUND<br>All AROUND SOLDER MASK SOLDER MASK<br>OPENING OPENING<br>METAL UNDER<br>METAL<br>SOLDER MASK<br>NON-SOLDER MASK DEFINED  SOLDER MASK DEFINED<br>Unit: mm<br>awinic Confidential<br>**----- End of picture text -----**<br>


www.awinic.com 45             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Revision History** 

|**Version**|**Date**|**Change Record**|
|---|---|---|
|V1.0|Jun. 2021|Official Released|
|V1.1|Aug. 2021<br>|1.1 Changed VBAT_REG=4.38V, REG04[7:2]=110100 to 110010 in EC table<br>1.2 Changed VSYS_REGtest condition from “VIN=5.5V, EN_HIZ=0, RSYS=100Ω,<br>ICHG=0A, VSYS_REG=4.6V” to “VIN=5.0V, REG07[3:0]=0000, RSYS=100Ω,<br>ICHG=0A, VSYS_REG=4.6V”, added VSYS_REG=4.2V and VSYS_REG=4.95V test<br>condition description.<br>1.3 Changed deglitch time VRECHfor test condition from “VBATfalling after<br>charge termination” to “VBATfalling below VRECHafter charge termination”<br>1.4 Added TDGL_UVLO, TDGL_OVPand ILKG_INTparameter in EC table.<br>1.5 Changed the parameter VSYS name to VSYS_REGin EC table<br>1.6 Changed the parameter VIN_MIN name to VIN_DPM and VIN_DPMin EC<br>table.<br>1.7 Changed the parameter IIN_LMT name to IIN_LIM and IIN_LIMin EC table.<br>1.8 Changed the parameter VOL(STAT)name to VOL(INT)in EC table.<br>1.9 Added Register Map.<br>1.10 Changed the REG22H default value from 00000000 to 00000011.<br>1.11 Added NTC current mode description.<br>1.12 Added Table 6: Recommended external capacitors.<br>1.13 Other detail description.<br>1.14 Change theSupply current IINand Charge current ICHG value of<br>Recommended Operating Conditions<br>fidential|
|V1.2|Mar. 2022<br>|1.1 Deleted NTC current mode description<br>1.2 Added theBAT pin handle Voltage<br>n|
|V1.3|Jun. 2023<br>|ChangedICHGto ITERMintest conditions of ITERM.(P9)<br>|
|V1.4|Sep. 2023<br>|Changed the entry/exit UVLO threshold inpage 25.<br>|
||awinic C||



www.awinic.com 46             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

**AW32001E** Sep. 2023 V1.4 

**==> picture [284 x 38] intentionally omitted <==**

## **Disclaimer** 

Information in this document is believed to be accurate and reliable. However, Shanghai AWINIC Technology Co., Ltd (AWINIC Technology) does not give any representations or warranties, expressed or implied, as to the accuracy or completeness of such information and shall have no liability for the consequences of use of such information. AWINIC Technology reserves the right to make changes to information published in this document, including without limitation specifications and product descriptions, at any time and without notice. Customers shall obtain the latest relevant information before placing orders and shall verify that such information is current and complete. This document supersedes and replaces all information supplied prior to the publication hereof. AWINIC Technology products are not designed, authorized or warranted to be suitable for use in medical, military, aircraft, space or life support equipment, nor in applications where failure or malfunction of an AWINIC Technology product can reasonably be expected to result in personal injury, death or severe property or environmental damage. AWINIC Technology accepts no liability for inclusion and/or use of AWINIC Technology products in such equipment or applications and therefore such inclusion and/or use is at the customer’s own risk. Applications that are described herein for any of these products are for illustrative purposes only. AWINIC Technology makes no representation or warranty that such applications will be suitable for the specified use without further testing or modification. All products are sold subject to the general terms and conditions of commercial sale supplied at the time of order acknowledgement. Nothing in this document may be interpreted or construed as an offer to sell products that is open for acceptance or the grant, conveyance or implication of any license under any copyrights, patents or other industrial or intellectual property rights. Reproduction of AWINIC information in AWINIC data books or data sheets is permissible only if reproduction is without alteration and is accompanied by all associated warranties, conditions, limitations, and notices. AWINIC is not responsible or liable for such altered documentation. Information of third parties may be subject to additional restrictions. Resale of AWINIC components or services with statements different from or beyond the parameters stated by AWINIC for that component or service voids all express and any implied warranties for the associated AWINIC component or service and is an unfair and deceptive business practice. AWINIC is not responsible or liable for any such statements. 

AWINIC Technology products are not designed, authorized or warranted to be suitable for use in medical, military, aircraft, space or life support equipment, nor in applications where failure or malfunction of an AWINIC Technology product can reasonably be expected to result in personal injury, death or severe property or environmental damage. AWINIC Technology accepts no liability for inclusion and/or use of AWINIC Technology products in such equipment or applications and therefore such inclusion and/or use is at the 

www.awinic.com 47             ©2023 Shanghai Awinic Technology Co., Ltd. All Rights Reserved 

