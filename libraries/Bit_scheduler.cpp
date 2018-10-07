/*
 *@File     : Bit_scheduler.cpp
 *@Author   : wangbo
 *@Date     : Jun 19, 2018
 *@Copyright: 2018 Beijing Institute of Technology. All rights reserved.
 *@Warning  : This content is limited to internal circulation, forbidding disclosure and for other commercial purposes.
 */

#include <stdio.h>
#include <string.h>

#include "Bit_clock.h" // 获取时间us ms s函数

#include "Bit_scheduler.h"

// 初始化调度任务表及其参数
void BIT_Scheduler::init(const BIT_Scheduler::Task *tasks, uint8_t num_tasks)
{
    _tasks = tasks;
    _num_tasks = num_tasks;  // 因为_num_tasks是uint8_t的 所以任务最多有255个 不要超出范围
    _last_run = new uint16_t[_num_tasks];
    memset(_last_run, 0, sizeof(_last_run[0]) * _num_tasks);
    _tick_counter = 0;
    _loop_rate_hz = 100; // 100hz 目前频率范围限制是1~1000hz 不要超出这个范围

    if(_num_tasks > 254)
    {
    	printf("There are too many tasks, please reset scheduler \n");
    }

    if(_loop_rate_hz > 1000)
    {
    	printf("the task scheduler is too fast, please reset the <_loop_rate_hz> \n");
    }
}

// 经过了一个tick
void BIT_Scheduler::tick(void)
{
    _tick_counter++;
}

/*
 * 执行一次tick
 * 这个会在最大允许时间内执行尽可能多的任务
 */
void BIT_Scheduler::run(uint32_t time_available)
{
    for (uint8_t i=0; i<_num_tasks; i++)
    {
        uint16_t dt = _tick_counter - _last_run[i];

        uint16_t interval_ticks = _loop_rate_hz / _tasks[i].rate_hz;
        if(interval_ticks < 1)
        {
            interval_ticks = 1;
        }
        else if(interval_ticks > 65534)
        {
        	interval_ticks = 65535;
        	printf("the task[%d] is too slow \n", i);
        }

        if (dt >= interval_ticks)
        {
            // 拷贝该第i个任务允许执行的时间
            memcpy(&_task_time_allowed, &_tasks[i].max_time_micros, sizeof(uint16_t));
            //printf("_tasks[%d].max_time_micros = %d \n", i, _tasks[i].max_time_micros);

            if (dt >= interval_ticks * 2)
            {
                printf("Scheduler slip task[%u] \n",(unsigned)i);// 说明应该执行该任务的但是错过了一次
            }

            if (_task_time_allowed <= time_available)
            {

                _task_time_started = (uint64_t)Bit_Clock::clock_us();
                _tasks[i].function();

                /*
                 * 记录该任务这一次执行时计数器tick的值
                 */
                _last_run[i] = _tick_counter;

                // 计算这个任务到底需要花了多少时间
                uint32_t time_taken = (uint64_t)Bit_Clock::clock_us() - _task_time_started;
                //printf("task [%2d]  time_taken    : =%d \n", i, time_taken);

                if (time_taken > _task_time_allowed)
                {
                    printf("Scheduler overrun task[%2u], time_taken is:%d \n", (unsigned)i, time_taken);
                    return;
                }
                if(time_taken >= time_available)
                {
                    //_spare_micros = 0;
                    _spare_micros = 10; // 按道理应该是不再等待的，因为这些任务加起来已经把所有的时间给用完了，但是为了保险起见我还是等待10us吧
                }
                time_available -= time_taken;
            }
        }
    } // for() end
    _spare_micros = time_available;
}

uint32_t BIT_Scheduler::time_available_usec(void)
{
    return _spare_micros;
}

uint16_t BIT_Scheduler::get_loop_rate_hz(void)
{
    if(_loop_rate_hz < 1)
    {
        return 1;
    }
    else if(_loop_rate_hz > 1000)
    {
        return 1000; // 最高1000hz
    }

    return _loop_rate_hz;
}


