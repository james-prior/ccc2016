/* Modification History
* 2016-10-20 jep Pruned for CCC.
*/

#define Uart_C
#include "misc.h"
#include "8031.h"
#include "slf32x.h"
#include "myboard.h"
#include "uart.h"

/*****************************************************************************/

void putUartByte(byte c)
{
   while (!ti)
      ;
   ti=False;
   sbuf=c;
}

/*****************************************************************************/

byte getUartByte(void)
{
   while (!ri)
      ;
   ri=False;

   return sbuf;
}

/*****************************************************************************/

void setUartBitRate(word bitRate /* unit is 1 bit per second */)
{
   idata byte i=-((Sysclk+(Timer01Prescale*2*(ulong)bitRate)/2/*rounding term*/)
   /                      (Timer01Prescale*2*(ulong)bitRate));
/*$$$ for Sysclk==22.1184MHz Timer01Prescale==48 bitRate==1200, 
* $$$ i should be 0x40 (-192) */
/*$$$ for Sysclk==22.1184MHz Timer01Prescale==48 bitRate==19200, 
* $$$ i should be 0xF4 (-12) */
/*$$$ for Sysclk==24MHz Timer01Prescale==48 
* $$$ and bitRate==1200  i should be -208.333 (0x30) (+0.16% bit rate error)
* $$$ and bitRate==9600  i should be  -26.042 (0xE6) (+0.16% bit rate error)
* $$$ and bitRate==19200 i should be  -13.021 (0xF3) (+0.16% bit rate error)
* $$$ and bitRate==38400 i should be   -6.510 (0xF9) (-6.99% bit rate error)
* $$$ The need to support 1200 for PnP, limits the bit rates to 19200, 
* $$$ when Sysclk is 24MHz. 
* $$$ for Sysclk==6MHz Timer01Prescale==12
* $$$ and bitRate==19200 i should be  -13.021 (0xF3) (+0.16% bit rate error)
* $$$ for Sysclk==3MHz Timer01Prescale==1
* $$$ and bitRate==19200 i should be  -78.125 (0xB2) (+0.16% bit rate error)
*/
#if 0
   /* for ordinary 8051 CPUS, (but not the Silicon Labs derivatives). */
   pcon|=Smod1_Mask; /* SMOD1=True; for faster baud rates */
#endif

   th1=i;
   tl1=i;
}

/*****************************************************************************/

void initializeUart(word bitRate)
{
   byte i;

   es=False;

   i=ckcon;
   i&=~(T1M_Mask|Timer01Prescale_Mask);
#if Timer01Prescale==12
   i|=PrescaleSysClkDiv12;
#else
   error missing code for Timer01Prescale
#endif
   ckcon=i;
   /* timer 1 8-bit auto-reload SYSCLK */
   et1=False;
   tr1=False;
   i=tmod;
   i=(i&~0xF0)|0x20;
   tmod=i;
   setUartBitRate(bitRate);
   tr1=True;

   scon=UART8N1Mode|MCE0|ReceiveEnable_Mask|TxInterruptFlag_Mask; /* 8N1 UART 
   * transmit flag primed */
   /* ` I sure hope that setting ti in software is OK */
   /* flush the receive buffer */
#if defined(Keil)
   acc= /* crappy Keil compiler can't do volatile registers */
#endif
   sbuf;
#if defined(Keil)
   acc= /* crappy Keil compiler can't do volatile registers */
#endif
   sbuf;
}

