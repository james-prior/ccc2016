/* Registers definitions particular to Silicon Laboratories' C8051F32[01], 
*  that are not contained in <reg52.h> for generic 8052. 
*  See http://www.keil.com/dd/docs/datashts/silabs/c8051f32x.pdf.
*
* Modification History
*
* 2016-10-25 JEP Added URL for datasheet.
* 2009-09-11 JEP Added tmr2cn and i2c* registers. 
* 2008-07-12 JEP Added eip1. 
* 2008-06-15 JEP Added SPI stuff. 
* 2007-05-11 JEP Added flash stuff. 
* 2006-04-30 JEP Created. 
*/

/* Rising slew of unloaded push/pull output (P2.2 of C8051F32XDK) 
*  is 2V/3us (666mV/us).
*  Rise from 0V to 2.6V (of ~3.1V) is about 4.8us. 
*  Fall is about 5ns. 
*  (so one has classic TTL assymetry) */

#include <8051F320.h>

/* Port 3 */
#define C2D_Mask          (1<<0) /* P3.0      unused by me */
#define C2CK_Mask         (1<<1) /* P3.1      unused by me */

sfr reg0cn=0xC9; /* Voltage Regulator Control */
#define RegulatorDisable_Mask    (1<<7)
#define VBUSSignalPresent_Mask   (1<<6)
#define VBUSIntHigh_Mask         (1<<5)
#define USB0RegLowPowerMode_Mask (1<<4)

#define VoltageRegulatorEnabled      (0<<7) 
#define VoltageRegulatorDisabled     (1<<7)
#define VBUS_SignalPresent_Mask      (1<<6)
#define VBUS_LowInterrupt            (0<<5)
#define VBUS_HighInterrupt           (1<<5)
#define USB0VoltageRegulatorNormal   (0<<4)
#define USB0VoltageRegulatorLowPower (1<<4)

sfr xbr0=0xE1; /* Port I/O Crossbar Register 0 */
#define AsyncCP1NotAtPin (0<<7)
#define AsyncCP1AtPin    (1<<7)
#define CP1NotAtPin      (0<<6)
#define CP1AtPin         (1<<6)
#define AsyncCP0NotAtPin (0<<5)
#define AsyncCP0AtPin    (1<<5)
#define CP0NotAtPin      (0<<4)
#define CP0AtPin         (1<<4)
#define SYSCLKNotAtPin   (0<<3)
#define SYSCLKAtPin      (1<<3)
#define I2cNotAtPin      (0<<2)
#define I2cAtPin         (1<<2)
#define SPINotAtPin      (0<<1)
#define SPIAtPin         (1<<1)
#define UARTNotAtPin     (0<<0)
#define UARTAtPin        (1<<0)

sfr xbr1=0xE2; /* Port I/O Crossbar Register 1 */
#define WeakPullupsEnabled (0<<7)
#define WeakPullupsDisabled (1<<7)
#define CrossbarDisabled    (0<<6)
#define CrossbarEnabled     (1<<6)
#define T1NotAtPin          (0<<5)
#define T1AtPin             (1<<5)
#define T0NotAtPin          (0<<4)
#define T0AtPin             (1<<4)
#define ECINotAtPin         (0<<3)
#define ECIAtPin            (1<<3)
#define PCA0ME_Mask         (((1<<3)-1)<<0)
#define PCANotAtPins        (0<<0)
#define CEX0AtPin           (1<<0)
#define CEX01AtPins         (2<<0)
#define CEX012AtPins        (3<<0)
#define CEX0123AtPins       (4<<0)
#define CEX01234AtPins      (5<<0)

sfr oscicn=0xB2; /* Internal Oscillator Control Register */
/* $$$ contrary to manual, value read after reset is 11000000 */
#define IntOscEnable_Mask  (1<<7)
#define IntOscReady_Mask   (1<<6)
#define IntOscSuspend_Mask (1<<5)
#define IntOscDivider_Mask (((1<<2)-1)<<0)
#define IntOscDivideBy8    (0x0<<0)
#define IntOscDivideBy4    (0x1<<0)
#define IntOscDivideBy2    (0x2<<0)
#define IntOscDivideBy1    (0x3<<0)

sfr oscicl=0xB3; /* Internal Oscillator Calibration Register */
/* for the chip in my development kit, this number is 0x10 */

