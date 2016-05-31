#ifndef _I2C_H_
#define _I2C_H_

#define I2C_HARDWARE    1
#define I2C_SOFTWARE    2

#define I2C_TYPE  I2C_HARDWARE

#if I2C_TYPE == I2C_HARDWARE
extern void InitI2CMaster(LPC_I2C_TypeDef *I2Cx, UINT32 freq);
extern ulong I2C_Start(LPC_I2C_TypeDef *I2Cx);
extern ulong I2C_SendByte (LPC_I2C_TypeDef *I2Cx, uchar databyte);
extern void I2C_Stop (LPC_I2C_TypeDef *I2Cx);
extern ulong I2C_GetByte (LPC_I2C_TypeDef *I2Cx, uchar *retdat, bool ack);

#elif I2C_TYPE == I2C_SOFTWARE
extern void InitI2CMaster(void);
extern void I2CStart(void);
extern void I2CStop(void);
extern void WriteI2CByte(uchar c);
extern bool CheckI2CAck(void);
extern uchar ReceiveI2CByte(void);
extern void SendI2CAck(bool ack);
#else
#error "Invalid i2c type"
#endif

#endif
