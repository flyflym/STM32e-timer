#include "clock.h"
#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "key.h"
#include "lcd1602.h"



extern int b[3];

void timedel(void)
{

     if(b[2]==0)
	 {
	   b[1]--;
	   b[2]=60;
	   if(b[1]==0&&b[0]!=0)
	   {
	   b[0]--;
	   b[1]=60;
	   }
	 }
	 else 
	 {
	   b[2]--;
	 }

}


	
void timeset(void)
{
	u8 KeyNum = 0;
    int j=0; 
	KEY_Scan(&KeyNum);
	if(FLAG == 1) 
	{
	   FLAG = 0;
	   if(KeyNum==5)
		   
	   {	
		   
		   
		int pos=6;
		KeyNum = 0;   
		
		Lcd1602_DisplayString(2,1,"                   ");
        Lcd1602_DisplayString(2,1,"    00:00:00       ");
	while(1)
   {

	        Lcd1602_DisplayChar(2,pos,'_');
			delay_ms (100);
			LCD_ShowNum(2,5,b[0],2);
            LCD_ShowNum(2,8,b[1],2);
            LCD_ShowNum(2,11,b[2],2);		


		KEY_Scan(&KeyNum);
		if(FLAG == 1) 
		{
			 
		   FLAG = 0;
		   if(KeyNum==6)
			   
	    {
			KeyNum = 0;
		if(pos == 12)
			pos = 5;
		if(pos == 6)
			pos = 8;
			if(pos == 6)
			pos = 8;
			if(pos == 9)
			pos = 11;
		if(pos == 5||pos == 11||pos == 8)
			pos++;

	    }
	

		
		if(KeyNum==1)
		{
			if(pos==6||pos==9||pos==12)
			{
				j=pos/3-2;
				b[j]++;
			}
			
			if(pos==5)
				b[0]+=10;
			if(pos==8)
				b[1]+=10;
			if(pos==11)
				b[2]+=10;
		}
		
			if(KeyNum==2)
		{
			if(pos==6||pos==9||pos==12)
			{
				j=pos/3-2;
				b[j]--;
			}
			
			if(pos==5)
				b[0]-=10;
			if(pos==8)
				b[1]-=10;
			if(pos==11)
				b[2]-=10;
		}
		

		if(KeyNum==8){break;}

					 }
	
	}
	}
	}

}


