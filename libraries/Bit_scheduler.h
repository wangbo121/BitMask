/*
 *@File     : Bit_scheduler.h
 *@Author   : wangbo
 *@Date     : Jun 19, 2018
 *@Copyright: 2018 Beijing Institute of Technology. All rights reserved.
 *@Warning  : This content is limited to internal circulation, forbidding disclosure and for other commercial purposes.
 */

#ifndef LIBRARIES_BIT_SCHEDULER_H_
#define LIBRARIES_BIT_SCHEDULER_H_

#include <stdint.h>

class BIT_Scheduler
{
public:
    typedef void (*task_fn_t) (void);

    struct Task
    {
        task_fn_t function;
        double     rate_hz;
        uint32_t  max_time_micros;
    };

    // 调度初始化，指定任务表的地址，明确有多少个任务
    void init(const Task *tasks, uint8_t num_tasks);

    // 主程序是个循环，每次循环称为一次tick，tick()函数每执行一次会把_tick_counter计数加1
    void tick(void);

    // 在time_available时间内执行任务调度表尽可能多的任务
    void run(uint32_t time_available);

    // return the number of microseconds available for the current task
    uint32_t time_available_usec(void);

    uint16_t get_loop_rate_hz(void);

private:
    // progmem list of tasks to run
    const struct Task *_tasks;

    // number of tasks in _tasks list
    uint8_t _num_tasks;

    // number of 'ticks' that have passed
    // number of times that tick() has been called
    uint16_t _tick_counter;

    // tick counter at the time we last ran each task
    uint16_t *_last_run;

    // number of microseconds allowed for the current task
    uint16_t _task_time_allowed;

    // the time in microseconds when the task started
    uint64_t _task_time_started;

    uint16_t _loop_rate_hz; // fastest freq is 1000hz

    uint32_t _spare_micros;
};

#endif /* LIBRARIES_BIT_SCHEDULER_H_ */


