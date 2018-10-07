/*
 *@File     : Mask.h
 *@Author   : wangbo
 *@Date     : Jun 19, 2018
 *@Copyright: 2018 Beijing Institute of Technology. All rights reserved.
 *@Warning  : This content is limited to internal circulation, forbidding disclosure and for other commercial purposes.
 */
#ifndef MASK_H_
#define MASK_H_

//C标准头文件
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>//创建文件
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <termio.h>
#include <errno.h>
#include <math.h>
#include <signal.h>

//自定义库文件
#include "Bit_scheduler.h"
#include "Bit_clock.h"

#include "global.h"

#include "Bit_pthread.h"
#include "Camera.h"

#define KEY_BOARD_LENGTH 10 // 键盘输入指令必须小于 KEY_BOARD_LENGTH-2 个字符

typedef struct T_DateTime
{
	unsigned short year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	unsigned char stuffing;//填充字节，保证数据包字节数为4的整数倍
}T_DATETIME;

class Mask
{
public:
	Mask();

public:
    BIT_Scheduler scheduler;
    static const BIT_Scheduler::Task scheduler_tasks[];

    void setup();
    void loop();
    void loop_fast();

public:
    /*
     * 这块放静态函数-能够被任务调度表调用
     */
    static void get_gcs_udp(); // 通过udp获取地面站发送的命令
    static void send_gcs_udp(); // 通过udp发送数据给地面站

    static void loop_1hz();
    static void loop_50hz();
    static void loop_100hz();

    static void get_timedata_now();// 获取当前的时间，包含年月日时分秒的
    static void record_log(); // 记录日志

    static void end_of_task();

public:
    T_DATETIME datetime_now;//当前的日期和时间，精确到秒。在主线程中每秒更新一次，其它程序直接使用即可。

public:
    /*
     * 这块放Mask类的内部函数
     */
    void wait_ms(int ms); // 等待时间[ms]
    void wait_us(uint32_t us); // 等待时间[us]

public:
    /*
     * 读取键盘输入数据相关
     */
    int8_t read_key_board();
    void update_key_board();
    char key_board_in[KEY_BOARD_LENGTH];
	uint8_t key_board_cnt;
	uint8_t key_board_end;

public:
	static void return_to_init_state(int sig);

public:
	/*
	 * 创建线程相关
	 */
	// Bit_Pthread *thread_camera; // 请勿删除
	Camera thread_camera;
};

extern Mask mask;

#endif /* MASK_H_ */


