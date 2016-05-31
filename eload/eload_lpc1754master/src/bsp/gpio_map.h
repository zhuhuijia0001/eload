#ifndef _GPIO_MAP_H_
#define _GPIO_MAP_H_

#include "lpc17xx_gpio.h"

//port num
#define PORT0_OFS      0
#define PORT1_OFS      1
#define PORT2_OFS      2
#define PORT3_OFS      3
#define PORT4_OFS      4


#define GPIO_PORT_SHIFT        8
#define GPIO_OFS_SHIFT         0

#define MAKE_GPIO_NUM(p, o)   ((p << GPIO_PORT_SHIFT) | (o << GPIO_OFS_SHIFT))

//GPIO 0
#define GPIO_0_0      MAKE_GPIO_NUM(PORT0_OFS, 0)
#define GPIO_0_1      MAKE_GPIO_NUM(PORT0_OFS, 1)
#define GPIO_0_2      MAKE_GPIO_NUM(PORT0_OFS, 2)
#define GPIO_0_3      MAKE_GPIO_NUM(PORT0_OFS, 3)
#define GPIO_0_4      MAKE_GPIO_NUM(PORT0_OFS, 4)
#define GPIO_0_5      MAKE_GPIO_NUM(PORT0_OFS, 5)
#define GPIO_0_6      MAKE_GPIO_NUM(PORT0_OFS, 6)
#define GPIO_0_7      MAKE_GPIO_NUM(PORT0_OFS, 7)
#define GPIO_0_8      MAKE_GPIO_NUM(PORT0_OFS, 8)
#define GPIO_0_9      MAKE_GPIO_NUM(PORT0_OFS, 9)
#define GPIO_0_10     MAKE_GPIO_NUM(PORT0_OFS, 10)
#define GPIO_0_11     MAKE_GPIO_NUM(PORT0_OFS, 11)

#define GPIO_0_15     MAKE_GPIO_NUM(PORT0_OFS, 15)
#define GPIO_0_16     MAKE_GPIO_NUM(PORT0_OFS, 16)
#define GPIO_0_17     MAKE_GPIO_NUM(PORT0_OFS, 17)
#define GPIO_0_18     MAKE_GPIO_NUM(PORT0_OFS, 18)
#define GPIO_0_19     MAKE_GPIO_NUM(PORT0_OFS, 19)
#define GPIO_0_20     MAKE_GPIO_NUM(PORT0_OFS, 20)
#define GPIO_0_21     MAKE_GPIO_NUM(PORT0_OFS, 21)
#define GPIO_0_22     MAKE_GPIO_NUM(PORT0_OFS, 22)
#define GPIO_0_23     MAKE_GPIO_NUM(PORT0_OFS, 23)
#define GPIO_0_24     MAKE_GPIO_NUM(PORT0_OFS, 24)
#define GPIO_0_25     MAKE_GPIO_NUM(PORT0_OFS, 25)
#define GPIO_0_26     MAKE_GPIO_NUM(PORT0_OFS, 26)
#define GPIO_0_27     MAKE_GPIO_NUM(PORT0_OFS, 27)
#define GPIO_0_28     MAKE_GPIO_NUM(PORT0_OFS, 28)
#define GPIO_0_29     MAKE_GPIO_NUM(PORT0_OFS, 29)
#define GPIO_0_30     MAKE_GPIO_NUM(PORT0_OFS, 30)

//GPIO1
#define GPIO_1_0      MAKE_GPIO_NUM(PORT1_OFS, 0)
#define GPIO_1_1      MAKE_GPIO_NUM(PORT1_OFS, 1)

#define GPIO_1_4      MAKE_GPIO_NUM(PORT1_OFS, 4)

#define GPIO_1_8      MAKE_GPIO_NUM(PORT1_OFS, 8)
#define GPIO_1_9      MAKE_GPIO_NUM(PORT1_OFS, 9)
#define GPIO_1_10     MAKE_GPIO_NUM(PORT1_OFS, 10)

#define GPIO_1_14     MAKE_GPIO_NUM(PORT1_OFS, 14)
#define GPIO_1_15     MAKE_GPIO_NUM(PORT1_OFS, 15)
#define GPIO_1_16     MAKE_GPIO_NUM(PORT1_OFS, 16)
#define GPIO_1_17     MAKE_GPIO_NUM(PORT1_OFS, 17)
#define GPIO_1_18     MAKE_GPIO_NUM(PORT1_OFS, 18)
#define GPIO_1_19     MAKE_GPIO_NUM(PORT1_OFS, 19)
#define GPIO_1_20     MAKE_GPIO_NUM(PORT1_OFS, 20)
#define GPIO_1_21     MAKE_GPIO_NUM(PORT1_OFS, 21)
#define GPIO_1_22     MAKE_GPIO_NUM(PORT1_OFS, 22)
#define GPIO_1_23     MAKE_GPIO_NUM(PORT1_OFS, 23)
#define GPIO_1_24     MAKE_GPIO_NUM(PORT1_OFS, 24)
#define GPIO_1_25     MAKE_GPIO_NUM(PORT1_OFS, 25)
#define GPIO_1_26     MAKE_GPIO_NUM(PORT1_OFS, 26)
#define GPIO_1_27     MAKE_GPIO_NUM(PORT1_OFS, 27)
#define GPIO_1_28     MAKE_GPIO_NUM(PORT1_OFS, 28)
#define GPIO_1_29     MAKE_GPIO_NUM(PORT1_OFS, 29)
#define GPIO_1_30     MAKE_GPIO_NUM(PORT1_OFS, 30)
#define GPIO_1_31     MAKE_GPIO_NUM(PORT1_OFS, 31)

