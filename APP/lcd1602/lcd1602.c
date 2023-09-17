#include "lcd1602.h"


void Lcd1602_Pin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_8 | 
								GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 |
								GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

/*******************************************************************************
*函数的原型：void Lcd1602_Init(void)
*函数的功能：LCD1602初始化
*函数的参数：None
*函数返回值：None
*函数的说明：
*函数编写者：庆
*函数编写日期：2021/2/4
*函数的版本号：V1.0
********************************************************************************/
void Lcd1602_Init(void)
{
	Lcd1602_Pin_Init();
	
	delay_ms(15);
	
	Lcd1602_Write_Cmd(0X38);
	Lcd1602_Write_Cmd(0X0C);//开显示不显示光标
	Lcd1602_Write_Cmd(0X06);//写一个指针加1
	Lcd1602_Write_Cmd(0X01);//清屏
	Lcd1602_Write_Cmd(0X80);//设置数据指针起点	
	

}

/*******************************************************************************
*函数的原型：void Lcd1602_DisplayChar(u8 row,u8 col,int ch)
*函数的功能：显示字符
*函数的参数：
	@u8 row：行
	@u8 col：列
	@int ch：字符
*函数返回值：None
*函数的说明：
*函数编写者：庆
*函数编写日期：2021/2/7
*函数的版本号：V1.0
********************************************************************************/
void Lcd1602_DisplayChar(u8 row,u8 col,int ch)
{
	//显示位置
	int add = 0;
	//判断是那一行
	if(row == 2)
	{
		//第二行的首地址 0x40
		add += 0x40;
	}
	//第一行的首地址 0x80
	add += 0x80 + col - 1;
	Lcd1602_Write_Cmd(add); 
	//显示内容	
	Lcd1602_Write_Data(ch);	
}

/*******************************************************************************
*函数的原型：void Lcd1602_DisplayString(u8 row,u8 col,u8 *str)
*函数的功能：
	@u8 row：行
	@u8 col：列
	@u8 *str：字符串首地址
*函数的参数：None
*函数返回值：None
*函数的说明：
*函数编写者：庆
*函数编写日期：2021/2/7
*函数的版本号：V1.0
********************************************************************************/
void Lcd1602_DisplayString(u8 row,u8 col,u8 *str)
{
	while(*str != '\0')
	{
		Lcd1602_DisplayChar(row,col,*str);
		col += 1;
		str++;
	}
}

/*******************************************************************************
*函数的原型：void Lcd1602_Check_Busy(void)
*函数的功能：检测忙碌状态：
*函数的参数：None
*函数返回值：None
*函数的说明：
	BF=1:不接受外部指令和数据
	BE=0:允许接受外部指令和数据
*函数编写者：庆
*函数编写日期：2021/2/7
*函数的版本号：V1.0
********************************************************************************/
void Lcd1602_Check_Busy(void)
{
	u8 signal;
	LCD_RS = 0;
	LCD_RW = 1;

	do
	{
		LCD_EN = 1;
		signal = LCD_BUSY;
		LCD_EN = 0;
	}while(signal);
}

/*******************************************************************************
*函数的原型：void Lcd1602_Write_Cmd(int cmd)
*函数的功能：写指令
*函数的参数：@int cmd：指令
*函数返回值：None
*函数的说明：
*函数编写者：庆
*函数编写日期：2021/2/4
*函数的版本号：V1.0
********************************************************************************/
void Lcd1602_Write_Cmd(int cmd)
{
	//Lcd1602_Check_Busy();//检测忙碌状态
	LCD_RS = 0;
	LCD_RW = 0; 
	LCD_EN = 0;
	
	cmd=cmd<<8;
	GPIOB->ODR=((GPIOB->ODR & 0x00FF)|(cmd&0xFF00));//PB15-8是数据位，PB0-7的数据不能变
	
//	GPIOB->ODR = ((GPIOB->ODR & 0X00FF) | (cmd <<= 8)); //与上述等价
	
	delay_us(2); 
	LCD_EN = 1;
	delay_us(2);
	LCD_EN = 0;
	
	
	delay_ms(15);//不加，不可以显示
}

/*******************************************************************************
*函数的原型：void Lcd1602_Write_Data(int data)
*函数的功能：写数据
*函数的参数：@int data：数据
*函数返回值：None
*函数的说明：
*函数编写者：庆
*函数编写日期：2021/2/4
*函数的版本号：V1.0
********************************************************************************/
void Lcd1602_Write_Data(int data)
{
	//Lcd1602_Check_Busy();//检测忙碌状态
	LCD_RS = 1; 
	LCD_RW = 0;
	LCD_EN = 0;
	
	data <<= 8;
	GPIOB->ODR = ((GPIOB->ODR & 0X00FF) | (data & 0XFF00));
	
//	GPIOB->ODR = ((GPIOB->ODR & 0X00FF) | (data <<= 8));
	
	delay_us(2);
	LCD_EN = 1;
	delay_us(2);
	LCD_EN = 0;
	delay_ms(15);
}

int LCD_Pow(int X,int Y)
{
	unsigned char i;
	int Result=1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}

void LCD_ShowNum(unsigned char row,unsigned char col,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	
	if(row==1)
	{
		Lcd1602_Write_Cmd(0x80|(col-1));
	}
	else if(row==2)
	{
		Lcd1602_Write_Cmd(0x80|(col-1+0x40));
	}

	for(i=Length;i>0;i--)
	{
		Lcd1602_Write_Data(Number/LCD_Pow(10,i-1)%10+'0');
	}
}

