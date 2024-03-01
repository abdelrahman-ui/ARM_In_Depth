


#include "uart.h"




void uart_init(uint32_t baudrate,uint32_t f_cpu)
{
  
//1. Enable UART
  SYSCTL->RCGCUART |=(1U<<2);
//2. Enable clock to GPIO module 
  SYSCTL->RCGCGPIO |=(1U<<3);
//3. Set the GPIO AFSEL bits
  GPIOD->AFSEL |=(1U<<6)|(1U<<7);
  GPIOD->DEN   &=~(1U<<6)|(1U<<7); 
//4. Configure the PMCn fields 
  GPIOD->PCTL |=(1U<<24)|(1U<<28);

//UART clock is 16 MHz
// Disable the UART
  UART2->CTL &=~(1U<<0);
//Write the integer portion of the BRD to the UARTIBRD register.
  UART2->IBRD = 104;
//Write the fractional portion of the BRD to the UARTFBRD register.
  UART2->FBRD = 11;
  //Configure the UART clock source
  UART2->CC = 0x00;
  
  UART2->LCRH = 0x60; /* 8-bit, no parity, 1-stop bit, no FIFO */
  UART2->CTL = 0x301; /* enable UART2, TXE, RXE */
  
}

   
 void UART_Write(uint8_t ch)
{
  while((UART2->FR & (1U<<7))==0);  /* wait for transmitter buffer to be free*/
  UART2->DR = ch;
}
uint8_t UART_Read(void)
{
  char data;
  while((UART2->FR & (1U<<6))==0);  /* wait for reciever buffer to have data*/
  data = UART2->DR;
  return data;
}

void uart_write_string(char const * string)
{
  while(*string != '\0')
  {
    UART_Write(*string);
    string++;
  }
}

void uart_write_int(uint32_t number)
{
  uint16_t length = snprintf( NULL, 0, "%d", number );
  char* str = malloc( length + 1 );
  snprintf( str, length + 1, "%d", number );
  free(str);
  uart_write_string(str);
}