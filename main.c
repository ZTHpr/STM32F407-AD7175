#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "gpio.h"
#include "AD7175.h"
#include "main.h"
#include "dma.h"
#include "PGA281.h"
#include "timer.h"

#define SEND_BUF_SIZE (10)	//�������ݳ���
u8 SendBuff_AD1[SEND_BUF_SIZE];	//�������ݻ�����
u8 SendBuff_AD2[SEND_BUF_SIZE];

uint32_t AD_Value;   //��ת���� 
float AD1_Transit_Value;   //��ת���� 
float AD2_Transit_Value;   //��ת���� 
int32_t AD1_Data[Data_Number];
float AD1_Value[Data_Number];
int32_t AD2_Data[Data_Number];
float AD2_Value[Data_Number];

unsigned int Ave_Num;

volatile unsigned char AD1AD2_Start_Flag;
extern unsigned int Timer2_AD_time;

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		  //��ʼ����ʱ����
	TIM3_Int_Init(500-1,840-1);	//��ʱ��ʱ��84M����Ƶϵ��840������84M/840=100Khz�ļ���Ƶ�ʣ�����500��Ϊ500ms
  TIM2_Int_Init(10000-1,8400-1);  // 1s��ʱ��	
	uart_U1_init(115200);	//���ڳ�ʼ��������Ϊ115200
	uart_U2_init(115200);	//���ڳ�ʼ��������Ϊ115200
	MYDMA_Config(DMA2_Stream7,DMA_Channel_4,(u32)&USART1->DR,(u32)SendBuff_AD1,SEND_BUF_SIZE);//DMA2,USART1.
	MYDMA_Config(DMA1_Stream6,DMA_Channel_4,(u32)&USART2->DR,(u32)SendBuff_AD2,SEND_BUF_SIZE);//DMA1,USART2
	Gpio_Init();		        //��ʼ��LED�˿�	
	AD_1_Init();
	AD_2_Init();
	AD7175_AD1_Init_Offset(&AD1_Offset,&AD1_Gain);   //��У׼ ���²���
	AD7175_AD2_Init_Offset(&AD2_Offset,&AD2_Gain);   //��У׼ ���²���
  PGA1_Init();
  PGA2_Init();
	PGA1_SetGain(Gain__0p125);
  PGA2_SetGain(Gain__0p125);
	while(1)
	{

		if(AD1AD2_Start_Flag)
		{
			Ave_Num=(unsigned int)((2500*Timer2_AD_time)/6000);
			if(Ave_Num<1)  Ave_Num=1;
//			if(Timer2_AD_time<=2)
//			{
//				AD7175_regs[Filter_Config_1].value=0x0509;
//				AD7175_AD1_WriteRegister(AD7175_regs[Filter_Config_1]);//2500sps
//				AD7175_AD2_WriteRegister(AD7175_regs[Filter_Config_1]);//2500sps
//			}
//			else if(Timer2_AD_time<=5)
//			{
//				AD7175_regs[Filter_Config_1].value=0x050a;
//				AD7175_AD1_WriteRegister(AD7175_regs[Filter_Config_1]);//1000sps
//				AD7175_AD2_WriteRegister(AD7175_regs[Filter_Config_1]);
//			}
//			else if(Timer2_AD_time<=10)
//			{
//				AD7175_regs[Filter_Config_1].value=0x050b;
//				AD7175_AD1_WriteRegister(AD7175_regs[Filter_Config_1]);//500sps
//				AD7175_AD2_WriteRegister(AD7175_regs[Filter_Config_1]);
//			}
//			else if(Timer2_AD_time<=25)
//			{
//				AD7175_regs[Filter_Config_1].value=0x050d;
//				AD7175_AD1_WriteRegister(AD7175_regs[Filter_Config_1]);//200sps
//				AD7175_AD2_WriteRegister(AD7175_regs[Filter_Config_1]);
//			}
//			else if(Timer2_AD_time<=50)
//			{
//				AD7175_regs[Filter_Config_1].value=0x050e;
//				AD7175_AD1_WriteRegister(AD7175_regs[Filter_Config_1]);//100sps
//				AD7175_AD2_WriteRegister(AD7175_regs[Filter_Config_1]);
//			}
//			else if(Timer2_AD_time<=120)
//			{
//				AD7175_regs[Filter_Config_1].value=0x0510;
//				AD7175_AD1_WriteRegister(AD7175_regs[Filter_Config_1]);//49.96sps
//				AD7175_AD2_WriteRegister(AD7175_regs[Filter_Config_1]);
//			}
//			else if(Timer2_AD_time<=250)
//			{
//				AD7175_regs[Filter_Config_1].value=0x0511;
//				AD7175_AD1_WriteRegister(AD7175_regs[Filter_Config_1]);//20sps
//				AD7175_AD2_WriteRegister(AD7175_regs[Filter_Config_1]);
//			}
//			else 
//			{
//				AD7175_regs[Filter_Config_1].value=0x0512;
//				AD7175_AD1_WriteRegister(AD7175_regs[Filter_Config_1]);//16.66sps
//			}
//			delay_ms(1000);
			AD1AD2_Send_Date();
			AD1AD2_Start_Flag=0;

		}
	}
}


