#ifndef __AD7175_H
#define __AD7175_H
#include "sys.h"
#include <stdint.h>
#include "AD7175_regs.h"

/*****************************************************************************/
/******************* AD7175 Constants ****************************************/
/*****************************************************************************/
#define AD7175_CRC_POLYNOMIAL 0x07 // x^8 + x^2 + x +1 (MSB first)
#define AD7175_CRC_CHECK_CODE 0xF3 

int32_t AD_1_Init(void);     //AD1


unsigned char SPI_AD1_ReadChar(void);
void SPI_AD1_WriteChar(unsigned char dat);
unsigned char SPI_AD1_Read(unsigned char slaveDeviceId,unsigned char* data,unsigned char bytesNumber);
unsigned char SPI_AD1_Write(unsigned char slaveDeviceId,unsigned char* data,unsigned char bytesNumber);											
int32_t AD7175_AD1_ReadRegister(st_reg* pReg);
int32_t AD7175_AD1_WriteRegister(st_reg reg);												
int32_t AD7175_AD1_WaitForReady(uint32_t timeout);
int32_t AD7175_AD1_ReadData(int32_t* pData);
void AD7175_AD1_Init_Offset(int32_t* Offset, int32_t* Gain);
											 
							
void AD1_SCLK_0(void);
void AD1_SCLK_1(void);
void AD1_CS_0(void);
void AD1_CS_1(void);
void AD1_SYNC_0(void);
void AD1_SYNC_1(void);
void AD1_DIN_0(void);
void AD1_DIN_1(void);
uint8_t AD1_DOUT(void);

int32_t AD_2_Init(void);     //AD2


unsigned char SPI_AD2_ReadChar(void);
void SPI_AD2_WriteChar(unsigned char dat);
unsigned char SPI_AD2_Read(unsigned char slaveDeviceId,unsigned char* data,unsigned char bytesNumber);
unsigned char SPI_AD2_Write(unsigned char slaveDeviceId,unsigned char* data,unsigned char bytesNumber);											
int32_t AD7175_AD2_ReadRegister(st_reg* pReg);
int32_t AD7175_AD2_WriteRegister(st_reg reg);												
int32_t AD7175_AD2_WaitForReady(uint32_t timeout);
int32_t AD7175_AD2_ReadData(int32_t* pData);
void AD7175_AD2_Init_Offset(int32_t* Offset, int32_t* Gain);
											 
							
void AD2_SCLK_0(void);
void AD2_SCLK_1(void);
void AD2_CS_0(void);
void AD2_CS_1(void);
void AD2_SYNC_0(void);
void AD2_SYNC_1(void);
void AD2_DIN_0(void);
void AD2_DIN_1(void);
uint8_t AD2_DOUT(void);




uint8_t AD7175_ComputeCRC(uint8_t* pBuf, uint8_t bufSize);
#endif
