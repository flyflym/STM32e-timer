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
*������ԭ�ͣ�void Lcd1602_Init(void)
*�����Ĺ��ܣ�LCD1602��ʼ��
*�����Ĳ�����None
*��������ֵ��None
*������˵����
*������д�ߣ���
*������д���ڣ�2021/2/4
*�����İ汾�ţ�V1.0
********************************************************************************/
void Lcd1602_Init(void)
{
	Lcd1602_Pin_Init();
	
	delay_ms(15);
	
	Lcd1602_Write_Cmd(0X38);
	Lcd1602_Write_Cmd(0X0C);//����ʾ����ʾ���
	Lcd1602_Write_Cmd(0X06);//дһ��ָ���1
	Lcd1602_Write_Cmd(0X01);//����
	Lcd1602_Write_Cmd(0X80);//��������ָ�����	
	

}

/*******************************************************************************
*������ԭ�ͣ�void Lcd1602_DisplayChar(u8 row,u8 col,int ch)
*�����Ĺ��ܣ���ʾ�ַ�
*�����Ĳ�����
	@u8 row����
	@u8 col����
	@int ch���ַ�
*��������ֵ��None
*������˵����
*������д�ߣ���
*������д���ڣ�2021/2/7
*�����İ汾�ţ�V1.0
********************************************************************************/
void Lcd1602_DisplayChar(u8 row,u8 col,int ch)
{
	//��ʾλ��
	int add = 0;
	//�ж�����һ��
	if(row == 2)
	{
		//�ڶ��е��׵�ַ 0x40
		add += 0x40;
	}
	//��һ�е��׵�ַ 0x80
	add += 0x80 + col - 1;
	Lcd1602_Write_Cmd(add); 
	//��ʾ����	
	Lcd1602_Write_Data(ch);	
}

/*******************************************************************************
*������ԭ�ͣ�void Lcd1602_DisplayString(u8 row,u8 col,u8 *str)
*�����Ĺ��ܣ�
	@u8 row����
	@u8 col����
	@u8 *str���ַ����׵�ַ
*�����Ĳ�����None
*��������ֵ��None
*������˵����
*������д�ߣ���
*������д���ڣ�2021/2/7
*�����İ汾�ţ�V1.0
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
*������ԭ�ͣ�void Lcd1602_Check_Busy(void)
*�����Ĺ��ܣ����æµ״̬��
*�����Ĳ�����None
*��������ֵ��None
*������˵����
	BF=1:�������ⲿָ�������
	BE=0:��������ⲿָ�������
*������д�ߣ���
*������д���ڣ�2021/2/7
*�����İ汾�ţ�V1.0
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
*������ԭ�ͣ�void Lcd1602_Write_Cmd(int cmd)
*�����Ĺ��ܣ�дָ��
*�����Ĳ�����@int cmd��ָ��
*��������ֵ��None
*������˵����
*������д�ߣ���
*������д���ڣ�2021/2/4
*�����İ汾�ţ�V1.0
********************************************************************************/
void Lcd1602_Write_Cmd(int cmd)
{
	//Lcd1602_Check_Busy();//���æµ״̬
	LCD_RS = 0;
	LCD_RW = 0; 
	LCD_EN = 0;
	
	cmd=cmd<<8;
	GPIOB->ODR=((GPIOB->ODR & 0x00FF)|(cmd&0xFF00));//PB15-8������λ��PB0-7�����ݲ��ܱ�
	
//	GPIOB->ODR = ((GPIOB->ODR & 0X00FF) | (cmd <<= 8)); //�������ȼ�
	
	delay_us(2); 
	LCD_EN = 1;
	delay_us(2);
	LCD_EN = 0;
	
	
	delay_ms(15);//���ӣ���������ʾ
}

/*******************************************************************************
*������ԭ�ͣ�void Lcd1602_Write_Data(int data)
*�����Ĺ��ܣ�д����
*�����Ĳ�����@int data������
*��������ֵ��None
*������˵����
*������д�ߣ���
*������д���ڣ�2021/2/4
*�����İ汾�ţ�V1.0
********************************************************************************/
void Lcd1602_Write_Data(int data)
{
	//Lcd1602_Check_Busy();//���æµ״̬
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

