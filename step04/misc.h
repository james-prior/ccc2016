/* Rather generic stuff for my style of coding. 
*
* Modification History
*
* 2016-10-20 JEP Added Stripped down to core.
*/

#define False (0)
#define True (!False)

#define ArrayLength(x) (sizeof(x)/sizeof(*(x)))

typedef unsigned char flag;
typedef unsigned char byte;
typedef unsigned int word;
typedef   signed int signedWord;
typedef unsigned long ulong;

#define Mutex /* comment indicating Mutex sensitive code or data */

#define M(x,y) (((1<<(x))-1)<<(y))
#define MsB(x) (((x)>>8)&((1<<8)-1)) /* most significant byte (of word) */
#define LsB(x) (((x)>>0)&((1<<8)-1)) /* least significant byte (of word) */

