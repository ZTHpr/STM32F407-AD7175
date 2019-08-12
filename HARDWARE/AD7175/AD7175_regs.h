
#include <stdint.h>
#ifndef __AD7175_REGS_H__
#define __AD7175_REGS_H__

/*! AD7175 register info */
typedef struct _st_reg 
{
		int32_t addr;
		int32_t value;
    int32_t size;
}st_reg;

/*! AD7175 registers list*/
enum AD7175_registers
{
	Status_Register = 0x00,
	ADC_Mode_Register,
	Interface_Mode_Register,
	REGCHECK,
	Data_Register,
	IOCon_Register,
	ID_st_reg,
	CH_Map_1,
	CH_Map_2,
	CH_Map_3,
	CH_Map_4,
	Setup_Config_1,
	Setup_Config_2,
	Setup_Config_3,
	Setup_Config_4,
	Filter_Config_1,
	Filter_Config_2,
	Filter_Config_3,
	Filter_Config_4,
	Offset_1,
	Offset_2,
	Offset_3,
	Offset_4,
	Gain_1,
	Gain_2,
	Gain_3,
	Gain_4,
	Communications_Register,
	AD7175_REG_NO
};

#ifdef AD7175_INIT
/*! Array holding the info for the AD7175 registers - address, initial value, size */
st_reg AD7175_regs[] = 
{
    {0x00, 0x00,   1}, //Status_Register
    {0x01, 0x200c, 2}, //ADC_Mode_Register 1010000000001100 使能内部稳压源 单通道 外部晶振 0xa00c
											 //禁用内部2.5V  0x200c
		                   //内部失调校准模式 0xa04c  系统失调校准模式  0xa06c  系统增益校准 0x0a7c
												
    {0x02, 0x0000, 2}, //Interface_Mode_Register    无STAT 不校验
    {0x03, 0x000000,3}, //REGCHECK	
    {0x04, 0x0000, 3}, //Data_Register
    {0x06, 0x080e, 2}, //IOCon_Register//  (sync设置）
		//0x080e      
    {0x07, 0x0000, 2}, //ID_st_reg
    {0x10, 0x8043 , 2}, //CH_Map_1   配置第一个通道为设置0   vin0+  vin1- 0x8001    (avdd-avss)/5 0x8274 
												//vin2+  vin3-  0x8043   ref  0x82b6
		{0x11, 0x0000, 2}, //CH_Map_2
		{0x12, 0x0000, 2}, //CH_Map_3
		{0x13, 0x0000, 2}, //CH_Map_4
		{0x20, 0x0300, 2}, //Setup_Config_1  双极性   ref缓冲禁用 VIN缓冲使能 内部基准电压  0x1320  （ 单极性 0x0320 ）
																	//		 双极性   ref缓冲禁用 VIN缓冲使能 外部基准电压  0x1300  （ 单极性 0x0300 ）      
		{0x21, 0x0000, 2}, //Setup_Config_2
		{0x22, 0x0000, 2}, //Setup_Config_3
		{0x23, 0x0000, 2}, //Setup_Config_4
		{0x28, 0x0509, 2}, //Filter_Config_1  20sps 0x0511         5sps  0x0514   1000sps  0x050a   
											 //									2500sps   0x0509      5000sps  0x0508   10000sps 0x0507   
																					//25000	0x0505 31250 0x0504	50000 0x0503	62500 0x0502	125000 0x0501	250000 0x0500
		
		//sin3    0x8064   50  0x9388
		{0x29, 0x0200, 2}, //Filter_Config_2
		{0x2a, 0x0200, 2}, //Filter_Config_3
		{0x2b, 0x0200, 2}, //Filter_Config_4
		{0x30, 0x800000, 3}, //Offset_1     默认0x800000
		{0x31, 0, 3}, //Offset_2
		{0x32, 0, 3}, //Offset_3
		{0x33, 0, 3}, //Offset_4
		{0x38, 0x800000, 3}, //Gain_1
		{0x39, 0, 3}, //Gain_2
		{0x3a, 0, 3}, //Gain_3
		{0x3b, 0, 3}, //Gain_4
		{0xFF, 0, 1} //Communications_Register
};
#else
extern st_reg AD7175_regs[AD7175_REG_NO];
#endif

