#include "gpio.h"
#include "sys.h"
void Gpio_Init(void)
{    	

	
	
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOFʱ��

  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//LED0��LED1��ӦIO��
	//0 LED0  1 LED1
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO
	
	GPIO_SetBits(GPIOD,GPIO_Pin_0 | GPIO_Pin_1);//close leds
	

}
void LED0_ON(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_0); 
}

void LED0_OFF(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_0);	   
}

void LED1_ON(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_1); 
}
void LED1_OFF(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_1);	 
}
