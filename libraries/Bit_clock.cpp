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

Bit_Clock::Bit_Clock(void)
{

}

uint64_t Bit_Clock::clock_s()
{
    struct timespec current_time;

    clock_gettime(CLOCK_MONOTONIC, &current_time);

    return ((uint64_t)(current_time.tv_sec));
}

uint64_t Bit_Clock::clock_ms()
{
    struct timespec current_time;

    clock_gettime(CLOCK_MONOTONIC, &current_time);

    return ((uint64_t)(current_time.tv_sec * 1e3) + (uint64_t)(current_time.tv_nsec)) / 1000000;
}

uint64_t Bit_Clock::clock_us()
{
    struct timespec current_time;

    clock_gettime(CLOCK_MONOTONIC, &current_time);

    return ((uint64_t)(current_time.tv_sec * 1e9) + (uint64_t)(current_time.tv_nsec)) / 1000;
}

uint64_t Bit_Clock::clock_ns()
{
	struct timespec current_time;

	clock_gettime(CLOCK_MONOTONIC, &current_time);

	return ((uint64_t)(current_time.tv_sec * 1e9) + (uint64_t)(current_time.tv_nsec));
}

void Bit_Clock::delay_s(uint32_t s)
{
    struct timeval delay;
    delay.tv_sec = s;
    delay.tv_usec = 0;
    select(0, NULL, NULL, NULL, &delay);
}

void Bit_Clock::delay_ms(uint32_t ms)
{
    struct timeval delay;
    delay.tv_sec = 0;
    delay.tv_usec = ms * 1000;
    select(0, NULL, NULL, NULL, &delay);
}

void Bit_Clock::delay_us(uint32_t us)
{
    struct timeval delay;
    delay.tv_sec = 0;
    delay.tv_usec = us;
    select(0, NULL, NULL, NULL, &delay);
}



