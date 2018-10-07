/*
 *@File     : Bit_clock.cpp
 *@Author   : wangbo
 *@Date     : Jun 19, 2018
 *@Copyright: 2018 Beijing Institute of Technology. All rights reserved.
 *@Warning  : This content is limited to internal circulation, forbidding disclosure and for other commercial purposes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include "Bit_clock.h"

uint64_t clock_us()
{
    struct timespec current_time;

    clock_gettime(CLOCK_MONOTONIC, &current_time);

    return ((uint64_t)(current_time.tv_sec * 1e9) + (uint64_t)(current_time.tv_nsec)) / 1000;
}

uint64_t clock_ns()
{
	struct timespec current_time;

	clock_gettime(CLOCK_MONOTONIC, &current_time);

	return ((uint64_t)(current_time.tv_sec * 1e9) + (uint64_t)(current_time.tv_nsec));
}

void delay_ms(uint32_t ms)
{
    struct timeval delay;
    delay.tv_sec = 0;
    delay.tv_usec = ms * 1000;
    select(0, NULL, NULL, NULL, &delay);
}

void delay_us(uint32_t us)
{
    struct timeval delay;
    delay.tv_sec = 0;
    delay.tv_usec = us;
    select(0, NULL, NULL, NULL, &delay);
}

/*
 * 获取系统时间
 * 从UTC(coordinated universal time)时间
 * 1970年1月1日00时00分00秒(也称为Linux系统的Epoch时间)到当前时刻的秒数
 */
double gettimeofday_s()
{
    struct timeval current_time;

    gettimeofday(&current_time,NULL);

    return (current_time.tv_sec) * 1 + (current_time.tv_usec) * 1e-6;
}

double gettimeofday_ms()
{
    struct timeval current_time;

    gettimeofday(&current_time,NULL);

    return (current_time.tv_sec) * 1e3 + (current_time.tv_usec) * 1e-3;
}

double gettimeofday_us()
{
    struct timeval current_time;

    gettimeofday(&current_time,NULL);

    return (current_time.tv_sec) * 1e6 + (current_time.tv_usec) * 1;
}

/*
 * 从系统启动瞬间到当前时间所经过的时间[second]
 */
double clock_gettime_s()
{
    struct timespec current_time;

    clock_gettime(CLOCK_MONOTONIC, &current_time);

    return (current_time.tv_sec) * 1 + (current_time.tv_nsec) * 1e-9;
}

double clock_gettime_ms()
{
    double time_s = 0.0;

    time_s = clock_gettime_s();

    return time_s * 1e3;
}

double clock_gettime_us()
{
    double time_s = 0.0;

    time_s = clock_gettime_s();

    return time_s * 1e6;
}


