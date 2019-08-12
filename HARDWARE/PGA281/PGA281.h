#include <stdint.h>
#include "sys.h"
#ifndef __PGA281_H__
#define __PGA281_H__
enum PGA_Gain_Value
{
	Gain__0p125 = 1,
	Gain__0p25,
	Gain__0p5,
	Gain__1,
	Gain__2,
	Gain__4,
	Gain__8,
	Gain__16,
	Gain__32,
	Gain__64,
	Gain__128
};

void PGA1_Init(void);
void PGA2_Init(void);

void PGA1_GO_Low(void);
void PGA1_GO_High(void);

void PGA1_G1_Low(void);
void PGA1_G1_High(void);

void PGA1_G2_Low(void);
void PGA1_G2_High(void);

void PGA1_G3_Low(void);
void PGA1_G3_High(void);

void PGA1_G4_Low(void);
void PGA1_G4_High(void);

unsigned char Get_PGA1_EF(void);

void PGA2_GO_Low(void);
void PGA2_GO_High(void);

void PGA2_G1_Low(void);
void PGA2_G1_High(void);

void PGA2_G2_Low(void);
void PGA2_G2_High(void);

void PGA2_G3_Low(void);
void PGA2_G3_High(void);

void PGA2_G4_Low(void);
void PGA2_G4_High(void);

unsigned char Get_PGA2_EF(void);



void PGA1_SetGain(unsigned char gain);
void PGA2_SetGain(unsigned char gain);
#endif