//GPIO2
#define GPIO_2_0      MAKE_GPIO_NUM(PORT2_OFS, 0)
#define GPIO_2_1      MAKE_GPIO_NUM(PORT2_OFS, 1)
#define GPIO_2_2      MAKE_GPIO_NUM(PORT2_OFS, 2)
#define GPIO_2_3      MAKE_GPIO_NUM(PORT2_OFS, 3)
#define GPIO_2_4      MAKE_GPIO_NUM(PORT2_OFS, 4)
#define GPIO_2_5      MAKE_GPIO_NUM(PORT2_OFS, 5)
#define GPIO_2_6      MAKE_GPIO_NUM(PORT2_OFS, 6)
#define GPIO_2_7      MAKE_GPIO_NUM(PORT2_OFS, 7)
#define GPIO_2_8      MAKE_GPIO_NUM(PORT2_OFS, 8)
#define GPIO_2_9      MAKE_GPIO_NUM(PORT2_OFS, 9)
#define GPIO_2_10      MAKE_GPIO_NUM(PORT2_OFS, 10)
#define GPIO_2_11      MAKE_GPIO_NUM(PORT2_OFS, 11)
#define GPIO_2_12      MAKE_GPIO_NUM(PORT2_OFS, 12)
#define GPIO_2_13      MAKE_GPIO_NUM(PORT2_OFS, 13)

//GPIO3
#define GPIO_3_25      MAKE_GPIO_NUM(PORT3_OFS, 25)
#define GPIO_3_26      MAKE_GPIO_NUM(PORT3_OFS, 26)

//GPIO4
#define GPIO_4_28      MAKE_GPIO_NUM(PORT4_OFS, 28)
#define GPIO_4_29      MAKE_GPIO_NUM(PORT4_OFS, 29)

#define GPIO_PORT_MASK         0x0000ff00
#define GPIO_OFS_MASK          0x000000ff

#define GRAB_PORT(x)           (((x) & GPIO_PORT_MASK) >> GPIO_PORT_SHIFT)
#define GRAB_OFS(x)            (((x) & GPIO_OFS_MASK) >> GPIO_OFS_SHIFT)

//macro
#define SET_GPIO_BIT(x)		(((LPC_GPIO_TypeDef *)(LPC_GPIO0_BASE + (GRAB_PORT(x) << 5)))->FIOSET = (1ul << GRAB_OFS(x)))
//#define SET_GPIO_BIT(x)		GPIO_SetValue(GRAB_PORT(x), (1ul << GRAB_OFS(x)))

#define CLR_GPIO_BIT(x)		(((LPC_GPIO_TypeDef *)(LPC_GPIO0_BASE + (GRAB_PORT(x) << 5)))->FIOCLR = (1ul << GRAB_OFS(x)))
//#define CLR_GPIO_BIT(x)		GPIO_ClearValue(GRAB_PORT(x), (1ul << GRAB_OFS(x)))

#define GET_GPIO_BIT(x)   	((((LPC_GPIO_TypeDef *)(LPC_GPIO0_BASE + (GRAB_PORT(x) << 5)))->FIOPIN >> GRAB_OFS(x)) & 0x01)
//#define GET_GPIO_BIT(x)      	((GPIO_ReadValue(GRAB_PORT(x)) >> GRAB_OFS(x)) & 0x01)                             

#define SET_GPIO_INPUT(x)       (((LPC_GPIO_TypeDef *)(LPC_GPIO0_BASE + (GRAB_PORT(x) << 5)))->FIODIR &= ~(1ul << GRAB_OFS(x)))
//#define SET_GPIO_INPUT(x)    GPIO_SetDir(GRAB_PORT(x), (1ul << GRAB_OFS(x)), 0)

#define SET_GPIO_OUTPUT(x)		(((LPC_GPIO_TypeDef *)(LPC_GPIO0_BASE + (GRAB_PORT(x) << 5)))->FIODIR |= (1ul << GRAB_OFS(x)))
//#define SET_GPIO_OUTPUT(x)    GPIO_SetDir(GRAB_PORT(x), (1ul << GRAB_OFS(x)), 1)

#endif

