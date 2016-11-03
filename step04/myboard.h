/* Registers definitions and other stuff particular to my board.
*
* Modification History 
*
* 2016-10-20 JEP Added definitions for UART.
* 2016-10-20 JEP Barest definitions to start with.
*/

#define Keil /* to work around compiler bugs and limitations */

#define UsingC8051F320 (True)
#define UsingC8051F340 (False)

#define Sysclk (6000000) /* in Hz */

#if Sysclk==6000000
#define Timer01Prescale (12) /* divisor */
#endif

#define UartBitRate (19200)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* Port 0 */
#define TXD_Mask          (1<<4) /* P0.4 DO   TXD (RXD at PC) */
#define RXD_Mask          (1<<5) /* P0.5 DI   RXD (TXD at PC) */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* Port 2 */
sbit led1Dark     =0xA3; /* DO; P2.3; 0==light   1==dark */