#define AD7175_SLAVE_ID    1

/* Communication Register bits */
#define COMM_REG_WEN    (0 << 7)
#define COMM_REG_WR     (0 << 6)
#define COMM_REG_RD     (1 << 6)

/* Status Register bits */
#define STATUS_REG_RDY      (1 << 7)
#define STATUS_REG_ADC_ERR  (1 << 6)
#define STATUS_REG_CRC_ERR  (1 << 5)
#define STATUS_REG_REG_ERR  (1 << 4)
#define STATUS_REG_CH(x)    ((x) & 0x03)

/* ADC Mode Register */
#define ADC_MODE_REG_REF_EN         (1 << 15)
#define ADC_MODE_REG_DELAY(x)       (((x) & 0x7) << 8)
#define ADC_MODE_REG_MODE(x)        (((x) & 0x7) << 4)
#define ADC_MODE_REG_CLKSEL(x))     (((x) & 0x3) << 2)

/* Interface Mode Register bits */
#define INTF_MODE_REG_DOUT_RESET    (1 << 8)
#define INTF_MODE_REG_CONT_READ     (1 << 7)
#define INTF_MODE_REG_DATA_STAT     (1 << 6)
#define INTF_MODE_REG_CRC_EN        (0x02 << 2)
#define INTF_MODE_REG_CRC_STAT(x)   (((x) & INTF_MODE_REG_CRC_EN) == INTF_MODE_REG_CRC_EN)

/* GPIO Configuration Register */
#define GPIO_CONF_REG_MUX_IO        (1 << 12)
#define GPIO_CONF_REG_SYNC_EN       (1 << 11)
#define GPIO_CONF_REG_ERR_EN(x)     (((x) & 0x3) << 9)
#define GPIO_CONF_REG_ERR_DAT       (1 << 8)
#define GPIO_CONF_REG_IP_EN1        (1 << 5)
#define GPIO_CONF_REG_IP_EN0        (1 << 4)
#define GPIO_CONF_REG_OP_EN1        (1 << 3)
#define GPIO_CONF_REG_OP_EN0        (1 << 2)
#define GPIO_CONF_REG_DATA1         (1 << 1)
#define GPIO_CONF_REG_DATA0         (1 << 0)

/* ID Register */
#define ID_REG_PRODUCT_ID(x)        (((x) & 0xFF) << 8)

/* Channel Map Register 1-4 */
#define CH_MAP_REG_CHEN         (1 << 15)
#define CH_MAP_REG_SETUP(x)     (((x) & 0x7) << 12)
#define CH_MAP_REG_AINPOS(x)    (((x) & 0x1F) << 5)    
#define CH_MAP_REG_AINNEG(x)    (((x) & 0x1F) << 0)

/* Setup Configuration Register 1-4 */
#define SETUP_CONF_REG_CHOP_MD(x)       (((x) & 0x3) << 14)
#define SETUP_CONF_REG_BI_UNIPOLAR      (1 << 12)
#define SETUP_CONF_REG_REF_BUF_P        (1 << 11)
#define SETUP_CONF_REG_REF_BUF_N        (1 << 10)
#define SETUP_CONF_REG_AIN_BUF_P        (1 << 9)
#define SETUP_CONF_REG_AIN_BUF_N        (1 << 8)
#define SETUP_CONF_REG_BRNOUT_EN        (1 << 7)
#define SETUP_CONF_REG_REF_SEL(x)       (((x) & 0x3) << 4)

/* Filter Configuration Register 1-4 */
#define FILT_CONF_REG_EXTCLKFREQ(x)     (((x) & 0x3) << 13)
#define FILT_CONF_REG_ENHFILTEN         (1 << 11)
#define FILT_CONF_REG_ENHFILTSEL(x)     (((x) & 0x7) << 8)
#define FILT_CONF_REG_ORDER(x)          (((x) & 0x7) << 5)
#define FILT_CONF_REG_ODR(x)            (((x) & 0x1F) << 0)


#endif //__AD7175_REGS_H__
