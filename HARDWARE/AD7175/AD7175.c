#define AD7175_INIT


#include "AD7175.h"
#include "AD7175_regs.h"
#include "delay.h"




/******************************************************************************/
/************************ Local variables and types ***************************/
/******************************************************************************/
struct AD7175_state
{
    uint8_t useCRC;
}AD7175_AD1_st,AD7175_AD2_st;

/*AD1*/
int32_t AD_1_Init(void)   //AD1
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	int32_t ret;

	/*输出引脚*/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7;//SCLK,CS,SYNC，DIN	输出模式
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	GPIO_SetBits(GPIOA,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7);//set 1
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	
	
	
	/*输入引脚*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;//DOUT
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//in mode
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
	
	
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();




		//自检
    
/* Initialize ADC mode register */
    ret = AD7175_AD1_WriteRegister(AD7175_regs[ADC_Mode_Register]);
    if(ret < 0)
        return ret;
    
    /* Initialize Interface mode register */
    ret = AD7175_AD1_WriteRegister(AD7175_regs[Interface_Mode_Register]);
    if(ret < 0)
        return ret;
		delay_ms(1000);
    AD7175_AD1_st.useCRC = INTF_MODE_REG_CRC_STAT(AD7175_regs[Interface_Mode_Register].value);
    
    /* Initialize GPIO configuration register */
    ret = AD7175_AD1_WriteRegister(AD7175_regs[IOCon_Register]);   
    if(ret < 0)
        return ret;   
    
    /* Initialize Channel Map registers */
    ret = AD7175_AD1_WriteRegister(AD7175_regs[CH_Map_1]);
    if(ret < 0)
        return ret;   
    ret = AD7175_AD1_WriteRegister(AD7175_regs[CH_Map_2]);
    if(ret < 0)
        return ret;   
    ret = AD7175_AD1_WriteRegister(AD7175_regs[CH_Map_3]);
    if(ret < 0)
        return ret;    
    ret = AD7175_AD1_WriteRegister(AD7175_regs[CH_Map_4]);
    if(ret < 0)
        return ret;
    
    /* Initialize Setup Configuration registers */
    ret = AD7175_AD1_WriteRegister(AD7175_regs[Setup_Config_1]);
    if(ret < 0)
        return ret;
    ret = AD7175_AD1_WriteRegister(AD7175_regs[Setup_Config_2]);
    if(ret < 0)
        return ret;
    ret = AD7175_AD1_WriteRegister(AD7175_regs[Setup_Config_3]);
    if(ret < 0)
        return ret;
    ret = AD7175_AD1_WriteRegister(AD7175_regs[Setup_Config_4]);
    if(ret < 0)
        return ret;

    /* Initialize Filter Configuration registers */
    ret = AD7175_AD1_WriteRegister(AD7175_regs[Filter_Config_1]);
    if(ret < 0)
        return ret;
    ret = AD7175_AD1_WriteRegister(AD7175_regs[Filter_Config_2]);
    if(ret < 0)
        return ret;
    ret = AD7175_AD1_WriteRegister(AD7175_regs[Filter_Config_3]);
    if(ret < 0)
        return ret;
    ret = AD7175_AD1_WriteRegister(AD7175_regs[Filter_Config_4]);
    if(ret < 0)
        return ret;

    return ret;
	
}