sfr oscxcn=0xB1; /* External Oscillator Control Register */
#define CrystalOscValid_Mask (1<<7) /* read only */
#define ExtOscMode_Mask    (((1<<3)-1)<<4)
#define ExtOscDisabled     (0<<4)
#define ExtClockMode       (1<<4)
#define ExtClockDiv2Mode   (2<<4)
#define RCOscMode          (4<<4)
#define CapOscMode         (5<<4)
#define CrystalOscMode     (6<<4)
#define CrystalOscDiv2Mode (7<<4)
#define ExtOscFrequency_Mask (((1<<3)-1)<<0)
#define XFCN(x)              ((x)<<0)
#define Xtal_10to30MHz       XFCN(7)

sfr clkmul=0xB9; /* Clock Multiplier Control Register */
#define ClkMultEnable_Mask       (1<<7)
#define ClkMultInit_Mask         (1<<6)
#define ClkMultReady_Mask        (1<<5) /* read-only */
#define ClkMultInputSelect_Mask  (((1<<2)-1)<<0)
#define IntOscMultInput_Mask     (0<<0)
#define ExtOscMultInput_Mask     (1<<0)
#define ExtOscDiv2MultInput_Mask (2<<0)

sfr clksel=0xA9; /* Clock Select Register */
#define USBClkSelect_Mask       (((1<<3)-1)<<4)
#define USBClk4XMult            (0<<4)
#define USBClkIntOscDiv2        (1<<4)
#define USBClkExtOsc            (2<<4)
#define USBClkExtOscDiv2        (3<<4)
#define USBClkExtOscDiv3        (4<<4)
#define USBClkExtOscDiv4        (5<<4)
#define SysClkSelect_Mask       (((1<<2)-1)<<0)
#define SysClkIntOsc            (0<<0)
#define SysClkExtOsc            (1<<0)
#define SysClk4XClkMultDiv2     (2<<0)

sfr emi0cn=0xAA; /* External Memory Interface Control */

sfr scon0=0x98; /* Serial Port 0 Control Register */
#define UART8N1Mode          (1<<6)
#define UART9N1Mode          (3<<6)
#define MCE0                 (1<<5)
#define ReceiveEnable_Mask   (1<<4)
#define Tx9thBit_Mask        (1<<3)
#define Rx9thBit_Mask        (1<<2)
#define TxInterruptFlag_Mask (1<<1)
#define RxInterruptFlag_Mask (1<<0)
sbit txInterruptFlag=0x99;
sbit rxInterruptFlag=0x98;

/* of PCON */
#if 0
#define Smod1_Mask (1<<7)
#endif
#define IdleModeSelect_Mask (1<<0)

sfr ckcon=0x8E; /* Clock Control Register */
#define T3MH_Mask            (1<<7)
#define T3ML_Mask            (1<<6)
#define T2MH_Mask            (1<<5)
#define T2ML_Mask            (1<<4)
#define T1M_Mask             (1<<3)
#define T0M_Mask             (1<<2)
#define Timer01Prescale_Mask (((1<<2)-1)<<0)
#define PrescaleSysClkDiv12  (0<<0)
#define PrescaleSysClkDiv4   (1<<0)
#define PrescaleSysClkDiv48  (2<<0)
#define PrescaleExtClkDiv8   (3<<0)

sfr pca0md=0xD9; /* PCA Mode Register */
#define CIDL_Mask                (1<<7)
#define WatchdogTimerEnable_Mask (1<<6)
#define WDLCK_Mask               (1<<5)
#define CPS_Mask                 (((1<<3)-1)<<1)
#define PCASysClkDiv12           (0<<1)
#define PCASysClkDiv4            (1<<1)
#define PCATimer0Overflow        (2<<1)
#define PCAECIHi2Lo              (3<<1)
#define PCASysClk                (4<<1)
#define PCAExtClkDiv8            (5<<1)
#define ECF_Mask                 (1<<0)

/* PCA0CPM[01]  */
#define PCA0FrequencyOutput (0x46)

