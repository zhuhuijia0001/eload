#include "type.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_i2c.h"

#include "PinDefine.h"
#include "I2C.h"

#if I2C_TYPE == I2C_HARDWARE

void InitI2CMaster(LPC_I2C_TypeDef *I2Cx, UINT32 freq)
{
	PINSEL_CFG_Type PinSelCfgType;

	//SCL
	PinSelCfgType.Portnum = PINSEL_PORT_0;
	PinSelCfgType.Pinnum  = PINSEL_PIN_11;
	PinSelCfgType.Funcnum = PINSEL_FUNC_2;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_OPENDRAIN;
	PINSEL_ConfigPin(&PinSelCfgType);

	//SDA
	PinSelCfgType.Portnum = PINSEL_PORT_0;
	PinSelCfgType.Pinnum  = PINSEL_PIN_10;
	PinSelCfgType.Funcnum = PINSEL_FUNC_2;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_OPENDRAIN;
	PINSEL_ConfigPin(&PinSelCfgType);	
	
	I2C_Init(I2Cx, freq);
	
	I2C_Cmd(I2Cx, I2C_MASTER_MODE, ENABLE);
}

ulong I2C_Start(LPC_I2C_TypeDef *I2Cx)
{
	I2Cx->I2CONCLR = I2C_I2CONCLR_SIC;
	I2Cx->I2CONSET = I2C_I2CONSET_STA;

	// Wait for complete
	while (!(I2Cx->I2CONSET & I2C_I2CONSET_SI));
	I2Cx->I2CONCLR = I2C_I2CONCLR_STAC;
	return (I2Cx->I2STAT & I2C_STAT_CODE_BITMASK);
}

ulong I2C_SendByte (LPC_I2C_TypeDef *I2Cx, uchar databyte)
{
	/* Make sure start bit is not active */
	if (I2Cx->I2CONSET & I2C_I2CONSET_STA)
	{
		I2Cx->I2CONCLR = I2C_I2CONCLR_STAC;
	}
	I2Cx->I2DAT = databyte & I2C_I2DAT_BITMASK;
	I2Cx->I2CONCLR = I2C_I2CONCLR_SIC;

	while (!(I2Cx->I2CONSET & I2C_I2CONSET_SI));
	return (I2Cx->I2STAT & I2C_STAT_CODE_BITMASK);
}

void I2C_Stop (LPC_I2C_TypeDef *I2Cx)
{
	/* Make sure start bit is not active */
	if (I2Cx->I2CONSET & I2C_I2CONSET_STA)
	{
		I2Cx->I2CONCLR = I2C_I2CONCLR_STAC;
	}
	I2Cx->I2CONSET = I2C_I2CONSET_STO;
	I2Cx->I2CONCLR = I2C_I2CONCLR_SIC;
}

ulong I2C_GetByte (LPC_I2C_TypeDef *I2Cx, uchar *retdat, bool ack)
{
	if (ack)
	{
		I2Cx->I2CONSET = I2C_I2CONSET_AA;
	}
	else
	{
		I2Cx->I2CONCLR = I2C_I2CONCLR_AAC;
	}
	I2Cx->I2CONCLR = I2C_I2CONCLR_SIC;

	while (!(I2Cx->I2CONSET & I2C_I2CONSET_SI));
	*retdat = (uchar) (I2Cx->I2DAT & I2C_I2DAT_BITMASK);
	return (I2Cx->I2STAT & I2C_STAT_CODE_BITMASK);
}

#elif I2C_TYPE == I2C_SOFTWARE

void InitI2CMaster(void)
{
	SET_GPIO_BIT(PIN_SCL);
	SET_GPIO_OUTPUT(PIN_SCL);
	
	SET_GPIO_BIT(PIN_SDA);
	SET_GPIO_OUTPUT(PIN_SDA);
}

//I2C 1
static void I2CDelay(void)
{
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
}

void I2CStart(void)
{
	SET_GPIO_BIT(PIN_SDA);
	__NOP();
	SET_GPIO_BIT(PIN_SCL);
	I2CDelay();
	CLR_GPIO_BIT(PIN_SDA);
	I2CDelay();	
	CLR_GPIO_BIT(PIN_SCL);
}

void I2CStop(void)
{
	CLR_GPIO_BIT(PIN_SDA);
	I2CDelay();
	SET_GPIO_BIT(PIN_SCL);
	I2CDelay();
	SET_GPIO_BIT(PIN_SDA);
	I2CDelay();
}

void WriteI2CByte(uchar c)
{
	uchar i;
	i = 8;
	
	do
	{
		if (c & 0x80)
		{
			SET_GPIO_BIT(PIN_SDA);
		}
		else
		{
			CLR_GPIO_BIT(PIN_SDA);
		}

		__NOP();
		I2CDelay();
		SET_GPIO_BIT(PIN_SCL);
		I2CDelay();
		CLR_GPIO_BIT(PIN_SCL);
		I2CDelay();
		c <<= 1;
	} while (--i);	
}

bool CheckI2CAck(void)
{
	uchar loop = 0xff;
	bool res;
	
	SET_GPIO_BIT(PIN_SCL);
	SET_GPIO_INPUT(PIN_SDA);
	

	while (GET_GPIO_BIT(PIN_SDA) && loop--);
	
	res = (GET_GPIO_BIT(PIN_SDA) == 0);
	
	CLR_GPIO_BIT(PIN_SCL);
	I2CDelay();
	
	SET_GPIO_OUTPUT(PIN_SDA);
	
	return res;
}

uchar ReceiveI2CByte(void)
{
	uchar i;
	
	uchar c = 0x00;

	SET_GPIO_INPUT(PIN_SDA);
	
	for (i = 0; i < 8; i++)
	{
		c <<= 1;
		SET_GPIO_BIT(PIN_SCL);
		I2CDelay();
		c |= GET_GPIO_BIT(PIN_SDA);			
		CLR_GPIO_BIT(PIN_SCL);
		I2CDelay();
	}		
	
	SET_GPIO_OUTPUT(PIN_SDA);
	
	return c;
}

void SendI2CAck(bool ack)
{
	if (ack)
	{
		SET_GPIO_BIT(PIN_SDA);
	}
	else
	{
		CLR_GPIO_BIT(PIN_SDA);
	}
	__NOP();
	SET_GPIO_BIT(PIN_SCL);
	I2CDelay();
	CLR_GPIO_BIT(PIN_SCL);
	I2CDelay();
}


#else 
#error "Invalid i2c type"
#endif

