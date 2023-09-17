#ifndef _LCD1602_H
#define _LCD1602_H

#include "stm32f10x.h"
#include "SysTick.h" 

#define LCD_RS PBout(1)
#define LCD_RW PBout(2)
#define LCD_EN PBout(0)

#define LCD_BUSY PBin(15)

void Lcd1602_Pin_Init(void);
void Lcd1602_Init(void);
void Lcd1602_Write_Cmd(int cmd);
void Lcd1602_Write_Data(int	data);
void Lcd1602_DisplayChar(u8 row,u8 col,int ch);
void Lcd1602_DisplayString(u8 row,u8 col,u8 *str);

void Lcd1602_Check_Busy(void);
void LCD_ShowNum(unsigned char row,unsigned char col,unsigned int Number,unsigned char Length);
int  LCD_Pow(int X,int Y);
#endif