void AD1AD2_Send_Date(void)
{
	int32_t ret,i,j;
	unsigned char cha[10]= {0,0,0,0,0,0,0,0,0,0};
	unsigned long value;
	memset(&AD1_Value, 0, Data_Number*sizeof(float));         //�������
	memset(&AD1_Data, 0, Data_Number*sizeof(int32_t));         //�������
	memset(&AD2_Value, 0, Data_Number*sizeof(float));         //�������
	memset(&AD2_Data, 0, Data_Number*sizeof(int32_t));         //�������
	USART_ClearFlag(USART1,USART_FLAG_TC); 
	USART_ClearFlag(USART2,USART_FLAG_TC); 
//	USART_SendData(USART1,'A');          //�򴮿�1��������
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ��� 
//	USART_SendData(USART2,'A');          //�򴮿�2��������
//	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���	
//	USART_SendData(USART1,'D');         //�򴮿�1��������
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
//	USART_SendData(USART2,'D');         //�򴮿�2��������
//	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
//	USART_SendData(USART1,'1');         //�򴮿�1��������
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
//	USART_SendData(USART2,'2');         //�򴮿�2��������
//	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
//	USART_SendData(USART1,0x0a);         //�򴮿�1��������
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
//	USART_SendData(USART2,0x0a);         //�򴮿�2��������
//	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
	AD1_CS_0();  //Ƭѡѡ��
	AD2_CS_0();
	delay_ms(500);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM2,ENABLE); //ʧ���ܶ�ʱ��3
	for(i=0;i<Data_Number;i++)
		{
		for(j=0;j<Ave_Num;j++)
		{
    AD1_SYNC_1();AD2_SYNC_1();  //AD1AD2ͬʱ��ʼת����ͬʱ����SYNC
		while( (AD1_DOUT()==1) | (AD1_DOUT()==1) );  //AD1��AD2 ���ݾ���
		ret = AD7175_AD1_ReadRegister(&AD7175_regs[Data_Register]); //AD1�ɼ�

	  AD_Value  =AD7175_regs[Data_Register].value>>8;
		AD_Value  =AD_Value & 0x00ffffff;
		AD1_Data[i]=AD1_Data[i]+(uint32_t)(AD_Value/Ave_Num);    //��ֵ
		
		ret = AD7175_AD2_ReadRegister(&AD7175_regs[Data_Register]);  //AD2�ɼ�
	
	  AD_Value  =AD7175_regs[Data_Register].value>>8;
		AD_Value  =AD_Value & 0x00ffffff;
		AD2_Data[i]  =AD2_Data[i]+(uint32_t)(AD_Value/Ave_Num);   //��ֵ
		
		AD1_SYNC_0();AD2_SYNC_0();  //AD1AD2ͬʱ��ʼת����ͬʱ����SYNC
		}
		if(BIPOLAR)
		{
			AD1_Value[i] = ( ((float)AD1_Data[i]-0x800000)*(0x400000/(float)AD1_Gain)
										+ ((float)AD1_Offset-0x800000) ) 
											* (float)(Vref/((float)Date_24*0.75)) *RATIO;
			AD2_Value[i] = ( ((float)AD2_Data[i]-0x800000)*(0x400000/(float)AD2_Gain)
										+ ((float)AD2_Offset-0x800000) ) 
											* (float)(Vref/((float)Date_24*0.75)) *RATIO;
		}
		else
		{
			if(i==0)
			{
			AD1_Value[i] = ( ((float)AD1_Data[i])*(0x400000/ (2*(float)AD1_Gain))
										+ ((float)AD1_Offset-0x800000) ) 
											* (float)(Vref/((float)Date_24*0.75))  *RATIO;
			AD2_Value[i] = ( ((float)AD2_Data[i])*(0x400000/ (2*(float)AD2_Gain))
										+ ((float)AD2_Offset-0x800000) ) 
											* (float)(Vref/((float)Date_24*0.75))  *RATIO;		
			}							
			else
			{
				AD1_Value[i] = (
														( ((float)AD1_Data[i])*(0x400000/ (2*(float)AD1_Gain))
														+ ((float)AD1_Offset-0x800000) ) 
											* (float)(Vref/((float)Date_24*0.75))  *RATIO
												)*0.5
											+AD1_Value[i-1]*0.5;
			  AD2_Value[i] = (
											( ((float)AD2_Data[i])*(0x400000/ (2*(float)AD2_Gain))
										+ ((float)AD2_Offset-0x800000) ) 
											* (float)(Vref/((float)Date_24*0.75))  *RATIO
												)*0.5
											+AD2_Value[i-1]*0.5 ;		                                         //һ�������˲�
			}
		}
		
		if(Timer2_AD_time==0)
		{
//			break;  //ʱ�䵽 �˳�
		}
			

		}
		Timer2_AD_time=0;
    
 
			for(i=0;i<Data_Number;i++)
		{
			if(BIPOLAR)
			{
				//AD1���ݷ���
				if(AD1_Value[i]<0) 
				{
					cha[0]='-'-'0';
					value=(unsigned long)(( (-AD1_Value[i])*1000000 + 0.5));
				}
				else
				{
					cha[0]='+'-'0';
					value=(unsigned long)(( (AD1_Value[i])*1000000 + 0.5));
				}
				cha[1]=value/10000000;
				cha[2]=(value%10000000)/1000000;
				cha[3]='.'-'0';
				cha[4]=(value%1000000)/100000;
				cha[5]=(value%100000)/10000;
				cha[6]=(value%10000)/1000;
				cha[7]=(value%1000)/100;
				cha[8]=(value%100)/10;
				cha[9]=(value%10);
				for(j=0;j<10;j++)
			{
				SendBuff_AD1[i*11+j]=cha[j]+'0';	 
			}
			  SendBuff_AD1[i*11+10]=0x0a;   //����
	
			//AD2����
			if(AD2_Value[i]<0) 
				{
					cha[0]='-'-'0';
					value=(unsigned long)(( (-AD2_Value[i])*1000000 + 0.5));
				}
				else
				{
					cha[0]='+'-'0';
					value=(unsigned long)(( (AD2_Value[i])*1000000 + 0.5));
				}
				cha[1]=value/10000000;
				cha[2]=(value%10000000)/1000000;
				cha[3]='.'-'0';
				cha[4]=(value%1000000)/100000;
				cha[5]=(value%100000)/10000;
				cha[6]=(value%10000)/1000;
				cha[7]=(value%1000)/100;
				cha[8]=(value%100)/10;
				cha[9]=(value%10);
				for(j=0;j<10;j++)
			{
				SendBuff_AD2[i*11+j]=cha[j]+'0';
				USART_SendData(USART2,cha[j]+'0');         //�򴮿�2��������
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  		 
			}
			SendBuff_AD2[i*11+10]=0x0a;   //����
			USART_SendData(USART2,0x0a);         //�򴮿�2��������
			while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
			}
			else
			{
				//AD1����
				value=(unsigned long)(AD1_Value[i]*1000000 + 0.5);
				cha[0]=value/10000000;
				cha[1]=(value%10000000)/1000000;
				cha[2]='.'-'0';
				cha[3]=(value%1000000)/100000;
				cha[4]=(value%100000)/10000;
				cha[5]=(value%10000)/1000;
				cha[6]=(value%1000)/100;
				cha[7]=(value%100)/10;
				cha[8]=(value%10);
				for(j=0;j<9;j++)
				{
					SendBuff_AD1[j]=cha[j]+'0';  		 
				}
				SendBuff_AD1[9]=0x0a;   //����
				USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //ʹ�ܴ���1��DMA����     
				MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //��ʼһ��DMA���䣡	
   		
				//AD2����
				value=(unsigned long)(AD2_Value[i]*1000000 + 0.5);
				cha[0]=value/10000000;
				cha[1]=(value%10000000)/1000000;
				cha[2]='.'-'0';
				cha[3]=(value%1000000)/100000;
				cha[4]=(value%100000)/10000;
				cha[5]=(value%10000)/1000;
				cha[6]=(value%1000)/100;
				cha[7]=(value%100)/10;
				cha[8]=(value%10);
				for(j=0;j<9;j++)
				{
					SendBuff_AD2[j]=cha[j]+'0';	 
				}
				SendBuff_AD2[9]=0x0a;   //����
				USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);  //ʹ�ܴ���1��DMA����     
				MYDMA_Enable(DMA1_Stream6,SEND_BUF_SIZE);     //��ʼһ��DMA����
				 while(1)
		    {
					if((DMA_GetFlagStatus(DMA1_Stream6,DMA_FLAG_TCIF6)!=RESET)
							&(DMA_GetFlagStatus(DMA2_Stream7,DMA_FLAG_TCIF7)!=RESET))//�ȴ�DMA1_Steam6�������
					{ 
						DMA_ClearFlag(DMA1_Stream6,DMA_FLAG_TCIF6);//���DMA1_Steam6������ɱ�־
						DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);//���DMA2_Steam7������ɱ�־
						break; 
					}
				}			
			}	
		}
		AD1_CS_1();
		AD2_CS_1();    //Ƭѡ����
    TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE); //����ʱ��3�����ж�
	  TIM_Cmd(TIM2,DISABLE); //ʹ�ܶ�ʱ��3
}