int32_t AD_2_Init(void)   //AD2
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	int32_t ret;

	/*输出引脚*/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15;//SCLK,CS,SYNC，DIN	输出模式
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
	GPIO_SetBits(GPIOB,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15);//set 1
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);//
	
	
	
	/*输入引脚*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOD时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;//DOUT
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//in mode
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO
	
	
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();




		//自检
    
/* Initialize ADC mode register */
    ret = AD7175_AD2_WriteRegister(AD7175_regs[ADC_Mode_Register]);
    if(ret < 0)
        return ret;
    
    /* Initialize Interface mode register */
    ret = AD7175_AD2_WriteRegister(AD7175_regs[Interface_Mode_Register]);
    if(ret < 0)
        return ret;
		delay_ms(1000);
    AD7175_AD2_st.useCRC = INTF_MODE_REG_CRC_STAT(AD7175_regs[Interface_Mode_Register].value);
    
    /* Initialize GPIO configuration register */
    ret = AD7175_AD2_WriteRegister(AD7175_regs[IOCon_Register]);   
    if(ret < 0)
        return ret;   
    
    /* Initialize Channel Map registers */
    ret = AD7175_AD2_WriteRegister(AD7175_regs[CH_Map_1]);
    if(ret < 0)
        return ret;   
    ret = AD7175_AD2_WriteRegister(AD7175_regs[CH_Map_2]);
    if(ret < 0)
        return ret;   
    ret = AD7175_AD2_WriteRegister(AD7175_regs[CH_Map_3]);
    if(ret < 0)
        return ret;    
    ret = AD7175_AD2_WriteRegister(AD7175_regs[CH_Map_4]);
    if(ret < 0)
        return ret;
    
    /* Initialize Setup Configuration registers */
    ret = AD7175_AD2_WriteRegister(AD7175_regs[Setup_Config_1]);
    if(ret < 0)
        return ret;
    ret = AD7175_AD2_WriteRegister(AD7175_regs[Setup_Config_2]);
    if(ret < 0)
        return ret;
    ret = AD7175_AD2_WriteRegister(AD7175_regs[Setup_Config_3]);
    if(ret < 0)
        return ret;
    ret = AD7175_AD2_WriteRegister(AD7175_regs[Setup_Config_4]);
    if(ret < 0)
        return ret;

    /* Initialize Filter Configuration registers */
    ret = AD7175_AD2_WriteRegister(AD7175_regs[Filter_Config_1]);
    if(ret < 0)
        return ret;
    ret = AD7175_AD2_WriteRegister(AD7175_regs[Filter_Config_2]);
    if(ret < 0)
        return ret;
    ret = AD7175_AD2_WriteRegister(AD7175_regs[Filter_Config_3]);
    if(ret < 0)
        return ret;
    ret = AD7175_AD2_WriteRegister(AD7175_regs[Filter_Config_4]);
    if(ret < 0)
        return ret;

    return ret;
	
}

void AD1_SCLK_0(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}

void AD1_SCLK_1(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_4);//set 1
}

void AD1_CS_0(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}

void AD1_CS_1(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_5);//set 1
}
void AD1_SYNC_0(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);
}

void AD1_SYNC_1(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_6);//set 1
}

void AD1_DIN_0(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);
}

void AD1_DIN_1(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_7);//set 1
}

uint8_t AD1_DOUT(void)
{
	uint8_t resut;
	resut=GPIO_ReadInputDataBit(GPIOC ,GPIO_Pin_4);
	return resut;
}


void AD2_SCLK_0(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}

void AD2_SCLK_1(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);//set 1
}

void AD2_CS_0(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
}

void AD2_CS_1(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_13);//set 1
}
void AD2_SYNC_0(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
}

void AD2_SYNC_1(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_14);//set 1
}

void AD2_DIN_0(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}

void AD2_DIN_1(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_15);//set 1
}

uint8_t AD2_DOUT(void)
{
	uint8_t resut;
	resut=GPIO_ReadInputDataBit(GPIOD ,GPIO_Pin_8);
	return resut;
}

unsigned char SPI_AD1_ReadChar(void)
{
	unsigned char n,dat;
	
	
	dat=0;
	for(n=0;n<8;n++)
	{
		AD1_SCLK_0();
//		__nop();__nop();__nop();__nop();__nop();__nop(); 
//		__nop();__nop();__nop();__nop();
		__nop();         //SCLK下降沿到数据有效延迟，最大25ns
		//低电平脉宽延时 最大25ns
//		dat<<=1;
//		if(AD1_DOUT()==1)
//			dat|=0x01;
//		else 
//			dat&=0xfe;
//		__nop();__nop();__nop();__nop();__nop();__nop();
//		__nop();__nop();__nop();__nop();__nop();
//		__nop();
		
		if (AD1_DOUT() )
        {
            dat |= (0x01 << (7 - n));
        }
		
		AD1_SCLK_1(); 
		
		
//		__nop();__nop();__nop();__nop();__nop();__nop();
//		__nop();__nop();__nop();__nop();
		__nop();
		//高电平脉宽延时 最大25ns
	}
	
	return dat;
}

unsigned char SPI_AD2_ReadChar(void)
{
	unsigned char n,dat;
	
	
	dat=0;
	for(n=0;n<8;n++)
	{
		AD2_SCLK_0();
//		__nop();__nop();__nop();__nop();__nop();__nop(); 
//		__nop();__nop();__nop();__nop();
//		__nop();
		__nop();         //SCLK下降沿到数据有效延迟，最大25ns


		
		if (AD2_DOUT() )
        {
            dat |= (0x01 << (7 - n));
        }

		AD2_SCLK_1(); 
		
		
//		__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();
		//高电平脉宽延时 最大25ns
	}
	
	return dat;
}

