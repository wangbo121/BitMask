/*
 *@File     : global.h
 *@Author   : wangbo
 *@Date     : Jun 19, 2018
 *@Copyright: 2018 Beijing Institute of Technology. All rights reserved.
 *@Warning  : This content is limited to internal circulation, forbidding disclosure and for other commercial purposes.
 */
#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdint.h>

/*
 * 简单打印调试信息
 * 如果不想打印信息，就将这句代码注释掉
 */
#define DEBUG_SWITCH   1

#ifdef  DEBUG_SWITCH
#define DEBUG_PRINTF(fmt,args...) printf(fmt, ##args)
#else
#define DEBUG_PRINTF(fmt,args...) /*do nothing */
#endif

// mark a function as not to be inlined
#define NOINLINE __attribute__((noinline))

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef M_E
#define M_E        2.71828182845904523536  /* 自然数 */
#endif
#ifndef M_PI
#define M_PI       3.14159265358979323846  /* pi */
#endif
#ifndef M_1_PI
#define M_1_PI      0.31830988618379067154  /* 1/pi */
#endif

class GLOBAL_BOOL_MASK
{
public:
	uint32_t cnt_100hz;
	uint32_t cnt_50hz;
	uint32_t cnt_1hz;
};

extern GLOBAL_BOOL_MASK global_bool_mask;

#endif /* GLOBAL_H_ */


