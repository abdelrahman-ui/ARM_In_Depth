/****************************************************************************************
****************************  - GPS_App			      ***************************
***************************   - Created: 8/26/2021	      ***************************
***************************   - Author: Abdelrahman_Magdy     ***************************
***************************   - Version : _1_	 	      ***************************
***************************   - Note :
					  *-
					  *-
 ****************************************************************************************/ 

/************** INCLUDE LIB **************/
    #include "STD_TYPE.h"
    #include "BIT_MATH.h"
    #include "TM4C123GH6PM.h"
/*****************************************/

/************** INCLUDE MCAL**************/
#include "GPIO_interface.h"
#include "UART_interface.h"
/*****************************************/

/************** INCLUDE HAL **************/
#include "LCD_interface.h"
/*****************************************/

/************** Golbal_Var ***************/

/*****************************************/

/************* Prototype_Fun *************/


/*****************************************/
/* - GPS neo6format , must start by $GPGGA after that i need thr latitude and longitude To know the Location  
   - i Need to take data from GPS (  &   ) , after that put them in LCD .




*/

// RS  --> PB0
// RW  --> PB1 or GND
// EN  --> PB2

// ( D4 to D7 ) with ( PB4 to PB7 )


// D6 and D7 UART2

#include"TM4C123GH6PM.h"
void delayMS(int n);
void delayUS(int n);
extern void HLCD_vInit(void);
extern void HLCD_vDisplayString(const char *Str);
extern void HLCD_vGoToRowColumn(unsigned char row,unsigned char col);
extern void HLCD_vSendCommand(u8 copy_u8Command);
extern void HLCD_vDisplayCharacter(u8 data);
/*************************************************************************

*                                GPS                                     *

*************************************************************************/
char buf[100];
volatile char ind , flag,stringReceived ;
/**/
char gpgga[]={'$' , 'G' , 'P' , 'G', 'G','A'};

unsigned char lastitude[12];
unsigned char logitude[12];


unsigned char GPS_data;



int main(void)
{
	
	uart_init();
	HLCD_vInit();
	HLCD_vGoToRowColumn(0,2);
	HLCD_vDisplayString("GPS Tracking ");
	HLCD_vGoToRowColumn(1,5);
	HLCD_vDisplayString("System ");
	delayMS(5000);
	HLCD_vSendCommand(0x01); // Clear Screen 
	
	while(1){
		
		GPS_data = UArt_Read();
		buf[ind]=GPS_data;
		ind ++ ;
		if(ind < 7)
		{
			// Compare the frist char == $
		if(buf[ind-1] !=gpgga[ind -1])
			ind = 0 ; 
		}
		if(ind >=50)( stringReceived=1;) // need 50 char from $ and rais flag 
			
		if(stringReceived ==1) // if i recive the 50 
		{
			stringReceived = 0 ; // to next location 
			HLCD_vGoToRowColumn(0,0);
			HLCD_vDisplayString("Lat : ");
			for(int i = 15;i<27;i++)
			{
				lastitude[i]=buf[i];
				HLCD_vDisplayCharacter(lastitude[i]);
				if(i == 24)
				{
					HLCD_vDisplayCharacter(''); // space 
					i++;
				}
			}
			HLCD_vGoToRowColumn(0,0);
			HLCD_vDisplayString("Log : ");
			for(int i = 29 ; i <41 ; i++) 
			{
				logitude[i]=buf[i];
				HLCD_vDisplayCharacter(logitude[i]);
				if( i ==38)
				{
				    HLCD_vDisplayCharacter(''); // space 
					i++;
					
				}
			}
			
			delayMS(2000);
			HLCD_vSendCommand(0x01);
				
			
		}
		
		
		
	}
	
	
	
	
	
}



// delay n millisecond ( 16 MHz CPU Clock )
void delayMs(int n )
{
	int i , j ;
	for(volatile i=0 ; i<n ; i++)
	for(volatile j=0 ; j<3180 ; i++)	
	{} // 1ms
	
}


// delay n microsecond ( 16 MHz CPU Clock )
void delayUs(int n )
{
	int i , j ;
	for(volatile i=0 ; i<n ; i++)
	for(volatile j=0 ; j<3 ; i++)	
	{} // 1ms
	
}