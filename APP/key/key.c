#include "stm32f10x.h"
#include "SysTick.h"
#include "key.h"

u8 FLAG = 0;

void KEY_4x4_Init(void) //IO???
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = KEY_HANG;  //?  0123
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(KEY_PROT, &GPIO_InitStructure);
	GPIO_SetBits(KEY_PROT,KEY_HANG);
	
	//init GPIOA	  ????
	GPIO_InitStructure.GPIO_Pin  = KEY1|KEY2|KEY3|KEY4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(KEY_PROT, &GPIO_InitStructure);
	GPIO_SetBits(KEY_PROT,KEY1|KEY2|KEY3|KEY4);
		 

}


void KEY_Scan(u8 *key) 
{	 
	
	GPIO_Write(KEY_PROT,0x00fe);//???
	if((KEY1_Input==RESET)||(KEY2_Input==RESET)||(KEY3_Input==RESET)||(KEY4_Input==RESET))   
	{
		delay_ms(10);//??? 
		
		if(KEY1_Input==RESET)
		{
				FLAG = 1;
				*key = 1;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY1));
		}
		else if(KEY2_Input==RESET)
		{
	 	 
	     	FLAG = 1;
				*key = 2;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY2));
		}
		else if(KEY3_Input==RESET)
		{
	 
	    	FLAG = 1;
				*key = 3;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY3));
		}
		else if(KEY4_Input==RESET)
		{
	 
	    	FLAG = 1;
				*key = 4;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY4));
		}else 
					{
						FLAG = 0;
						GPIO_Write(KEY_PROT,0x00ff);
					}
		}
	GPIO_Write(KEY_PROT,0x00fd);//???
	if((KEY1_Input==RESET)||(KEY2_Input==RESET)||(KEY3_Input==RESET)||(KEY4_Input==RESET))
	{
		delay_ms(10);//??? 
		
		if(KEY1_Input==RESET)
		{
				FLAG = 1;
				*key = 5;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY1));
		}
		else if(KEY2_Input==RESET)
		{
	 	 
	     	FLAG = 1;
				*key = 6;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY2));
		}
		else if(KEY3_Input==RESET)
		{
	 
	    	FLAG = 1;
				*key = 7;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY3));
		}
		else if(KEY4_Input==RESET)
		{
	 
	    	FLAG = 1;
				*key = 8;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY4));
		}else 
					{
						FLAG = 0;
						GPIO_Write(KEY_PROT,0x00ff);
					}
		}
	GPIO_Write(KEY_PROT,0x00fb);//???
	if((KEY1_Input==RESET)||(KEY2_Input==RESET)||(KEY3_Input==RESET)||(KEY4_Input==RESET))
	{
		delay_ms(10);//??? 
		
		if(KEY1_Input==RESET)
		{
				FLAG = 1;
				*key = 9;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY1));
		}
		else if(KEY2_Input==RESET)
		{
	 	 
	     	FLAG = 1;
				*key = 10;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY2));
		}
		else if(KEY3_Input==RESET)
		{
	 
	    	FLAG = 1;
				*key = 11;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY3));
		}
		else if(KEY4_Input==RESET)
		{
	 
	    	FLAG = 1;
				*key = 12;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY4));
		}else 
					{
						FLAG = 0;
						GPIO_Write(KEY_PROT,0x00ff);
					}
		}
		GPIO_Write(KEY_PROT,0x00f7);//???
	if((KEY1_Input==RESET)||(KEY2_Input==RESET)||(KEY3_Input==RESET)||(KEY4_Input==RESET))
	{
		delay_ms(10);//??? 
		
		if(KEY1_Input==RESET)
		{
				FLAG = 1;
				*key = 13;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY1));
		}
		else if(KEY2_Input==RESET)
		{
	 	 
	     	FLAG = 1;
				*key = 14;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY2));
		}
		else if(KEY3_Input==RESET)
		{
	 
	    	FLAG = 1;
				*key = 15;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY3));
		}
		else if(KEY4_Input==RESET)
		{
	 
	    	FLAG = 1;
				*key = 16;
				while(!GPIO_ReadInputDataBit(KEY_PROT,KEY4));
		}else 
					{
						FLAG = 0;
						GPIO_Write(KEY_PROT,0x00ff);
					}
		}
	
}
