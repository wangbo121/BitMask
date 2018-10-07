/*
 *@File     : Camera.cpp
 *@Author   : wangbo
 *@Date     : Oct 7, 2018 11:43:15 PM
 *@Copyright: 2018 Beijing Institute of Technology. All rights reserved.
 *@Warning  : This content is limited to internal circulation, forbidding disclosure and for other commercial purposes.
 */

#include "Mask.h"

#include "Camera.h"

void Camera::pthread_loop()
{
	printf("Enter the Camera::pthread_loop...\n");

	while(1)
	{
		sem_wait(&task_sem);     /*等待信号量*/

		pthread_loop_cnt++;
		printf("Enter the Camera::loop ---- pthread_loop_cnt = %d...\n", pthread_loop_cnt);

		// 接收和处理从Mask来的变量
		printf("Camera::loop    mask.cnt = %d \n", mask.datetime_now.year);
	}
}

void Camera::camera_init()
{

}