sfr amx0p=0xBB; /* AMUX0 Positive Channel Select Register */
sfr amx0n=0xBA; /* AMUX0 Negative Channel Select Register */
#define AMUX_P1_0       (0x00)
#define AMUX_P1_1       (0x01)
#define AMUX_P1_2       (0x02)
#define AMUX_P1_3       (0x03)
#define AMUX_P1_4       (0x04)
#define AMUX_P1_5       (0x05)
#define AMUX_P1_6       (0x06)
#define AMUX_P1_7       (0x07)
#define AMUX_P2_0       (0x08)
#define AMUX_P2_1       (0x09)
#define AMUX_P2_2       (0x0A)
#define AMUX_P2_3       (0x0B)
#define AMUX_P2_4       (0x0C)
#define AMUX_P2_5       (0x0D)
#define AMUX_P2_6       (0x0E)
#define AMUX_P2_7       (0x0F)
#define AMUX_P3_0       (0x10)
#define AMUX_TempSensor (0x1E) /* amx0p only */
#define AMUX_VDD        (0x1F) /* amx0p only */
#define AMUX_Vref       (0x1E) /* amx0n only */
#define AMUX_Gnd        (0x1F) /* amx0n only */

sfr adc0cn=0xE8; /* ADC0 Control Register */
#define AD0EN_Mask               (1<<7)
//sbit AD0EN=0xEF;
#define AD0TM_Mask               (1<<6)
//sbit AD0TM=0xEE;
#define AD0INT_Mask              (1<<5)
//sbit AD0INT=0xED;
#define AD0BUSY_Mask             (1<<4)
//sbit AD0BUSY=0xEC;
#define AD0WINT_Mask             (1<<3)
//sbit AD0WINT=0xEB;
#define AD0ConversionMode_Mask (((1<<3)-1)<<0)
/* when AD0TM==0: */
#define StartOnWrite1ToAD0BUSY   (0<<0)
#define StartOnTimer0Overflow    (1<<0)
#define StartOnTimer2Overflow    (2<<0)
#define StartOnTimer1Overflow    (3<<0)
#define StartOnExtCNVSTRRise     (4<<0)
#define StartOnTimer3Overflow    (5<<0)

sfr adc0cf=0xBC; /* ADC0 Configuration Register */
#define ADC0_SARConversionClockPeriod_Shift (3)
#define ADC0_LeftJustify_Mask               (1<<2)
#define CLKsar (3000000) /* max SAR conversion clock in Hz */

sfr ref0cn=0xD1; /* REF0CN Reference Control Register */
#define SelectVREFPinForRef  (0<<3)
#define SelectVDDForRef      (1<<3)
#define DisableIntTempSensor (0<<2)
#define EnableIntTempSensor  (1<<2)
#define DisableIntBiasGen    (0<<1)
#define EnableIntBiasGen     (1<<1)
#define DisableIntRefBuffer  (0<<0)
#define EnableIntRefBuffer   (1<<0)

sfr eie1=0xE6; /* EIE1 Extended Interrupt Enable 1
* for each bit, 0 disables interrupt; 1 enables interrupt */
sfr eip1=0xF6; /* EIP1 Extended Interrupt Priority 1
* for each bit, 0 makes interrupt low priority; 
*               1 makes interrupt high priority */
#define USBInterrupt_Mask       (1<<1)
#define DisableUSBInterrupt     (0<<1)
#define EnableUSBInterrupt      (1<<1)
#define I2cInterrupt_Mask       (1<<0)
#define DisableI2cInterrupt     (0<<0)
#define EnableI2cInterrupt      (1<<0)

sfr psctl=0x8F; /* PSCTL Program Store R/W Control */
#define PSWE_Mask               (1<<0)
#define PSEE_Mask               (1<<1)

sfr flkey=0xB7; /* FLKEY FLASH Lock and Key Register */
#define FlashWriteErase_Unlock1 (0xA5)
#define FlashWriteErase_Unlock2 (0xF1)
#define FlashLockStatus_Mask    ((1<<2)-1)
#define FlashIsWriteEraseLocked (0<<0)
#define FlashFirstKeyWritten    (1<<0)
#define FlashIsUnlocked         (2<<0)
#define FlashIsLocked           (3<<0)

sfr spi0config=0xA1; /* SPI0 Configuration Register */
#define SPI_Busy_Mask               (1<<7) /* RO */
#define SPI_MasterNotSlave_Mask     (1<<6) /* RW */
#define SPI_Master                  (1<<6)
#define SPI_Slave                   (0<<6)
#define SPI_CKPHA_Mask              (1<<5) /* RW */
#define SPI_CKPHA_0                 (0<<5)
#define SPI_CKPHA_1                 (1<<5)
#define SPI_CKPOL                   (1<<4) /* RW */
#define SPI_CKPOL_0                 (0<<4)
#define SPI_CKPOL_1                 (1<<4)
#define SPI_SlaveIsSelected_Mask    (1<<3) /* RO debounced !NSS */
#define SPI_RawNSS_Mask             (1<<2) /* RO undebounced NSS */
#define SPI_ShiftRegisterEmpty_Mask (1<<1) /* RO */
#define SPI_ReceiveBufferEmpty_Mask (1<<0) /* RO */

