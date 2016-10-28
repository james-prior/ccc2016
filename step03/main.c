/* Modification History
* 
* 2016-10-20 jep Start with almost barest minimum: Just toggle LED fast.
*/

#define Main_C
#include "misc.h"
#include "myboard.h"
#include "8051f3xx.h"
#include "slf32x.h"
#include "main.h"

void main(void)
{
   pca0md&=~WatchdogTimerEnable_Mask; /* disable watchdog */

   xbr1=CrossbarEnabled;

   for (;;) {
      led1Dark=False;
      led1Dark=True;
   }
}

