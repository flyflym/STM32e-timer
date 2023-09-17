#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "ds18b20.h"
#include "lcd1602.h"
#include "rtc.h"
#include "key.h"
#include "clock.h"

u8 KeyNum = 0;

int b [3] = {0,0,10};
#define BEEP_PORT 			GPIOB   
#define BEEP_PIN 			GPIO_Pin_5
#define BEEP_PORT_RCC		RCC_APB2Periph_GPIOB
#define beep PBout(5)
int main()
{
	float temper;
    int i=0;
	
	GPIO_InitTypeDef GPIO_InitStructure;	
  RCC_APB2PeriphClockCmd(BEEP_PORT_RCC,ENABLE);   
	GPIO_InitStructure.GPIO_Pin=BEEP_PIN;		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;		  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  
	GPIO_Init(BEEP_PORT,&GPIO_InitStructure); 
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	LED_Init();
	Lcd1602_Init();
	USART1_Init(9600);
	
	while(DS18B20_Init())
	{

		delay_ms(500);
	}

	RTC_Init();
	KEY_4x4_Init();
	
	Lcd1602_DisplayString(1,1,"1.time");
	Lcd1602_DisplayString(1,10,"2.clock");
	Lcd1602_DisplayString(2,1,"3.temperature");

	
	while (1)
	{
		KEY_Scan(&KeyNum);
		
		if(FLAG == 1) 
		{	
			FLAG=0;
			
			
			
			if (KeyNum == 1)
		{
			Lcd1602_DisplayString(1,1,"                   ");
			Lcd1602_DisplayString(2,1,"                   ");
			
		    while(1)
				{
					KeyNum = 0 ;
				
	                RTC_Write();
					
					KEY_Scan(&KeyNum);
				   if(FLAG == 1) 
					 {
						 FLAG = 0;
						 if (KeyNum == 4)
						{
						
					  Lcd1602_DisplayString(1,1,"                   ");
					  Lcd1602_DisplayString(2,1,"                   ");		
	                  Lcd1602_DisplayString(1,1,"1.time");
	                  Lcd1602_DisplayString(1,10,"2.clock");
	                  Lcd1602_DisplayString(2,1,"3.temperature");
							break;
							
						}		
					 }
				   			
	             }   
		
		}
		
		//2
		if (KeyNum == 2)
		{
			Lcd1602_DisplayString(1,1,"                   ");
			Lcd1602_DisplayString(2,1,"                   ");
			
		    Lcd1602_DisplayString(1,1,"1.timer");		
            Lcd1602_DisplayString(2,1,"2.alarm");	
			

			while(1){
			
			KeyNum = 0 ;


			KEY_Scan(&KeyNum);	

			if(FLAG == 1) 
		{
			FLAG = 0;	
				
            if(KeyNum == 1)
				
			{
				KeyNum = 0;
				Lcd1602_DisplayString(2,1,"                   ");
			while(!(b[2] == 0 && b[1] == 0 && b[0] == 0))
			{
				
				
				
			LCD_ShowNum(2,5,b[0],2);
            LCD_ShowNum(2,8,b[1],2);
            LCD_ShowNum(2,11,b[2],2);	
            Lcd1602_DisplayChar(2,7,':');
	        Lcd1602_DisplayChar(2,10,':');	
				
				
						if(FLAG == 1) 
					 {
						 FLAG = 0;
						 if (KeyNum == 4)
						{
						KeyNum = 0;
					  Lcd1602_DisplayString(1,1,"                   ");
					  Lcd1602_DisplayString(2,1,"                   ");		
	                  Lcd1602_DisplayString(1,1,"1.time");
	                  Lcd1602_DisplayString(1,10,"2.clock");
	                  Lcd1602_DisplayString(2,1,"3.temperature");
						break;
							
						
						}
					 }
			timeset();
				
		    timedel(); 

				
			
		    
		    delay_ms(1000);
			}
			
		    LCD_ShowNum(2,5,b[0],2);
            LCD_ShowNum(2,8,b[1],2);
            LCD_ShowNum(2,11,b[2],2);
			Lcd1602_DisplayChar(2,7,':');
	        Lcd1602_DisplayChar(2,10,':');	
		     while(1)
			{
						
						 KEY_Scan(&KeyNum);
						if(FLAG == 1) 
					 {
						 FLAG = 0;
						 if(KeyNum == 4)
						{
					  KeyNum = 0;
					  b[2] = 5 ;
											
						break;
						}
					 }
						 
						 i++;
						 if(i%10==0)
						 {
						 	beep=!beep;
						 }
						 if(i%20000==0)
						 {
						 	led1=!led1;	
						 }
						 delay_us(10);  
			
					 }
			
			
			
			
			
			
			
			Lcd1602_DisplayString(1,1,"                   ");
			Lcd1602_DisplayString(2,1,"                   ");
			
		    Lcd1602_DisplayString(1,1,"1.timer");		
            Lcd1602_DisplayString(2,1,"2.alarm");
		}
					
						
       if(KeyNum == 2)
	   {
		   
		   
		    KeyNum = 0;
		   
	        Lcd1602_DisplayString(1,1,"                ");
	        Lcd1602_DisplayString(2,1,"                ");	
	        
			    RTC_W();
			Lcd1602_DisplayString(1,1,"Now:");
			Lcd1602_DisplayString(2,1,"End:");
			 Lcd1602_DisplayChar(2,7,':');
	        Lcd1602_DisplayChar(2,10,':');	
		   
			LCD_ShowNum(2,5,b[0],2);
            LCD_ShowNum(2,8,b[1],2);
            LCD_ShowNum(2,11,b[2],2);	
		   
	        while(!(b[0]==calendar.hour&&b[1]==calendar.min&&b[2]==calendar.sec))
	        {
				

				
				
				
				
			LCD_ShowNum(2,5,b[0],2);
            LCD_ShowNum(2,8,b[1],2);
            LCD_ShowNum(2,11,b[2],2);	
            Lcd1602_DisplayChar(2,7,':');
	        Lcd1602_DisplayChar(2,10,':');	
				
				
				
							RTC_W();	
				            KEY_Scan(&KeyNum);
						if(FLAG == 1) 
					 {
						 FLAG = 0;
						 if (KeyNum == 4)
						{
						KeyNum = 0;
					  Lcd1602_DisplayString(1,1,"                   ");
					  Lcd1602_DisplayString(2,1,"                   ");		
		              Lcd1602_DisplayString(1,1,"1.timer");		
                      Lcd1602_DisplayString(2,1,"2.alarm");
						break;
							
						
						}
					 }
					
				
				
				
			timeset();
	


					
					
		    }
					while(b[0]==calendar.hour&&b[1]==calendar.min&&b[2]==calendar.sec)
					{
						
							Lcd1602_DisplayString(1,1,"                   ");
			                Lcd1602_DisplayString(1,3,"Time is up!!");
						 KEY_Scan(&KeyNum);
						 if(KeyNum == 4)
					    {
							KeyNum = 0;
						b[2] = 5 ;
						Lcd1602_DisplayString(1,1,"                   ");
					    Lcd1602_DisplayString(2,1,"                   ");		
		                Lcd1602_DisplayString(1,1,"1.timer");		
                        Lcd1602_DisplayString(2,1,"2.alarm");
						break;
						}
						 i++;
						 if(i%10==0)
						 {
						 	beep=!beep;
						 }
						 if(i%20000==0)
						 {
						 	led1=!led1;	
						 }
						 delay_ms(100);  
					}
		   
		   }
		
		   if (KeyNum == 4)
						{
						KeyNum = 0;
					  Lcd1602_DisplayString(1,1,"                   ");
					  Lcd1602_DisplayString(2,1,"                   ");		
	                  Lcd1602_DisplayString(1,1,"1.time");
	                  Lcd1602_DisplayString(1,10,"2.clock");
	                  Lcd1602_DisplayString(2,1,"3.temperature");
						break;
							
						
						}
		   
		   
		   
			
		}
	}
}
		i=0;

	
		if (KeyNum == 3)
		{
					KeyNum = 0 ;
	        Lcd1602_DisplayString(1,1,"                ");
	        Lcd1602_DisplayString(2,1,"                ");	
	        Lcd1602_DisplayString(1,1,"Temperature:");
	        while(1)
	        {

		        temper=DS18B20_GetTemperture();
				Lcd1602_DisplayString(1,1,"Temperature:");
                LCD_ShowNum(2,2,temper,3);	
		        Lcd1602_DisplayChar(2,5,'.');		
		        LCD_ShowNum(2,6,(unsigned long)(temper*10000)%10000,3);
						Lcd1602_DisplayString(2,9,"'C");

						
				KEY_Scan(&KeyNum);
						if(FLAG == 1) 
					 {
						 FLAG = 0;
						 if (KeyNum == 4)
						{
						
					  Lcd1602_DisplayString(1,1,"                   ");
					  Lcd1602_DisplayString(2,1,"                   ");		
	                  Lcd1602_DisplayString(1,1,"1.time");
	                  Lcd1602_DisplayString(1,10,"2.clock");
	                  Lcd1602_DisplayString(2,1,"3.temperature");
						break;
							
						
						}
					 }
				
		    }
		}	

		}

	}

}