sfr spi0control=0xF8; /* SPI0 Control Register */
#define SPI_InterruptFlag_Mask      (1<<7)
#define SPI_WriteCollision_Mask     (1<<6)
#define SPI_ModeFault_Mask          (1<<5)
#define SPI_ReceiveOverrun_Mask     (1<<4)
#define SPI_Mode_Mask               (((1<<2)-1)<<2)
#define SPI_3WireMode                        (0<<2)
#define SPI_4WireSlaveOrMultiMaster          (1<<2)
#define SPI_4WireSingleMaster                (2<<2)
#define SPI_TransmitBufferEmpty_Mask (1<<1)
#define SPI_Enable_Mask             (1<<0)
#define SPI_Disable                 (0<<0)
#define SPI_Enable                  (1<<0)

sfr spi0clock=0xA2; /* SPI0 Clock Rate Register */
/* spi0ckr=(SYSCLK/(2*fsck) - 1)
*  fsck=SYSCLK/(2*(spi0ckr+1))
*
*  (where fsck is frequency for SCK)
*/

sfr spi0data=0xA3; /* SPI Data Register */

/* I2C (aka SMB) stuff */

/* BEWARE: 
*
* Although tmr2cn of Silabs 'F32x is at the same address as t2con of an 8032, 
* tmr2cn behaves differently from t2con. BEWARE! */
#define tmr2cn t2con

sfr i2cConfig =0xC1; /* I2C Clock/Configuration Register */
#define I2cEnable_Mask                       (1<<7)
#define I2cDisable                           (0<<7)
#define I2cEnable                            (1<<7)

#define I2cSlaveInhibit_Mask                 (1<<6)
#define I2cEnableSlaveModeInterrupts         (0<<6)
#define I2cDisableSlaveModeInterrupts        (1<<6)

#define I2cBusyNotIdle_Mask                  (1<<5)
#define I2cIdle                              (0<<5)
#define I2cBusy                              (1<<5)

#define I2cExtendedSetupHold_Mask            (1<<4)
#define I2cDisableExtendedSetupHold          (0<<4)
#define I2cEnableExtendedSetupHold           (1<<4)

#define I2cTimeout_Mask                      (1<<3)
#define I2cDisableTimeoutDetection           (0<<3)
#define I2cEnableTimeoutDetection            (1<<3)

#define I2cFreeTimeout_Mask                  (1<<2)
#define I2cDisableFreeTimeoutDetection       (0<<2)
#define I2cEnableFreeTimeoutDetection        (1<<2)

#define I2cClkSrc_Mask                       M(2,0)
#define I2cTimer0OverflowClockSource         (0<<0)
#define I2cTimer1OverflowClockSource         (1<<0)
#define I2cTimer2HighByteOverflowClockSource (2<<0)
#define I2cTimer2LowByteOverflowClockSource  (3<<0)

sfr i2cControl=0xC0; /* I2C Control Register */
sbit i2cIsMaster          =0xC7; /* RO */
sbit i2cIsTransmitter     =0xC6; /* RO */
sbit i2cStart             =0xC5;
sbit i2cStop              =0xC4;
sbit i2cAckIsRequested    =0xC3; /* RO */
sbit i2cArbitrationIsLost =0xC2; /* RO */
sbit i2cAck               =0xC1;
sbit i2cInterruptRequested=0xC0; /* set by hardware, must clear by software */
#define I2cIsMaster_Mask               (1<<7)
#define I2cIsTransmitter_Mask          (1<<6)
#define I2cStart_Mask                  (1<<5)
#define I2cStop_Mask                   (1<<4)
#define I2cAckIsRequested              (1<<3)
#define I2cArbitrationIsRequested_Mask (1<<2)
#define I2cAck_Mask                    (1<<1)
#define I2cInterruptRequested_Mask     (1<<0)

sfr i2cData   =0xC2; /* I2C Data Register */
#define I2cAddress_Mask      M(7,1)
#define I2cReadNotWrite_Mask M(1,0)

