/*
 *@File     : BitMask.cpp
 *@Author   : wangbo
 *@Date     : Jun 19, 2018
 *@Copyright: 2018 Beijing Institute of Technology. All rights reserved.
 *@Warning  : This content is limited to internal circulation, forbidding disclosure and for other commercial purposes.
 */

#include "Mask.h"

/*
 * 这是任务调度表，除了fast_loop中的任务，其他任务都在这里执行，任务最多255个
 * 第1个字段是task的函数名称
 * 第2个字段是该函数执行频率[hz]
 * 第3个字段是分配给该函数的最大可执行时间[us]
 * 每个任务都需要测试一下实际需要多长时间，如果大于每个tick所允许的剩余时间，就会出现Scheduler overrun task，剩余任务也就不会再执行
 * 因此需要特别注意串口读取 以及 udp读取等阻塞式的读取方式，阻塞等待的时间需要小于这个任务调度允许的最大时间
 * 必须保证每种频率下的所有函数的运行时间的和 是小于 scheduler的_loop_rate_hz所对应的时间
 * 比如当_loop_rate_hz = 100时，对应的时间是10ms，设定某个频率下的需要执行的函数个数是n
 * 则该相同频率下的 前(n-1)个函数的实际执行所需要时间的总和 加上 第n个函数所允许的最大执行时间 必须小于10ms
 */
#define SCHED_TASK(func) (void (*)())&Mask::func

const BIT_Scheduler::Task Mask::scheduler_tasks[] =
{
    { SCHED_TASK(get_gcs_udp),                                                 10,      300 },
    { SCHED_TASK(send_gcs_udp),                                                10,      200 },

    { SCHED_TASK(loop_1hz),                                                     1,      200 },
    { SCHED_TASK(loop_50hz),                                                   50,      200 },
    { SCHED_TASK(loop_100hz),                                                 100,      200 },

    { SCHED_TASK(get_timedata_now),                                             1,      350 },
    { SCHED_TASK(record_log),                                                   1,      200 },

    { SCHED_TASK(end_of_task),                                                  1,       10 }
};

int main(int argc,char * const argv[])
{
    DEBUG_PRINTF("Welcome to BitRobot \n");

    mask.scheduler.init(&mask.scheduler_tasks[0], sizeof(mask.scheduler_tasks) / sizeof(mask.scheduler_tasks[0]));
    DEBUG_PRINTF("There are %d tasks to run !!! \n", sizeof(mask.scheduler_tasks) / sizeof(mask.scheduler_tasks[0]));

    mask.setup();

    while(1)
    {
    	mask.loop();
    }

    return 0;
}








