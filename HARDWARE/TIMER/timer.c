#include "timer.h"
#include "gpio.h"
#include "AD7175.h"
unsigned int Timer3_LED_Num;

volatile unsigned int Timer3_Usart1_Num;
volatile unsigned int Timer3_Usart2_Num;

volatile unsigned int Timer2_AD_time;

extern unsigned char AD1AD2_Start_Flag;

extern unsigned char Usart1_Res[Usart_Size];
extern unsigned char Usart2_Res[Usart_Size];
extern unsigned char Usart1_Res_Num;
extern unsigned char Usart2_Res_Num;


void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM2,DISABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
  Timer2_AD_time=0;
	
}
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	Timer3_LED_Num=0;
	Timer3_Usart1_Num=0;
	Timer3_Usart2_Num=0;
	
}


//��ʱ��2�жϷ�����
void TIM2_IRQHandler(void)     
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�        1s
	{
		
		if(Timer2_AD_time>0)
		{
//		Timer2_AD_time--;
			LED0=!LED0;
		}
		
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //����жϱ�־λ
}


//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)     
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�        5ms
	{
		Timer3_LED_Num++;
		Timer3_Usart1_Num++;
		Timer3_Usart2_Num++;
		if(Timer3_Usart1_Num>=50)
		{
			Timer3_Usart1_Num=0;
			if( (Usart1_Res[0]==0xaa)&&(Usart1_Res[5]==0xee))
			{
				if(Usart1_Res[1]==0xa1)    //����1����
				{
					  USART_ClearFlag(USART1,USART_FLAG_TC); 
					 	USART_SendData(USART1,0xa1);         //�򴮿�1��������
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ��� 
						AD7175_regs[IOCon_Register].value=0x080c;
						AD7175_AD1_WriteRegister(AD7175_regs[IOCon_Register]);//LED    00

					
				}
				if(Usart1_Res[1]==0x01)
				{
					AD1AD2_Start_Flag=1;
					Timer2_AD_time=Usart1_Res[2];
				}
				
				
			}
			memset(Usart1_Res,0,Usart_Size);
			Usart1_Res_Num=0;
			LED1=!LED1;
		}
		if(Timer3_Usart2_Num>=100)
		{
			Timer3_Usart2_Num=0;
			if( (Usart2_Res[0]==0xaa)&&(Usart2_Res[5]==0xee))
			{

				if(Usart2_Res[1]==0xa2)    //����2����
				{
						USART_ClearFlag(USART2,USART_FLAG_TC); 
					 	USART_SendData(USART2,0xa2);         //�򴮿�2��������
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ��� 
						AD7175_regs[IOCon_Register].value=0x080c;
						AD7175_AD2_WriteRegister(AD7175_regs[IOCon_Register]);//LED					 00
				}
				
			}
			memset(Usart2_Res,0,Usart_Size);
			Usart2_Res_Num=0;		
		}
		if(Timer3_LED_Num>=200)
		{
//			Timer3_LED_Num=0;
//			LED0=!LED0;
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}
