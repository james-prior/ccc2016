/* Modification History
* 2016-10-20 jep Stripped for CCC.
*/

#undef Global
#undef Init
#if defined(Uart_C)
#define Global
#define Init(x) =(x)
#else
#define Global extern
#define Init(x)
#endif

Global void putUartByte(byte c);
Global byte getUartByte(void);
Global void setUartBitRate(word bitRate);
Global void initializeUart(word bitRate);