void AD1_Send_Date(void)
{
  	int32_t ret,i,j;
	  unsigned char cha[10]= {0,0,0,0,0,0,0,0,0,0};
		unsigned long value;
		
		memset(&AD1_Value, 0, Data_Number);         //�������

		memset(&AD1_Data, 0, Data_Number);         //�������
    AD1_CS_0();
		USART_SendData(USART1,'A');          //�򴮿�1��������
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
		USART_SendData(USART1,'D');         //�򴮿�1��������
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
		USART_SendData(USART1,'1');         //�򴮿�1��������
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
		USART_SendData(USART1,0x0a);         //�򴮿�1��������
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
		delay_ms(500);
		for(i=0;i<Data_Number;i++)
		{

			while(AD1_DOUT()==1);
		
		ret = AD7175_AD1_ReadRegister(&AD7175_regs[Data_Register]);
	  AD1_Data[i]  =AD7175_regs[Data_Register].value>>8;
		AD1_Data[i]  =AD1_Data[i] & 0x00ffffff;
		if(BIPOLAR)
		{
			AD1_Value[i] = ( ((float)AD1_Data[i]-0x800000)*(0x400000/(float)AD1_Gain)
										+ ((float)AD1_Offset-0x800000) ) 
											* (float)(Vref/((float)Date_24*0.75)) *RATIO;
		}
		else
		{
			AD1_Value[i] = ( ((float)AD1_Data[i])*(0x400000/ (2*(float)AD1_Gain))
										+ ((float)AD1_Offset-0x800000) ) 
											* (float)(Vref/((float)Date_24*0.75))  *RATIO;
		}
			
				
		}


			for(i=0;i<Data_Number;i++)
		{
			if(BIPOLAR)
			{
				if(AD1_Value[i]<0) 
				{
					cha[0]='-'-'0';
					value=(unsigned long)(( (-AD1_Value[i])*1000000 + 0.5));
				}
				else
				{
					cha[0]='+'-'0';
					value=(unsigned long)(( (AD1_Value[i])*1000000 + 0.5));
				}
				cha[1]=value/10000000;
				cha[2]=(value%10000000)/1000000;
				cha[3]='.'-'0';
				cha[4]=(value%1000000)/100000;
				cha[5]=(value%100000)/10000;
				cha[6]=(value%10000)/1000;
				cha[7]=(value%1000)/100;
				cha[8]=(value%100)/10;
				cha[9]=(value%10);
				for(j=0;j<10;j++)
			{
				USART_SendData(USART1,cha[j]+'0');         //�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  		 
			}
			}
			else
			{
				value=(unsigned long)(AD1_Value[i]*1000000 + 0.5);
				cha[0]=value/10000000;
				cha[1]=(value%10000000)/1000000;
				cha[2]='.'-'0';
				cha[3]=(value%1000000)/100000;
				cha[4]=(value%100000)/10000;
				cha[5]=(value%10000)/1000;
				cha[6]=(value%1000)/100;
				cha[7]=(value%100)/10;
				cha[8]=(value%10);
				for(j=0;j<9;j++)
			{
				USART_SendData(USART1,cha[j]+'0');         //�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  		 
			}
			}
			USART_SendData(USART1,0x0a);         //�򴮿�1��������
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
		//	delay_ms(10);	
		}
		AD1_CS_1();
}

