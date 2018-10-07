/*
 *@File     : Mask.cpp
 *@Author   : wangbo
 *@Date     : Jun 19, 2018
 *@Copyright: 2018 Beijing Institute of Technology. All rights reserved.
 *@Warning  : This content is limited to internal circulation, forbidding disclosure and for other commercial purposes.
 */

#include "Mask.h"

Mask mask;
Mask::Mask()
{

}

void Mask::setup( void )
{

}

#define US_PER_SECOND 1e6  // 1 second == 1e6 micro seconds
void Mask::loop( void )
{
    //DEBUG_PRINTF("time_available_usec = %d \n", scheduler.time_available_usec());
    wait_us(scheduler.time_available_usec());

    uint64_t timer = (uint64_t)Bit_Clock::clock_us(); //当前系统运行时间精确到微秒

    loop_fast(); // 优先级别最高的函数

    scheduler.tick(); // 告诉调度器scheduler一个tick已经过去了

    uint32_t loop_us = (uint32_t)(US_PER_SECOND / scheduler.get_loop_rate_hz()); // uint32 4294967295 最大4294.967295秒
    uint32_t time_available = loop_us - (uint32_t)( (uint64_t)Bit_Clock::clock_us() - (uint64_t)timer );

    // DEBUG_PRINTF("loop_fast   : time_available = %d \n", time_available);
    scheduler.run(time_available > loop_us ? 0u : time_available);
}

void Mask::loop_fast()
{

}

void Mask::get_gcs_udp()
{
//	Mask.update_key_board();
//    signal(SIGINT, set_all_servos_ready_due_to_kill);
}

void Mask::send_gcs_udp()
{

}

#define DIRECTION_TIME_DELAY 10
void Mask::loop_1hz()
{
	// DEBUG_PRINTF("Hello loop_1hz\n");
}

void Mask::loop_50hz()
{
    // DEBUG_PRINTF("Hello loop_50hz\n");
}

void Mask::loop_100hz()
{
    // DEBUG_PRINTF("Hello loop_1hz\n");
	// global_bool_Mask.cnt_100hz ++;
}

void Mask::get_timedata_now()
{
    struct tm *gbl_time_val;//全局时间变量，其它的时间都从这里取
    time_t timep;

    //获取系统时间
    time(&timep);
    gbl_time_val = localtime(&timep);
    mask.datetime_now.year = (unsigned short)(gbl_time_val->tm_year + 1900);
    mask.datetime_now.month = (unsigned char)(gbl_time_val->tm_mon + 1);
    mask.datetime_now.day = (unsigned char)gbl_time_val->tm_mday;
    mask.datetime_now.hour = (unsigned char)gbl_time_val->tm_hour;
    mask.datetime_now.minute = (unsigned char)gbl_time_val->tm_min;
    mask.datetime_now.second = (unsigned char)gbl_time_val->tm_sec;

    DEBUG_PRINTF("当前系统时间是:%d年%02d月%02d日%02d时%02d分%02d秒\n", mask.datetime_now.year, mask.datetime_now.month, mask.datetime_now.day, mask.datetime_now.hour, mask.datetime_now.minute, mask.datetime_now.second);
}

void Mask::record_log()
{
	//DEBUG_PRINTF("Hello record_log\n");
}

void Mask::end_of_task()
{
    //DEBUG_PRINTF("Hello end_of_task\n");
}

void Mask::wait_ms(int ms)
{
	Bit_Clock::delay_ms(ms);
}

void Mask::wait_us(uint32_t us)
{
	Bit_Clock::delay_us(us);
}

int8_t Mask::read_key_board()
{
	uint32_t time_out_us = 100;
	int fd = 0; // 标准输入是 0
	int retval;
	static fd_set rfds;
	struct timeval tv;
	int ret;
	tv.tv_sec = 0;  //set the rcv wait time
	tv.tv_usec = time_out_us;
	struct stat temp_stat;

	char get_char;

	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);

	if(-1==fstat(fd, &temp_stat))
	{
		printf("fstat %d error:%s",fd,strerror(errno));
	}

	retval = select(fd + 1, &rfds, NULL, NULL, &tv);//非堵塞模式读取串口数据

	if (retval == -1)
	{
		perror("select()");
		return -1;
	}
	else if (retval)
	{
		struct termios new_settings;
		struct termios stored_settings;
		tcgetattr(0,&stored_settings);
		new_settings = stored_settings;
		new_settings.c_lflag &= (~ICANON);
		new_settings.c_cc[VTIME] = 0;
		tcgetattr(0,&stored_settings);
		new_settings.c_cc[VMIN] = 1;
		tcsetattr(0,TCSANOW,&new_settings);

		ret = read(fd, &get_char, 1);

		if(ret != -1)
		{
			return get_char;
		}

		tcsetattr(0, TCSANOW, &stored_settings);
	}

	return 0;
}

void Mask::update_key_board()
{
	char get_char;

	get_char = read_key_board();

	if(get_char > 0)
	{
		if((get_char != '\r') && (get_char != '\n') && (get_char != '\b') && (get_char != ' '))
		{
			// printf("getchar = %c \n ", get_char);
			if(key_board_cnt < KEY_BOARD_LENGTH - 2)
			{
				key_board_in[key_board_cnt++] = get_char;
			}
			else
			{
				printf("输入字符太长 \n");
			}
		}
		else if(((get_char == '\r') || (get_char == '\n')) && (key_board_cnt != 0))
		{
			key_board_end = TRUE;
			key_board_in[key_board_cnt++] = '\0';
			key_board_cnt = 0;
			printf("key_board_in = %s \n", key_board_in);
		}
		else if(((get_char == '\r') || (get_char == '\n')) && (key_board_cnt == 0))
		{
			printf("请输入正确指令：start | over |");
			fflush(stdout);
		}
	}
	fflush(stdout);
}



