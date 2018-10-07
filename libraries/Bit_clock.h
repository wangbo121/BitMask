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
uint64_t clock_us();
uint64_t clock_ns(); // 纳秒

void delay_ms(uint32_t ms);
void delay_us(uint32_t us);

#endif /* LIBRARIES_BIT_CLOCK_H_ */


