/*
 *@File     : Bit_thread.cpp
 *@Author   : wangbo
 *@Date     : Oct 7, 2018 10:16:07 PM
 *@Copyright: 2018 Beijing Institute of Technology. All rights reserved.
 *@Warning  : This content is limited to internal circulation, forbidding disclosure and for other commercial purposes.
 */


#include "Bit_pthread.h"

Bit_Pthread::Bit_Pthread()
{


}

Bit_Pthread::Bit_Pthread(uint8_t priority)
{
	task_priority = priority;

	// 保护一下
	if(task_priority < 10 )
	{
		task_priority = 10;
	}
	else if(task_priority > 90)
	{
		task_priority = 90;
	}
}

void Bit_Pthread::pthread_set_priority()
{
	// pthread_attr_t attr;
	struct sched_param param;
	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_RR);
	param.sched_priority = 10;
	// param.sched_priority = task_priority;
	pthread_attr_setschedparam(&attr, &param);
}

template <typename TYPE, void (TYPE::*pthread_loop)() >
void * pthread_task(void * param)
{

    TYPE *p=(TYPE*)param;

    p->pthread_loop();

    return NULL;
}

void Bit_Pthread::pthread_init()
{
	int ret;

	/*
	* 初始化快循环信号量
	*/
	sem_init(&task_sem, 0, 1);/*初始化时，信号量为1*/
	ret = pthread_create (&task_pthread_ID,          //线程标识符指针
						 NULL,                     //默认属性
						 pthread_task<Bit_Pthread, &Bit_Pthread::pthread_loop>,         //运行函数
						 (void *)this);                    //无参数
	if(0 != ret)
	{
		perror("pthread create error\n");
	}
}

void Bit_Pthread::pthread_sem_post()
{
	sem_getvalue(&task_sem, &task_sem_cnt);
	if(task_sem_cnt < 1)
	{
		sem_post(&task_sem);/*释放信号量*/
	}
}

//void Bit_Pthread::pthread_loop()
//{
//	printf("Enter the pthread_loop...\n");
//
//	while(1)
//	{
//		sem_wait(&task_sem);     /*等待信号量*/
//
//		pthread_loop_cnt++;
//		printf("Enter the pthread_loop pthread_loop_cnt = %d...\n", pthread_loop_cnt);
//	}
//}

void Bit_Pthread::pthread_loop()
{
//	printf("Enter the pthread_loop...\n");
//
//	while(1)
//	{
//		sem_wait(&task_sem);     /*等待信号量*/
//
//		pthread_loop_cnt++;
//		printf("Enter the pthread_loop pthread_loop_cnt = %d...\n", pthread_loop_cnt);
//	}
}



int Bit_Pthread::get_thread_policy( pthread_attr_t &attr )
{
	int policy;
	int rs = pthread_attr_getschedpolicy( &attr, &policy );
	assert( rs == 0 );
	switch ( policy )
	{
		case SCHED_FIFO:
		printf("policy = SCHED_FIFO \n");
		break;

		case SCHED_RR:
		printf("policy = SCHED_RR \n");
		break;

		case SCHED_OTHER:
		printf("policy = SCHED_OTHER");
		break;

		default:
		printf("policy = UNKNOWN");
		break;
	}

	return policy;
}

void Bit_Pthread::show_thread_priority( pthread_attr_t &attr, int policy )
{
	int priority = sched_get_priority_max( policy );
	assert( priority != -1 );
	printf("max_priority = %d \n", priority);

	priority = sched_get_priority_min( policy );
	assert( priority != -1 );
	printf("min_priority = %d \n", priority);
}

int Bit_Pthread::get_thread_priority( pthread_attr_t &attr )
{
	struct sched_param param;

	int rs = pthread_attr_getschedparam( &attr, &param );
	assert( rs == 0 );
	printf("priority = %d \n", param.__sched_priority);

	return param.__sched_priority;
}

void Bit_Pthread::set_thread_policy( pthread_attr_t &attr, int policy )
{
	int rs = pthread_attr_setschedpolicy( &attr, policy );
	assert( rs == 0 );
	get_thread_policy( attr );
}
