void SPI_AD1_WriteChar(unsigned char dat)
{
	unsigned char n;
	
	
	
	for(n=0;n<8;n++)
	{
		AD1_SCLK_0();
//  	__nop();__nop();__nop();__nop();
		__nop();  
	//数据有效到sclk建立延时，最小8ns
//		__nop();__nop();__nop();__nop();__nop();__nop();
//		__nop();__nop();__nop();__nop();
//		__nop();
//		__nop();
		//低电平脉宽延时
		if(dat&0x80)
			AD1_DIN_1();
		else 
			AD1_DIN_0();
		dat<<=1;
		AD1_SCLK_1();
//		__nop();__nop();__nop();__nop();__nop();__nop();
//		__nop();__nop();__nop();__nop();
		__nop();
		//高电平脉宽延时

	}
	
}

void SPI_AD2_WriteChar(unsigned char dat)
{
	unsigned char n;
	
	
	
	for(n=0;n<8;n++)
	{
		AD2_SCLK_0();

		__nop();
		//低电平脉宽延时
		if(dat&0x80)
			AD2_DIN_1();
		else 
			AD2_DIN_0();
		dat<<=1;
		AD2_SCLK_1();
	  __nop();
		//高电平脉宽延时

	}
	
}
unsigned char SPI_AD1_Read(unsigned char slaveDeviceId,
													 unsigned char* data,
													 unsigned char bytesNumber)
{
	unsigned char byte = 0;
	unsigned char out;
	
	AD1_SCLK_1();
	AD1_CS_0();
	__nop();__nop();
//	__nop();__nop();__nop();__nop();__nop();__nop();
//	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	//CS下降沿到DOUT有效时间延时，最大需要40ns
	
//		while(1)
//	{
//		out=AD1_DOUT();
//		if(out==0)
//			break;
//	}
	SPI_AD1_WriteChar(data[0]);   //写入寄存器地址
	for(byte = 0; byte < bytesNumber; byte++)
	{      
			
			data[byte] = SPI_AD1_ReadChar();
		  
	}

	__nop();__nop();__nop();__nop();__nop();__nop();//此时sclk=1
	__nop();__nop();__nop();__nop();__nop();__nop(); 
//	AD1_CS_1();  
	__nop();__nop();__nop();__nop();__nop();__nop();  
	__nop();__nop();__nop();__nop();__nop();__nop();//总线释放时间 最大需要20ns
	
	return bytesNumber;
		
 
}

unsigned char SPI_AD2_Read(unsigned char slaveDeviceId,
													 unsigned char* data,
													 unsigned char bytesNumber)
{
	unsigned char byte = 0;
	unsigned char out;
	
	AD2_SCLK_1();
	AD2_CS_0();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	//CS下降沿到DOUT有效时间延时，最大需要40ns
	

	SPI_AD2_WriteChar(data[0]);   //写入寄存器地址
	for(byte = 0; byte < bytesNumber; byte++)
	{      
			
			data[byte] = SPI_AD2_ReadChar();
		  
	}

	__nop();__nop();__nop();__nop();__nop();__nop();//此时sclk=1
	__nop();__nop();__nop();__nop();__nop();__nop(); 
//	AD2_CS_1();  
	__nop();__nop();__nop();__nop();__nop();__nop();  
	__nop();__nop();__nop();__nop();__nop();__nop();//总线释放时间 最大需要20ns
	
	return bytesNumber;
		
 
}
													

unsigned char SPI_AD1_Write(unsigned char slaveDeviceId,
														unsigned char* data,
														unsigned char bytesNumber)
{
	unsigned char byte = 0;
//	unsigned char read = 0;
	
	AD1_SCLK_1();
	AD1_CS_0();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	//CS下降沿到SCLK有效时间，最小为0，但还是加上延时
	for(byte = 0; byte < bytesNumber; byte++)
   {
		 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			SPI_AD1_WriteChar(data[byte]);   //写入寄存器
   }
	__nop();__nop();__nop();__nop();__nop();__nop();  //此时sclk=1
	__nop();__nop();__nop();__nop();__nop();__nop();
	AD1_CS_1();
	__nop();__nop();__nop();__nop();__nop();__nop();  
	__nop();__nop();__nop();__nop();__nop();__nop();//总线释放时间 最大需要20ns
	
	return bytesNumber;
	
	
	
	
	
}