void AD2_Send_Date(void)
{
  	int32_t ret,i,j;
	  unsigned long value;
	  unsigned char cha[10]= {0,0,0,0,0,0,0,0,0,0};
		
		
  	memset(&AD2_Value, 0, Data_Number);         //�������
	
  	memset(&AD2_Data, 0, Data_Number);         //�������
		
		AD2_CS_0();
		USART_SendData(USART1,'A');          //�򴮿�1��������
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
		USART_SendData(USART1,'D');         //�򴮿�1��������
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
		USART_SendData(USART1,'2');         //�򴮿�1��������
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
		USART_SendData(USART1,0x0a);         //�򴮿�1��������
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
		delay_ms(500);
		for(i=0;i<Data_Number;i++)
		{

			while(AD2_DOUT()==1);
		
		ret = AD7175_AD2_ReadRegister(&AD7175_regs[Data_Register]);
	  AD2_Data[i]  =AD7175_regs[Data_Register].value>>8;
		AD2_Data[i]  =AD2_Data[i] & 0x00ffffff;
		if(BIPOLAR)
		{
			AD2_Value[i] = ( ((float)AD2_Data[i]-0x800000)*(0x400000/(float)AD2_Gain)
										+ ((float)AD2_Offset-0x800000) ) 
											* (float)(Vref/((float)Date_24*0.75))*RATIO;
		}
		else
		{
			AD2_Value[i] = ( ((float)AD2_Data[i])*(0x400000/ (2*(float)AD2_Gain))
										+ ((float)AD2_Offset-0x800000) ) 
											* (float)(Vref/((float)Date_24*0.75)) *RATIO ;
		}
			
				
		}

		for(i=0;i<Data_Number;i++)
		{
			if(BIPOLAR)
			{
				if(AD2_Value[i]<0) 
				{
					cha[0]='-'-'0';
					value=(unsigned long)(( (-AD2_Value[i])*1000000 + 0.5));
				}
				else
				{
					cha[0]='+'-'0';
					value=(unsigned long)(( (AD2_Value[i])*1000000 + 0.5));
				}
				cha[1]=value/10000000;
				cha[2]=(value%10000000)/1000000;
				cha[3]='.'-'0';
				cha[4]=(value%1000000)/100000;
				cha[5]=(value%100000)/10000;
				cha[6]=(value%10000)/1000;
				cha[7]=(value%1000)/100;
				cha[8]=(value%100)/10;
				cha[9]=(value%10);
				for(j=0;j<10;j++)
			{
				USART_SendData(USART1,cha[j]+'0');         //�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  		 
			}
			}
			else
			{
				value=(unsigned long)(AD2_Value[i]*1000000 + 0.5);
				cha[0]=value/10000000;
				cha[1]=(value%10000000)/1000000;
				cha[2]='.'-'0';
				cha[3]=(value%1000000)/100000;
				cha[4]=(value%100000)/10000;
				cha[5]=(value%10000)/1000;
				cha[6]=(value%1000)/100;
				cha[7]=(value%100)/10;
				cha[8]=(value%10);
				for(j=0;j<9;j++)
			{
				USART_SendData(USART1,cha[j]+'0');         //�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  		 
			}
			}
			USART_SendData(USART1,0x0a);         //�򴮿�1��������
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  

		}
		
		AD2_CS_1();
}





