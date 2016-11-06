/* Modification History
* 2016-10-21 jep Made interrupt driven version.
* 2016-10-20 jep Pruned for CCC.
*/

#define Uart_C
#include "misc.h"
#include "8031.h"
#include "slf32x.h"
#include "myboard.h"
#include "uart.h"

/* stuff enters queue at tail and leaves from head */

#define UartRxQLength ((byte)(1<<3))
Mutex static xdata byte uartRxQ[UartRxQLength];
Mutex static xdata byte uartRxQHead;
Mutex static xdata byte uartRxQTail;

#define UartTxQLength ((byte)(1<<5))
Mutex static xdata byte uartTxQ[UartTxQLength];
Mutex static xdata byte uartTxQHead;
Mutex static xdata byte uartTxQTail;
#if 0
Mutex static flag transmitterIsRunning=False; /* $$$ check code */
#else
Mutex static flag transmitterIsRunning; /* $$$ check code */
#endif

/*****************************************************************************/

void putUartByte(byte c)
{
   /* wait for room in uartTxQ */
#if 1 /* idata head and tail */
   for (;;) {
      es=False;
      if ((byte)(uartTxQHead-uartTxQTail-1)%UartTxQLength>0)
         break;
      es=True;
   }
   es=True;
#else
   while ((byte)(uartTxQHead-uartTxQTail-1)%UartTxQLength<=0)
      ;
#endif

   es=False;
   if (transmitterIsRunning) {
      uartTxQ[uartTxQTail%UartTxQLength]=c;
      uartTxQTail++;
   }
   else { /* prime the pump */
      sbuf=c;
      transmitterIsRunning=True;
   }
   es=True;
}

/******************************************************************************
* returns how many bytes are in transmit queue */

byte uartTxQHas(void)
{
   return ((byte)(uartTxQTail-uartTxQHead))%UartTxQLength;
}

/*****************************************************************************/

byte getUartByte(void)
{
   byte c;

#if 1 /* idata head and tail */
   for (;;) {
      es=False; /* disable serial interrupt */
      if ((byte)(uartRxQTail-uartRxQHead)%UartRxQLength>0)
         break;
      es=True; /* enable serial interrupts */
   }
   es=True; /* enable serial interrupts */
#else
   /* Note: because uartRxQHead and uartRxQTail are each only a byte long,
   *  interrupts do not have to be disabled.
   *  Nonetheless care is warranted.  */

   while ((byte)(uartRxQTail-uartRxQHead)%UartRxQLength==0)
      ;
#endif

#if 1 /* idata head and tail */
   es=False; /* disable serial interrupt */
#endif
   c=uartRxQ[uartRxQHead%UartRxQLength];
   uartRxQHead++;
#if 1 /* idata head and tail */
   es=True; /* enable serial interrupts */
#endif

   return c;
}

/******************************************************************************
* returns how many bytes are in receive queue */

byte uartRxQHas(void)
{
   return ((byte)(uartRxQTail-uartRxQHead))%UartRxQLength;
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

void uartInterruptHandler(void) interrupt 4
{
   if (ri) {
      if ((byte)(uartRxQHead-uartRxQTail-1)%UartRxQLength>0) {
         uartRxQ[uartRxQTail%UartRxQLength]=sbuf;
         ri=False;
         uartRxQTail++;
      }
      else { /* no room in uartRxQ, so throw away new byte */
#if defined(Keil)
         acc=/* compensate for Keil compiler's inability to do volatile regs */
#endif
         sbuf;
         ri=False;
      }
   }

   if (ti) {
      ti=False;
      if ((byte)(uartTxQTail-uartTxQHead)%UartTxQLength>0) {
         sbuf=uartTxQ[uartTxQHead%UartTxQLength];
         uartTxQHead++;
         transmitterIsRunning=True;
      }
      else
         transmitterIsRunning=False;
   }
}

/*****************************************************************************/

void initializeUart(word bitRate)
{
   byte i;

   es=False;

   i=ckcon;
   i&=~(T1M_Mask|Timer01Prescale_Mask);
#if Timer01Prescale==48
   i|=PrescaleSysClkDiv48;
#elif Timer01Prescale==12
   i|=PrescaleSysClkDiv12;
#elif Timer01Prescale==1
   i|=T1M_Mask;
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

#if 0
   rxd=1; /* float to allow UART to use this pin */
   txd=1; /* to allow UART to use this pin */
#endif
   scon=UART8N1Mode|MCE0|ReceiveEnable_Mask; /* 8N1 UART */
#if 0
   scon=0x50; /* plain old 8N1 UART, rx enabled */
#endif
   /* flush the receive buffer */
#if defined(Keil)
   acc= /* crappy Keil compiler can't do volatile registers */
#endif
   sbuf;
#if defined(Keil)
   acc= /* crappy Keil compiler can't do volatile registers */
#endif
   sbuf;
   uartRxQHead=uartRxQTail=0;
   uartTxQHead=uartTxQTail=0;
   transmitterIsRunning=False;

   ps=1; /* high priority */
   es=True;
}