unsigned char SPI_AD2_Write(unsigned char slaveDeviceId,
														unsigned char* data,
														unsigned char bytesNumber)
{
	unsigned char byte = 0;
//	unsigned char read = 0;
	
	AD2_SCLK_1();
	AD2_CS_0();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	//CS下降沿到SCLK有效时间，最小为0，但还是加上延时
	for(byte = 0; byte < bytesNumber; byte++)
   {
		 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			SPI_AD2_WriteChar(data[byte]);   //写入寄存器
   }
	__nop();__nop();__nop();__nop();__nop();__nop();  //此时sclk=1
	__nop();__nop();__nop();__nop();__nop();__nop();
	AD2_CS_1();
	__nop();__nop();__nop();__nop();__nop();__nop();  
	__nop();__nop();__nop();__nop();__nop();__nop();//总线释放时间 最大需要20ns
	
	return bytesNumber;
	
	
	
	
	
}



int32_t AD7175_AD1_ReadRegister(st_reg* pReg)
{
	  int32_t ret       = 0;
    uint8_t buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t i         = 0;
    uint8_t crc       = 0;

    /* Build the Command word */
    buffer[0] = COMM_REG_WEN | COMM_REG_RD | pReg->addr;
    
    /* Read data from the device */
    ret = SPI_AD1_Read(AD7175_SLAVE_ID, 
                   buffer, 
                   (AD7175_AD1_st.useCRC ? pReg->size + 1 : pReg->size) + 1);
    if(ret < 0)
        return ret;

    /* Check the CRC */
  		if(AD7175_AD1_st.useCRC)
    {
        crc = AD7175_ComputeCRC(&buffer[1], pReg->size + 1);
        if(crc != AD7175_CRC_CHECK_CODE)
            return -1;
    }

    /* Build the result */
    pReg->value = 0;
    for(i = 0; i < pReg->size + 1; i++)
    {
        pReg->value <<= 8;
        pReg->value += buffer[i];
    }

    return ret;
}

int32_t AD7175_AD2_ReadRegister(st_reg* pReg)
{
	  int32_t ret       = 0;
    uint8_t buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t i         = 0;
    uint8_t crc       = 0;

    /* Build the Command word */
    buffer[0] = COMM_REG_WEN | COMM_REG_RD | pReg->addr;
    
    /* Read data from the device */
    ret = SPI_AD2_Read(AD7175_SLAVE_ID, 
                   buffer, 
                   (AD7175_AD2_st.useCRC ? pReg->size + 1 : pReg->size) + 1);
    if(ret < 0)
        return ret;

    /* Check the CRC */
  		if(AD7175_AD2_st.useCRC)
    {
        crc = AD7175_ComputeCRC(&buffer[1], pReg->size + 1);
        if(crc != AD7175_CRC_CHECK_CODE)
            return -1;
    }

    /* Build the result */
    pReg->value = 0;
    for(i = 0; i < pReg->size + 1; i++)
    {
        pReg->value <<= 8;
        pReg->value += buffer[i];
    }

    return ret;
}

int32_t AD7175_AD1_WriteRegister(st_reg reg)
{
	  int32_t ret      = 0;
    int32_t regValue = 0;
    uint8_t wrBuf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t i        = 0;
    uint8_t crc      = 0;
    
    /* Build the Command word */
    wrBuf[0] = COMM_REG_WEN | COMM_REG_WR | reg.addr;
    
    /* Fill the write buffer */
    regValue = reg.value;
    for(i = 0; i < reg.size; i++)
    {
        wrBuf[reg.size - i] = regValue & 0xFF;
        regValue >>= 8;
    }

    /* Compute the CRC */
    if(AD7175_AD1_st.useCRC)
    {
        crc = AD7175_ComputeCRC(wrBuf, reg.size+1);
        wrBuf[reg.size + 1] = ~crc;
    }

    /* Write data to the device */
    ret = SPI_AD1_Write(AD7175_SLAVE_ID,
                    wrBuf,
                    AD7175_AD1_st.useCRC ? reg.size + 2 : reg.size + 1);
    
    return ret;
}

int32_t AD7175_AD2_WriteRegister(st_reg reg)
{
	  int32_t ret      = 0;
    int32_t regValue = 0;
    uint8_t wrBuf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t i        = 0;
    uint8_t crc      = 0;
    
    /* Build the Command word */
    wrBuf[0] = COMM_REG_WEN | COMM_REG_WR | reg.addr;
    
    /* Fill the write buffer */
    regValue = reg.value;
    for(i = 0; i < reg.size; i++)
    {
        wrBuf[reg.size - i] = regValue & 0xFF;
        regValue >>= 8;
    }

    /* Compute the CRC */
    if(AD7175_AD2_st.useCRC)
    {
        crc = AD7175_ComputeCRC(wrBuf, reg.size+1);
        wrBuf[reg.size + 1] = ~crc;
    }

    /* Write data to the device */
    ret = SPI_AD2_Write(AD7175_SLAVE_ID,
                    wrBuf,
                    AD7175_AD2_st.useCRC ? reg.size + 2 : reg.size + 1);
    
    return ret;
}

