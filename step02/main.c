/* Modification History
* 
* 2016-10-20 jep Start with almost barest minimum: Just toggle LED fast.
*/

#define False (0)
#define True (!False)

/* Silicon Laboratories C8051F321 registers
*  see http://www.keil.com/dd/docs/datashts/silabs/c8051f32x.pdf */

sfr pca0md=0xD9; /* PCA Mode Register */
#define WatchdogTimerEnable_Mask (1<<6)

sfr xbr1=0xE2; /* Port I/O Crossbar Register 1 */
#define CrossbarEnabled     (1<<6)

/* particular to this board */

sbit led1Dark     =0xA3; /* DO; P2.3; 0==light   1==dark */

void main(void)
{
   pca0md&=~WatchdogTimerEnable_Mask; /* disable watchdog */

   xbr1=CrossbarEnabled;

   for (;;) {
      led1Dark=False;
      led1Dark=True;
   }
}

