#ifndef __GPIO_H
#define __GPIO_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED�˿ڶ���
#define LED0 PDout(0)	// DS0
#define LED1 PDout(1)	// DS1	 

void Gpio_Init(void);//��ʼ��		

void LED0_ON(void);
void LED0_OFF(void);

void LED1_ON(void);
void LED1_OFF(void);

#endif
