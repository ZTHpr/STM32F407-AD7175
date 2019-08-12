#include <stdint.h>
#include <stdio.h>
#ifndef __MAIN_H__
#define __MAIN_H__

#define Data_Number  (6000) 
#define Vref  (2.5)
#define Date_24 (0x800000)
#define BIPOLAR  (0)

#define RATIO  (11/1)
int32_t AD1_Offset,AD2_Offset,AD1_Gain,AD2_Gain; //校准参数
extern void *memset(void *s, int ch, size_t n);
void AD1_Send_Date(void);
void AD2_Send_Date(void);
void AD1AD2_Send_Date(void);




#endif