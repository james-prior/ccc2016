/* Modification History
* 
* 2016-10-20 jep Send 'U' on UART.
* 2016-10-20 jep Start with almost barest minimum: Just toggle LED fast.
*/

#define Main_C
#include "misc.h"
#include "myboard.h"
#include "8051f3xx.h"
#include "slf32x.h"
#include "uart.h"
#include "main.h"

/*****************************************************************************/

void initializeOscillators(void)
{
   oscicn=IntOscEnable_Mask|IntOscDivideBy2;
   while (!(oscicn&IntOscReady_Mask))
      ;

   oscxcn=ExtOscDisabled;

   /* configure the 4* clock multiplier */
   clkmul=0; /* reset the multiplier */

   /* 4X multiplier will be low power, if multiplier has no input */
   clksel=USBClk4XMult    |SysClkIntOsc;
}

/*****************************************************************************/

void initialize(void)
{
   pca0md&=~WatchdogTimerEnable_Mask; /* disable watchdog */

   P0    =RXD_Mask|TXD_Mask;
   P0MDIN=RXD_Mask|TXD_Mask;
   P0MDOUT=TXD_Mask;

   /* The crossbar must be enabled and configured before digital peripherals 
   *  are enabled. */
   xbr0=UARTAtPin;
   xbr1=CrossbarEnabled;

   initializeOscillators();
   initializeUart(UartBitRate);

#if 1
   /* drivel to shut up whiny compiler */
   if (EA && !EA) {
      getUartByte();
   }
#endif
}

/*****************************************************************************/

void main(void)
{
   initialize();

   for (;;) {
      putUartByte('U');

      led1Dark=False;
      led1Dark=True;
   }
}

