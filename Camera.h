#ifndef CAMERA_H_
#define CAMERA_H_
/*
 *@File     : Camera.h
 *@Author   : wangbo
 *@Date     : Oct 7, 2018 11:43:05 PM
 *@Copyright: 2018 Beijing Institute of Technology. All rights reserved.
 *@Warning  : This content is limited to internal circulation, forbidding disclosure and for other commercial purposes.
 */

#include "Bit_pthread.h"

class Camera : public Bit_Pthread
{
public:
	Camera(){}

public:
    void pthread_loop();

    /*
     * 下面是Camera这个类自己的函数
     */
public:
    void camera_init();
};

#endif /* CAMERA_H_ */
