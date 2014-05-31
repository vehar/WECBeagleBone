#ifndef _TPS65217_H_
#define _TPS65217_H_

/* I2C chip address */
#define TPS65217_CHIP_PM		0x24

/* Registers */
#define CHIPID				0x00
#define POWER_PATH			0x01
#define INTERRUPT			0x02
#define CHGCONFIG0			0x03
#define CHGCONFIG1			0x04
#define CHGCONFIG2			0x05
#define CHGCONFIG3			0x06
#define WLEDCTRL1			0x07
#define WLEDCTRL2			0x08
#define MUXCTRL				0x09
#define STATUS				0x0A
#define PASSWORD			0x0B
#define PGOOD				0x0C
#define DEFPG				0x0D
#define DEFDCDC1			0x0E
#define DEFDCDC2			0x0F
#define DEFDCDC3			0x10
#define DEFSLEW				0x11
#define DEFLDO1				0x12
#define DEFLDO2				0x13
#define DEFLS1				0x14
#define DEFLS2				0x15
#define ENABLE				0x16
#define DEFUVLO				0x18
#define SEQ1				0x19
#define SEQ2				0x1A
#define SEQ3				0x1B
#define SEQ4				0x1C
#define SEQ5				0x1D
#define SEQ6				0x1E

#define PROT_LEVEL_NONE			0x00
#define PROT_LEVEL_1			0x01
#define PROT_LEVEL_2			0x02

#define PASSWORD_LOCK_FOR_WRITE		0x00
#define PASSWORD_UNLOCK			0x7D

#define DCDC_GO				0x80

#define MASK_ALL_BITS			0xFF

#define USB_INPUT_CUR_LIMIT_MASK	0x03
#define USB_INPUT_CUR_LIMIT_100MA	0x00
#define USB_INPUT_CUR_LIMIT_500MA	0x01
#define USB_INPUT_CUR_LIMIT_1300MA	0x02
#define USB_INPUT_CUR_LIMIT_1800MA	0x03

#define DCDC_VOLT_SEL_1125MV		0x09
#define DCDC_VOLT_SEL_1275MV		0x0F
#define DCDC_VOLT_SEL_1325MV		0x11

#define LDO_MASK				0x1F
#define LDO_VOLTAGE_OUT_1_8		0x06
#define LDO_VOLTAGE_OUT_3_3		0x1F

#define PWR_SRC_USB_BITMASK		0x4
#define PWR_SRC_AC_BITMASK		0x8



/* FUNCTIONS */
extern BOOL TWLSetOPVoltage(UINT voltage,UINT32 mv);

BOOL TWLUpdateVoltage(unsigned char dc_cntrl_reg, unsigned char volt_sel);
BOOL TWLProtWriteRegs(unsigned char prot_level, unsigned char dest_reg,
        unsigned char dest_val, unsigned char mask);
BOOL TWLGetStatusReg(unsigned char * buf);


#endif
