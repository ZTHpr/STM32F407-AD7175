#include "PGA281.h"
void PGA1_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* GPIOE*/	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIO
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8| GPIO_Pin_9 | GPIO_Pin_10| GPIO_Pin_11 ;//LED0和LED1对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_ResetBits(GPIOE,GPIO_Pin_7 | GPIO_Pin_8| GPIO_Pin_9 | GPIO_Pin_10| GPIO_Pin_11 );//0 0000
	
		/*输入引脚*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIO
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;//
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//in mode
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
}

void PGA2_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIO
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO
	GPIO_ResetBits(GPIOD,GPIO_Pin_15);//
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIO
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9  ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
	GPIO_ResetBits(GPIOC,GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);//
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIO
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;//
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//in mode
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
}

void PGA1_GO_Low(void)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_7);//0 0000
}
void PGA1_GO_High(void)
{
	GPIO_SetBits(GPIOE,GPIO_Pin_7);
}

void PGA1_G1_Low(void)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_8);//0 0000
}
void PGA1_G1_High(void)
{
	GPIO_SetBits(GPIOE,GPIO_Pin_8);
}

void PGA1_G2_Low(void)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_9);
}
void PGA1_G2_High(void)
{
	GPIO_SetBits(GPIOE,GPIO_Pin_9);
}

void PGA1_G3_Low(void)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_10);
}
void PGA1_G3_High(void)
{
	GPIO_SetBits(GPIOE,GPIO_Pin_10);
}

void PGA1_G4_Low(void)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_11);
}
void PGA1_G4_High(void)
{
	GPIO_SetBits(GPIOE,GPIO_Pin_11);
}

unsigned char Get_PGA1_EF(void)
{
	unsigned char result;
	result=GPIO_ReadInputDataBit(GPIOE ,GPIO_Pin_12);
	return result;
}

void PGA2_GO_Low(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_15);
}
void PGA2_GO_High(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_15);
}

void PGA2_G1_Low(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
}
void PGA2_G1_High(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
}

void PGA2_G2_Low(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);
}
void PGA2_G2_High(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_7);
}

void PGA2_G3_Low(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
}
void PGA2_G3_High(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_8);
}

void PGA2_G4_Low(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);
}
void PGA2_G4_High(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_9);
}

unsigned char Get_PGA2_EF(void)
{
	unsigned char result;
	result=GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_8);
	return result;
}

void PGA1_SetGain(unsigned char gain)
{
	unsigned char i;
	unsigned char cha[4];
	for(i=0;i<4;i++)
	{
		cha[i]=(gain>>i)&0x0001;
		
	}
	
	PGA1_G4_Low();
	if(cha[0]==0)  
		PGA1_GO_Low();
	else			
		PGA1_GO_High();
	if(cha[1]==0) 
		PGA1_G1_Low();
	else				
		PGA1_G1_High();
	if(cha[2]==0) 
		PGA1_G2_Low();
	else				
		PGA1_G2_High();
	if(cha[3]==0) 
		PGA1_G3_Low();
	else				
		PGA1_G3_High();
	
	
}
void PGA2_SetGain(unsigned char gain)
{
	unsigned char i;
	unsigned char cha[4];
	for(i=0;i<4;i++)
	{
		cha[i]=(gain>>i)&0x0001;
	}
	PGA2_G4_Low();
	if(cha[0]==0)  
		PGA2_GO_Low();
	else			
		PGA2_GO_High();
	if(cha[1]==0) 
		PGA2_G1_Low();
	else				
		PGA2_G1_High();
	if(cha[2]==0) 
		PGA2_G2_Low();
	else				
		PGA2_G2_High();
	if(cha[3]==0) 
		PGA2_G3_Low();
	else				
		PGA2_G3_High();
	
}
