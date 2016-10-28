/* Registers definitions and other stuff particular to my board.
*
* Modification History 
*
* 2016-10-20 JEP Barest definitions to start with.
*/

#define Keil /* to work around compiler bugs and limitations */

#define UsingC8051F320 (True)
#define UsingC8051F340 (False)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* Port 2 */
sbit led1Dark     =0xA3; /* DO; P2.3; 0==light   1==dark */