uint8_t AD7175_ComputeCRC(uint8_t* pBuf, uint8_t bufSize)
{
    uint8_t i = 0;
    uint8_t crc = 0xFF;

	while(bufSize--)
	{
		crc ^= *pBuf++;
		for(i = 0; i < 8; i++)
		{
			if(crc & 0x80)
				crc = (crc << 1) ^ AD7175_CRC_POLYNOMIAL;
            else
				crc <<= 1;
		}
	}
	return crc;
}

int32_t AD7175_AD1_WaitForReady(uint32_t timeout)
{
    int32_t ret;
    int8_t ready = 0;

    while(!ready && --timeout)
    {
        /* Read the value of the Status Register */
        ret = AD7175_AD1_ReadRegister(&AD7175_regs[Status_Register]);
        if(ret < 0)
            return ret;

        /* Check the RDY bit in the Status Register */
        ready = (AD7175_regs[Status_Register].value & STATUS_REG_RDY) != 0;
    }

    return timeout ? 0 : -1; 
}


int32_t AD7175_AD2_WaitForReady(uint32_t timeout)
{
    int32_t ret;
    int8_t ready = 0;

    while(!ready && --timeout)
    {
        /* Read the value of the Status Register */
        ret = AD7175_AD2_ReadRegister(&AD7175_regs[Status_Register]);
        if(ret < 0)
            return ret;

        /* Check the RDY bit in the Status Register */
        ready = (AD7175_regs[Status_Register].value & STATUS_REG_RDY) != 0;
    }

    return timeout ? 0 : -1; 
}

int32_t AD7175_AD1_ReadData(int32_t* pData)
{
    int32_t ret;

    /* Read the value of the Status Register */
    ret = AD7175_AD1_ReadRegister(&AD7175_regs[Data_Register]);

    /* Get the read result */
    *pData = AD7175_regs[Data_Register].value;

    return ret;
}

int32_t AD7175_AD2_ReadData(int32_t* pData)
{
    int32_t ret;

    /* Read the value of the Status Register */
    ret = AD7175_AD2_ReadRegister(&AD7175_regs[Data_Register]);

    /* Get the read result */
    *pData = AD7175_regs[Data_Register].value;

    return ret;
}

void AD7175_AD1_Init_Offset(int32_t* Offset, int32_t* Gain)
{
	int32_t ret,mode;
	mode=AD7175_regs[ADC_Mode_Register].value;
	AD7175_regs[ADC_Mode_Register].value=0xa04c;    //内部失调校准模式 
	AD7175_AD1_WriteRegister(AD7175_regs[ADC_Mode_Register]);
	delay_ms(1000);
	ret = AD7175_AD1_ReadRegister(&AD7175_regs[Offset_1]);
	*Offset = AD7175_regs[Offset_1].value>>8;
	
	*Offset = *Offset & 0x00ffffff;
	ret    = AD7175_AD1_ReadRegister(&AD7175_regs[Gain_1]);
	*Gain   = AD7175_regs[Gain_1].value>>8;
	*Gain=*Gain & 0x00ffffff;
	AD7175_regs[ADC_Mode_Register].value=mode;
	AD7175_AD1_WriteRegister(AD7175_regs[ADC_Mode_Register]);
  delay_ms(1000);	
}


void AD7175_AD2_Init_Offset(int32_t* Offset, int32_t* Gain)
{
	int32_t ret,mode;
	mode=AD7175_regs[ADC_Mode_Register].value;
	AD7175_regs[ADC_Mode_Register].value=0xa04c;    //内部失调校准模式 
	AD7175_AD2_WriteRegister(AD7175_regs[ADC_Mode_Register]);
	delay_ms(10);
	ret = AD7175_AD2_ReadRegister(&AD7175_regs[Offset_1]);
	*Offset = AD7175_regs[Offset_1].value>>8;
	
	*Offset = *Offset & 0x00ffffff;
	ret    = AD7175_AD2_ReadRegister(&AD7175_regs[Gain_1]);
	*Gain   = AD7175_regs[Gain_1].value>>8;
	*Gain=*Gain & 0x00ffffff;
	AD7175_regs[ADC_Mode_Register].value=mode;
	AD7175_AD2_WriteRegister(AD7175_regs[ADC_Mode_Register]);
  delay_ms(10);	
}