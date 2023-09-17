/*#ifndef __KEY_H
#define __KEY_H

void Key_Init(void);
uint8_t Key_GetNum(void);

#endif
*/
#ifndef __KEYS_H
#define __KEYS_H	 

#include "stm32f10x.h"

#define KEY_HANG 0x000f   //0123
#define KEY1 GPIO_Pin_4   
#define KEY2 GPIO_Pin_5	   
#define KEY3 GPIO_Pin_6	 
#define KEY4 GPIO_Pin_7   

#define KEY1_Input GPIO_ReadInputDataBit(KEY_PROT,KEY1)
#define KEY2_Input GPIO_ReadInputDataBit(KEY_PROT,KEY2)
#define KEY3_Input GPIO_ReadInputDataBit(KEY_PROT,KEY3)
#define KEY4_Input GPIO_ReadInputDataBit(KEY_PROT,KEY4)

#define KEY_PROT GPIOA

extern u8 FLAG;

void KEY_4x4_Init(void);//IO???
//u8 KEY_Scan(void);
void KEY_Scan(u8 *key);  //??????		

#endif

