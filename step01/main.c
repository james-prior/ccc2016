/* Modification History
* 
* 2016-10-20 jep Start with almost barest minimum: Just toggle LED fast.
*/

#define False (0)
#define True (!False)

/* Silicon Laboratories C8051F321 registers
*  see http://www.keil.com/dd/docs/datashts/silabs/c8051f32x.pdf */

sfr xbr1=0xE2; /* Port I/O Crossbar Register 1 */
#define CrossbarEnabled     (1<<6)

/* particular to this board */

sbit led1Dark     =0xA3; /* DO; P2.3; 0==light   1==dark */

void main(void)
{
   xbr1=CrossbarEnabled;

   for (;;) {
      led1Dark=False;
      led1Dark=True;
   }
}

