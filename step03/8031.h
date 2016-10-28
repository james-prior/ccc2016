/* register definitions for _standard_ 8031/8032/8051/8052 MCUs
*
* Modification History
*
* 2009-09-02 JEP Created. 
*/

sfr p0=0x80;
sfr p1=0x90;
sfr p2=0xA0;
sfr p3=0xB0;
sbit p3_1=0xB1;
sbit p3_0=0xB0;
#define txd p3_1
#define rxd p3_0

sfr acc=0xE0;
sfr b  =0xF0;
sfr dpl=0x82;
sfr dph=0x83;
sfr psw=0xD0;
sfr sp =0x81;

sfr pcon=0x87;
#define Smod_Mask      (1<<7)
#define PowerDown_Mask (1<<1)
#define IdleMode_Mask  (1<<0)

sfr tcon=0x88;
sbit tf1=0x8F;
sbit tr1=0x8E;
sbit tf0=0x8D;
sbit tr0=0x8C;
sbit ie1=0x8B;
sbit it1=0x8A;
sbit ie0=0x89;
sbit it0=0x88;

sfr tmod=0x89;

sfr tl0=0x8A;
sfr th0=0x8C;
sfr tl1=0x8B;
sfr th1=0x8D;

/* UART */

sfr sbuf=0x99;
sfr scon=0x98;
#define UART8N1Mode          (1<<6)
#define UART9N1Mode          (3<<6)
#define MCE_Mask             (1<<5)
#define MCE_Disable          (0<<5)
#define MCE_Enable           (1<<5)
#define ReceiveEnable_Mask   (1<<4)
#define ReceiveEnable        (1<<4)
#define ReceiveDisable       (0<<4)
#define Tx9thBit_Mask        (1<<3)
#define Rx9thBit_Mask        (1<<2)
#define TxInterruptFlag_Mask (1<<1)
#define RxInterruptFlag_Mask (1<<0)
sbit ti    =0x99;
sbit ri    =0x98;

sfr ie=0xA8;
sbit ea =0xAF;
sbit et2=0xAD;
sbit es =0xAC;
sbit et1=0xAB;
sbit ex1=0xAA;
sbit et0=0xA9;
sbit ex0=0xA8;

sfr ip=0xB8;
sbit pt2=0xBD;
sbit ps =0xBC;
sbit pt1=0xBB;
sbit px1=0xBA;
sbit pt0=0xB9;
sbit px0=0xB8;

/* 8032/8052 only */
sfr t2con =0xC8;
sbit cpNotRl2=0xC8;
sbit cNotT2  =0xC9;
sbit tr2     =0xCA;
sbit exen2   =0xCB;
sbit tclk    =0xCC;
sbit rclk    =0xCD;
sbit exf2    =0xCE;
sbit tf2     =0xCF;
#define T2Overflowed_Mask       (1<<7)
#define T2NotOverflowed         (0<<7)
#define T2Overflowed            (1<<7)
#define T2ExtFlag_Mask          (1<<6)
#define T2ExtFlag_NotSet        (0<<6)
#define T2ExtFlag_Set           (1<<6)
#define RclkT2NotT1_Mask        (1<<5)
#define RclkT1                  (0<<5)
#define RclkT2                  (0<<5)
#define TclkT2NotT1_Mask        (1<<4)
#define TclkT1                  (0<<4)
#define TclkT2                  (0<<4)
#define T2ExtInEnable_Mask      (1<<3)
#define T2ExtInDisabled         (0<<3)
#define T2ExtInEnabled          (1<<3)
#define T2Run_Mask              (1<<2)
#define T2Run                   (1<<2)
#define T2Stop                  (0<<2)
#define T2CountNotTimer_Mask    (1<<1)
#define T2Count                 (1<<1)
#define T2Timer                 (0<<1)
#define T2CaptureNotReload_Mask (1<<0)
#define T2Capture               (1<<0)
#define T2Reload                (0<<0)

sfr rcap2l=0xCA;
sfr rcap2h=0xCB;
sfr tl2   =0xCC;
sfr th2   =0xCD;

