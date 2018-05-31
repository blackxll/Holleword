uint8_t receive_buff[QUEUE_SIZE] = { 0 };
uint8_t front = 0;
uint8_t rear = 0;

bool QueryPush(uint8_t dat)
{
    if (((front + 1) % QUEUE_SIZE) != rear)  //队列没满
    {
        receive_buff[front++] = dat;
        front %= QUEUE_SIZE;
        return TRUE;
    }
    else
        return FALSE;
}

bool QueryPop(uint8_t *dat)
{
    if (front != rear)       //队列不为空
    {
        *dat = receive_buff[rear++];
        rear %= QUEUE_SIZE;
        return TRUE;
    }
    return FALSE;
}
/*
Modbus一帧数据出栈
*/
bool PopFreame(uint8_t *buffer)
{
    uint8_t data = 0;
    uint8_t count = 0;
    while ((count < FREAME_SIZE) && QueryPop(&data))
    {
        buffer[count++] = data;
    }
    if (count != FREAME_SIZE)      
        return FALSE;
    else
    {
        count = 0;
        return TRUE;
    }
}


.h文件

#ifndef __QUEUE_H_
#define __QUEUE_H_

#include "stm8s.h"

#define QUEUE_SIZE 32           //需要定义的空间大小为帧大小*帧数，例如帧大小为8B共4帧则为32

bool QueryPush(uint8_t dat);
bool QueryPop(uint8_t *dat);
bool PopFreame(uint8_t *buffer);
#endif