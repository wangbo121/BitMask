/*
 *@File     : Bit_clock.h
 *@Author   : wangbo
 *@Date     : Jun 19, 2018
 *@Copyright: 2018 Beijing Institute of Technology. All rights reserved.
 *@Warning  : This content is limited to internal circulation, forbidding disclosure and for other commercial purposes.
 */

#ifndef LIBRARIES_BIT_CLOCK_H_
#define LIBRARIES_BIT_CLOCK_H_

#include <stdint.h>

/*
 * 此文件所有函数
 * 当在Linux系统下的实现时
 * 在编译链接时需加上 -lrt
 */
class Bit_Clock
{
public:
	Bit_Clock(void);

	/*
	 * 从系统启动瞬间到当前时间所经过的时间[s]
	 */
	static uint64_t clock_s();
	static uint64_t clock_ms();
	static uint64_t clock_us();
	static uint64_t clock_ns();

	static void delay_s(uint32_t s);
	static void delay_ms(uint32_t ms);
	static void delay_us(uint32_t us);
};

#endif /* LIBRARIES_BIT_CLOCK_H_ */


