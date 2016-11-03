/* Modification History
*
* 2016-10-20 jep First version for CCC.
*/

#undef Global
#undef Init
#if defined(Main_C)
#define Global
#define Init(x) =(x)
#else
#define Global extern
#define Init(x)
#endif

