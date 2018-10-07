#ifndef BIT_PTHREAD_H_
#define BIT_PTHREAD_H_
/*
 *@File     : Bit_pthread.h
 *@Author   : wangbo
 *@Date     : Oct 7, 2018 10:15:46 PM
 *@Copyright: 2018 Beijing Institute of Technology. All rights reserved.
 *@Warning  : This content is limited to internal circulation, forbidding disclosure and for other commercial purposes.
 */

#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>



class Bit_Pthread
{
public:
	Bit_Pthread();
	Bit_Pthread(uint8_t priority);

	void pthread_init();

	void pthread_sem_post(); // 定时释放信号量

	// 封装线程 参考网址 https://www.cnblogs.com/shijingxiang/articles/5389294.html
	virtual void pthread_loop();

	void pthread_set_priority();

	// 设置优先级
	int get_thread_policy( pthread_attr_t &attr);
	void show_thread_priority( pthread_attr_t &attr, int policy);
	int get_thread_priority( pthread_attr_t &attr);
	void set_thread_policy( pthread_attr_t &attr, int policy );

public:
    sem_t task_sem;
    int task_sem_cnt;
	pthread_t task_pthread_ID;
	uint8_t task_priority;
	pthread_attr_t attr;

public:
	/*
	 * 这里写线程函数pthread_loop使用的变量
	 */
	uint32_t pthread_loop_cnt;
};





#endif /* BIT_PTHREAD_H_ */
